import QtQuick
import QtQuick.Controls
import QtCharts

import Stocks

import "../../StyleObjects"

Page {
    BrowsePageHelper {
        id: helper

        // Set the series to update in C++ side
        candleSeries: series
        interval: "1d"
    }

    background: Rectangle {
        anchors.fill: parent
        color: StTheme.firstColor
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

            onAccepted: {
                helper.updateSeries(searchField.text)
            }
        }
    }

    // Chart View
    StXYChartView {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: searchBar.bottom
        anchors.topMargin: 30

        width: parent.width * 4 / 5
        height: parent.height * 2 / 3

        ValueAxis {
            id: axisY
            max: 250
            min: 180
        }

        DateTimeAxis {
            id: axisX
            max: new Date(2026, 4, 30)
            min: new Date(2026, 3, 30)
        }

        CandlestickSeries {
            id: series
            name: "series"
            axisX: axisX
            axisY: axisY
        }
    }


}
