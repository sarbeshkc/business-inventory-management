#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include "databasemanager.h"
#include "inventorymodel.h"
#include "salesmodel.h"

class UserModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isLoggedIn READ isLoggedIn NOTIFY loginStatusChanged)
    Q_PROPERTY(QString currentUser READ currentUser NOTIFY loginStatusChanged)

public:
    explicit UserModel(DatabaseManager *dbManager, InventoryModel *invModel, SalesModel *salesModel, QObject *parent = nullptr);

    Q_INVOKABLE bool login(const QString &username, const QString &password);
    Q_INVOKABLE bool signup(const QString &username, const QString &password, const QString &email);
    Q_INVOKABLE void logout();

    bool isLoggedIn() const;
    QString currentUser() const;
    int currentUserId() const;

signals:
    void errorOccurred(const QString &error);
    void loginStatusChanged();
    void loginSuccessful();

private:
    DatabaseManager *m_dbManager;
    InventoryModel *m_invModel;
    SalesModel *m_salesModel;
    bool m_isLoggedIn;
    QString m_currentUser;
    int m_currentUserId;
};

#endif // USERMODEL_H
