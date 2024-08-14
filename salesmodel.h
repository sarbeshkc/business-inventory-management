#ifndef SALESMODEL_H
#define SALESMODEL_H

#include "databasemanager.h"
#include <QAbstractListModel>
#include <QDateTime>

class SalesModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(int totalSales READ totalSales NOTIFY totalSalesChanged)
  Q_PROPERTY(double revenueThisMonth READ revenueThisMonth NOTIFY
                 revenueThisMonthChanged)
  Q_PROPERTY(double totalRevenue READ totalRevenue NOTIFY totalRevenueChanged)
  Q_PROPERTY(
      double maxMonthlySales READ maxMonthlySales NOTIFY maxMonthlySalesChanged)
  Q_PROPERTY(QVariantList monthlySalesData READ monthlySalesData NOTIFY
                 monthlySalesDataChanged)
  Q_PROPERTY(
      QVariantList topProducts READ topProducts NOTIFY topProductsChanged)

public:
  enum SalesRoles {
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
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  void setUserId(int userId);

  Q_INVOKABLE bool addSale(int itemId, int quantity, double price,
                           const QString &category, const QString &supplierName,
                           const QString &supplierAddress);
  Q_INVOKABLE void searchSales(const QString &searchText);
  Q_INVOKABLE void sortSales(const QString &column, Qt::SortOrder order);
  Q_INVOKABLE void refresh();
  Q_INVOKABLE void refreshAnalytics();

  int totalSales() const;
  double revenueThisMonth() const;
  double totalRevenue() const;
  double maxMonthlySales() const;
  QVariantList monthlySalesData() const;
  QVariantList topProducts() const;

signals:
  void errorOccurred(const QString &error);
  void totalSalesChanged();
  void revenueThisMonthChanged();
  void totalRevenueChanged();
  void maxMonthlySalesChanged();
  void monthlySalesDataChanged();
  void topProductsChanged();

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

  DatabaseManager *m_dbManager;
  int m_userId;
  QList<SaleItem> m_sales;
  double m_revenueThisMonth;
  double m_totalRevenue;
  double m_maxMonthlySales;
  QVariantList m_monthlySalesData;
  QVariantList m_topProducts;
};

#endif // SALESMODEL_H
