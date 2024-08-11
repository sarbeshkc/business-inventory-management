#include "salesmodel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

SalesModel::SalesModel(DatabaseManager *dbManager, QObject *parent)
    : QAbstractListModel(parent), m_dbManager(dbManager), m_userId(-1) {
  qDebug() << "SalesModel constructor called";
}

int SalesModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;
  return m_sales.size();
}

QVariant SalesModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_sales.size())
    return QVariant();

  const SaleItem &sale = m_sales.at(index.row());

  switch (role) {
  case IdRole:
    return sale.id;
  case ItemIdRole:
    return sale.itemId;
  case ItemNameRole:
    return sale.itemName;
  case QuantityRole:
    return sale.quantity;
  case PriceRole:
    return sale.price;
  case TotalPriceRole:
    return sale.totalPrice;
  case SaleDateRole:
    return sale.saleDate;
  case CategoryRole:
    return sale.category;
  case SupplierNameRole:
    return sale.supplierName;
  case SupplierAddressRole:
    return sale.supplierAddress;
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> SalesModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[IdRole] = "id";
  roles[ItemIdRole] = "itemId";
  roles[ItemNameRole] = "itemName";
  roles[QuantityRole] = "quantity";
  roles[PriceRole] = "price";
  roles[TotalPriceRole] = "totalPrice";
  roles[SaleDateRole] = "saleDate";
  roles[CategoryRole] = "category";
  roles[SupplierNameRole] = "supplierName";
  roles[SupplierAddressRole] = "supplierAddress";
  return roles;
}

void SalesModel::setUserId(int userId) {
  qDebug() << "SalesModel::setUserId called with userId:" << userId;
  if (m_userId != userId) {
    m_userId = userId;
    refresh();
  }
}

bool SalesModel::addSale(int itemId, int quantity, double price,
                         const QString &category, const QString &supplierName,
                         const QString &supplierAddress) {
  qDebug() << "SalesModel::addSale called";
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to add sale.");
    return false;
  }

  QSqlDatabase db = m_dbManager->database();
  db.transaction();

  QSqlQuery query(db);

  // Check if a sale for this item and supplier already exists
  query.prepare("SELECT id, quantity, total_price FROM Sales "
                "WHERE user_id = :userId AND item_id = :itemId AND "
                "supplier_name = :supplierName");
  query.bindValue(":userId", m_userId);
  query.bindValue(":itemId", itemId);
  query.bindValue(":supplierName", supplierName);

  if (!query.exec()) {
    db.rollback();
    emit errorOccurred(
        tr("Failed to check existing sales: %1").arg(query.lastError().text()));
    return false;
  }

  if (query.next()) {
    // Update existing sale
    int existingId = query.value("id").toInt();
    int existingQuantity = query.value("quantity").toInt();
    double existingTotalPrice = query.value("total_price").toDouble();

    query.prepare("UPDATE Sales SET quantity = :quantity, price = :price, "
                  "total_price = :totalPrice, "
                  "sale_date = :saleDate, category = :category, "
                  "supplier_address = :supplierAddress "
                  "WHERE id = :id");
    query.bindValue(":quantity", existingQuantity + quantity);
    query.bindValue(":price", price);
    query.bindValue(":totalPrice", existingTotalPrice + (price * quantity));
    query.bindValue(":saleDate", QDateTime::currentDateTime());
    query.bindValue(":category", category);
    query.bindValue(":supplierAddress", supplierAddress);
    query.bindValue(":id", existingId);
  } else {
    // Insert new sale
    query.prepare(
        "INSERT INTO Sales (user_id, item_id, quantity, price, total_price, "
        "sale_date, category, supplier_name, supplier_address) "
        "VALUES (:userId, :itemId, :quantity, :price, :totalPrice, :saleDate, "
        ":category, :supplierName, :supplierAddress)");
    query.bindValue(":userId", m_userId);
    query.bindValue(":itemId", itemId);
    query.bindValue(":quantity", quantity);
    query.bindValue(":price", price);
    query.bindValue(":totalPrice", price * quantity);
    query.bindValue(":saleDate", QDateTime::currentDateTime());
    query.bindValue(":category", category);
    query.bindValue(":supplierName", supplierName);
    query.bindValue(":supplierAddress", supplierAddress);
  }

  if (!query.exec()) {
    db.rollback();
    emit errorOccurred(
        tr("Failed to add/update sale: %1").arg(query.lastError().text()));
    return false;
  }

  // Update inventory
  query.prepare("UPDATE Inventory SET quantity = quantity - :soldQuantity "
                "WHERE id = :itemId AND user_id = :userId");
  query.bindValue(":soldQuantity", quantity);
  query.bindValue(":itemId", itemId);
  query.bindValue(":userId", m_userId);

  if (!query.exec()) {
    db.rollback();
    emit errorOccurred(
        tr("Failed to update inventory: %1").arg(query.lastError().text()));
    return false;
  }

  db.commit();
  refresh();
  return true;
}

