
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Text {
            text: "Welcome, " + userModel.currentUser
            font.pixelSize: 24
            font.bold: true
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

        // Top Items List
        GroupBox {
            title: "Top 5 Items by Quantity"
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                anchors.fill: parent
                model: inventoryModel.getTopItems(5)
                delegate: ItemDelegate {
                    width: parent.width
                    contentItem: RowLayout {
                        Text { 
                            text: modelData.name
                            Layout.fillWidth: true
                        }
                        Text { 
                            text: modelData.quantity
                            Layout.preferredWidth: 100
                        }
                    }
                }
            }
        }

        // Navigation Buttons
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "Manage Inventory"
                onClicked: stackView.push("InventoryView.qml")
                Layout.fillWidth: true
            }

            Button {
                text: "Manage Sales"
                onClicked: stackView.push("SalesView.qml")
                Layout.fillWidth: true
            }
        }
    }

    Component.onCompleted: {
        console.log("Dashboard view loaded")
        inventoryModel.refresh()
    }

    Connections {
        target: inventoryModel
        function onDataChanged() {
            console.log("Inventory data changed")
        }
    }
}
