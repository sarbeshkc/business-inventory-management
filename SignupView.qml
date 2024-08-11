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

        Text {
            text: "Create an Account"
            font.pixelSize: 24
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }

        TextField {
            id: usernameField
            placeholderText: "Username"
            Layout.fillWidth: true
        }

        TextField {
            id: emailField
            placeholderText: "Email"
            Layout.fillWidth: true
        }

        TextField {
            id: passwordField
            placeholderText: "Password"
            echoMode: TextInput.Password
            Layout.fillWidth: true
        }

        TextField {
            id: confirmPasswordField
            placeholderText: "Confirm Password"
            echoMode: TextInput.Password
            Layout.fillWidth: true
        }

        Button {
            text: "Sign Up"
            Layout.fillWidth: true
            onClicked: {
                if (passwordField.text === confirmPasswordField.text) {
                    if (userModel.signup(usernameField.text, passwordField.text, emailField.text)) {
                        console.log("Signup successful")
                    } else {
                        console.log("Signup failed")
                    }
                } else {
                    errorText.text = "Passwords do not match"
                    errorText.visible = true
                }
            }
        }

        Text {
            text: "Already have an account? Log in"
            color: "blue"
            Layout.alignment: Qt.AlignHCenter
            MouseArea {
                anchors.fill: parent
                onClicked: stackView.pop()
            }
        }

        Text {
            id: errorText
            color: "red"
            Layout.alignment: Qt.AlignHCenter
            visible: false
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
            stackView.push("qrc:/qml/DashboardView.qml")
        }
    }
}
