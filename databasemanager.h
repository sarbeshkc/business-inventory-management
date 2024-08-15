#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool initialize();
    QSqlDatabase database() const;

signals:
    void errorOccurred(const QString &error);

private:
    QSqlDatabase m_db;
    bool createTables();
};

#endif // DATABASEMANAGER_H
