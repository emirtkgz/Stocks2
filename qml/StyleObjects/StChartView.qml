import QtQuick 2.15
import QtCharts

ChartView {
    id: chartView

    // Implement zoom and scroll
    MouseArea {
        anchors.fill: parent

        property real old_x: 0
        property real old_y: 0

        onPressed: {
          old_x = mouseX
          old_y = mouseY
        }

        // Scroll
        onPositionChanged: mouseEvent => {
            if(mouseEvent.buttons & 1) {
                parent.scrollRight(old_x - mouseX)
                parent.scrollDown(old_y - mouseY)
            }

            old_x = mouseX
            old_y = mouseY
        }

        // Zoom
        onWheel: wheelEvent => {
            let deltaAngle = wheelEvent.angleDelta.y

            if (deltaAngle >= 0) {
                parent.zoom(deltaAngle / 80)
            }
            else {
                parent.zoom(-deltaAngle / 180)
            }
        }
    }

    // Implement Y-Axis Scroll
    MouseArea {
        id: axisYScroller
        y: 35
        width: 23
        height: 382
        anchors.left: parent.left
        anchors.leftMargin: 38
        cursorShape: Qt.SizeVerCursor

        property real old_y: 0

        onPressed: {
            old_y = mouseY
        }

        onPositionChanged: mouseEvent => {
            if(mouseEvent.buttons & 1) {
                var delta = old_y - mouseY
                var difference = parent.axisY().max - parent.axisY().min
                var coefficient = delta * difference / 100

                parent.axisY().max += coefficient
                parent.axisY().min -= coefficient
            }

            old_y = mouseY
        }
    }

    // Implement X-Axis Scroll
    MouseArea {
        id: axisXScroller
        y: 392
        width: 520
        height: 25
        anchors.left: parent.bottom
        anchors.leftMargin: 48
        cursorShape: Qt.SizeHorCursor

        property real old_x: 0
        x: 60

        onPressed: {
            old_x = mouseX
        }

        onPositionChanged: mouseEvent => {
            if(mouseEvent.buttons & 1) {
                var delta = old_x - mouseX
                var difference = parent.axisX().max - parent.axisX().min
                var coefficient = delta * difference / 100

                parent.axisX().max = new Date(parent.axisX().max.getTime() + coefficient)
                parent.axisX().min = new Date(parent.axisX().min.getTime() - coefficient)
            }

            old_x = mouseX
        }
    }
}
