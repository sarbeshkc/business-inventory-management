import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "#f0f0f0"
    }

    ColumnLayout {
        anchors.centerIn: parent
        width: 300
        spacing: 20

        Image {
            source: "/home/satvara/Downloads/soham.jpg"
            Layout.alignment: Qt.AlignHCenter
            width: 100
            height: 100
            fillMode: Image.PreserveAspectFit
        }

        Text {
            text: "Business Inventory Management System"
            font.pixelSize: 18
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: usernameField
            placeholderText: "Username"
            Layout.fillWidth: true
        }

        TextField {
            id: passwordField
            placeholderText: "Password"
            echoMode: TextInput.Password
            Layout.fillWidth: true
        }

        Button {
            text: "Login"
            Layout.fillWidth: true
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
            color: "blue"
            Layout.alignment: Qt.AlignHCenter
            MouseArea {
                anchors.fill: parent
                onClicked: stackView.push("SignupView.qml")
            }
        }

        Text {
            id: errorText
            color: "red"
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
