#include "userdashboard.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

UserDashboard::UserDashboard(DatabaseManager *dbManager, InventoryModel *inventoryModel, SalesModel *salesModel, QObject *parent)
    : QObject(parent), m_dbManager(dbManager), m_inventoryModel(inventoryModel), m_salesModel(salesModel),
      m_userId(-1), m_totalInventoryItems(0), m_lowStockItems(0), m_totalInventoryValue(0.0),
      m_totalSales(0), m_totalRevenue(0.0), m_profitMargin(0.0), m_maxMonthlyRevenue(0.0), m_maxTopProductValue(0.0)
{
    qDebug() << "UserDashboard constructed";
}

void UserDashboard::setUserId(int userId)
{
    qDebug() << "UserDashboard::setUserId called with userId:" << userId;
    if (m_userId != userId) {
        m_userId = userId;
        refresh();
    }
}

void UserDashboard::refresh()
{
    qDebug() << "UserDashboard::refresh() called for userId:" << m_userId;
    
    if (m_userId == -1) {
        emit errorOccurred("User not set. Unable to refresh dashboard.");
        return;
    }

    m_totalInventoryItems = m_inventoryModel->rowCount();
    m_lowStockItems = calculateLowStockItems();
    m_totalInventoryValue = calculateTotalInventoryValue();
    m_totalSales = m_salesModel->totalSales();
    m_totalRevenue = m_salesModel->totalRevenue();

    if (m_totalRevenue > 0) {
        m_profitMargin = (m_totalRevenue - m_totalInventoryValue) / m_totalRevenue * 100;
    } else {
        m_profitMargin = 0.0;
    }

    updateRecentActivities();
    updateLowStockItems();
    updateMonthlyRevenue();
    updateTopProducts();

    emit totalInventoryItemsChanged();
    emit lowStockItemsChanged();
    emit totalInventoryValueChanged();
    emit totalSalesChanged();
    emit totalRevenueChanged();
    emit profitMarginChanged();

    qDebug() << "UserDashboard refreshed:"
             << "Total Inventory Items:" << m_totalInventoryItems
             << "Low Stock Items:" << m_lowStockItems
             << "Total Inventory Value:" << m_totalInventoryValue
             << "Total Sales:" << m_totalSales
             << "Total Revenue:" << m_totalRevenue
             << "Profit Margin:" << m_profitMargin;
}

int UserDashboard::calculateLowStockItems() const
{
    int lowStockCount = 0;
    for (int i = 0; i < m_inventoryModel->rowCount(); ++i) {
        QModelIndex index = m_inventoryModel->index(i, 0);
        int quantity = m_inventoryModel->data(index, InventoryModel::QuantityRole).toInt();
        int threshold = m_inventoryModel->data(index, InventoryModel::ThresholdRole).toInt();
        if (quantity <= threshold) {
            ++lowStockCount;
        }
    }
    return lowStockCount;
}

double UserDashboard::calculateTotalInventoryValue() const
{
    double totalValue = 0.0;
    for (int i = 0; i < m_inventoryModel->rowCount(); ++i) {
        QModelIndex index = m_inventoryModel->index(i, 0);
        int quantity = m_inventoryModel->data(index, InventoryModel::QuantityRole).toInt();
        double price = m_inventoryModel->data(index, InventoryModel::PriceRole).toDouble();
        totalValue += quantity * price;
    }
    return totalValue;
}

int UserDashboard::totalInventoryItems() const { return m_totalInventoryItems; }
int UserDashboard::lowStockItems() const { return m_lowStockItems; }
double UserDashboard::totalInventoryValue() const { return m_totalInventoryValue; }
int UserDashboard::totalSales() const { return m_totalSales; }
double UserDashboard::totalRevenue() const { return m_totalRevenue; }
double UserDashboard::profitMargin() const { return m_profitMargin; }
QVariantList UserDashboard::recentActivities() const { return m_recentActivities; }
QVariantList UserDashboard::lowStockItemsList() const { return m_lowStockItemsList; }
QStringList UserDashboard::monthlyRevenueLabels() const { return m_monthlyRevenueLabels; }
QVariantList UserDashboard::monthlyRevenueData() const { return m_monthlyRevenueData; }
double UserDashboard::maxMonthlyRevenue() const { return m_maxMonthlyRevenue; }
QStringList UserDashboard::topProductNames() const { return m_topProductNames; }
QVariantList UserDashboard::topProductValues() const { return m_topProductValues; }
double UserDashboard::maxTopProductValue() const { return m_maxTopProductValue; }

