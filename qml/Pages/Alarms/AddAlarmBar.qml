import QtQuick 2.15
import QtQuick.Controls

import Stocks

import "../../StyleObjects"

Column {
    required property AlarmsPageHelper helper
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
        height: 500
        color: StTheme.secondColor

        Column {
            anchors.fill: parent

            // Header
            Text {
                text: qsTr("Add New Alarm")
                font.pixelSize: 20
                topPadding: 10
                color: StTheme.isDarkTheme ? "white" : "black"

                StTickButton {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.right
                    anchors.leftMargin: 5
                    anchors.topMargin: 10
                    onClicked: {
                        helper.postNewAlarm({
                            "ticker":         repeater.itemAt(0).text,
                            "type":  parseInt(repeater.itemAt(1).text),
                            "value": parseInt(repeater.itemAt(2).text),
                            "message":        repeater.itemAt(3).text,
                            "is_on":          true
                        })
                    }
                }
            }
            // Values
            Repeater {
                id: repeater
                model: ["Ticker", "Type", "Value", "Message"]
                delegate: Row {
                    id: repeaterDelegate

                    required property var index
                    required property var modelData
                    property alias text: textInput.text

                    Text {
                        id: labelText
                        text: qsTr(modelData) + ": "
                        font.pixelSize: 20
                        color: "gray"
                    }

                    StTextInput {
                        id: textInput

                        font.pixelSize: 20
                        color: "gray"
                        width: Math.max(80, Math.min(contentWidth + 10, addAlarmPopup.width - 100))  // min: 80, max: addAlarmPopup.width - 100
                    }
                }
            }
        }

        // Close button
        CloseButton {
            size: 10
            onClicked: addAlarmPopup.visible = false
        }
    }
}


