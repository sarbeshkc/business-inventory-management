import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property var lowStockItems: []

    Popup {
        id: notificationPopup
        width: 300
        height: 400
        x: parent.width - width - 20
        y: 60
        modal: false
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        background: Rectangle {
            color: "#2c3137"
            border.color: "#F44336"
            radius: 5
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 10

            RowLayout {
                Layout.fillWidth: true

                Text {
                    text: "Low Stock Notifications"
                    font.pixelSize: 18
                    font.bold: true
                    color: "white"
                }

                Item { Layout.fillWidth: true }

                Button {
                    text: "X"
                    onClicked: notificationPopup.close()
                    background: Rectangle {
                        color: "transparent"
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        font.pixelSize: 16
                    }
                }
            }

            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: lowStockItems
                clip: true
                delegate: ItemDelegate {
                    width: parent.width
                    contentItem: RowLayout {
                        Text { 
                            text: modelData.name
                            color: "white"
                            font.pixelSize: 14
                            Layout.fillWidth: true
                        }
                        Text { 
                            text: "Quantity: " + modelData.quantity
                            color: "#F44336"
                            font.pixelSize: 14
                        }
                    }
                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }
        }
    }

    function showNotifications() {
        lowStockItems = userDashboard.lowStockItemsList
        if (lowStockItems.length > 0) {
            notificationPopup.open()
        }
    }

    Connections {
        target: userDashboard
        function onLowStockItemsListChanged() {
            showNotifications()
        }
    }
}
