#include "userdashboard.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

UserDashboard::UserDashboard(DatabaseManager *dbManager,
                             InventoryModel *inventoryModel,
                             SalesModel *salesModel, QObject *parent)
    : QObject(parent), m_dbManager(dbManager), m_inventoryModel(inventoryModel),
      m_salesModel(salesModel), m_userId(-1), m_totalInventoryItems(0),
      m_lowStockItems(0), m_totalInventoryValue(0.0), m_totalSales(0),
      m_totalRevenue(0.0), m_totalCost(0.0), m_grossProfit(0.0),
      m_profitMargin(0.0), m_expiringItems(0) {
  qDebug() << "UserDashboard constructed";
  connect(m_inventoryModel, &InventoryModel::itemNearExpiry, this,
          &UserDashboard::itemNearExpiry);
}

void UserDashboard::setUserId(int userId) {
  qDebug() << "UserDashboard::setUserId called with userId:" << userId;
  if (m_userId != userId) {
    m_userId = userId;
    m_inventoryModel->setUserId(userId);
    m_salesModel->setUserId(userId);
    refresh();
  }
}

void UserDashboard::refresh() {
  qDebug() << "UserDashboard::refresh() called for userId:" << m_userId;

  if (m_userId == -1) {
    emit errorOccurred("User not set. Unable to refresh dashboard.");
    return;
  }

  m_inventoryModel->refresh();
  m_salesModel->refresh();

  m_totalInventoryItems = m_inventoryModel->rowCount();
  m_lowStockItems = m_inventoryModel->lowStockItems();
  m_totalInventoryValue = m_inventoryModel->totalCost();
  m_totalSales = m_salesModel->totalSales();
  m_totalRevenue = m_salesModel->totalRevenue();

  calculateProfitAndLoss();
  updateRecentActivities();
  updateLowStockItems();
  fetchMonthlyProfitData();
  checkExpiringItems();

  emit totalInventoryItemsChanged();
  emit lowStockItemsChanged();
  emit totalInventoryValueChanged();
  emit totalSalesChanged();
  emit totalRevenueChanged();
  emit totalCostChanged();
  emit grossProfitChanged();
  emit profitMarginChanged();
  emit expiringItemsChanged();

  qDebug() << "UserDashboard refreshed:" << "Total Inventory Items:"
           << m_totalInventoryItems << "Low Stock Items:" << m_lowStockItems
           << "Total Inventory Value:" << m_totalInventoryValue
           << "Total Sales:" << m_totalSales
           << "Total Revenue:" << m_totalRevenue << "Total Cost:" << m_totalCost
           << "Gross Profit:" << m_grossProfit
           << "Profit Margin:" << m_profitMargin
           << "Expiring Items:" << m_expiringItems;
}

void UserDashboard::updateRecentActivities() {
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

void UserDashboard::updateLowStockItems() {
  m_lowStockItemsList = m_inventoryModel->getLowStockItems();
  emit lowStockItemsListChanged();
  qDebug() << "Low stock items updated. Count:" << m_lowStockItemsList.size();
}

void UserDashboard::calculateProfitAndLoss() {
  m_totalCost = m_inventoryModel->totalCost();
  m_grossProfit = m_totalRevenue - m_totalCost;

  if (m_totalRevenue > 0) {
    m_profitMargin = (m_grossProfit / m_totalRevenue) * 100;
  } else {
    m_profitMargin = 0;
  }
}

void UserDashboard::fetchMonthlyProfitData() {
  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT strftime('%Y-%m', s.sale_date) as month, "
                "SUM(s.total_price) as revenue, "
                "SUM(i.price * s.quantity) as cost "
                "FROM Sales s "
                "JOIN Inventory i ON s.item_id = i.id "
                "WHERE s.user_id = :userId "
                "GROUP BY month "
                "ORDER BY month DESC "
                "LIMIT 6");
  query.bindValue(":userId", m_userId);

  if (!query.exec()) {
    emit errorOccurred(tr("Failed to fetch monthly profit data: %1")
                           .arg(query.lastError().text()));
    return;
  }

  m_monthlyProfitData.clear();
  while (query.next()) {
    QString month = query.value("month").toString();
    double revenue = query.value("revenue").toDouble();
    double cost = query.value("cost").toDouble();
    double profit = revenue - cost;

    QVariantMap dataPoint;
    dataPoint["month"] = month;
    dataPoint["revenue"] = revenue;
    dataPoint["cost"] = cost;
    dataPoint["profit"] = profit;
    m_monthlyProfitData.prepend(dataPoint);
  }

  emit monthlyProfitDataChanged();
  qDebug() << "Monthly profit data updated. Count:"
           << m_monthlyProfitData.size();
}

void UserDashboard::checkExpiringItems() {
  QDate currentDate = QDate::currentDate();
  QDate thirtyDaysFromNow = currentDate.addDays(30);

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT id, name, expiry_date FROM Inventory "
                "WHERE user_id = :userId AND expiry_date <= :expiryDate AND "
                "expiry_date >= :currentDate");
  query.bindValue(":userId", m_userId);
  query.bindValue(":expiryDate", thirtyDaysFromNow);
  query.bindValue(":currentDate", currentDate);

  if (!query.exec()) {
    emit errorOccurred(
        tr("Failed to check expiring items: %1").arg(query.lastError().text()));
    return;
  }

  m_expiringItems = 0;
  QSet<int> notifiedItems;
  while (query.next()) {
    int itemId = query.value("id").toInt();
    QString itemName = query.value("name").toString();
    QDate expiryDate = query.value("expiry_date").toDate();

    m_expiringItems++;

    if (!notifiedItems.contains(itemId)) {
      emit itemNearExpiry(itemId, itemName, expiryDate);
      notifiedItems.insert(itemId);
    }
  }

  emit expiringItemsChanged();
  qDebug() << "Expiring items updated. Count:" << m_expiringItems;
}

int UserDashboard::totalInventoryItems() const { return m_totalInventoryItems; }
int UserDashboard::lowStockItems() const { return m_lowStockItems; }
double UserDashboard::totalInventoryValue() const {
  return m_totalInventoryValue;
}
int UserDashboard::totalSales() const { return m_totalSales; }
double UserDashboard::totalRevenue() const { return m_totalRevenue; }
double UserDashboard::totalCost() const { return m_totalCost; }
double UserDashboard::grossProfit() const { return m_grossProfit; }
double UserDashboard::profitMargin() const { return m_profitMargin; }
QVariantList UserDashboard::recentActivities() const {
  return m_recentActivities;
}
QVariantList UserDashboard::lowStockItemsList() const {
  return m_lowStockItemsList;
}
QVariantList UserDashboard::monthlyProfitData() const {
  return m_monthlyProfitData;
}
int UserDashboard::expiringItems() const { return m_expiringItems; }
