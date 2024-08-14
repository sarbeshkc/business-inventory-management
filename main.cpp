#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "databasemanager.h"
#include "inventorymodel.h"
#include "salesmodel.h"
#include "userdashboard.h"
#include "usermodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DatabaseManager dbManager;
    if (!dbManager.initialize()) {
        qCritical() << "Failed to initialize database";
        return -1;
    }

    InventoryModel inventoryModel(&dbManager);
    SalesModel salesModel(&dbManager);
    UserModel userModel(&dbManager, &inventoryModel, &salesModel);
    UserDashboard userDashboard(&dbManager, &inventoryModel, &salesModel);

    QObject::connect(&userModel, &UserModel::loginStatusChanged, [&]() {
        if (userModel.isLoggedIn()) {
            qDebug() << "User logged in, setting user ID for dashboard";
            userDashboard.setUserId(userModel.currentUserId());
        } else {
            qDebug() << "User logged out, clearing dashboard";
            userDashboard.setUserId(-1);
        }
    });

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("userModel", &userModel);
    engine.rootContext()->setContextProperty("inventoryModel", &inventoryModel);
    engine.rootContext()->setContextProperty("salesModel", &salesModel);
    engine.rootContext()->setContextProperty("userDashboard", &userDashboard);

    const QUrl url(QStringLiteral("../../Demo/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
