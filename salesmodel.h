#ifndef SALESMODEL_H
#define SALESMODEL_H

#include <QAbstractListModel>
#include <QDateTime>
#include "databasemanager.h"

class SalesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int totalSales READ totalSales NOTIFY totalSalesChanged)
    Q_PROPERTY(double totalRevenue READ totalRevenue NOTIFY totalRevenueChanged)

public:
    enum SalesRoles {
        IdRole = Qt::UserRole + 1,
        ItemIdRole,
        ItemNameRole,
        QuantityRole,
        PriceRole,
        TotalPriceRole,
        SaleDateRole
    };

    explicit SalesModel(DatabaseManager *dbManager, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setUserId(int userId);

    Q_INVOKABLE bool addSale(int itemId, int quantity, double price);
    Q_INVOKABLE void searchSales(const QString &searchText);
    Q_INVOKABLE void refresh();

    int totalSales() const;
    double totalRevenue() const;

signals:
    void errorOccurred(const QString &error);
    void totalSalesChanged();
    void totalRevenueChanged();

private:
    struct SaleItem {
        int id;
        int itemId;
        QString itemName;
        int quantity;
        double price;
        double totalPrice;
        QDateTime saleDate;
    };

    DatabaseManager *m_dbManager;
    int m_userId;
    QList<SaleItem> m_sales;
    int m_totalSales;
    double m_totalRevenue;
};

#endif // SALESMODEL_H
