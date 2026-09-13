import QtQuick 2.15
import QtQuick.Controls

import Stocks

import "../../StyleObjects"
import "qrc:/js/string-to-color.js" as StringToColor

Rectangle {
    required property PortfolioPageHelper helper

    required property string name
    required property real amount
    required property string type
    required property string currency
    required property real price
    required property bool isPriceCurrent
    required property real profit
    required property real averagePrice
    required property real profitPercent

    width: contentWidth
    height: 200

    color: StTheme.secondColor

    Column {
        id: mainColumn
        leftPadding: 20
        topPadding: 10

        Row {
            spacing: 10

            // Icon
            Rectangle {
                id: icon
                width: 50
                height: 50
                radius: width / 2
                color: Qt.color(StringToColor.stringToColor(name))

                // Text inside the icon containing initial 2 letters of the name
                Text {
                    anchors.centerIn: parent

                    text: name.slice(0, 2)
                    color: "white"
                    font {
                        pointSize: 15
                        bold: true
                    }
                }
            }

            // Name
            Text {
                id: name_text
                anchors.verticalCenter: icon.verticalCenter
                text: name
                color: "white"
                font {
                    bold: true
                    pixelSize: 25
                }
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

        Column {
            topPadding: 10
            leftPadding: 20

            // Amount
            StTextInput {
                // Display 5 decimals if it is crypto
                property int decimals: (type === "Cryptos") ? (5) : (2)

                id: amount_text
                readOnly: true

                font.pixelSize: 15
                color: "gray"

                baseText: "Amount: "
                text: amount.toFixed(decimals).toLocaleString()
            }

            // Value
            Text {
                text: "Value: " + (amount * price).toFixed(2) + " " + currency
                font.pixelSize: 15
                color: "gray"
            }

            // Price
            Text {
                text: "Market Price: " + price.toFixed(2).toLocaleString()
                font.pixelSize: 15
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

            // Average Price
            StTextInput {
                id: avgPriceText
                readOnly: true

                font.pixelSize: 15
                color: "gray"

                baseText: "Average Price: "
                text: averagePrice.toFixed(2).toLocaleString()
            }
        }
    }

    // Profit
    Column {
        anchors.right: parent.right
        rightPadding: 30
        topPadding: 20

        // Profit
        Text {
            // Add + if positive (QML adds - sign on its own)
            text: ((profit >= 0) ? "+" : "") + profit.toFixed(2).toLocaleString() + " " + currency
            font.pixelSize: 20
            color: ((profit >= 0) ? "green" : "red")
        }

        // Percentage
        Text {
            // Add + if positive (QML adds - sign on its own)
            text: ((profitPercent >= 0) ? "+" : "") + profitPercent.toFixed(2).toLocaleString() + "%"
            font.pixelSize: 20
            color: ((profitPercent >= 0) ? "green" : "red")
        }
    }

    // Seperator
    HorizontalLine {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: mainColumn.bottom
            topMargin: 20
        }

        width: 0.9 * parent.width
    }
}

