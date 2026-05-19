import QtQuick 2.15
import QtQuick.Controls

import Stocks

import "../../StyleObjects"

StPage {
    id: alarmsPage
    anchors.fill: parent

    ScrollView {
        anchors.fill: parent
        contentWidth: availableWidth

        Column {
            anchors.fill: parent
            spacing: 10

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Alarms"
                font.bold: true
                font.pointSize: 30
                color: "white"
            }

            AddAlarmBar {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width * 10 / 12
                barHeight: 30
                spacing: 10
            }

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                color: StTheme.secondColor
                width: parent.width * 10 / 12
                height: 600

                ListView {
                    id: alarmsList
                    anchors.fill: parent
                    interactive: false

                    model: 20
                    delegate: ItemDelegate {
                        text: "Item " + index
                        background: Rectangle {
                            color: "transparent"
                        }

                        required property int index
                    }
                }
            }
        }
    }




}



