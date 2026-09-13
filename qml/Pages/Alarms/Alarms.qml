import QtQuick 2.15
import QtQuick.Controls

import Stocks

import "../../StyleObjects"

StPage {
    id: alarmsPage
    anchors.fill: parent

    AlarmsPageHelper {
        id: pageHelper
    }

    Component.onCompleted: pageHelper.updateAlarmsList()

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
                helper: pageHelper

                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width * 10 / 12
                barHeight: 30
                spacing: 10
            }

            ListView {
                id: alarmsList

                width: parent.width * 10 / 12
                height: contentHeight
                anchors.horizontalCenter: parent.horizontalCenter
                interactive: false

                // Background
                Rectangle {
                    anchors.fill: parent
                    color: StTheme.secondColor
                    z: -1
                }

                model: pageHelper.alarmsList
                delegate: AlarmDelegate {
                    width: alarmsList.width
                }
            }
        }
    }
}



