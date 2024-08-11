import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: inventoryView

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
                text: "Inventory Management"
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
                placeholderText: "Search items..."
                Layout.fillWidth: true
                onTextChanged: inventoryModel.searchItems(text)
            }
            ComboBox {
                id: sortComboBox
                model: ["Name", "Quantity", "Price"]
                onCurrentTextChanged: inventoryModel.sortItems(currentText, Qt.AscendingOrder)
            }
            Button {
                text: "Add Item"
                onClicked: addItemDialog.open()
            }
        }

        TableView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: inventoryModel

            TableViewColumn {
                title: "Name"
                role: "name"
                width: 200
            }
            TableViewColumn {
                title: "Quantity"
                role: "quantity"
                width: 100
                delegate: SpinBox {
                    value: styleData.value
                    onValueModified: inventoryModel.updateItem(styleData.row, "quantity", value)
                }
            }
            
 TableViewColumn {
                title: "Actions"
                width: 100
                delegate: Button {
                    text: "Delete"
                    onClicked: deleteConfirmationDialog.open()

                    Dialog {
                        id: deleteConfirmationDialog
                        title: "Confirm Deletion"
                        standardButtons: Dialog.Yes | Dialog.No
                        modal: true

                        Text {
                            text: "Are you sure you want to delete this item?"
                        }

                        onAccepted: {
                            inventoryModel.deleteItem(styleData.row)
                        }
                    }
                }
            }
        }
    }

    Dialog {
        id: addItemDialog
        title: "Add New Item"
        standardButtons: Dialog.Ok | Dialog.Cancel
        modal: true
        anchors.centerIn: parent
        width: 300

        onAccepted: {
            if (nameField.text && quantityField.text && priceField.text) {
                inventoryModel.addItem(nameField.text, parseInt(quantityField.text), parseFloat(priceField.text))
                nameField.text = ""
                quantityField.text = ""
                priceField.text = ""
            } else {
                errorDialog.open()
            }
        }

        contentItem: ColumnLayout {
            spacing: 10
            TextField {
                id: nameField
                placeholderText: "Item Name"
                Layout.fillWidth: true
            }
            TextField {
                id: quantityField
                placeholderText: "Quantity"
                validator: IntValidator { bottom: 0 }
                Layout.fillWidth: true
            }
            TextField {
                id: priceField
                placeholderText: "Price"
                validator: DoubleValidator { bottom: 0; decimals: 2 }
                Layout.fillWidth: true
            }
        }
    }

    Dialog {
        id: errorDialog
        title: "Error"
        standardButtons: Dialog.Ok
        modal: true

        Text {
            text: "Please fill in all fields."
        }
    }

    Component.onCompleted: {
        console.log("Inventory view loaded")
        inventoryModel.refresh()
    }
}

