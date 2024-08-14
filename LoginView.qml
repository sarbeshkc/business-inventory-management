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
            source: "qrc:/images/logo.png"  // Replace with your logo
            Layout.alignment: Qt.AlignHCenter
            width: 120
            height: 120
            fillMode: Image.PreserveAspectFit
        }

        Text {
            text: "Business Inventory\nManagement System"
            font.pixelSize: 24
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

        Button {
            text: "Login"
            Layout.fillWidth: true
            implicitHeight: 50
            background: Rectangle {
                color: parent.pressed ? "#1e88e5" : "#2196f3"
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
            color: "#64b5f6"
            font.pixelSize: 14
            Layout.alignment: Qt.AlignHCenter
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: stackView.push("SignupView.qml")
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
        }
    }
}
