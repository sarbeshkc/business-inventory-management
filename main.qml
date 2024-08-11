import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 768
    title: qsTr("Business Inventory Management System")

    Drawer {
        id: drawer
        width: 250
        height: window.height
        interactive: userModel.isLoggedIn

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            ItemDelegate {
                text: qsTr("Dashboard")
                width: parent.width
                onClicked: {
                    stackView.push("DashboardView.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Inventory")
                width: parent.width
                onClicked: {
                    stackView.push("InventoryView.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Sales")
                width: parent.width
                onClicked: {
                    stackView.push("SalesView.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Analytics")
                width: parent.width
                onClicked: {
                    stackView.push("AnalyticsView.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Logout")
                width: parent.width
                onClicked: {
                    userModel.logout()
                    stackView.pop(null)
                    stackView.push("LoginView.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: LoginView {}
    }

    Connections {
        target: userModel
        function onLoginSuccessful() {
            console.log("Login successful, transitioning to dashboard")
            stackView.push("DashboardView.qml")
        }
        function onErrorOccurred(error) {
            console.log("Error occurred:", error)
            errorDialog.text = error
            errorDialog.open()
        }
    }

    Dialog {
        id: errorDialog
        title: "Error"
        standardButtons: Dialog.Ok
        modal: true

        property alias text: errorText.text

        Text {
            id: errorText
            wrapMode: Text.Wrap
        }
    }

    Component.onCompleted: {
        console.log("Main QML loaded")
    }
}
