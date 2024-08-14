import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Text {
                text: "Sales Management"
                font.pixelSize: 24
                font.bold: true
                color: "white"
            }

            Item { Layout.fillWidth: true }

            TextField {
                id: searchField
                placeholderText: "Search sales..."
                Layout.preferredWidth: 200
                onTextChanged: salesModel.searchSales(text)
            }

            Button {
                text: "Add Sale"
                onClicked: addSaleDialog.open()
            }
        }

        ListView {
            id: salesListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: salesModel
            delegate: Rectangle {
                width: salesListView.width
                height: 60
                color: index % 2 === 0 ? "#2c3137" : "#252a31"

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    Text { text: Qt.formatDateTime(model.saleDate, "yyyy-MM-dd hh:mm"); color: "#a0a0a0"; font.pixelSize: 14; Layout.preferredWidth: 150 }
                    Text { text: model.itemName || ""; color: "white"; font.pixelSize: 16; Layout.fillWidth: true }
                    Text { text: model.quantity !== undefined ? model.quantity : ""; color: "white"; font.pixelSize: 16; Layout.preferredWidth: 80 }
                    Text { text: model.price !== undefined ? "$" + model.price.toFixed(2) : ""; color: "#4CAF50"; font.pixelSize: 16; Layout.preferredWidth: 100 }
                    Text { text: model.totalPrice !== undefined ? "$" + model.totalPrice.toFixed(2) : ""; color: "#4CAF50"; font.bold: true; font.pixelSize: 16; Layout.preferredWidth: 120 }
                }
            }
        }
    }

    Dialog {
        id: addSaleDialog
        title: "Add New Sale"
        modal: true

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: 400

        contentItem: ColumnLayout {
            spacing: 20

            GridLayout {
                columns: 2
                columnSpacing: 10
                rowSpacing: 10

                Label { text: "Item:"; color: "white" }
                ComboBox {
                    id: itemComboBox
                    model: inventoryModel
                    textRole: "name"
                    valueRole: "id"
                    Layout.fillWidth: true
                }

                Label { text: "Quantity:"; color: "white" }
                SpinBox {
                    id: quantityField
                    from: 1
                    to: 1000000
                    editable: true
                }

                Label { text: "Price:"; color: "white" }
                TextField {
                    id: priceField
                    Layout.fillWidth: true
                    placeholderText: "Enter price"
                    validator: DoubleValidator { bottom: 0; decimals: 2 }
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight
                spacing: 10

                Button {
                    text: "Cancel"
                    onClicked: addSaleDialog.close()
                }

                Button {
                    text: "Add Sale"
                    enabled: itemComboBox.currentIndex !== -1 && priceField.text !== ""
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
                }
            }
        }
    }
}
