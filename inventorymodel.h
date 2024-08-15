#ifndef INVENTORYMODEL_H
#define INVENTORYMODEL_H

#include <QAbstractListModel>
#include <QDate>
#include "databasemanager.h"

class InventoryModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int lowStockItems READ lowStockItems NOTIFY lowStockItemsChanged)
    Q_PROPERTY(double totalCost READ totalCost NOTIFY totalCostChanged)

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CategoryRole,
        QuantityRole,
        PriceRole,
        SupplierNameRole,
        SupplierAddressRole,
        ExpiryDateRole,
        LastUpdatedRole
    };

    explicit InventoryModel(DatabaseManager *dbManager, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setUserId(int userId);
    Q_INVOKABLE bool addItem(const QString &name, const QString &category, int quantity, double price,
                             const QString &supplierName, const QString &supplierAddress, const QDate &expiryDate);
    Q_INVOKABLE bool updateItem(int id, const QString &name, const QString &category, int quantity, double price,
                                const QString &supplierName, const QString &supplierAddress, const QDate &expiryDate);
    Q_INVOKABLE bool deleteItem(int id);
    Q_INVOKABLE void searchItems(const QString &searchText);
    Q_INVOKABLE void refresh();

    int lowStockItems() const;
    double totalCost() const;
    QVariantList getLowStockItems() const;

signals:
    void errorOccurred(const QString &error);
    void lowStockItemsChanged();
    void totalCostChanged();
    void itemNearExpiry(int itemId, const QString &itemName, const QDate &expiryDate);

private:
    static const int LOW_STOCK_THRESHOLD = 10;

    struct InventoryItem {
        int id;
        QString name;
        QString category;
        int quantity;
        double price;
        QString supplierName;
        QString supplierAddress;
        QDate expiryDate;
        QDateTime lastUpdated;
    };

    DatabaseManager *m_dbManager;
    QList<InventoryItem> m_items;
    int m_userId;
    int m_lowStockItems;
    double m_totalCost;

    void checkLowStockItems();
    void checkExpiringItems();
};

#endif // INVENTORYMODEL_H
