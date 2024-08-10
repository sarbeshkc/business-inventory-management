import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Text {
            text: "Sales Management"
            font.pixelSize: 24
            font.bold: true
        }

        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: searchField
                placeholderText: "Search sales..."
                Layout.fillWidth: true
                onTextChanged: salesModel.searchSales(text)
            }
            ComboBox {
                id: sortComboBox
                model: ["Date", "Item", "Quantity", "Total Price"]
                onCurrentTextChanged: salesModel.sortSales(currentText, Qt.AscendingOrder)
            }
            Button {
                text: "Add Sale"
                onClicked: addSaleDialog.open()
            }
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: salesModel

            delegate: ItemDelegate {
                width: parent.width
                contentItem: RowLayout {
                    Text { 
                        text: Qt.formatDateTime(saleDate, "yyyy-MM-dd hh:mm")
                        Layout.preferredWidth: 150
                    }
                    Text { 
                        text: itemName
                        Layout.preferredWidth: 200
                    }
                    Text { 
                        text: quantity.toString()
                        Layout.preferredWidth: 100
                    }
                    Text { 
                        text: "$" + totalPrice.toFixed(2)
                        Layout.preferredWidth: 100
                    }
                }
            }
        }
    }

    Dialog {
        id: addSaleDialog
        title: "Add New Sale"
        standardButtons: Dialog.Ok | Dialog.Cancel
        modal: true

        onAccepted: {
            salesModel.addSale(itemComboBox.currentValue, parseInt(quantityField.text), parseFloat(totalPriceField.text))
            itemComboBox.currentIndex = -1
            quantityField.text = ""
            totalPriceField.text = ""
        }

        contentItem: ColumnLayout {
            ComboBox {
                id: itemComboBox
                model: inventoryModel
                textRole: "name"
                valueRole: "id"
                Layout.fillWidth: true
            }
            TextField {
                id: quantityField
                placeholderText: "Quantity"
                validator: IntValidator { bottom: 1 }
                Layout.fillWidth: true
            }
            TextField {
                id: totalPriceField
                placeholderText: "Total Price"
                validator: DoubleValidator { bottom: 0; decimals: 2 }
                Layout.fillWidth: true
            }
        }
    }

    Component.onCompleted: {
        console.log("Sales view loaded")
        salesModel.refresh()
    }
}
