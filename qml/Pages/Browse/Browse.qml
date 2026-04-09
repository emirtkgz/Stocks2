import QtQuick
import QtQuick.Controls
import QtCharts

import Stocks

import "../../StyleObjects"

Page {

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
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: searchBar.bottom
        anchors.topMargin: 30

        width: parent.width * 4 / 5
        height: parent.height * 2 / 3

        ValueAxis {
            id: axisY
        }

        DateTimeAxis {
            id: axisX
        }

        LineSeries {
            id: lineSeries
            name: "series"
            axisX: axisX
            axisY: axisY

            XYPoint {
                x: new Date(2026, 3, 24)
                y: 10
            }
            XYPoint {
                x: new Date(2026, 3, 26)
                y: 20
            }
        }
    }


}
