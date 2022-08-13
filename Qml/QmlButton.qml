import QtQuick 2.8

Rectangle {
    id: _btn
    property alias text: txt.text

    color: "grey"
    border.color: Qt.lighter(_btn.color)
    border.width: 1
    radius: 3

    signal clicked

    Text {
        id: txt
        x: 0
        y: 0
        anchors.centerIn: parent
    }

    MouseArea {
        id: _btnAddTask
        anchors.fill: parent
        onClicked: {
            _btn.clicked();
        }
    }
}
