import QtQuick 2.15
import QtQuick.Controls

import Stocks

import "../../StyleObjects"


Rectangle {
    required property PortfolioPageHelper helper

    required property string name
    required property real amount
    required property string type
    required property string currency
    required property real price
    required property bool isPriceCurrent
    required property real profit

    width: contentWidth
    height: 100

    color: StTheme.secondColor

    Column {
        leftPadding: 20

        Row {
            spacing: 10
            // Name
            Text {
                id: name_text
                text: name
                font.bold: true
                font.pixelSize: 25
                color: "white"
            }
            // Edit button
            StEditButton {
                anchors.verticalCenter: name_text.verticalCenter
                onEdit: amount_text.readOnly = false
                onSave: {
                    amount_text.readOnly = true

                    helper.patchNewData({
                        "name": name,
                        "amount": parseFloat(amount_text.text)
                    })
                }
            }
        }

        // Amount
        Row {
            // Text that says "Amount: "
            Text {
                text: "Amount: "
                font.pixelSize: 20
                color: "gray"
            }
            // Editable text that displays the amount
            TextInput {
                // Display 5 decimals if it is crypto
                property int decimals: (type === "Cryptos") ? (5) : (2)

                id: amount_text
                readOnly: true

                font.pixelSize: 20
                color: "gray"

                text: amount.toFixed(decimals).toLocaleString()
            }
        }

        // Price
        Text {
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

