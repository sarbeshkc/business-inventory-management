import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        color: "#1e2329"
    }

    ColumnLayout {
        anchors.centerIn: parent
        width: 300
        spacing: 20

        Text {
            text: "Business Inventory Management System"
            font.pixelSize: 24
            font.bold: true
            color: "white"
            Layout.alignment: Qt.AlignHCenter
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: usernameField
            placeholderText: "Username"
            Layout.fillWidth: true
            background: Rectangle {
                color: "#2c3137"
                radius: 5
            }
            color: "white"
            placeholderTextColor: "#6c757d"
        }

        TextField {
            id: passwordField
            placeholderText: "Password"
            echoMode: TextInput.Password
            Layout.fillWidth: true
            background: Rectangle {
                color: "#2c3137"
                radius: 5
            }
            color: "white"
            placeholderTextColor: "#6c757d"
        }

        Button {
            text: "Login"
            Layout.fillWidth: true
            background: Rectangle {
                color: "#3050c0"
                radius: 5
            }
            contentItem: Text {
                text: parent.text
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            onClicked: {
                if (usernameField.text && passwordField.text) {
                    userModel.login(usernameField.text, passwordField.text)
                } else {
                    errorText.text = "Please enter both username and password"
                    errorText.visible = true
                }
            }
        }

        Text {
            text: "Don't have an account? Sign up"
            color: "#3050c0"
            Layout.alignment: Qt.AlignHCenter
            MouseArea {
                anchors.fill: parent
                onClicked: stackView.push("SignupView.qml")
            }
        }

        Text {
            id: errorText
            color: "#dc3545"
            Layout.alignment: Qt.AlignHCenter
            visible: false
            wrapMode: Text.Wrap
        }
    }

    Connections {
        target: userModel
        function onErrorOccurred(error) {
            errorText.text = error
            errorText.visible = true
        }
        function onLoginSuccessful() {
            errorText.visible = false
        }
    }
}
