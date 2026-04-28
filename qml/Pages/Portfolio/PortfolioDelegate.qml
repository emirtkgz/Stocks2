import QtQuick 2.15
import QtQuick.Controls

import Stocks

Component {
    Rectangle {
        width: parent.width
        height: 100

        color: StTheme.secondColor

        Column {
            // Name
            Text {
                leftPadding: 20
                text: name
                font.bold: true
                font.pixelSize: 25
                color: "white"
            }
            // Amount
            Text {
                leftPadding: 20
                // Display 5 decimals if it is crypto
                property int decimals: (type === "Cryptos") ? (5) : (2)
                text: "Amount: " + amount.toFixed(decimals).toLocaleString()
                font.pixelSize: 20
                color: "gray"
            }
            // Price
            Text {
                leftPadding: 20
                text: "Market Price: " + price.toFixed(2).toLocaleString()
                font.pixelSize: 20
                color: "gray"

                Text {
                    anchors.left: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 5
                    text: ((isPriceCurrent) ? "" : "(Warning: Price shown is not current!)")
                    font.pixelSize: 10
                    color: "red"
                }
            }
        }

        // Profit
        Text {
            anchors.right: parent.right
            rightPadding: 20
            // Add + if positive (QML adds - sign on its own)
            text: ((profit >= 0) ? "+" : "") + profit.toFixed(2).toLocaleString() + " " + currency
            font.pixelSize: 20
            color: ((profit >= 0) ? "green" : "red")
        }
    }
}

