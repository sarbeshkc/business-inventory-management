import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        RowLayout {
            Layout.fillWidth: true

        //    Button {
        //        text: "Menu"
         //       onClicked: sideBar.open()
          //  }

            Text {
                text: "Welcome, " + userModel.currentUser
                font.pixelSize: 24
                font.bold: true
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }
        }

        // Inventory Summary
        GroupBox {
            title: "Inventory Summary"
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent

                Text {
                    text: "Total Items: " + inventoryModel.totalItems
                    font.pixelSize: 16
                }

                Text {
                    text: "Low Stock Items: " + inventoryModel.lowStockItems
                    font.pixelSize: 16
                }
            }
        }

        // Sales Summary
        GroupBox {
            title: "Sales Summary"
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent

                Text {
                    text: "Total Sales: " + salesModel.totalSales
                    font.pixelSize: 16
                }

                Text {
                    text: "Revenue This Month: $" + salesModel.revenueThisMonth.toFixed(2)
                    font.pixelSize: 16
                }
            }
        }

        // Quick Actions
        GroupBox {
            title: "Quick Actions"
            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent
                spacing: 10

                Button {
                    text: "Add Inventory"
                    Layout.fillWidth: true
                    onClicked: stackView.push("InventoryView.qml")
                }

                Button {
                    text: "Record Sale"
                    Layout.fillWidth: true
                    onClicked: stackView.push("SalesView.qml")
                }

                Button {
                    text: "View Analytics"
                    Layout.fillWidth: true
                    onClicked: stackView.push("AnalyticsView.qml")
                }
            }
        }
    }

    Component.onCompleted: {
        inventoryModel.refresh()
        salesModel.refresh()
    }
}
