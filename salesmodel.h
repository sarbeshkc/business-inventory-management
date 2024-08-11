#ifndef SALESMODEL_H
#define SALESMODEL_H

#include <QAbstractListModel>
#include <QDateTime>
#include "databasemanager.h"

class SalesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int totalSales READ totalSales NOTIFY totalSalesChanged)
    Q_PROPERTY(double revenueThisMonth READ revenueThisMonth NOTIFY revenueThisMonthChanged)
    Q_PROPERTY(double totalRevenue READ totalRevenue NOTIFY totalRevenueChanged)

public:
    enum SaleRoles {
        IdRole = Qt::UserRole + 1,
        ItemIdRole,
        ItemNameRole,
        QuantityRole,
        PriceRole,
        TotalPriceRole,
        SaleDateRole,
        CategoryRole,
        SupplierNameRole,
        SupplierAddressRole
    };

    explicit SalesModel(DatabaseManager *dbManager, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setUserId(int userId);
    Q_INVOKABLE bool addSale(int itemId, int quantity, double price, const QString &category,
                             const QString &supplierName, const QString &supplierAddress);
    Q_INVOKABLE void searchSales(const QString &searchText);
    Q_INVOKABLE void sortSales(const QString &column, Qt::SortOrder order);
    Q_INVOKABLE QVariantList getSalesDistribution() const;
    Q_INVOKABLE QVariantList getMonthlySales() const;
    Q_INVOKABLE void insertTestData();

    int totalSales() const;
    double revenueThisMonth() const;
    double totalRevenue() const;

public slots:
    void refresh();

signals:
    void totalSalesChanged();
    void revenueThisMonthChanged();
    void totalRevenueChanged();
    void errorOccurred(const QString &error);

private:
    struct SaleItem {
        int id;
        int itemId;
        QString itemName;
        int quantity;
        double price;
        double totalPrice;
        QDateTime saleDate;
        QString category;
        QString supplierName;
        QString supplierAddress;
    };

    QList<SaleItem> m_sales;
    DatabaseManager *m_dbManager;
    int m_userId;
};

#endif // SALESMODEL_H