void UserDashboard::updateRecentActivities()
{
    QSqlQuery query(m_dbManager->database());
    query.prepare("SELECT 'Sale' as type, s.sale_date as date, i.name as "
                  "item_name, s.quantity, s.total_price "
                  "FROM Sales s "
                  "JOIN Inventory i ON s.item_id = i.id "
                  "WHERE s.user_id = :userId "
                  "UNION ALL "
                  "SELECT 'Inventory Update' as type, i.last_updated as date, "
                  "i.name as item_name, i.quantity, i.price "
                  "FROM Inventory i "
                  "WHERE i.user_id = :userId "
                  "ORDER BY date DESC LIMIT 10");
    query.bindValue(":userId", m_userId);

    if (!query.exec()) {
        emit errorOccurred(tr("Failed to fetch recent activities: %1")
                               .arg(query.lastError().text()));
        return;
    }

    m_recentActivities.clear();
    while (query.next()) {
        QVariantMap activity;
        activity["type"] = query.value("type").toString();
        activity["date"] = query.value("date").toDateTime();
        activity["itemName"] = query.value("item_name").toString();
        activity["quantity"] = query.value("quantity").toInt();
        activity["price"] = query.value("total_price").toDouble();
        m_recentActivities.append(activity);
    }

    emit recentActivitiesChanged();
    qDebug() << "Recent activities updated. Count:" << m_recentActivities.size();
}

void UserDashboard::updateLowStockItems()
{
    m_lowStockItemsList.clear();
    for (int i = 0; i < m_inventoryModel->rowCount(); ++i) {
        QModelIndex index = m_inventoryModel->index(i, 0);
        int quantity = m_inventoryModel->data(index, InventoryModel::QuantityRole).toInt();
        int threshold = m_inventoryModel->data(index, InventoryModel::ThresholdRole).toInt();
        if (quantity <= threshold) {
            QVariantMap item;
            item["name"] = m_inventoryModel->data(index, InventoryModel::NameRole).toString();
            item["quantity"] = quantity;
            item["threshold"] = threshold;
            m_lowStockItemsList.append(item);
        }
    }
    emit lowStockItemsListChanged();
    qDebug() << "Low stock items updated. Count:" << m_lowStockItemsList.size();
}

void UserDashboard::updateMonthlyRevenue()
{
    QSqlQuery query(m_dbManager->database());
    query.prepare("SELECT strftime('%Y-%m', sale_date) as month, SUM(total_price) as revenue "
                  "FROM Sales "
                  "WHERE user_id = :userId "
                  "GROUP BY month "
                  "ORDER BY month DESC "
                  "LIMIT 6");
    query.bindValue(":userId", m_userId);

    if (!query.exec()) {
        emit errorOccurred(tr("Failed to fetch monthly revenue: %1")
                               .arg(query.lastError().text()));
        return;
    }

    m_monthlyRevenueLabels.clear();
    m_monthlyRevenueData.clear();
    m_maxMonthlyRevenue = 0.0;

    while (query.next()) {
        QString month = query.value("month").toString();
        double revenue = query.value("revenue").toDouble();

        m_monthlyRevenueLabels.prepend(month);
        m_monthlyRevenueData.prepend(revenue);

        if (revenue > m_maxMonthlyRevenue) {
            m_maxMonthlyRevenue = revenue;
        }
    }

    emit monthlyRevenueDataChanged();
    qDebug() << "Monthly revenue updated. Count:" << m_monthlyRevenueData.size();
}

void UserDashboard::updateTopProducts()
{
    QSqlQuery query(m_dbManager->database());
    query.prepare("SELECT i.name, SUM(s.total_price) as revenue "
                  "FROM Sales s "
                  "JOIN Inventory i ON s.item_id = i.id "
                  "WHERE s.user_id = :userId "
                  "GROUP BY s.item_id "
                  "ORDER BY revenue DESC "
                  "LIMIT 5");
    query.bindValue(":userId", m_userId);

    if (!query.exec()) {
        emit errorOccurred(tr("Failed to fetch top products: %1")
                               .arg(query.lastError().text()));
        return;
    }

    m_topProductNames.clear();
    m_topProductValues.clear();
    m_maxTopProductValue = 0.0;

    while (query.next()) {
        QString name = query.value("name").toString();
        double revenue = query.value("revenue").toDouble();

        m_topProductNames.append(name);
        m_topProductValues.append(revenue);

        if (revenue > m_maxTopProductValue) {
            m_maxTopProductValue = revenue;
        }
    }

    emit topProductsDataChanged();
    qDebug() << "Top products updated. Count:" << m_topProductNames.size();
}
