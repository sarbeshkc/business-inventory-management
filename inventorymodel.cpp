#include "inventorymodel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

InventoryModel::InventoryModel(DatabaseManager *dbManager, QObject *parent)
    : QAbstractListModel(parent), m_dbManager(dbManager), m_userId(-1) {}

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
  case QuantityRole:
    return item.quantity;
  case PriceRole:
    return item.price;
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> InventoryModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[IdRole] = "id";
  roles[NameRole] = "name";
  roles[QuantityRole] = "quantity";
  roles[PriceRole] = "price";
  return roles;
}

void InventoryModel::setUserId(int userId) {
  if (m_userId != userId) {
    m_userId = userId;
    refresh();
  }
}

bool InventoryModel::addItem(const QString &name, int quantity, double price) {
  qDebug() << "Adding item:" << name << "for user ID:" << m_userId;
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to add item.");
    return false;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("INSERT INTO Inventory (user_id, name, quantity, price) "
                "VALUES (:userId, :name, :quantity, :price)");
  query.bindValue(":userId", m_userId);
  query.bindValue(":name", name);
  query.bindValue(":quantity", quantity);
  query.bindValue(":price", price);

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to add item: %1").arg(query.lastError().text()));
    return false;
  }

  refresh();
  return true;
}

bool InventoryModel::updateItem(int id, const QString &name, int quantity,
                                double price) {
  qDebug() << "Updating item:" << id << "for user ID:" << m_userId;
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to update item.");
    return false;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("UPDATE Inventory SET name = :name, quantity = :quantity, "
                "price = :price WHERE id = :id AND user_id = :userId");
  query.bindValue(":name", name);
  query.bindValue(":quantity", quantity);
  query.bindValue(":price", price);
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
  qDebug() << "Deleting item:" << id << "for user ID:" << m_userId;
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
  qDebug() << "Searching items for user ID:" << m_userId
           << "with text:" << searchText;
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to search items.");
    return;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT id, name, quantity, price FROM Inventory "
                "WHERE user_id = :userId AND name LIKE :searchText");
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
    item.quantity = query.value("quantity").toInt();
    item.price = query.value("price").toDouble();
    m_items.append(item);
  }
  endResetModel();
  emit totalItemsChanged();
  emit lowStockItemsChanged();
}

void InventoryModel::sortItems(const QString &column, Qt::SortOrder order) {
  qDebug() << "Sorting items for user ID:" << m_userId
           << "by column:" << column;
  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to sort items.");
    return;
  }

  QString orderByClause;
  if (column == "Name") {
    orderByClause = "name";
  } else if (column == "Quantity") {
    orderByClause = "quantity";
  } else if (column == "Price") {
    orderByClause = "price";
  } else {
    emit errorOccurred(tr("Invalid sort column"));
    return;
  }

  orderByClause += (order == Qt::AscendingOrder) ? " ASC" : " DESC";

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT id, name, quantity, price FROM Inventory "
                "WHERE user_id = :userId ORDER BY " +
                orderByClause);
  query.bindValue(":userId", m_userId);

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to sort items: %1").arg(query.lastError().text()));
    return;
  }

  beginResetModel();
  m_items.clear();
  while (query.next()) {
    InventoryItem item;
    item.id = query.value("id").toInt();
    item.name = query.value("name").toString();
    item.quantity = query.value("quantity").toInt();
    item.price = query.value("price").toDouble();
    m_items.append(item);
  }
  endResetModel();
  emit totalItemsChanged();
  emit lowStockItemsChanged();
}

void InventoryModel::refresh() {
  qDebug() << "Refreshing inventory for user ID:" << m_userId;
  if (m_userId == -1) {
    qWarning() << "User not set. Unable to refresh inventory.";
    return;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT id, name, quantity, price FROM Inventory WHERE user_id "
                "= :userId");
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
    item.quantity = query.value("quantity").toInt();
    item.price = query.value("price").toDouble();
    m_items.append(item);
  }
  endResetModel();
  emit totalItemsChanged();
  emit lowStockItemsChanged();
}

int InventoryModel::totalItems() const { return m_items.size(); }

int InventoryModel::lowStockItems() const {
  int count = 0;
  for (const auto &item : m_items) {
    if (item.quantity < 10) { // Assuming low stock is less than 10
      count++;
    }
  }
  return count;
}

QVariantList InventoryModel::getTopItems(int count) const {
  QVariantList result;
  QList<InventoryItem> sortedItems = m_items;

  // Sort items by quantity in descending order
  std::sort(sortedItems.begin(), sortedItems.end(),
            [](const InventoryItem &a, const InventoryItem &b) {
              return a.quantity > b.quantity;
            });

  // Take the top 'count' items
  for (int i = 0; i < qMin(count, sortedItems.size()); ++i) {
    QVariantMap item;
    item["name"] = sortedItems[i].name;
    item["quantity"] = sortedItems[i].quantity;
    result.append(item);
  }

  return result;
}
