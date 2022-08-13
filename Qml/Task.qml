import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Controls 2.12

Item {
    id: _root
    anchors.fill: parent
    anchors.margins: 2

    property alias task_name: _txtNameTask.text
    property alias task_text: _txtTask.text
    property alias task_perform: _txtPerform.text
    property alias task_limit_time: _txtDate.text

    signal clicked

    property int degreePerform: 0

    Row {
        Rectangle {
            id: _nameTask
            color: "lightcyan"
            width: (_root.width - 10) * 0.25
            height: _root.height

            TextInput {
                id: _txtNameTask
                x: 5; y: 5
                width: _nameTask.width - 10
                height: _nameTask.height - 10

                text: qsTr("Название задачи")

                font.pointSize: _nameTask.height <= 5 ? 1 : _nameTask.height / 5
                font.bold: true
                maximumLength: 18
                horizontalAlignment: TextEdit.AlignHCenter
                verticalAlignment: TextEdit.AlignVCenter

                onTextEdited: {
                    model_tasks.update_name_task(_view.currentIndex,_txtNameTask.text);
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: (mouse)=> {
                    _txtNameTask.forceActiveFocus(Qt.MouseFocusReason)
                    _root.clicked();
                }
            }
        }
        Rectangle {
            id: _task
            color: "lightgoldenrodyellow"
            width: (_root.width - 10) * 0.50
            height: _root.height

            TextEdit {
                id: _txtTask
                x: 5; y: 5
                width: _task.width - 10
                height: _task.height - 10

                font.pointSize: _task.height <= 6 ? 1 : _task.height / 6
                font.bold: true

                text: qsTr("Описание задачи")

                horizontalAlignment: TextEdit.AlignHCenter
                verticalAlignment: TextEdit.AlignVCenter

                wrapMode: TextEdit.Wrap

                onTextChanged: {
                    console.log("_txtTask: onTextChanged");
                    var pos = _txtTask.positionAt(1, _txtTask.height + 1);
                    if(pos > 0 && _txtTask.length > pos)
                    {
                        console.log(_txtTask.text)
                        _txtTask.remove(pos, _txtTask.length);
                        console.log(_txtTask.text)
                    }
                    model_tasks.update_description_task(_view.currentIndex,_txtTask.text);
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: (mouse)=> {
                    _txtTask.forceActiveFocus(Qt.MouseFocusReason)
                    _root.clicked();
                }
            }
        }
        Rectangle {
            id: _perform
            color: "lightcyan"
            width: (_root.width - 10) * 0.10
            height: _root.height

            MouseArea {
                anchors.fill: parent
                onClicked: _root.clicked();
                onWheel: (wheel)=> {
                    _root.clicked();
                    var delta = wheel.angleDelta.y;
                    console.log("_perform: onWheel " + delta)
                    model_tasks.update_progress_task(_view.currentIndex,delta);
                }
            }

            Text {
                id: _txtPerform
                x: 5; y: 5
                width: _perform.width - 10
                height: _perform.height - 10

                font.pointSize: _task.height <= 6 ? 1 : _task.height / 6
                font.bold: true

                text: _root.degreePerform

                horizontalAlignment: TextEdit.AlignHCenter
                verticalAlignment: TextEdit.AlignVCenter
            }
        }
        Rectangle {
            id: _limitDate
            color: "lightgoldenrodyellow"
            width: (_root.width - 10) * 0.15
            height: _root.height

            MouseArea {
                anchors.fill: parent
                onClicked: _root.clicked();
                onWheel: (wheel)=> {
                    _root.clicked();

                    var delta = wheel.angleDelta.y;
                    console.log("_limitDate: onWheel " + delta);
                    model_tasks.update_limit_date(_view.currentIndex, delta);
                }
            }

            Text {
                id: _txtDate
                x: 5; y: 5
                width: _limitDate.width - 10
                height: _limitDate.height - 10

                font.pointSize: _limitDate.height <= 6 ? 1 : _limitDate.height / 6
                font.bold: true

                horizontalAlignment: TextEdit.AlignHCenter
                verticalAlignment: TextEdit.AlignVCenter
            }
        }
    }
}
