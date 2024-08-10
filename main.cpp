#include "databasemanager.h"
#include "inventorymodel.h"
#include "salesmodel.h"
#include "usermodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtChartsQml/QtChartsQml>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  DatabaseManager dbManager;
  if (!dbManager.initialize()) {
    qCritical() << "Failed to initialize database";
    return -1;
  }
  InventoryModel inventoryModel(&dbManager);
  SalesModel salesModel(&dbManager);
  UserModel userModel(&dbManager, &inventoryModel, &salesModel);

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("userModel", &userModel);
  engine.rootContext()->setContextProperty("inventoryModel", &inventoryModel);
  engine.rootContext()->setContextProperty("salesModel", &salesModel);

  const QUrl url(QStringLiteral("../../Demo/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
