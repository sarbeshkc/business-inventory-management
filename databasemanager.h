#pragma once
#include <QObject>
#include <QSqlDatabase>

class DatabaseManager : public QObject {
  Q_OBJECT

public:
  explicit DatabaseManager(QObject *parent = nullptr);
  ~DatabaseManager();

  bool initialize();
  QSqlDatabase database() const;

signals:
  void errorOccurred(const QString &error);

private:
  bool createTables();

  QSqlDatabase m_db;
};
