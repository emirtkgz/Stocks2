import QtQuick 2.15
import QtQuick.Controls

import Stocks

MouseArea {
    property int size: 10

    width: size
    height: size
    anchors.top: parent.top
    anchors.right: parent.right

    cursorShape: Qt.PointingHandCursor

    Text {
        anchors.fill: parent
        text: "x"
        font.pixelSize: size
        font.bold: true
        color: StTheme.isDarkTheme ? "white" : "black"
    }
}
