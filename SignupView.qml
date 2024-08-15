import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "#1e2329"
    }

    ColumnLayout {
        anchors.centerIn: parent
        width: 320
        spacing: 20


        Image {
            source: "/home/satvara/Downloads/BIMSLOGO(1).png"  // Replace with your logo
            Layout.alignment: Qt.AlignHCenter
            width: 50
            height: 50
            fillMode: Image.PreserveAspectFit
        }

        Text {
            text: "Create an Account"
            font.pixelSize: 28
            font.bold: true
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
        }

        Rectangle {
            Layout.fillWidth: true
            height: 50
            color: "#2c3137"
            radius: 25

            TextField {
                id: usernameField
                anchors.fill: parent
                anchors.margins: 5
                placeholderText: "Username"
                color: "white"
                background: Item {}
                leftPadding: 15
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 50
            color: "#2c3137"
            radius: 25

            TextField {
                id: emailField
                anchors.fill: parent
                anchors.margins: 5
                placeholderText: "Email"
                color: "white"
                background: Item {}
                leftPadding: 15
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 50
            color: "#2c3137"
            radius: 25

            TextField {
                id: passwordField
                anchors.fill: parent
                anchors.margins: 5
                placeholderText: "Password"
                echoMode: TextInput.Password
                color: "white"
                background: Item {}
                leftPadding: 15
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 50
            color: "#2c3137"
            radius: 25

            TextField {
                id: confirmPasswordField
                anchors.fill: parent
                anchors.margins: 5
                placeholderText: "Confirm Password"
                echoMode: TextInput.Password
                color: "white"
                background: Item {}
                leftPadding: 15
            }
        }

        Button {
            text: "Sign Up"
            Layout.fillWidth: true
            implicitHeight: 50
            background: Rectangle {
                color: parent.pressed ? "#43a047" : "#4caf50"
                radius: 25
            }
            contentItem: Text {
                text: parent.text
                font.pixelSize: 16
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
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
            color: "#64b5f6"
            font.pixelSize: 14
            Layout.alignment: Qt.AlignHCenter
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: stackView.pop()
            }
        }

        Text {
            id: errorText
            color: "#e57373"
            font.pixelSize: 14
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
            stackView.replace("DashboardView.qml")
        }
    }
}
