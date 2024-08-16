import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        color: "#1e1e1e"
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        RowLayout {
            Layout.fillWidth: true
            spacing: 15

            Text {
                text: "Analytics Dashboard"
                font.pixelSize: 28
                font.bold: true
                color: "#ffffff"
            }

            Item { Layout.fillWidth: true }

            Button {
                text: "Refresh Data"
                onClicked: userDashboard.refresh()
                background: Rectangle {
                    color: parent.pressed ? "#1e90ff" : "#2196f3"
                    radius: 20
                }
                contentItem: Text {
                    text: parent.text
                    color: "#ffffff"
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                Layout.preferredHeight: 40
                Layout.preferredWidth: 120
            }
        }

        GridLayout {
            Layout.fillWidth: true
            columns: {
                if (root.width > 1200) return 4;
                if (root.width > 800) return 3;
                if (root.width > 600) return 2;
                return 1;
            }
            rowSpacing: 20
            columnSpacing: 20

            Repeater {
                model: [
                    {title: "Total Revenue", value: "$" + userDashboard.totalRevenue.toFixed(2), icon: "₿", color: "#4CAF50"},
                    {title: "Total Inventory Value", value: "$" + userDashboard.totalInventoryValue.toFixed(2), icon: "📦", color: "#2196F3"},
                    {title: "Total Sales", value: userDashboard.totalSales, icon: "🛒", color: "#FFC107"},
                    {title: "Profit Margin", value: userDashboard.profitMargin.toFixed(2) + "%", icon: "📈", color: "#9C27B0"}
                ]

                delegate: Rectangle {
                    Layout.fillWidth: true
                    height: 120
                    color: "#2c2c2c"
                    radius: 10

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 15
                        spacing: 15

                        Rectangle {
                            width: 50
                            height: 50
                            radius: 25
                            color: modelData.color

                            Text {
                                anchors.centerIn: parent
                                text: modelData.icon
                                font.pixelSize: 24
                                color: "#ffffff"
                            }
                        }

                        ColumnLayout {
                            spacing: 5

                            Text {
                                text: modelData.title
                                font.pixelSize: 16
                                color: "#a0a0a0"
                            }

                            Text {
                                text: modelData.value
                                font.pixelSize: 24
                                font.bold: true
                                color: "#ffffff"
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#2c2c2c"
            radius: 10

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15

                Text {
                    text: "Recent Activities"
                    font.pixelSize: 24
                    font.bold: true
                    color: "#ffffff"
                }

                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: userDashboard.recentActivities
                    clip: true
                    spacing: 10

                    delegate: Rectangle {
                        width: parent.width
                        height: 70
                        color: "#1e1e1e"
                        radius: 5

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 10
                            spacing: 15

                            Rectangle {
                                width: 40
                                height: 40
                                radius: 20
                                color: modelData.type === "Sale" ? "#4CAF50" : "#FFC107"

                                Text {
                                    anchors.centerIn: parent
                                    text: modelData.type === "Sale" ? "S" : "P"
                                    color: "#ffffff"
                                    font.pixelSize: 18
                                    font.bold: true
                                }
                            }

                            ColumnLayout {
                                spacing: 5
                                Text { text: modelData.itemName; color: "#ffffff"; font.pixelSize: 16; font.bold: true }
                                Text { text: Qt.formatDateTime(modelData.date, "MMM dd, yyyy hh:mm ap"); color: "#a0a0a0"; font.pixelSize: 14 }
                            }

                            Item { Layout.fillWidth: true }

                            ColumnLayout {
                                spacing: 5
                                Text { text: modelData.quantity + " units"; color: "#ffffff"; font.pixelSize: 14; horizontalAlignment: Text.AlignRight }
                                Text { text: "$" + modelData.price.toFixed(2); color: "#4CAF50"; font.pixelSize: 16; font.bold: true; horizontalAlignment: Text.AlignRight }
                            }
                        }
                    }

                    ScrollBar.vertical: ScrollBar {
                        active: true
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        console.log("AnalyticsView loaded")
        userDashboard.refresh()
    }
}
