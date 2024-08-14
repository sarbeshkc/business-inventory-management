import QtQuick 2.1
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: qsTr("Business Inventory Management System")

    Rectangle {
        anchors.fill: parent
        color: "#1e2329"
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // Top Bar
        Rectangle {
            Layout.fillWidth: true
            height: 60
            color: "#212529"
            visible: userModel.isLoggedIn

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 20
                anchors.rightMargin: 20

                Text {
                    text: "Welcome, " + userModel.currentUser
                    color: "white"
                    font.pixelSize: 16
                }

                Item { Layout.fillWidth: true }

                Row {
                    spacing: 10
                    Rectangle {
                        width: 30
                        height: 30
                        color: "transparent"
                        border.color: "white"
                        border.width: 1
                        Text {
                            anchors.centerIn: parent
                            text: "N"
                            color: "white"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: notificationSystem.showNotifications()
                        }
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            // Sidebar (only visible when logged in)
            Rectangle {
                id: sidebar
                width: 200
                Layout.fillHeight: true
                color: "#272c33"
                visible: userModel.isLoggedIn

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 0

                    Repeater {
                        model: ["Dashboard", "Inventory", "Sales", "Analytics"]
                        delegate: ItemDelegate {
                            Layout.fillWidth: true
                            height: 50
                            contentItem: Text {
                                text: modelData
                                color: "white"
                                font.pixelSize: 14
                                verticalAlignment: Text.AlignVCenter
                            }
                            background: Rectangle {
                                color: "transparent"
                            }
                            onClicked: {
                                switch(modelData) {
                                    case "Dashboard":
                                        stackView.replace("DashboardView.qml")
                                        break
                                    case "Inventory":
                                        stackView.replace("InventoryView.qml")
                                        break
                                    case "Sales":
                                        stackView.replace("SalesView.qml")
                                        break
                                    case "Analytics":
                                        stackView.replace("AnalyticsView.qml")
                                        break
                                }
                            }
                        }
                    }

                    Item { Layout.fillHeight: true }

                    Button {
                        text: "Logout"
                        Layout.fillWidth: true
                        onClicked: {
                            userModel.logout()
                            stackView.replace("LoginView.qml")
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
    }

    NotificationSystem {
        id: notificationSystem
        anchors.fill: parent
    }

    // Handle login success
    Connections {
        target: userModel
        function onLoginSuccessful() {
            console.log("Login successful, transitioning to dashboard")
            stackView.replace("DashboardView.qml")
            userDashboard.refresh()
        }
        function onErrorOccurred(error) {
            console.log("Error occurred:", error)
        }
    }
}
