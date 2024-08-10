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

        Button {
            text: "Back to Login"
            Layout.fillWidth: true
            onClicked: stackView.pop()
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
            console.log("Error in SignupView:", error)
            errorText.text = error
            errorText.visible = true
        }
        function onLoginSuccessful() {
            console.log("Signup successful in SignupView")
            errorText.visible = false
            stackView.replace("DashboardView.qml")
        }
    }
}
