#ifndef INVENTORYMODEL_H
#define INVENTORYMODEL_H

#include <QAbstractListModel>
#include <QDateTime>
#include "databasemanager.h"

class InventoryModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int lowStockItems READ lowStockItems NOTIFY lowStockItemsChanged)

public:
    enum InventoryRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CategoryRole,
        QuantityRole,
        PriceRole,
        SupplierNameRole,
        SupplierAddressRole,
        LastUpdatedRole
    };

    explicit InventoryModel(DatabaseManager *dbManager, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setUserId(int userId);

    Q_INVOKABLE bool addItem(const QString &name, const QString &category, int quantity, double price, const QString &supplierName, const QString &supplierAddress);
    Q_INVOKABLE bool updateItem(int id, const QString &name, const QString &category, int quantity, double price, const QString &supplierName, const QString &supplierAddress);
    Q_INVOKABLE bool deleteItem(int id);
    Q_INVOKABLE void searchItems(const QString &searchText);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE QVariantList getLowStockItems() const;

    int lowStockItems() const;
    double totalCost() const;

signals:
    void errorOccurred(const QString &error);
    void lowStockItemsChanged();

private:
    struct InventoryItem {
        int id;
        QString name;
        QString category;
        int quantity;
        double price;
        QString supplierName;
        QString supplierAddress;
        QDateTime lastUpdated;
    };

    void checkLowStockItems();

    DatabaseManager *m_dbManager;
    int m_userId;
    QList<InventoryItem> m_items;
    int m_lowStockItems;
    double m_totalCost;

    static const int LOW_STOCK_THRESHOLD = 10;
};

#endif // INVENTORYMODEL_H
