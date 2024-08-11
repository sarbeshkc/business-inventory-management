import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        RowLayout {
            Layout.fillWidth: true

//            Button {
  //              text: "Menu"
    //            onClicked: sideBar.open()
//            }

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

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: inventoryModel
            delegate: ItemDelegate {
                width: parent.width
                contentItem: RowLayout {
                    Text { 
                        text: name
                        Layout.fillWidth: true
                    }
                    SpinBox {
                        value: quantity
                        onValueModified: inventoryModel.updateItem(id, name, value, price)
                    }
                    TextField {
                        text: price.toFixed(2)
                        validator: DoubleValidator { bottom: 0; decimals: 2 }
                        onEditingFinished: inventoryModel.updateItem(id, name, quantity, parseFloat(text))
                    }
                    Button {
                        text: "Delete"
                        onClicked: inventoryModel.deleteItem(id)
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
                    text: "Sales"
                    Layout.fillWidth: true
                    onClicked: stackView.push("SalesView.qml")
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
        id: addItemDialog
        title: "Add New Item"
        standardButtons: Dialog.Ok | Dialog.Cancel
        modal: true
        anchors.centerIn: parent
        width: 300

        onAccepted: {
            inventoryModel.addItem(nameField.text, parseInt(quantityField.text), parseFloat(priceField.text))
            nameField.text = ""
            quantityField.text = ""
            priceField.text = ""
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

    Component.onCompleted: {
        console.log("Inventory view loaded")
        inventoryModel.refresh()
    }
}
