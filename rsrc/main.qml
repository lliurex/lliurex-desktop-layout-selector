import QtQuick 2.6
import QtQuick.Controls 2.0

ApplicationWindow {
    id: root
    width: 300
    height: 480
    visible: true

    TextField {
        text: backend.userName
        placeholderText: qsTr("User name")
        anchors.centerIn: parent

    }
}