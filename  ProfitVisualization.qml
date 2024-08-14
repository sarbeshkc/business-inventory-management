import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    width: 600
    height: 300

    property var monthlyData: []
    property double maxValue: 0

    onMonthlyDataChanged: {
        canvas.requestPaint()
    }

    Component.onCompleted: {
        calculateMaxValue()
    }

    function calculateMaxValue() {
        maxValue = 0
        for (var i = 0; i < monthlyData.length; i++) {
            var revenue = Math.abs(monthlyData[i].revenue)
            var cost = Math.abs(monthlyData[i].cost)
            var profit = Math.abs(monthlyData[i].profit)
            maxValue = Math.max(maxValue, revenue, cost, profit)
        }
    }

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)

            var barWidth = width / (monthlyData.length * 3 + (monthlyData.length - 1))
            var spacing = barWidth / 2

            for (var i = 0; i < monthlyData.length; i++) {
                var x = i * (barWidth * 3 + spacing)
                
                // Revenue bar
                ctx.fillStyle = "#4CAF50"
                var revenueHeight = (monthlyData[i].revenue / maxValue) * height
                ctx.fillRect(x, height - revenueHeight, barWidth, revenueHeight)

                // Cost bar
                ctx.fillStyle = "#F44336"
                var costHeight = (monthlyData[i].cost / maxValue) * height
                ctx.fillRect(x + barWidth, height - costHeight, barWidth, costHeight)

                // Profit bar
                ctx.fillStyle = monthlyData[i].profit >= 0 ? "#2196F3" : "#FF9800"
                var profitHeight = (Math.abs(monthlyData[i].profit) / maxValue) * height
                ctx.fillRect(x + barWidth * 2, height - profitHeight, barWidth, profitHeight)

                // Month label
                ctx.fillStyle = "white"
                ctx.font = "12px Arial"
                ctx.textAlign = "center"
                ctx.fillText(monthlyData[i].month, x + barWidth * 1.5, height - 5)
            }
        }
    }

    // Legend
    Row {
        anchors.top: parent.top
        anchors.right: parent.right
        spacing: 10

        Repeater {
            model: [
                {color: "#4CAF50", label: "Revenue"},
                {color: "#F44336", label: "Cost"},
                {color: "#2196F3", label: "Profit"},
                {color: "#FF9800", label: "Loss"}
            ]

            delegate: Row {
                spacing: 5
                Rectangle {
                    width: 16
                    height: 16
                    color: modelData.color
                }
                Text {
                    text: modelData.label
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }
}
