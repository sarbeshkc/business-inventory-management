#include "inventorymodel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

InventoryModel::InventoryModel(DatabaseManager *dbManager, QObject *parent)
    : QAbstractListModel(parent), m_dbManager(dbManager), m_userId(-1),
      m_lowStockItems(0) {}

int InventoryModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;
  return m_items.size();
}

QVariant InventoryModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_items.size())
    return QVariant();

  const InventoryItem &item = m_items.at(index.row());

  switch (role) {
  case IdRole:
    return item.id;
  case NameRole:
    return item.name;
  case CategoryRole:
    return item.category;
  case QuantityRole:
    return item.quantity;
  case PriceRole:
    return item.price;
  case LastUpdatedRole:
    return item.lastUpdated;
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> InventoryModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[IdRole] = "id";
  roles[NameRole] = "name";
  roles[CategoryRole] = "category";
  roles[QuantityRole] = "quantity";
  roles[PriceRole] = "price";
  roles[LastUpdatedRole] = "lastUpdated";
  return roles;
}

void InventoryModel::setUserId(int userId) {
  if (m_userId != userId) {
    m_userId = userId;
    refresh();
  }
}

bool InventoryModel::addItem(const QString &name, const QString &category,
                             int quantity, double price) {
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to add item.");
    return false;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare(
      "INSERT INTO Inventory (user_id, name, category, quantity, price, "
      "last_updated) "
      "VALUES (:userId, :name, :category, :quantity, :price, :lastUpdated)");
  query.bindValue(":userId", m_userId);
  query.bindValue(":name", name);
  query.bindValue(":category", category);
  query.bindValue(":quantity", quantity);
  query.bindValue(":price", price);
  query.bindValue(":lastUpdated", QDateTime::currentDateTime());

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to add item: %1").arg(query.lastError().text()));
    return false;
  }

  refresh();
  return true;
}

bool InventoryModel::updateItem(int id, const QString &name,
                                const QString &category, int quantity,
                                double price) {
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to update item.");
    return false;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("UPDATE Inventory SET name = :name, category = :category, "
                "quantity = :quantity, "
                "price = :price, last_updated = :lastUpdated WHERE id = :id "
                "AND user_id = :userId");
  query.bindValue(":name", name);
  query.bindValue(":category", category);
  query.bindValue(":quantity", quantity);
  query.bindValue(":price", price);
  query.bindValue(":lastUpdated", QDateTime::currentDateTime());
  query.bindValue(":id", id);
  query.bindValue(":userId", m_userId);

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to update item: %1").arg(query.lastError().text()));
    return false;
  }

  refresh();
  return true;
}

bool InventoryModel::deleteItem(int id) {
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to delete item.");
    return false;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("DELETE FROM Inventory WHERE id = :id AND user_id = :userId");
  query.bindValue(":id", id);
  query.bindValue(":userId", m_userId);

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to delete item: %1").arg(query.lastError().text()));
    return false;
  }

  refresh();
  return true;
}

void InventoryModel::searchItems(const QString &searchText) {
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to search items.");
    return;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare(
      "SELECT id, name, category, quantity, price, last_updated FROM Inventory "
      "WHERE user_id = :userId AND (name LIKE :searchText OR category LIKE "
      ":searchText)");
  query.bindValue(":userId", m_userId);
  query.bindValue(":searchText", "%" + searchText + "%");

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to search items: %1").arg(query.lastError().text()));
    return;
  }

  beginResetModel();
  m_items.clear();
  while (query.next()) {
    InventoryItem item;
    item.id = query.value("id").toInt();
    item.name = query.value("name").toString();
    item.category = query.value("category").toString();
    item.quantity = query.value("quantity").toInt();
    item.price = query.value("price").toDouble();
    item.lastUpdated = query.value("last_updated").toDateTime();
    m_items.append(item);
  }
  endResetModel();

  checkLowStockItems();
}

void InventoryModel::refresh() {
  if (m_userId == -1) {
    qWarning() << "User not set. Unable to refresh inventory.";
    return;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT id, name, category, quantity, price, last_updated FROM "
                "Inventory WHERE user_id = :userId");
  query.bindValue(":userId", m_userId);

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to fetch inventory data: %1").arg(query.lastError().text()));
    return;
  }

  beginResetModel();
  m_items.clear();
  while (query.next()) {
    InventoryItem item;
    item.id = query.value("id").toInt();
    item.name = query.value("name").toString();
    item.category = query.value("category").toString();
    item.quantity = query.value("quantity").toInt();
    item.price = query.value("price").toDouble();
    item.lastUpdated = query.value("last_updated").toDateTime();
    m_items.append(item);
  }
  endResetModel();

  checkLowStockItems();
}

void InventoryModel::checkLowStockItems() {
  int lowStockCount = 0;
  for (const auto &item : m_items) {
    if (item.quantity < LOW_STOCK_THRESHOLD) {
      lowStockCount++;
    }
  }

  if (m_lowStockItems != lowStockCount) {
    m_lowStockItems = lowStockCount;
    emit lowStockItemsChanged();
  }
}

int InventoryModel::lowStockItems() const { return m_lowStockItems; }
