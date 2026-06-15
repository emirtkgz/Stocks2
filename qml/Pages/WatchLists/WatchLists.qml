import QtQuick
import QtQuick.Controls
import QtCharts

import Stocks

import "../../StyleObjects"

StPage {
    id: watchListsPage
    anchors.fill: parent

    WatchListsPageHelper {
        id: helper
        Component.onCompleted: {
            helper.updateWatchLists()
            console.log(helper.watchLists.length)
        }
    }

    ScrollView {
        anchors.fill: parent
        contentWidth: availableWidth

        Column {
            anchors.fill: parent
            spacing: 10

            Text {
                color: "white"
                font.pixelSize: 50
                text: "Hello There"
            }

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                color: StTheme.secondColor
                width: parent.width * 10 / 12
                height: 600

                Repeater {
                    model: helper.watchLists.length
                    Rectangle {
                        width: 100; height: 40
                        border.width: 1
                        color: "yellow"
                    }
                }

                /*
                ListView {
                    id: watchLists
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
                */
            }
        }
    }
}

