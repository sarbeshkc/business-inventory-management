
// databasemanager.cpp
#include "databasemanager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {}

DatabaseManager::~DatabaseManager() {
  if (m_db.isOpen()) {
    m_db.close();
  }
}

bool DatabaseManager::initialize() {
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName("business.db");

  if (!m_db.open()) {
    emit errorOccurred(
        tr("Failed to open database: %1").arg(m_db.lastError().text()));
    return false;
  }

  return createTables();
}

QSqlDatabase DatabaseManager::database() const { return m_db; }

bool DatabaseManager::createTables() {
  QSqlQuery query(m_db);

  // Create Users table
  if (!query.exec("CREATE TABLE IF NOT EXISTS Users "
                  "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "username TEXT UNIQUE, "
                  "password_hash TEXT, "
                  "email TEXT)")) {
    emit errorOccurred(
        tr("Failed to create Users table: %1").arg(query.lastError().text()));
    return false;
  }

  // Create Inventory table
  if (!query.exec("CREATE TABLE IF NOT EXISTS Inventory "
                  "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "user_id INTEGER, "
                  "name TEXT, "
                  "quantity INTEGER, "
                  "price REAL, "
                  "FOREIGN KEY(user_id) REFERENCES Users(id))")) {
    emit errorOccurred(tr("Failed to create Inventory table: %1")
                           .arg(query.lastError().text()));
    return false;
  }

  // Create Sales table
  if (!query.exec("CREATE TABLE IF NOT EXISTS Sales "
                  "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "user_id INTEGER, "
                  "item_id INTEGER, "
                  "quantity INTEGER, "
                  "total_price REAL, "
                  "sale_date DATETIME, "
                  "FOREIGN KEY(user_id) REFERENCES Users(id), "
                  "FOREIGN KEY(item_id) REFERENCES Inventory(id))")) {
    emit errorOccurred(
        tr("Failed to create Sales table: %1").arg(query.lastError().text()));
    return false;
  }

  return true;
}
