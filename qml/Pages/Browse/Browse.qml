import QtQuick
import QtQuick.Controls
import QtCharts

import Stocks

import "../../StyleObjects"

StPage {
    BrowsePageHelper {
        id: helper

        // Set the series to update in C++ side
        candleSeries: series
        period: "1mo"
        interval: "1d"
        valueAxis: axisY
        dateAxis: axisX
    }

    // Period buttons
    Row {
        anchors.bottom: chartView.top
        anchors.right: chartView.right

        Repeater {
            // [period, interval]
            model: [ ["10m", "1m"], ["30m", "2m"], ["1h", "5m"], ["24h", "30m"], ["7d", "1d"], ["1mo", "1d"], ["1y", "1d"], ["5y", "1d"], ["10y", "1wk"] ]
            Button {
                required property var modelData
                text: modelData[0]
                onClicked: {
                    helper.period   = modelData[0]
                    helper.interval = modelData[1]
                    helper.updateSeries()
                }
            }
        }
    }

    // Search Bar
    Rectangle {
        id: searchBar

        height: parent.height / 12
        width:  parent.width * 11 / 12
        anchors.topMargin: 50

        radius: 60

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        color: StTheme.secondColor

        BrowseSearchField {
            id: searchField
            helper: helper

            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10

            background: Rectangle {
                color: "transparent"
            }
        }
    }

    // Chart View
    StXYChartView {
        id: chartView
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: searchBar.bottom
        anchors.topMargin: 30

        antialiasing: false

        width: parent.width * 4 / 5
        height: parent.height * 2 / 3

        ValueAxis {
            id: axisY

            max: 100
            min: 0
        }

        DateTimeAxis {
            id: axisX
            max: new Date(2026, 5, 1)
            min: new Date(2025, 5, 1)
            format: "dd-MM-yyyy"

        }

        CandlestickSeries {
            id: series
            name: "Browse Anything"
            useOpenGL: true

            axisX: axisX
            axisY: axisY

            decreasingColor: "red"
            increasingColor: "green"
        }
    }


}
