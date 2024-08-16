import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#1a237e" }
            GradientStop { position: 1.0; color: "#0d47a1" }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Text {
            text: "Dashboard"
            font.pixelSize: 32
            font.bold: true
            color: "#ffffff"
        }

        // Summary Cards
        GridLayout {
            Layout.fillWidth: true
            columns: 2
            rowSpacing: 15
            columnSpacing: 15

            Repeater {
                model: [
                    {title: "Total Inventory Items", value: userDashboard.totalInventoryItems, color: "#4caf50"},
                    {title: "Low Stock Items", value: userDashboard.lowStockItems, color: "#ff9800"},
                    {title: "Expiring Items", value: userDashboard.expiringItems, color: "#f44336"},
                    {title: "Total Sales", value: userDashboard.totalSales, color: "#2196f3"},
                    {title: "Total Revenue", value: "$" + userDashboard.totalRevenue.toFixed(2), color: "#9c27b0"}
                ]

                delegate: Rectangle {
                    Layout.fillWidth: true
                    height: 100
                    radius: 10
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: Qt.lighter(modelData.color, 1.5) }
                        GradientStop { position: 1.0; color: modelData.color }
                    }
                    border.color: Qt.darker(modelData.color, 1.2)
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 15
                        spacing: 5

                        Text {
                            text: modelData.title
                            font.pixelSize: 16
                            color: "white"
                        }

                        Text {
                            text: modelData.value
                            font.pixelSize: 24
                            font.bold: true
                            color: "white"
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
                color: "#ffffff"
                radius: 10
                opacity: 0.9
                border.color: "#e0e0e0"
                border.width: 1
            }

            ListView {
                anchors.fill: parent
                model: userDashboard.recentActivities
                clip: true
                delegate: ItemDelegate {
                    width: parent.width
                    height: 50
                    contentItem: RowLayout {
                        Text { text: modelData.date.toLocaleString(Qt.locale(), "yyyy-MM-dd hh:mm"); color: "#333333"; Layout.preferredWidth: 150 }
                        Text { text: modelData.type; color: "#333333"; Layout.preferredWidth: 100 }
                        Text { text: modelData.itemName; color: "#333333"; Layout.fillWidth: true }
                        Text { text: modelData.quantity; color: "#333333"; Layout.preferredWidth: 50 }
                        Text { text: "$" + modelData.price.toFixed(2); color: "#333333"; Layout.preferredWidth: 80 }
                    }

                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 1
                        color: "#e0e0e0"
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

        background: Rectangle {
            color: "#ffffff"
            radius: 10
            border.color: "#e0e0e0"
            border.width: 1
        }

        header: Rectangle {
            color: "#f44336"
            height: 50
            radius: 10
            Text {
                anchors.centerIn: parent
                text: expiryNotificationDialog.title
                color: "white"
                font.pixelSize: 18
                font.bold: true
            }
        }

        contentItem: ColumnLayout {
            spacing: 10
            Text {
                text: "The following item is nearing its expiry date:"
                color: "#333333"
                font.pixelSize: 16
            }
            Text {
                text: expiryNotificationDialog.itemName
                color: "#f44336"
                font.pixelSize: 20
                font.bold: true
            }
            Text {
                text: "Expiry Date: " + Qt.formatDate(expiryNotificationDialog.expiryDate, "yyyy-MM-dd")
                color: "#333333"
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
