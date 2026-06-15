import QtQuick 2.15
import QtQuick.Controls

import Stocks

import "../../StyleObjects"

StPage {
    id: loginPage
    anchors.fill: parent

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        padding: 50
        text: "Login"
        font.bold: true
        font.pointSize: 30
        color: "white"
    }
}


