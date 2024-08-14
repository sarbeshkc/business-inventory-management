#include "salesmodel.h"
#include <QDateTime>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

SalesModel::SalesModel(DatabaseManager *dbManager, QObject *parent)
    : QAbstractListModel(parent), m_dbManager(dbManager), m_userId(-1),
      m_revenueThisMonth(0.0), m_totalRevenue(0.0), m_maxMonthlySales(0.0) {}

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
  if (m_userId != userId) {
    m_userId = userId;
    refresh();
  }
}

bool SalesModel::addSale(int itemId, int quantity, double price,
                         const QString &category, const QString &supplierName,
                         const QString &supplierAddress) {
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to add sale.");
    return false;
  }

  QSqlDatabase db = m_dbManager->database();
  db.transaction();

  QSqlQuery query(db);
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

  if (!query.exec()) {
    db.rollback();
    emit errorOccurred(
        tr("Failed to add sale: %1").arg(query.lastError().text()));
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
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to search sales.");
    return;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT s.id, s.item_id, i.name AS item_name, s.quantity, "
                "s.price, s.total_price, "
                "s.sale_date, s.category, s.supplier_name, s.supplier_address "
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
                "s.price, s.total_price, "
                "s.sale_date, s.category, s.supplier_name, s.supplier_address "
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
}

void SalesModel::refresh() {
  if (m_userId == -1) {
    qWarning() << "User not set. Unable to refresh sales.";
    return;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT s.id, s.item_id, i.name AS item_name, s.quantity, "
                "s.price, s.total_price, "
                "s.sale_date, s.category, s.supplier_name, s.supplier_address "
                "FROM Sales s "
                "JOIN Inventory i ON s.item_id = i.id "
                "WHERE s.user_id = :userId "
                "ORDER BY s.sale_date DESC");
  query.bindValue(":userId", m_userId);

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to fetch sales data: %1").arg(query.lastError().text()));
    return;
  }

  beginResetModel();
  m_sales.clear();
  m_revenueThisMonth = 0.0;
  m_totalRevenue = 0.0;
  QDateTime firstDayOfMonth = QDateTime::currentDateTime().addDays(
      -QDateTime::currentDateTime().date().day() + 1);
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

    m_totalRevenue += sale.totalPrice;
    if (sale.saleDate >= firstDayOfMonth) {
      m_revenueThisMonth += sale.totalPrice;
    }
  }
  endResetModel();
  emit totalSalesChanged();
  emit revenueThisMonthChanged();
  emit totalRevenueChanged();
}

void SalesModel::refreshAnalytics() {
  if (m_userId == -1) {
    qWarning() << "User not set. Unable to refresh analytics.";
    return;
  }

  // Fetch monthly sales data
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
    emit errorOccurred(tr("Failed to fetch monthly sales data: %1")
                           .arg(query.lastError().text()));
    return;
  }

  m_monthlySalesData.clear();
  m_maxMonthlySales = 0.0;
  while (query.next()) {
    QVariantMap monthData;
    monthData["month"] = query.value("month").toString();
    double monthlyRevenue = query.value("monthly_revenue").toDouble();
    monthData["revenue"] = monthlyRevenue;
    m_monthlySalesData.append(monthData);

    if (monthlyRevenue > m_maxMonthlySales) {
      m_maxMonthlySales = monthlyRevenue;
    }
  }
  emit monthlySalesDataChanged();
  emit maxMonthlySalesChanged();

  // Fetch top products
  query.prepare("SELECT i.name, SUM(s.total_price) as total_revenue "
                "FROM Sales s "
                "JOIN Inventory i ON s.item_id = i.id "
                "WHERE s.user_id = :userId "
                "GROUP BY s.item_id "
                "ORDER BY total_revenue DESC "
                "LIMIT 5");
  query.bindValue(":userId", m_userId);

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to fetch top products: %1").arg(query.lastError().text()));
    return;
  }

  m_topProducts.clear();
  while (query.next()) {
    QVariantMap product;
    product["name"] = query.value("name").toString();
    product["revenue"] = query.value("total_revenue").toDouble();
    m_topProducts.append(product);
  }
  emit topProductsChanged();
}

int SalesModel::totalSales() const { return m_sales.size(); }

double SalesModel::revenueThisMonth() const { return m_revenueThisMonth; }

double SalesModel::totalRevenue() const { return m_totalRevenue; }

double SalesModel::maxMonthlySales() const { return m_maxMonthlySales; }

QVariantList SalesModel::monthlySalesData() const { return m_monthlySalesData; }

QVariantList SalesModel::topProducts() const { return m_topProducts; }
