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
        emit errorOccurred(tr("Failed to open database: %1").arg(m_db.lastError().text()));
        return false;
    }

    return createTables();
}

QSqlDatabase DatabaseManager::database() const {
    return m_db;
}

bool DatabaseManager::createTables() {
    QSqlQuery query(m_db);

    // Create Users table
    if (!query.exec("CREATE TABLE IF NOT EXISTS Users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "username TEXT UNIQUE NOT NULL, "
                    "password_hash TEXT NOT NULL, "
                    "email TEXT UNIQUE NOT NULL, "
                    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP)")) {
        emit errorOccurred(tr("Failed to create Users table: %1").arg(query.lastError().text()));
        return false;
    }

    // Create Inventory table
    if (!query.exec("CREATE TABLE IF NOT EXISTS Inventory ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "user_id INTEGER NOT NULL, "
                    "name TEXT NOT NULL, "
                    "category TEXT NOT NULL, "
                    "quantity INTEGER NOT NULL DEFAULT 0, "
                    "price REAL NOT NULL, "
                    "last_updated DATETIME DEFAULT CURRENT_TIMESTAMP, "
                    "FOREIGN KEY(user_id) REFERENCES Users(id))")) {
        emit errorOccurred(tr("Failed to create Inventory table: %1").arg(query.lastError().text()));
        return false;
    }

    // Create Sales table
    if (!query.exec("CREATE TABLE IF NOT EXISTS Sales ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "user_id INTEGER NOT NULL, "
                    "item_id INTEGER NOT NULL, "
                    "quantity INTEGER NOT NULL, "
                    "price REAL NOT NULL, "
                    "total_price REAL NOT NULL, "
                    "sale_date DATETIME DEFAULT CURRENT_TIMESTAMP, "
                    "category TEXT NOT NULL, "
                    "supplier_name TEXT, "
                    "supplier_address TEXT, "
                    "FOREIGN KEY(user_id) REFERENCES Users(id), "
                    "FOREIGN KEY(item_id) REFERENCES Inventory(id))")) {
        emit errorOccurred(tr("Failed to create Sales table: %1").arg(query.lastError().text()));
        return false;
    }

    // Create indexes for better performance
    if (!query.exec("CREATE INDEX IF NOT EXISTS idx_inventory_user_id ON Inventory(user_id)")) {
        qWarning() << "Failed to create index on Inventory table:" << query.lastError().text();
    }
    if (!query.exec("CREATE INDEX IF NOT EXISTS idx_sales_user_id ON Sales(user_id)")) {
        qWarning() << "Failed to create index on Sales table (user_id):" << query.lastError().text();
    }
    if (!query.exec("CREATE INDEX IF NOT EXISTS idx_sales_item_id ON Sales(item_id)")) {
        qWarning() << "Failed to create index on Sales table (item_id):" << query.lastError().text();
    }

    return true;
}
