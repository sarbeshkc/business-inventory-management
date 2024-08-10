import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: qsTr("Business Inventory Management System")

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Sidebar (only visible when logged in)
        Rectangle {
            id: sidebar
            Layout.preferredWidth: 200
            Layout.fillHeight: true
            color: "#f0f0f0"
            visible: userModel.isLoggedIn

            ColumnLayout {
                anchors.fill: parent
                spacing: 10
                
                Text {
                    text: "Welcome, " + userModel.currentUser
                    font.pixelSize: 16
                    Layout.margins: 10
                }

                Button {
                    text: "Dashboard"
                    Layout.fillWidth: true
                    onClicked: stackView.replace("DashboardView.qml")
                }

                Button {
                    text: "Inventory"
                    Layout.fillWidth: true
                    onClicked: stackView.replace("InventoryView.qml")
                }

                Button {
                    text: "Sales"
                    Layout.fillWidth: true
                    onClicked: stackView.replace("SalesView.qml")
                }

                Item { Layout.fillHeight: true } // Spacer

                Button {
                    text: "Logout"
                    Layout.fillWidth: true
                    onClicked: {
                        userModel.logout();
                        stackView.replace("LoginView.qml");
                    }
                }
            }
        }

        // Main content area
        StackView {
            id: stackView
            Layout.fillWidth: true
            Layout.fillHeight: true
            initialItem: LoginView {}
        }
    }

    // Handle login success
    Connections {
        target: userModel
        function onLoginSuccessful() {
            console.log("Login successful, transitioning to dashboard")
            stackView.replace("DashboardView.qml")
        }
        function onErrorOccurred(error) {
            console.log("Error occurred:", error)
        }
    }

    Component.onCompleted: {
        console.log("Main QML loaded");
    }
}
