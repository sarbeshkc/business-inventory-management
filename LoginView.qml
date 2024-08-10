import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    ColumnLayout {
        anchors.centerIn: parent
        width: 300
        spacing: 10

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
                if (userModel.login(usernameField.text, passwordField.text)) {
                    console.log("Login successful")
                } else {
                    console.log("Login failed")
                }
            }
        }

        Button {
            text: "Sign Up"
            Layout.fillWidth: true
            onClicked: stackView.push("SignupView.qml")
        }

        Text {
            id: errorText
            color: "red"
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            visible: false
        }
    }

    Connections {
        target: userModel
        function onErrorOccurred(error) {
            console.log("Error in LoginView:", error)
            errorText.text = error
            errorText.visible = true
        }
        function onLoginSuccessful() {
            console.log("Login successful in LoginView")
            errorText.visible = false
        }
    }
}
