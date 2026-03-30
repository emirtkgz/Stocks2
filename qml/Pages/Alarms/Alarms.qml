import QtQuick 2.15
import QtQuick.Controls

import Stocks

import "../../StyleObjects"

Page {
    id: alarmsPage
    anchors.fill: parent

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        padding: 50
        text: "Alarms"
        font.bold: true
        font.pointSize: 50
        color: "green"
    }

    background: Rectangle {
        anchors.fill: parent
        color: StTheme.firstColor
    }

    ScrollView {
        x: 220
        y: 140
        width: 200
        height: 200

        ListView {
            model: 20
            delegate: ItemDelegate {
                text: "Item " + index

                required property int index
            }
        }
    }

    PlusSign {
        width: 20
        height: 60
    }

}



