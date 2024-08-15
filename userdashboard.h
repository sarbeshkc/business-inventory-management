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
    Q_PROPERTY(double totalCost READ totalCost NOTIFY totalCostChanged)
    Q_PROPERTY(double grossProfit READ grossProfit NOTIFY grossProfitChanged)
    Q_PROPERTY(double profitMargin READ profitMargin NOTIFY profitMarginChanged)
    Q_PROPERTY(QVariantList recentActivities READ recentActivities NOTIFY recentActivitiesChanged)
    Q_PROPERTY(QVariantList lowStockItemsList READ lowStockItemsList NOTIFY lowStockItemsListChanged)
    Q_PROPERTY(QVariantList monthlyProfitData READ monthlyProfitData NOTIFY monthlyProfitDataChanged)
    Q_PROPERTY(int expiringItems READ expiringItems NOTIFY expiringItemsChanged)

public:
    explicit UserDashboard(DatabaseManager *dbManager, InventoryModel *inventoryModel, SalesModel *salesModel, QObject *parent = nullptr);

    void setUserId(int userId);
    Q_INVOKABLE void refresh();

    int totalInventoryItems() const;
    int lowStockItems() const;
    double totalInventoryValue() const;
    int totalSales() const;
    double totalRevenue() const;
    double totalCost() const;
    double grossProfit() const;
    double profitMargin() const;
    QVariantList recentActivities() const;
    QVariantList lowStockItemsList() const;
    QVariantList monthlyProfitData() const;
    int expiringItems() const;

signals:
    void errorOccurred(const QString &error);
    void totalInventoryItemsChanged();
    void lowStockItemsChanged();
    void totalInventoryValueChanged();
    void totalSalesChanged();
    void totalRevenueChanged();
    void totalCostChanged();
    void grossProfitChanged();
    void profitMarginChanged();
    void recentActivitiesChanged();
    void lowStockItemsListChanged();
    void monthlyProfitDataChanged();
    void expiringItemsChanged();
    void itemNearExpiry(int itemId, const QString &itemName, const QDate &expiryDate);

private:
    DatabaseManager *m_dbManager;
    InventoryModel *m_inventoryModel;
    SalesModel *m_salesModel;
    int m_userId;
    int m_totalInventoryItems;
    int m_lowStockItems;
    double m_totalInventoryValue;
    int m_totalSales;
    double m_totalRevenue;
    double m_totalCost;
    double m_grossProfit;
    double m_profitMargin;
    QVariantList m_recentActivities;
    QVariantList m_lowStockItemsList;
    QVariantList m_monthlyProfitData;
    int m_expiringItems;

    void calculateProfitAndLoss();
    void updateRecentActivities();
    void updateLowStockItems();
    void fetchMonthlyProfitData();
    void checkExpiringItems();
};

#endif // USERDASHBOARD_H
