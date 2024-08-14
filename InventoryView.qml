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
                text: "Inventory Management"
                font.pixelSize: 24
                font.bold: true
                color: "white"
            }

            Item { Layout.fillWidth: true }

            TextField {
                id: searchField
                placeholderText: "Search items..."
                Layout.preferredWidth: 200
                onTextChanged: inventoryModel.searchItems(text)
            }

            Button {
                text: "Add Item"
                onClicked: addItemDialog.open()
            }
        }

        ListView {
            id: inventoryListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: inventoryModel
            delegate: Rectangle {
                width: inventoryListView.width
                height: 60
                color: index % 2 === 0 ? "#2c3137" : "#252a31"

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    Text { text: model.name || ""; color: "white"; font.pixelSize: 16; Layout.fillWidth: true }
                    Text { text: model.category || ""; color: "#a0a0a0"; font.pixelSize: 14; Layout.preferredWidth: 120 }
                    Text { text: model.quantity !== undefined ? model.quantity : ""; color: "white"; font.pixelSize: 16; Layout.preferredWidth: 80 }
                    Text { text: model.price !== undefined ? "$" + model.price.toFixed(2) : ""; color: "#4CAF50"; font.pixelSize: 16; Layout.preferredWidth: 100 }
                    Text { text: model.supplierName || ""; color: "#a0a0a0"; font.pixelSize: 14; Layout.preferredWidth: 150 }

                    Button {
                        text: "Edit"
                        onClicked: {
                            editItemDialog.itemId = model.id
                            editItemDialog.nameField.text = model.name || ""
                            editItemDialog.categoryField.text = model.category || ""
                            editItemDialog.quantityField.value = model.quantity || 0
                            editItemDialog.priceField.text = model.price !== undefined ? model.price.toFixed(2) : ""
                            editItemDialog.supplierNameField.text = model.supplierName || ""
                            editItemDialog.supplierAddressField.text = model.supplierAddress || ""
                            editItemDialog.open()
                        }
                    }

                    Button {
                        text: "Delete"
                        onClicked: deleteConfirmationDialog.open()

                        Dialog {
                            id: deleteConfirmationDialog
                            title: "Confirm Deletion"
                            standardButtons: Dialog.Yes | Dialog.No
                            modal: true

                            Text {
                                text: "Are you sure you want to delete this item?"
                                color: "white"
                            }

                            onAccepted: {
                                inventoryModel.deleteItem(model.id)
                            }
                        }
                    }
                }
            }
        }
    }

    Dialog {
        id: addItemDialog
        title: "Add New Item"
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

                Label { text: "Item Name:"; color: "white" }
                TextField {
                    id: nameField
                    Layout.fillWidth: true
                    placeholderText: "Enter item name"
                }

                Label { text: "Category:"; color: "white" }
                TextField {
                    id: categoryField
                    Layout.fillWidth: true
                    placeholderText: "Enter category"
                }

                Label { text: "Quantity:"; color: "white" }
                SpinBox {
                    id: quantityField
                    from: 0
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

                Label { text: "Supplier Name:"; color: "white" }
                TextField {
                    id: supplierNameField
                    Layout.fillWidth: true
                    placeholderText: "Enter supplier name"
                }

                Label { text: "Supplier Address:"; color: "white" }
                TextField {
                    id: supplierAddressField
                    Layout.fillWidth: true
                    placeholderText: "Enter supplier address"
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight
                spacing: 10

                Button {
                    text: "Cancel"
                    onClicked: addItemDialog.close()
                }

                Button {
                    text: "Add Item"
                    enabled: nameField.text !== "" && categoryField.text !== "" && priceField.text !== ""
                    onClicked: {
                        inventoryModel.addItem(nameField.text, categoryField.text, quantityField.value, parseFloat(priceField.text), supplierNameField.text, supplierAddressField.text)
                        addItemDialog.close()
                        nameField.text = ""
                        categoryField.text = ""
                        quantityField.value = 0
                        priceField.text = ""
                        supplierNameField.text = ""
                        supplierAddressField.text = ""
                    }
                }
            }
        }
    }

    Dialog {
        id: editItemDialog
        title: "Edit Item"
        modal: true

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: 400

        property int itemId: -1

        contentItem: ColumnLayout {
            spacing: 20

            GridLayout {
                columns: 2
                columnSpacing: 10
                rowSpacing: 10

                Label { text: "Item Name:"; color: "white" }
                TextField {
                    id: editNameField
                    Layout.fillWidth: true
                }

                Label { text: "Category:"; color: "white" }
                TextField {
                    id: editCategoryField
                    Layout.fillWidth: true
                }

                Label { text: "Quantity:"; color: "white" }
                SpinBox {
                    id: editQuantityField
                    from: 0
                    to: 1000000
                    editable: true
                }

                Label { text: "Price:"; color: "white" }
                TextField {
                    id: editPriceField
                    Layout.fillWidth: true
                    validator: DoubleValidator { bottom: 0; decimals: 2 }
                }

                Label { text: "Supplier Name:"; color: "white" }
                TextField {
                    id: editSupplierNameField
                    Layout.fillWidth: true
                }

                Label { text: "Supplier Address:"; color: "white" }
                TextField {
                    id: editSupplierAddressField
                    Layout.fillWidth: true
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight
                spacing: 10

                Button {
                    text: "Cancel"
                    onClicked: editItemDialog.close()
                }

               Button {
                    text: "Save Changes"
                    enabled: editNameField.text !== "" && editCategoryField.text !== "" && editPriceField.text !== ""
                    onClicked: {
                        inventoryModel.updateItem(
                            itemId,
                            editNameField.text,
                            editCategoryField.text,
                            editQuantityField.value,
                            parseFloat(editPriceField.text),
                            editSupplierNameField.text,
                            editSupplierAddressField.text
                        )
                        editItemDialog.close()
                    }
                }
            }
        }
    }
}
