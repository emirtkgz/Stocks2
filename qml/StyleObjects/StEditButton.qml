import QtQuick 2.15

StIcon {
    id: icon

    property int size: 10
    signal edit
    signal save

    source: "qrc:icons/edit.svg"

    width: size
    height: size

    MouseArea {
        id: mouseArea
        property bool isEditing: false

        anchors.fill: icon
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            isEditing = !isEditing

            if(isEditing) {
                icon.edit()
                icon.source = "qrc:icons/tick.svg"
            }
            else {
                icon.save()
                icon.source = "qrc:icons/edit.svg"
            }
        }
    }
}
