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
                text: "Sales Management"
                font.pixelSize: 28
                font.bold: true
                color: "#ffffff"
            }

            Item { Layout.fillWidth: true }

            Rectangle {
                Layout.preferredWidth: 240
                Layout.preferredHeight: 40
                color: "#2c2c2c"
                radius: 20

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 5

                    Text {
                        text: "🔍"
                        font.pixelSize: 18
                        color: "#808080"
                    }

                    TextField {
                        id: searchField
                        placeholderText: "Search sales..."
                        Layout.fillWidth: true
                        background: Item {}
                        color: "#ffffff"
                        placeholderTextColor: "#808080"
                        onTextChanged: salesModel.searchSales(text)
                    }
                }
            }

            Button {
                text: "Add Sale"
                onClicked: addSaleDialog.open()
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

        ListView {
            id: salesListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: salesModel
            spacing: 10
            delegate: Rectangle {
                width: salesListView.width
                height: 70
                color: "#2c2c2c"
                radius: 10

                Rectangle {
                    width: 4
                    height: parent.height
                    color: "#4CAF50"
                    anchors.left: parent.left
                    radius: 2
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 15
                    spacing: 15

                    Text { 
                        text: Qt.formatDateTime(model.saleDate, "MMM dd, yyyy\nhh:mm ap")
                        color: "#a0a0a0"
                        font.pixelSize: 14
                        Layout.preferredWidth: 120
                    }
                    Text { 
                        text: model.itemName || ""
                        color: "#ffffff"
                        font.pixelSize: 16
                        Layout.fillWidth: true
                    }
                    Text { 
                        text: model.quantity !== undefined ? model.quantity : ""
                        color: "#ffffff"
                        font.pixelSize: 16
                        Layout.preferredWidth: 80
                    }
                    Text { 
                        text: model.price !== undefined ? "$" + model.price.toFixed(2) : ""
                        color: "#4CAF50"
                        font.pixelSize: 16
                        Layout.preferredWidth: 100
                    }
                    Text { 
                        text: model.totalPrice !== undefined ? "$" + model.totalPrice.toFixed(2) : ""
                        color: "#4CAF50"
                        font.bold: true
                        font.pixelSize: 16
                        Layout.preferredWidth: 120
                    }
                }
            }

            add: Transition {
                NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 400 }
                NumberAnimation { property: "scale"; from: 0.9; to: 1.0; duration: 400 }
            }

            displaced: Transition {
                NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutQuad }
            }
        }
    }

    Dialog {
        id: addSaleDialog
        title: "Add New Sale"
        modal: true

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: 450
        height: 400

        background: Rectangle {
            color: "#2c2c2c"
            radius: 10
        }

        header: Rectangle {
            color: "#1e1e1e"
            height: 50
            radius: 10

            Text {
                anchors.centerIn: parent
                text: addSaleDialog.title
                color: "#ffffff"
                font.pixelSize: 18
                font.bold: true
            }
        }

        contentItem: ColumnLayout {
            spacing: 20
            anchors.margins: 20

            GridLayout {
                columns: 2
                columnSpacing: 15
                rowSpacing: 15

                Label { text: "Item:"; color: "#ffffff" }
                ComboBox {
                    id: itemComboBox
                    model: inventoryModel
                    textRole: "name"
                    valueRole: "id"
                    Layout.fillWidth: true
                    onCurrentIndexChanged: {
                        if (currentIndex >= 0) {
                            var item = inventoryModel.getItemDetails(currentValue)
                            quantityField.to = item.quantity
                            priceField.text = item.price.toFixed(2)
                        }
                    }
                }

                Label { text: "Quantity:"; color: "#ffffff" }
                SpinBox {
                    id: quantityField
                    from: 1
                    to: 1000000
                    editable: true
                    Layout.fillWidth: true
                }

                Label { text: "Price:"; color: "#ffffff" }
                TextField {
                    id: priceField
                    Layout.fillWidth: true
                    placeholderText: "Enter price"
                    validator: DoubleValidator { bottom: 0; decimals: 2 }
                    color: "#ffffff"
                }

                Label { text: "Total Price:"; color: "#ffffff" }
                Text {
                    id: totalPriceText
                    color: "#4CAF50"
                    font.pixelSize: 18
                    font.bold: true
                    text: "$" + (quantityField.value * parseFloat(priceField.text || "0")).toFixed(2)
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight
                spacing: 15

                Button {
                    text: "Cancel"
                    onClicked: addSaleDialog.close()
                    background: Rectangle {
                        color: parent.pressed ? "#505050" : "#404040"
                        radius: 5
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "#ffffff"
                        font.pixelSize: 14
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: 100
                }

                Button {
                    text: "Add Sale"
                    enabled: itemComboBox.currentIndex !== -1 && quantityField.value > 0 && priceField.text !== ""
                    onClicked: {
                        salesModel.addSale(
                            itemComboBox.currentValue,
                            quantityField.value,
                            parseFloat(priceField.text)
                        )
                        addSaleDialog.close()
                        itemComboBox.currentIndex = -1
                        quantityField.value = 1
                        priceField.text = ""
                    }
                    background: Rectangle {
                        color: parent.enabled ? (parent.pressed ? "#1e90ff" : "#2196f3") : "#808080"
                        radius: 5
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "#ffffff"
                        font.pixelSize: 14
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: 100
                }
            }
        }
    }
}
