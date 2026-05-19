import QtQuick 2.15
import QtQuick.Controls

import Stocks

import "../../StyleObjects"

Column {
    property int barHeight: 30

    Rectangle {
        id: searchBar
        anchors.horizontalCenter: parent.horizontalCenter
        color: StTheme.secondColor

        width: parent.width
        height: barHeight
        radius: 20

        PlusSign {
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            size: 20
            color: StTheme.isDarkTheme ? "white" : "black"

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    addAlarmPopup.visible = true
                }
            }
        }
    }

    Rectangle {
        id: addAlarmPopup

        visible: false
        anchors.leftMargin: 20
        width: parent.width
        height: 100
        color: StTheme.secondColor

        Column {
            anchors.fill: parent

            Text {
                text: qsTr("Add New Alarm")
                font.pixelSize: 20
                leftPadding: 20
                topPadding: 10
                color: StTheme.isDarkTheme ? "white" : "black"
            }
        }

        // Close button
        CloseButton {
            size: 10
            onClicked: addAlarmPopup.visible = false
        }
    }
}


