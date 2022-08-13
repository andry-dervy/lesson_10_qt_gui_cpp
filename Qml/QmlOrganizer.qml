import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Rectangle {
    id: _rootrect
    objectName: "rootrect"
    color: "gainsboro"

    property alias width_: _rootrect.width
    property alias height_: _rootrect.height

    RowLayout {
        id: _row
        anchors.top: _rootrect.top
        anchors.left: _rootrect.left
        anchors.right: _rootrect.right
        spacing: 5

        QmlButton {
            id: _addTask
            text: qsTr("Добавить задачу")
            height: 50

            Layout.fillWidth: true
            Layout.margins: 10

            onClicked: {
                model_tasks.add();
                console.log(_addTask.text + " MouseAreaClicked");
            }
        }

        QmlButton {
            id: _delTask
            text: qsTr("Удалить задачу")
            height: 50

            Layout.fillWidth: true
            Layout.margins: 10

            onClicked: {
                if(_view.currentIndex !== -1)
                    model_tasks.remove(_view.currentIndex);
                console.log(_delTask.text + " MouseAreaClicked");
            }
        }
    }

    ListView {
        id: _view

        anchors.top: _row.bottom
        anchors.left: _rootrect.left
        anchors.right: _rootrect.right
        anchors.bottom: _rootrect.bottom
        anchors.margins: 5

        headerPositioning: ListView.PullBackHeader

        clip: true

        highlight: Rectangle {
            color: "skyblue"
        }
        highlightFollowsCurrentItem: true

        header: Item {
            id: _header
            width: _view.width
            height: 40
            anchors.margins: 20

            Row {
                Rectangle {
                    id: _hdr_nameTask
                    color: "lightcyan"
                    width: (_header.width - 10) * 0.25
                    height: _header.height

                    Text {
                        id: _hdr_txtNameTask
                        x: 5; y: 5
                        width: _hdr_nameTask.width - 10
                        height: _hdr_nameTask.height - 10

                        text: qsTr("Название задачи")

                        font.pointSize: _hdr_nameTask.height <= 5 ? 1 : _hdr_nameTask.height / 5
                        font.bold: true
                        horizontalAlignment: TextEdit.AlignHCenter
                        verticalAlignment: TextEdit.AlignVCenter
                    }
                }
                Rectangle {
                    id: _hdr_task
                    color: "lightgoldenrodyellow"
                    width: (_header.width - 10) * 0.50
                    height: _header.height

                    Text {
                        id: _hdr_txtTask
                        x: 5; y: 5
                        width: _hdr_task.width - 10
                        height: _hdr_task.height - 10

                        font.pointSize: _hdr_txtNameTask.font.pointSize
                        font.bold: true

                        text: qsTr("Описание задачи")

                        horizontalAlignment: TextEdit.AlignHCenter
                        verticalAlignment: TextEdit.AlignVCenter
                    }
                }
                Rectangle {
                    id: _hdr_perform
                    color: "lightcyan"
                    width: (_header.width - 10) * 0.10
                    height: _header.height

                    Text {
                        id: _hdr_txtPerform
                        x: 5; y: 5
                        width: _hdr_perform.width - 10
                        height: _hdr_perform.height - 10

                        font.pointSize: _hdr_txtNameTask.font.pointSize
                        font.bold: true

                        text: qsTr("Прогресс")

                        horizontalAlignment: TextEdit.AlignHCenter
                        verticalAlignment: TextEdit.AlignVCenter
                    }
                }
                Rectangle {
                    id: _hdr_limitDate
                    color: "lightgoldenrodyellow"
                    width: (_header.width - 10) * 0.15
                    height: _header.height

                    Text {
                        id: _hdr_txtDate
                        x: 5; y: 5
                        width: _hdr_limitDate.width - 10
                        height: _hdr_limitDate.height - 10

                        font.pointSize: _hdr_txtNameTask.font.pointSize
                        font.bold: true

                        text: qsTr("Срок выполнения")

                        horizontalAlignment: TextEdit.AlignHCenter
                        verticalAlignment: TextEdit.AlignVCenter
                    }
                }
            }
        }

        delegate: Item {
            id: _listItem

            property var view: ListView._view
            property var isCurrent: ListView.isCurrentItem

            width: _view.width
            height: 60

            Task {
                id: _task
                task_name: name
                task_text: description
                task_perform: progress
                task_limit_time: limitDate
                onClicked: _view.currentIndex = model.index
            }
        }

        spacing: 5

        model: model_tasks
    }
}
