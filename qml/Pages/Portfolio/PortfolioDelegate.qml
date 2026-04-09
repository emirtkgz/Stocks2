import QtQuick 2.15
import QtQuick.Controls

import Stocks

Component {
    Rectangle {
        width: parent.width
        height: 70

        color: StTheme.secondColor

        Column {
            Text {
                leftPadding: 20
                text: name
                font.bold: true
                font.pixelSize: 25
                color: "white"
            }
            Text {
                leftPadding: 20
                text: "Amount: " + amount.toFixed(2)
                font.pixelSize: 20
                color: "gray"
            }
        }

        Text {
            anchors.right: parent.right
            rightPadding: 20
            // Add + if positive (QML adds - sign on its own)
            text: ((profit >= 0) ? "+" : "") + profit.toFixed(2)
            font.pixelSize: 20
            color: ((profit >= 0) ? "green" : "red")
        }
    }
}

