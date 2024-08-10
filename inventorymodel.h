#ifndef INVENTORYMODEL_H
#define INVENTORYMODEL_H

#include "databasemanager.h"
#include <QAbstractListModel>

class InventoryModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(int totalItems READ totalItems NOTIFY totalItemsChanged)
  Q_PROPERTY(int lowStockItems READ lowStockItems NOTIFY lowStockItemsChanged)

public:
  enum InventoryRoles {
    IdRole = Qt::UserRole + 1,
    NameRole,
    QuantityRole,
    PriceRole
  };

  explicit InventoryModel(DatabaseManager *dbManager,
                          QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE bool addItem(const QString &name, int quantity, double price);
  Q_INVOKABLE bool updateItem(int id, const QString &name, int quantity,
                              double price);
  Q_INVOKABLE bool deleteItem(int id);
  Q_INVOKABLE void searchItems(const QString &searchText);
  Q_INVOKABLE void sortItems(const QString &column,
                             Qt::SortOrder order = Qt::AscendingOrder);
  Q_INVOKABLE void refresh();
  Q_INVOKABLE QVariantList getTopItems(int count) const;

  int totalItems() const;
  int lowStockItems() const;

  void setUserId(int userId);

signals:
  void errorOccurred(const QString &error);
  void totalItemsChanged();
  void lowStockItemsChanged();

private:
  struct InventoryItem {
    int id;
    QString name;
    int quantity;
    double price;
  };

  QList<InventoryItem> m_items;
  DatabaseManager *m_dbManager;
  int m_userId;
};

#endif // INVENTORYMODEL_H
