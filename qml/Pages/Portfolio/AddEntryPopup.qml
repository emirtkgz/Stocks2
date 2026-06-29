import QtQuick 2.15
import QtQuick.Controls

import Stocks

import "../../StyleObjects"

Rectangle {
    required property PortfolioPageHelper helper

    id: addEntryPopup

    visible: false
    anchors.leftMargin: 20
    width: parent.width
    height: 185
    color: StTheme.secondColor

    Column {
        leftPadding: 20

        // Header
        Text {
            text: qsTr("Add New Entry")
            font.pixelSize: 20
            topPadding: 10
            color: StTheme.isDarkTheme ? "white" : "black"

            StTickButton {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.right
                anchors.leftMargin: 5
                anchors.topMargin: 10
                onClicked: {
                    helper.putNewData({
                        "name":      repeater.itemAt(0).text,
                        "type":      parseInt(repeater.itemAt(1).text),
                        "avg_price": parseFloat(repeater.itemAt(2).text),
                        "currency":  repeater.itemAt(3).text,
                        "amount":    parseFloat(repeater.itemAt(4).text),
                        "lastPrice": {
                            "price": 0,
                            "lastUpdated": 0
                        }
                    });
                }
            }
        }
        // Values
        Repeater {
            id: repeater
            model: ["Name", "Type", "Average Price", "Currency", "Amount"]
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
                    width: Math.max(80, Math.min(contentWidth + 10, addEntryPopup.width - 100))  // min: 80, max: addEntryPopup.width - 100
                }
            }
        }
    }



    // Close button
    CloseButton {
        size: 10
        onClicked: addEntryPopup.visible = false
    }
}
