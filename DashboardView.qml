import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Text {
            text: "Dashboard"
            font.pixelSize: 24
            font.bold: true
            color: "white"
        }

        // Summary Cards
        GridLayout {
            Layout.fillWidth: true
            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            Repeater {
                model: [
                    {title: "Total Inventory Items", value: userDashboard.totalInventoryItems},
                    {title: "Low Stock Items", value: userDashboard.lowStockItems},
                    {title: "Expiring Items", value: userDashboard.expiringItems},
                    {title: "Total Sales", value: userDashboard.totalSales},
                    {title: "Total Revenue", value: "$" + userDashboard.totalRevenue.toFixed(2)}
                ]

                delegate: Rectangle {
                    Layout.fillWidth: true
                    height: 80
                    color: "#2c3137"
                    radius: 5

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 5

                        Text {
                            text: modelData.title
                            font.pixelSize: 14
                            color: "white"
                        }

                        Text {
                            text: modelData.value
                            font.pixelSize: 18
                            font.bold: true
                            color: modelData.title === "Expiring Items" && modelData.value > 0 ? "#FF9800" : "white"
                        }
                    }
                }
            }
        }

        // Recent Activities
        GroupBox {
            title: "Recent Activities"
            Layout.fillWidth: true
            Layout.fillHeight: true

            background: Rectangle {
                color: "#2c3137"
                border.color: "#3a3f48"
            }

            ListView {
                anchors.fill: parent
                model: userDashboard.recentActivities
                clip: true
                delegate: ItemDelegate {
                    width: parent.width
                    contentItem: RowLayout {
                        Text { text: modelData.date.toLocaleString(Qt.locale(), "yyyy-MM-dd hh:mm"); color: "white"; Layout.preferredWidth: 150 }
                        Text { text: modelData.type; color: "white"; Layout.preferredWidth: 100 }
                        Text { text: modelData.itemName; color: "white"; Layout.fillWidth: true }
                        Text { text: modelData.quantity; color: "white"; Layout.preferredWidth: 50 }
                        Text { text: "$" + modelData.price.toFixed(2); color: "white"; Layout.preferredWidth: 80 }
                    }
                }
            }
        }
    }

    Connections {
        target: userDashboard
        function onItemNearExpiry(itemId, itemName, expiryDate) {
            expiryNotificationDialog.itemName = itemName
            expiryNotificationDialog.expiryDate = expiryDate
            expiryNotificationDialog.open()
        }
    }

    Dialog {
        id: expiryNotificationDialog
        title: "Item Nearing Expiry"
        modal: true
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        property string itemName: ""
        property date expiryDate

        contentItem: ColumnLayout {
            Text {
                text: "The following item is nearing its expiry date:"
                color: "white"
                font.pixelSize: 16
            }
            Text {
                text: expiryNotificationDialog.itemName
                color: "#FF9800"
                font.pixelSize: 18
                font.bold: true
            }
            Text {
                text: "Expiry Date: " + Qt.formatDate(expiryNotificationDialog.expiryDate, "yyyy-MM-dd")
                color: "white"
                font.pixelSize: 16
            }
        }

        standardButtons: Dialog.Ok
    }

    Component.onCompleted: {
        console.log("DashboardView loaded")
        userDashboard.refresh()
    }
}
