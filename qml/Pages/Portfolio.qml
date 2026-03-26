import QtQuick 2.15
import QtQuick.Controls

import Stocks

Page {
    id: portfolioPage
    anchors.fill: parent

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        padding: 50
        text: "Portfolio"
        font.bold: true
        font.pointSize: 50
        color: "red"
    }

    background: Rectangle {
        anchors.fill: parent
        color: StTheme.firstColor
    }
}


