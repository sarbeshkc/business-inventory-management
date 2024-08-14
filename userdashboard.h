#ifndef USERDASHBOARD_H
#define USERDASHBOARD_H

#include <QObject>
#include <QVariantList>
#include "databasemanager.h"
#include "inventorymodel.h"
#include "salesmodel.h"

class UserDashboard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int totalInventoryItems READ totalInventoryItems NOTIFY totalInventoryItemsChanged)
    Q_PROPERTY(int lowStockItems READ lowStockItems NOTIFY lowStockItemsChanged)
    Q_PROPERTY(double totalInventoryValue READ totalInventoryValue NOTIFY totalInventoryValueChanged)
    Q_PROPERTY(int totalSales READ totalSales NOTIFY totalSalesChanged)
    Q_PROPERTY(double totalRevenue READ totalRevenue NOTIFY totalRevenueChanged)
    Q_PROPERTY(double profitMargin READ profitMargin NOTIFY profitMarginChanged)
    Q_PROPERTY(QVariantList recentActivities READ recentActivities NOTIFY recentActivitiesChanged)
    Q_PROPERTY(QVariantList lowStockItemsList READ lowStockItemsList NOTIFY lowStockItemsListChanged)
    Q_PROPERTY(QStringList monthlyRevenueLabels READ monthlyRevenueLabels NOTIFY monthlyRevenueDataChanged)
    Q_PROPERTY(QVariantList monthlyRevenueData READ monthlyRevenueData NOTIFY monthlyRevenueDataChanged)
    Q_PROPERTY(double maxMonthlyRevenue READ maxMonthlyRevenue NOTIFY monthlyRevenueDataChanged)
    Q_PROPERTY(QStringList topProductNames READ topProductNames NOTIFY topProductsDataChanged)
    Q_PROPERTY(QVariantList topProductValues READ topProductValues NOTIFY topProductsDataChanged)
    Q_PROPERTY(double maxTopProductValue READ maxTopProductValue NOTIFY topProductsDataChanged)

public:
    explicit UserDashboard(DatabaseManager *dbManager, InventoryModel *inventoryModel, SalesModel *salesModel, QObject *parent = nullptr);

    Q_INVOKABLE void setUserId(int userId);
    Q_INVOKABLE void refresh();

    int totalInventoryItems() const;
    int lowStockItems() const;
    double totalInventoryValue() const;
    int totalSales() const;
    double totalRevenue() const;
    double profitMargin() const;
    QVariantList recentActivities() const;
    QVariantList lowStockItemsList() const;
    QStringList monthlyRevenueLabels() const;
    QVariantList monthlyRevenueData() const;
    double maxMonthlyRevenue() const;
    QStringList topProductNames() const;
    QVariantList topProductValues() const;
    double maxTopProductValue() const;

signals:
    void errorOccurred(const QString &error);
    void totalInventoryItemsChanged();
    void lowStockItemsChanged();
    void totalInventoryValueChanged();
    void totalSalesChanged();
    void totalRevenueChanged();
    void profitMarginChanged();
    void recentActivitiesChanged();
    void lowStockItemsListChanged();
    void monthlyRevenueDataChanged();
    void topProductsDataChanged();

private:
    void updateRecentActivities();
    void updateLowStockItems();
    void updateMonthlyRevenue();
    void updateTopProducts();
    int calculateLowStockItems() const;
    double calculateTotalInventoryValue() const;

    DatabaseManager *m_dbManager;
    InventoryModel *m_inventoryModel;
    SalesModel *m_salesModel;
    int m_userId;
    int m_totalInventoryItems;
    int m_lowStockItems;
    double m_totalInventoryValue;
    int m_totalSales;
    double m_totalRevenue;
    double m_profitMargin;
    QVariantList m_recentActivities;
    QVariantList m_lowStockItemsList;
    QStringList m_monthlyRevenueLabels;
    QVariantList m_monthlyRevenueData;
    double m_maxMonthlyRevenue;
    QStringList m_topProductNames;
    QVariantList m_topProductValues;
    double m_maxTopProductValue;
};

#endif // USERDASHBOARD_H
