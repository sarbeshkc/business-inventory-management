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
                height: 50
                color: index % 2 === 0 ? "#2c3137" : "#252a31"

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    Text { text: Qt.formatDateTime(model.saleDate, "yyyy-MM-dd hh:mm"); color: "white"; Layout.preferredWidth: 150 }
                    Text { text: model.itemName || ""; color: "white"; Layout.fillWidth: true }
                    Text { text: model.quantity !== undefined ? model.quantity : ""; color: "white"; Layout.preferredWidth: 80 }
                    Text { text: model.price !== undefined ? "$" + model.price.toFixed(2) : ""; color: "white"; Layout.preferredWidth: 80 }
                    Text { text: model.totalPrice !== undefined ? "$" + model.totalPrice.toFixed(2) : ""; color: "white"; Layout.preferredWidth: 100 }
                }
            }
        }
    }

    Dialog {
        id: addSaleDialog
        title: "Add New Sale"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        ColumnLayout {
            spacing: 10
            width: 300

            ComboBox {
                id: itemComboBox
                model: inventoryModel
                textRole: "name"
                valueRole: "id"
                Layout.fillWidth: true
            }

            SpinBox {
                id: quantityField
                from: 1
                to: 1000000
                Layout.fillWidth: true
            }

            TextField {
                id: priceField
                placeholderText: "Price"
                validator: DoubleValidator { bottom: 0; decimals: 2 }
                Layout.fillWidth: true
            }

            TextField {
                id: categoryField
                placeholderText: "Category"
                Layout.fillWidth: true
            }

            TextField {
                id: supplierNameField
                placeholderText: "Supplier Name"
                Layout.fillWidth: true
            }

            TextField {
                id: supplierAddressField
                placeholderText: "Supplier Address"
                Layout.fillWidth: true
            }
        }

        onAccepted: {
            salesModel.addSale(
                itemComboBox.currentValue,
                quantityField.value,
                parseFloat(priceField.text),
                categoryField.text,
                supplierNameField.text,
                supplierAddressField.text
            )
            quantityField.value = 1
            priceField.text = ""
            categoryField.text = ""
            supplierNameField.text = ""
            supplierAddressField.text = ""
        }
    }
}
