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
    enum SalesRoles {
        IdRole = Qt::UserRole + 1,
        ItemIdRole,
        ItemNameRole,
        QuantityRole,
        TotalPriceRole,
        SaleDateRole
    };

    explicit SalesModel(DatabaseManager *dbManager, QObject *parent = nullptr);
    ~SalesModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool addSale(int itemId, int quantity, double totalPrice);
    Q_INVOKABLE void searchSales(const QString &searchText);
    Q_INVOKABLE void sortSales(const QString &column, Qt::SortOrder order = Qt::AscendingOrder);
    Q_INVOKABLE QVariantList getSalesDistribution() const;
    Q_INVOKABLE QVariantList getMonthlySales() const;

    int totalSales() const;
    double revenueThisMonth() const;
    double totalRevenue() const;

    void setUserId(int userId);
    Q_INVOKABLE void refresh();

signals:
    void errorOccurred(const QString &error);
    void totalSalesChanged();
    void revenueThisMonthChanged();
    void totalRevenueChanged();
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());

private:
    struct SaleItem {
        int id;
        int itemId;
        QString itemName;
        int quantity;
        double totalPrice;
        QDateTime saleDate;
    };

    QList<SaleItem> m_sales;
    DatabaseManager *m_dbManager;
    int m_userId;
};

#endif // SALESMODEL_H
