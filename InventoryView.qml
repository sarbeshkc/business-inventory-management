import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#1a237e" }
            GradientStop { position: 1.0; color: "#0d47a1" }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Text {
                text: "Inventory Management"
                font.pixelSize: 28
                font.bold: true
                color: "white"
            }

            Item { Layout.fillWidth: true }

            TextField {
                id: searchField
                placeholderText: "Search items..."
                Layout.preferredWidth: 200
                onTextChanged: inventoryModel.searchItems(text)
                background: Rectangle {
                    radius: 5
                    color: "#ffffff"
                    opacity: 0.8
                }
            }

            Button {
                text: "Add Item"
                onClicked: addItemDialog.open()
                background: Rectangle {
                    radius: 5
                    color: "#4CAF50"
                }
                contentItem: Text {
                    text: parent.text
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
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
                color: index % 2 === 0 ? "#ffffff" : "#f5f5f5"
                opacity: 0.9

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    Text { text: model.name || ""; color: "#333333"; font.pixelSize: 16; Layout.fillWidth: true }
                    Text { text: model.category || ""; color: "#666666"; font.pixelSize: 14; Layout.preferredWidth: 120 }
                    Text { text: model.quantity !== undefined ? model.quantity : ""; color: "#333333"; font.pixelSize: 16; Layout.preferredWidth: 80 }
                    Text { text: model.price !== undefined ? "$" + model.price.toFixed(2) : ""; color: "#4CAF50"; font.pixelSize: 16; Layout.preferredWidth: 100 }
                    Text { text: model.supplierName || ""; color: "#666666"; font.pixelSize: 14; Layout.preferredWidth: 150 }
                    Text { 
                        text: model.expiryDate ? Qt.formatDate(model.expiryDate, "yyyy-MM-dd") : "N/A"
                        color: {
                            if (model.expiryDate) {
                                var daysUntilExpiry = Math.ceil((model.expiryDate - new Date()) / (1000 * 60 * 60 * 24));
                                return daysUntilExpiry <= 30 ? "#FF9800" : "#666666";
                            }
                            return "#666666";
                        }
                        font.pixelSize: 14
                        Layout.preferredWidth: 100
                    }

                    Button {
                        text: "Edit"
                        onClicked: {
                            editItemDialog.itemId = model.id
                            editNameField.text = model.name
                            editCategoryField.text = model.category
                            editQuantityField.value = model.quantity
                            editPriceField.text = model.price.toFixed(2)
                            editSupplierNameField.text = model.supplierName
                            editSupplierAddressField.text = model.supplierAddress
                            editExpiryDateField.text = model.expiryDate ? Qt.formatDate(model.expiryDate, "yyyy-MM-dd") : ""
                            editItemDialog.open()
                        }
                        background: Rectangle {
                            radius: 5
                            color: "#2196F3"
                        }
                        contentItem: Text {
                            text: parent.text
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    Button {
                        text: "Delete"
                        onClicked: deleteConfirmationDialog.open()
                        background: Rectangle {
                            radius: 5
                            color: "#F44336"
                        }
                        contentItem: Text {
                            text: parent.text
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        Dialog {
                            id: deleteConfirmationDialog
                            title: "Confirm Deletion"
                            standardButtons: Dialog.Yes | Dialog.No
                            modal: true

                            background: Rectangle {
                                color: "#ffffff"
                                radius: 10
                            }

                            header: Rectangle {
                                color: "#F44336"
                                height: 40
                                width: parent.width
                                Text {
                                    anchors.centerIn: parent
                                    text: deleteConfirmationDialog.title
                                    color: "white"
                                    font.bold: true
                                }
                            }

                            Text {
                                text: "Are you sure you want to delete this item?"
                                color: "#333333"
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

        background: Rectangle {
            color: "#ffffff"
            radius: 10
        }

        header: Rectangle {
            color: "#4CAF50"
            height: 40
            width: parent.width
            Text {
                anchors.centerIn: parent
                text: addItemDialog.title
                color: "white"
                font.bold: true
            }
        }

        contentItem: ColumnLayout {
            spacing: 20

            GridLayout {
                columns: 2
                columnSpacing: 10
                rowSpacing: 10

                Label { text: "Item Name:"; color: "#333333" }
                TextField {
                    id: nameField
                    Layout.fillWidth: true
                    placeholderText: "Enter item name"
                }

                Label { text: "Category:"; color: "#333333" }
                TextField {
                    id: categoryField
                    Layout.fillWidth: true
                    placeholderText: "Enter category"
                }

                Label { text: "Quantity:"; color: "#333333" }
                SpinBox {
                    id: quantityField
                    from: 0
                    to: 1000000
                    editable: true
                }

                Label { text: "Price:"; color: "#333333" }
                TextField {
                    id: priceField
                    Layout.fillWidth: true
                    placeholderText: "Enter price"
                    validator: DoubleValidator { bottom: 0; decimals: 2 }
                }

                Label { text: "Supplier Name:"; color: "#333333" }
                TextField {
                    id: supplierNameField
                    Layout.fillWidth: true
                    placeholderText: "Enter supplier name"
                }

                Label { text: "Supplier Address:"; color: "#333333" }
                TextField {
                    id: supplierAddressField
                    Layout.fillWidth: true
                    placeholderText: "Enter supplier address"
                }

                Label { text: "Expiry Date:"; color: "#333333" }
                TextField {
                    id: expiryDateField
                    Layout.fillWidth: true
                    placeholderText: "YYYY-MM-DD"
                    inputMask: "9999-99-99"
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight
                spacing: 10

                Button {
                    text: "Cancel"
                    onClicked: addItemDialog.close()
                    background: Rectangle {
                        radius: 5
                        color: "#F44336"
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Button {
                    text: "Add Item"
                    enabled: nameField.text !== "" && categoryField.text !== "" && priceField.text !== ""
                    onClicked: {
                        inventoryModel.addItem(
                            nameField.text,
                            categoryField.text,
                            quantityField.value,
                            parseFloat(priceField.text),
                            supplierNameField.text,
                            supplierAddressField.text,
                            new Date(expiryDateField.text)
                        )
                        addItemDialog.close()
                        nameField.text = ""
                        categoryField.text = ""
                        quantityField.value = 0
                        priceField.text = ""
                        supplierNameField.text = ""
                        supplierAddressField.text = ""
                        expiryDateField.text = ""
                    }
                    background: Rectangle {
                        radius: 5
                        color: "#4CAF50"
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
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

        background: Rectangle {
            color: "#ffffff"
            radius: 10
        }

        header: Rectangle {
            color: "#2196F3"
            height: 40
            width: parent.width
            Text {
                anchors.centerIn: parent
                text: editItemDialog.title
                color: "white"
                font.bold: true
            }
        }

        contentItem: ColumnLayout {
            spacing: 20

            GridLayout {
                columns: 2
                columnSpacing: 10
                rowSpacing: 10

                Label { text: "Item Name:"; color: "#333333" }
                TextField {
                    id: editNameField
                    Layout.fillWidth: true
                }

                Label { text: "Category:"; color: "#333333" }
                TextField {
                    id: editCategoryField
                    Layout.fillWidth: true
                }

                Label { text: "Quantity:"; color: "#333333" }
                SpinBox {
                    id: editQuantityField
                    from: 0
                    to: 1000000
                    editable: true
                }

                Label { text: "Price:"; color: "#333333" }
                TextField {
                    id: editPriceField
                    Layout.fillWidth: true
                    validator: DoubleValidator { bottom: 0; decimals: 2 }
                }

                Label { text: "Supplier Name:"; color: "#333333" }
                TextField {
                    id: editSupplierNameField
                    Layout.fillWidth: true
                }

                Label { text: "Supplier Address:"; color: "#333333" }
                TextField {
                    id: editSupplierAddressField
                    Layout.fillWidth: true
                }

                Label { text: "Expiry Date:"; color: "#333333" }
                TextField {
                    id: editExpiryDateField
                    Layout.fillWidth: true
                    placeholderText: "YYYY-MM-DD"
                    inputMask: "9999-99-99"
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight
                spacing: 10

                Button {
                    text: "Cancel"
                    onClicked: editItemDialog.close()
                    background: Rectangle {
                        radius: 5
                        color: "#F44336"
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
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
                            editSupplierAddressField.text,
                            new Date(editExpiryDateField.text)
                        )
                        editItemDialog.close()
                    }
                    background: Rectangle {
                        radius: 5
                        color: "#4CAF50"
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }
    }

    Connections {
        target: inventoryModel
        function onDataChanged() {
            inventoryListView.forceLayout()
        }
        function onErrorOccurred(error) {
            errorDialog.errorMessage = error
            errorDialog.open()
        }
    }

    Dialog {
        id: errorDialog
        title: "Error"
        modal: true
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        property string errorMessage: ""

        background: Rectangle {
            color: "#ffffff"
            radius: 10
        }

        header: Rectangle {
            color: "#F44336"
            height: 40
            width: parent.width
            Text {
                anchors.centerIn: parent
                text: errorDialog.title
                color: "white"
                font.bold: true
            }
        }

        Label {
            text: errorDialog.errorMessage
            color: "#333333"
            wrapMode: Text.WordWrap
        }

        standardButtons: Dialog.Ok
    }
}