void SalesModel::searchSales(const QString &searchText) {
  qDebug() << "SalesModel::searchSales called with searchText:" << searchText;
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to search sales.");
    return;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT s.id, s.item_id, i.name AS item_name, s.quantity, "
                "s.price, s.total_price, s.sale_date, "
                "s.category, s.supplier_name, s.supplier_address "
                "FROM Sales s "
                "JOIN Inventory i ON s.item_id = i.id "
                "WHERE s.user_id = :userId AND (i.name LIKE :searchText OR "
                "s.category LIKE :searchText "
                "OR s.supplier_name LIKE :searchText OR s.supplier_address "
                "LIKE :searchText) "
                "ORDER BY s.sale_date DESC");
  query.bindValue(":userId", m_userId);
  query.bindValue(":searchText", "%" + searchText + "%");

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to search sales: %1").arg(query.lastError().text()));
    return;
  }

  beginResetModel();
  m_sales.clear();
  while (query.next()) {
    SaleItem sale;
    sale.id = query.value("id").toInt();
    sale.itemId = query.value("item_id").toInt();
    sale.itemName = query.value("item_name").toString();
    sale.quantity = query.value("quantity").toInt();
    sale.price = query.value("price").toDouble();
    sale.totalPrice = query.value("total_price").toDouble();
    sale.saleDate = query.value("sale_date").toDateTime();
    sale.category = query.value("category").toString();
    sale.supplierName = query.value("supplier_name").toString();
    sale.supplierAddress = query.value("supplier_address").toString();
    m_sales.append(sale);
  }
  endResetModel();
  emit totalSalesChanged();
  emit revenueThisMonthChanged();
  emit totalRevenueChanged();
}

void SalesModel::sortSales(const QString &column, Qt::SortOrder order) {
  qDebug() << "SalesModel::sortSales called with column:" << column
           << "and order:" << order;
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to sort sales.");
    return;
  }

  QString orderByClause;
  if (column == "Date") {
    orderByClause = "s.sale_date";
  } else if (column == "Item") {
    orderByClause = "i.name";
  } else if (column == "Quantity") {
    orderByClause = "s.quantity";
  } else if (column == "Total Price") {
    orderByClause = "s.total_price";
  } else if (column == "Category") {
    orderByClause = "s.category";
  } else if (column == "Supplier") {
    orderByClause = "s.supplier_name";
  } else {
    emit errorOccurred(tr("Invalid sort column"));
    return;
  }

  orderByClause += (order == Qt::AscendingOrder) ? " ASC" : " DESC";

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT s.id, s.item_id, i.name AS item_name, s.quantity, "
                "s.price, s.total_price, s.sale_date, "
                "s.category, s.supplier_name, s.supplier_address "
                "FROM Sales s "
                "JOIN Inventory i ON s.item_id = i.id "
                "WHERE s.user_id = :userId "
                "ORDER BY " +
                orderByClause);
  query.bindValue(":userId", m_userId);

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to sort sales: %1").arg(query.lastError().text()));
    return;
  }

  beginResetModel();
  m_sales.clear();
  while (query.next()) {
    SaleItem sale;
    sale.id = query.value("id").toInt();
    sale.itemId = query.value("item_id").toInt();
    sale.itemName = query.value("item_name").toString();
    sale.quantity = query.value("quantity").toInt();
    sale.price = query.value("price").toDouble();
    sale.totalPrice = query.value("total_price").toDouble();
    sale.saleDate = query.value("sale_date").toDateTime();
    sale.category = query.value("category").toString();
    sale.supplierName = query.value("supplier_name").toString();
    sale.supplierAddress = query.value("supplier_address").toString();
    m_sales.append(sale);
  }
  endResetModel();
  emit totalSalesChanged();
  emit revenueThisMonthChanged();
  emit totalRevenueChanged();
}

QVariantList SalesModel::getSalesDistribution() const {
  QVariantList result;
  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT i.name, SUM(s.total_price) as total_revenue "
                "FROM Sales s "
                "JOIN Inventory i ON s.item_id = i.id "
                "WHERE s.user_id = :userId "
                "GROUP BY s.item_id "
                "ORDER BY total_revenue DESC "
                "LIMIT 5");
  query.bindValue(":userId", m_userId);
  if (!query.exec()) {
    qDebug() << "Error getting sales distribution:" << query.lastError().text();
  } else {
    while (query.next()) {
      QVariantMap item;
      item["name"] = query.value("name").toString();
      item["revenue"] = query.value("total_revenue").toDouble();
      result.append(item);
    }
  }
  return result;
}

