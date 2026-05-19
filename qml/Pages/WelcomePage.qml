import QtQuick 2.15
import QtQuick.Controls

import Stocks

import "../StyleObjects"

StPage {
    id: welcomePage
    anchors.fill: parent

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        padding: 50
        text: "Welcome!"
        font.bold: true
        font.pointSize: 50
        color: "white"
    }
}


