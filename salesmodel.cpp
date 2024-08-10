#include "salesmodel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

SalesModel::SalesModel(DatabaseManager *dbManager, QObject *parent)
    : QAbstractListModel(parent), m_dbManager(dbManager), m_userId(-1) {}

SalesModel::~SalesModel() {}

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
  case TotalPriceRole:
    return sale.totalPrice;
  case SaleDateRole:
    return sale.saleDate;
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
  roles[TotalPriceRole] = "totalPrice";
  roles[SaleDateRole] = "saleDate";
  return roles;
}

void SalesModel::setUserId(int userId) {
  if (m_userId != userId) {
    m_userId = userId;
    refresh();
  }
}

bool SalesModel::addSale(int itemId, int quantity, double totalPrice) {
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to add sale.");
    return false;
  }

  QSqlDatabase db = m_dbManager->database();
  db.transaction();

  QSqlQuery query(db);
  query.prepare(
      "INSERT INTO Sales (user_id, item_id, quantity, total_price, sale_date) "
      "VALUES (:userId, :itemId, :quantity, :totalPrice, :saleDate)");
  query.bindValue(":userId", m_userId);
  query.bindValue(":itemId", itemId);
  query.bindValue(":quantity", quantity);
  query.bindValue(":totalPrice", totalPrice);
  query.bindValue(":saleDate", QDateTime::currentDateTime());

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
                "s.total_price, s.sale_date "
                "FROM Sales s "
                "JOIN Inventory i ON s.item_id = i.id "
                "WHERE s.user_id = :userId AND i.name LIKE :searchText "
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
    sale.totalPrice = query.value("total_price").toDouble();
    sale.saleDate = query.value("sale_date").toDateTime();
    m_sales.append(sale);
  }
  endResetModel();
  emit dataChanged(index(0), index(m_sales.size() - 1));
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
  } else {
    emit errorOccurred(tr("Invalid sort column"));
    return;
  }

  orderByClause += (order == Qt::AscendingOrder) ? " ASC" : " DESC";

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT s.id, s.item_id, i.name AS item_name, s.quantity, "
                "s.total_price, s.sale_date "
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
    sale.totalPrice = query.value("total_price").toDouble();
    sale.saleDate = query.value("sale_date").toDateTime();
    m_sales.append(sale);
  }
  endResetModel();
  emit dataChanged(index(0), index(m_sales.size() - 1));
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
  if (m_userId == -1) {
    qWarning() << "User not set. Unable to refresh sales.";
    return;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT s.id, s.item_id, i.name AS item_name, s.quantity, "
                "s.total_price, s.sale_date "
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
  while (query.next()) {
    SaleItem sale;
    sale.id = query.value("id").toInt();
    sale.itemId = query.value("item_id").toInt();
    sale.itemName = query.value("item_name").toString();
    sale.quantity = query.value("quantity").toInt();
    sale.totalPrice = query.value("total_price").toDouble();
    sale.saleDate = query.value("sale_date").toDateTime();
    m_sales.append(sale);
  }
  endResetModel();
  emit totalSalesChanged();
  emit revenueThisMonthChanged();
  emit totalRevenueChanged();
  emit dataChanged(index(0), index(m_sales.size() - 1));
}
