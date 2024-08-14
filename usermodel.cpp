#include "usermodel.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

UserModel::UserModel(DatabaseManager *dbManager, InventoryModel *invModel,
                     SalesModel *salesModel, QObject *parent)
    : QObject(parent), m_dbManager(dbManager), m_invModel(invModel),
      m_salesModel(salesModel), m_isLoggedIn(false), m_currentUserId(-1) {}

bool UserModel::login(const QString &username, const QString &password) {
  QSqlQuery query(m_dbManager->database());
  query.prepare(
      "SELECT id, password_hash FROM Users WHERE username = :username");
  query.bindValue(":username", username);

  if (!query.exec()) {
    emit errorOccurred("Database error: " + query.lastError().text());
    return false;
  }

  if (query.next()) {
    QString storedHash = query.value("password_hash").toString();
    QString inputHash = QString(
        QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256)
            .toHex());
    if (storedHash == inputHash) {
      m_isLoggedIn = true;
      m_currentUser = username;
      m_currentUserId = query.value("id").toInt();
      m_invModel->setUserId(m_currentUserId);
      m_salesModel->setUserId(m_currentUserId);
      emit loginStatusChanged();
      emit loginSuccessful();
      return true;
    }
  }

  emit errorOccurred("Invalid username or password");
  return false;
}

bool UserModel::signup(const QString &username, const QString &password,
                       const QString &email) {
  if (username.isEmpty() || password.isEmpty() || email.isEmpty()) {
    emit errorOccurred("All fields must be filled");
    return false;
  }

  QSqlQuery query(m_dbManager->database());
  query.prepare("SELECT username FROM Users WHERE username = :username");
  query.bindValue(":username", username);

  if (!query.exec()) {
    emit errorOccurred("Database error: " + query.lastError().text());
    return false;
  }

  if (query.next()) {
    emit errorOccurred(
        "Username already exists. Please choose a different username.");
    return false;
  }

  query.prepare("INSERT INTO Users (username, password_hash, email) VALUES "
                "(:username, :password_hash, :email)");
  query.bindValue(":username", username);
  query.bindValue(":password_hash",
                  QString(QCryptographicHash::hash(password.toUtf8(),
                                                   QCryptographicHash::Sha256)
                              .toHex()));
  query.bindValue(":email", email);

  if (query.exec()) {
    m_isLoggedIn = true;
    m_currentUser = username;
    m_currentUserId = query.lastInsertId().toInt();
    emit loginStatusChanged();
    emit loginSuccessful();
    return true;
  } else {
    emit errorOccurred("Failed to create user: " + query.lastError().text());
    return false;
  }
}

void UserModel::logout() {
  m_isLoggedIn = false;
  m_currentUser.clear();
  m_currentUserId = -1;
  emit loginStatusChanged();
}

bool UserModel::isLoggedIn() const { return m_isLoggedIn; }

QString UserModel::currentUser() const { return m_currentUser; }

int UserModel::currentUserId() const { return m_currentUserId; }
