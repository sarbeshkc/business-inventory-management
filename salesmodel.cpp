#include "salesmodel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

SalesModel::SalesModel(DatabaseManager *dbManager, QObject *parent)
    : QAbstractListModel(parent), m_dbManager(dbManager), m_userId(-1), m_totalSales(0), m_totalRevenue(0.0)
{}

int SalesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_sales.size();
}

QVariant SalesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_sales.size())
        return QVariant();

    const SaleItem &sale = m_sales.at(index.row());

    switch (role) {
    case IdRole:
        return sale.id;
    case ItemIdRole:
        return sale.itemId;
    case ItemNameRole:
        return sale.itemName;
    case QuantityRole:
        return sale.quantity;
    case PriceRole:
        return sale.price;
    case TotalPriceRole:
        return sale.totalPrice;
    case SaleDateRole:
        return sale.saleDate;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> SalesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[ItemIdRole] = "itemId";
    roles[ItemNameRole] = "itemName";
    roles[QuantityRole] = "quantity";
    roles[PriceRole] = "price";
    roles[TotalPriceRole] = "totalPrice";
    roles[SaleDateRole] = "saleDate";
    return roles;
}

void SalesModel::setUserId(int userId)
{
    if (m_userId != userId) {
        m_userId = userId;
        refresh();
    }
}

bool SalesModel::addSale(int itemId, int quantity, double price)
{
    if (m_userId == -1) {
        emit errorOccurred("User not set. Unable to add sale.");
        return false;
    }

    QSqlDatabase db = m_dbManager->database();
    db.transaction();

    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO Sales (user_id, item_id, quantity, price, total_price, sale_date) "
        "VALUES (:userId, :itemId, :quantity, :price, :totalPrice, :saleDate)"
    );
    query.bindValue(":userId", m_userId);
    query.bindValue(":itemId", itemId);
    query.bindValue(":quantity", quantity);
    query.bindValue(":price", price);
    query.bindValue(":totalPrice", price * quantity);
    query.bindValue(":saleDate", QDateTime::currentDateTime());

    if (!query.exec()) {
        db.rollback();
        emit errorOccurred(tr("Failed to add sale: %1").arg(query.lastError().text()));
        return false;
    }

    // Update inventory
    query.prepare("UPDATE Inventory SET quantity = quantity - :soldQuantity WHERE id = :itemId AND user_id = :userId");
    query.bindValue(":soldQuantity", quantity);
    query.bindValue(":itemId", itemId);
    query.bindValue(":userId", m_userId);

    if (!query.exec()) {
        db.rollback();
        emit errorOccurred(tr("Failed to update inventory: %1").arg(query.lastError().text()));
        return false;
    }

    db.commit();
    refresh();
    return true;
}

void SalesModel::searchSales(const QString &searchText)
{
    if (m_userId == -1) {
        emit errorOccurred("User not set. Unable to search sales.");
        return;
    }

    QSqlQuery query(m_dbManager->database());
    query.prepare("SELECT s.id, s.item_id, i.name AS item_name, s.quantity, s.price, s.total_price, s.sale_date "
                  "FROM Sales s "
                  "JOIN Inventory i ON s.item_id = i.id "
                  "WHERE s.user_id = :userId AND i.name LIKE :searchText "
                  "ORDER BY s.sale_date DESC");
    query.bindValue(":userId", m_userId);
    query.bindValue(":searchText", "%" + searchText + "%");

    if (!query.exec()) {
        emit errorOccurred(tr("Failed to search sales: %1").arg(query.lastError().text()));
        return;
    }

    beginResetModel();
    m_sales.clear();
    m_totalRevenue = 0.0;
    while (query.next()) {
        SaleItem sale;
        sale.id = query.value("id").toInt();
        sale.itemId = query.value("item_id").toInt();
        sale.itemName = query.value("item_name").toString();
        sale.quantity = query.value("quantity").toInt();
        sale.price = query.value("price").toDouble();
        sale.totalPrice = query.value("total_price").toDouble();
        sale.saleDate = query.value("sale_date").toDateTime();
        m_sales.append(sale);
        m_totalRevenue += sale.totalPrice;
    }
    m_totalSales = m_sales.size();
    endResetModel();
    emit totalSalesChanged();
    emit totalRevenueChanged();
}

void SalesModel::refresh()
{
    if (m_userId == -1) {
        qWarning() << "User not set. Unable to refresh sales.";
        return;
    }

    QSqlQuery query(m_dbManager->database());
    query.prepare("SELECT s.id, s.item_id, i.name AS item_name, s.quantity, s.price, s.total_price, s.sale_date "
                  "FROM Sales s "
                  "JOIN Inventory i ON s.item_id = i.id "
                  "WHERE s.user_id = :userId "
                  "ORDER BY s.sale_date DESC");
    query.bindValue(":userId", m_userId);

    if (!query.exec()) {
        emit errorOccurred(tr("Failed to fetch sales data: %1").arg(query.lastError().text()));
        return;
    }

    beginResetModel();
    m_sales.clear();
    m_totalRevenue = 0.0;
    while (query.next()) {
        SaleItem sale;
        sale.id = query.value("id").toInt();
        sale.itemId = query.value("item_id").toInt();
        sale.itemName = query.value("item_name").toString();
        sale.quantity = query.value("quantity").toInt();
        sale.price = query.value("price").toDouble();
        sale.totalPrice = query.value("total_price").toDouble();
        sale.saleDate = query.value("sale_date").toDateTime();
        m_sales.append(sale);
        m_totalRevenue += sale.totalPrice;
    }
    m_totalSales = m_sales.size();
    endResetModel();
    emit totalSalesChanged();
    emit totalRevenueChanged();
}

int SalesModel::totalSales() const
{
    return m_totalSales;
}

double SalesModel::totalRevenue() const
{
    return m_totalRevenue;
}