QVariantList SalesModel::getMonthlySales() const {
  QVariantList result;
  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT strftime('%Y-%m', sale_date) as month, "
                "SUM(total_price) as monthly_revenue "
                "FROM Sales "
                "WHERE user_id = :userId "
                "GROUP BY month "
                "ORDER BY month DESC "
                "LIMIT 12");
  query.bindValue(":userId", m_userId);
  if (!query.exec()) {
    qDebug() << "Error getting monthly sales:" << query.lastError().text();
  } else {
    while (query.next()) {
      QVariantMap item;
      item["month"] = query.value("month").toString();
      item["revenue"] = query.value("monthly_revenue").toDouble();
      result.append(item);
    }
  }
  return result;
}

int SalesModel::totalSales() const { return m_sales.size(); }

double SalesModel::revenueThisMonth() const {
  QDateTime firstDayOfMonth = QDateTime::currentDateTime().addDays(
      -QDateTime::currentDateTime().date().day() + 1);
  double revenue = 0.0;
  for (const auto &sale : m_sales) {
    if (sale.saleDate >= firstDayOfMonth) {
      revenue += sale.totalPrice;
    }
  }
  return revenue;
}

double SalesModel::totalRevenue() const {
  double revenue = 0.0;
  for (const auto &sale : m_sales) {
    revenue += sale.totalPrice;
  }
  return revenue;
}

void SalesModel::refresh() {
  qDebug() << "SalesModel::refresh called for user ID:" << m_userId;
  if (m_userId == -1) {
    qWarning() << "User not set. Unable to refresh sales.";
    return;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT s.id, s.item_id, i.name AS item_name, s.quantity, "
                "s.price, s.total_price, s.sale_date, "
                "s.category, s.supplier_name, s.supplier_address "
                "FROM Sales s "
                "JOIN Inventory i ON s.item_id = i.id "
                "WHERE s.user_id = :userId "
                "ORDER BY s.sale_date DESC");
  query.bindValue(":userId", m_userId);

  if (!query.exec()) {
    qWarning() << "Failed to fetch sales data:" << query.lastError().text();
    emit errorOccurred(
        tr("Failed to fetch sales data: %1").arg(query.lastError().text()));
    return;
  }

  beginResetModel();
  m_sales.clear();
  while (query.next()) {
    SaleItem sale;
    sale.id = query.value("id").toInt();
    sale.itemId = query.value("item_id").toInt();
    sale.itemName = query.value("item_name").toString();
    sale.quantity = query.value("quantity").toInt();
    sale.price = query.value("price").toDouble();
    sale.totalPrice = query.value("total_price").toDouble();
    sale.saleDate = query.value("sale_date").toDateTime();
    sale.category = query.value("category").toString();
    sale.supplierName = query.value("supplier_name").toString();
    sale.supplierAddress = query.value("supplier_address").toString();
    m_sales.append(sale);
  }
  endResetModel();

  qDebug() << "SalesModel::refresh completed. Total sales loaded:"
           << m_sales.size();

  emit totalSalesChanged();
  emit revenueThisMonthChanged();
  emit totalRevenueChanged();
}
void SalesModel::insertTestData() {
  qDebug() << "SalesModel::insertTestData called";
  if (m_userId == -1) {
    qWarning() << "User not set. Unable to insert test data.";
    return;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare(
      "INSERT INTO Sales (user_id, item_id, quantity, price, total_price, "
      "sale_date, category, supplier_name, supplier_address) "
      "VALUES (:userId, :itemId, :quantity, :price, :totalPrice, :saleDate, "
      ":category, :supplierName, :supplierAddress)");

  // Insert a few test records
  for (int i = 1; i <= 5; ++i) {
    query.bindValue(":userId", m_userId);
    query.bindValue(":itemId", i);
    query.bindValue(":quantity", i * 10);
    query.bindValue(":price", 10.0 + i);
    query.bindValue(":totalPrice", (10.0 + i) * (i * 10));
    query.bindValue(":saleDate", QDateTime::currentDateTime().addDays(-i));
    query.bindValue(":category", QString("Category %1").arg(i));
    query.bindValue(":supplierName", QString("Supplier %1").arg(i));
    query.bindValue(":supplierAddress", QString("Address %1").arg(i));

    if (!query.exec()) {
      qWarning() << "Failed to insert test data:" << query.lastError().text();
    }
  }

  refresh();
  qDebug() << "SalesModel::insertTestData completed";
}
