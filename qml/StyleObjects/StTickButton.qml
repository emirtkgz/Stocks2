import QtQuick 2.15

StIcon {
    id: icon

    property int size: 10
    signal clicked

    source: "qrc:icons/tick.svg"

    width: size
    height: size

    MouseArea {
        id: mouseArea

        anchors.fill: icon
        cursorShape: Qt.PointingHandCursor
        onClicked: icon.clicked()
    }
}
