import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtCharts 2.15

Item {
    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        RowLayout {
            Layout.fillWidth: true

            Button {
                text: "Menu"
                onClicked: drawer.open()
            }

            Text {
                text: "Welcome, " + userModel.currentUser
                font.pixelSize: 24
                font.bold: true
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }
        }

        // Summary Cards
        Flow {
            Layout.fillWidth: true
            spacing: 20

            Repeater {
                model: [
                    { title: "Total Items", value: inventoryModel.totalItems },
                    { title: "Low Stock Items", value: inventoryModel.lowStockItems },
                    { title: "Total Sales", value: salesModel.totalSales },
                    { title: "Revenue This Month", value: "$" + salesModel.revenueThisMonth.toFixed(2) }
                ]

                delegate: Rectangle {
                    width: 200
                    height: 100
                    color: "#e0e0e0"
                    radius: 10

                    ColumnLayout {
                        anchors.centerIn: parent

                        Text {
                            text: modelData.title
                            font.pixelSize: 16
                            Layout.alignment: Qt.AlignHCenter
                        }

                        Text {
                            text: modelData.value
                            font.pixelSize: 24
                            font.bold: true
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                }
            }
        }

        // Charts
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 20

            // Sales Distribution Pie Chart
            ChartView {
                title: "Sales Distribution"
                Layout.fillWidth: true
                Layout.fillHeight: true
                antialiasing: true

                PieSeries {
                    id: pieSeries
                    size: 0.8

                    Connections {
                        target: salesModel
                        function onDataChanged() {
                            pieSeries.clear();
                            var distribution = salesModel.getSalesDistribution();
                            for (var i = 0; i < distribution.length; ++i) {
                                pieSeries.append(distribution[i].name, distribution[i].revenue);
                            }
                        }
                    }
                }
            }

            // Monthly Revenue Line Chart
            ChartView {
                title: "Monthly Revenue"
                Layout.fillWidth: true
                Layout.fillHeight: true
                antialiasing: true

                LineSeries {
                    id: lineSeries
                    axisX: DateTimeAxis {
                        format: "MMM yyyy"
                        tickCount: 6
                    }
                    axisY: ValueAxis {
                        min: 0
                        // max will be set dynamically
                    }

                    Connections {
                        target: salesModel
                        function onDataChanged() {
                            lineSeries.clear();
                            var monthlySales = salesModel.getMonthlySales();
                            var maxRevenue = 0;
                            for (var i = 0; i < monthlySales.length; ++i) {
                                var date = new Date(monthlySales[i].month);
                                lineSeries.append(date.getTime(), monthlySales[i].revenue);
                                if (monthlySales[i].revenue > maxRevenue) {
                                    maxRevenue = monthlySales[i].revenue;
                                }
                            }
                            lineSeries.axisY.max = maxRevenue * 1.1; // Set max to 110% of highest value
                        }
                    }
                }
            }
        }

        // Quick Actions
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "Manage Inventory"
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

    Component.onCompleted: {
        inventoryModel.refresh()
        salesModel.refresh()
    }
}
