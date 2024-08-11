import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: salesView

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        RowLayout {
            Layout.fillWidth: true

   //         Button {
     //           text: "Menu"
       //         onClicked: sideBar.open()
         //   }

            Text {
                text: "Sales Management"
                font.pixelSize: 24
                font.bold: true
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }
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
                model: ["Date", "Item", "Quantity", "Total Price", "Category", "Supplier"]
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
                width: ListView.view.width
                contentItem: RowLayout {
                    Text { 
                        text: Qt.formatDateTime(saleDate, "yyyy-MM-dd hh:mm")
                        Layout.preferredWidth: 150
                    }
                    Text { 
                        text: itemName
                        Layout.preferredWidth: 150
                    }
                    Text { 
                        text: quantity.toString()
                        Layout.preferredWidth: 80
                    }
                    Text { 
                        text: "$" + price.toFixed(2)
                        Layout.preferredWidth: 80
                    }
                    Text { 
                        text: "$" + totalPrice.toFixed(2)
                        Layout.preferredWidth: 80
                    }
                    Text { 
                        text: category
                        Layout.preferredWidth: 100
                    }
                    Text { 
                        text: supplierName
                        Layout.preferredWidth: 150
                    }
                    Text { 
                        text: supplierAddress
                        Layout.fillWidth: true
                    }
                }
            }
        }

        GroupBox {
            title: "Quick Actions"
            Layout.fillWidth: true
            RowLayout {
                anchors.fill: parent
                spacing: 10
                Button {
                    text: "Dashboard"
                    Layout.fillWidth: true
                    onClicked: stackView.push("DashboardView.qml")
                }
                Button {
                    text: "Inventory"
                    Layout.fillWidth: true
                    onClicked: stackView.push("InventoryView.qml")
                }
                Button {
                    text: "Analytics"
                    Layout.fillWidth: true
                    onClicked: stackView.push("AnalyticsView.qml")
                }
            }
        }
    }

    Dialog {
        id: addSaleDialog
        title: "Add New Sale"
        standardButtons: Dialog.Ok | Dialog.Cancel
        modal: true
        anchors.centerIn: parent
        width: 300

        onAccepted: {
            salesModel.addSale(
                itemComboBox.currentValue,
                parseInt(quantityField.text),
                parseFloat(priceField.text),
                categoryField.text,
                supplierNameField.text,
                supplierAddressField.text
            )
            itemComboBox.currentIndex = -1
            quantityField.text = ""
            priceField.text = ""
            categoryField.text = ""
            supplierNameField.text = ""
            supplierAddressField.text = ""
        }

        contentItem: ColumnLayout {
            spacing: 10
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
    }

    Component.onCompleted: {
        console.log("Sales view loaded")
        salesModel.refresh()
    }
}
