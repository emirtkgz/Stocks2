import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

import Stocks

import "../../StyleObjects"

ItemDelegate {
    id: delegate

    required property string code
    required property real type
    required property real value
    required property string message
    required property bool is_on

    height: 125

    background: Rectangle {
        color: StTheme.secondColor
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 5

        Text {
            text: code
            font.pixelSize: 20
            color: StTheme.headerTextColor
            leftPadding: 20
        }
        Text {
            text: "Type: " + 0
            font.pixelSize: 15
            color: StTheme.bodyTextColor
            leftPadding: 20
        }
        Text {
            text: "Value: " + value
            font.pixelSize: 15
            color: StTheme.bodyTextColor
            leftPadding: 20
        }
        Text {
            text: "Message: " + message
            font.pixelSize: 15
            color: StTheme.bodyTextColor
            leftPadding: 20
        }
        HorizontalLine {
            width: 0.9 * parent.width
            Layout.alignment: Qt.AlignHCenter
            anchors.topMargin: 20
        }
    }

    Switch {
        anchors {
            right: parent.right
            rightMargin: 20
        }

        checked: is_on
    }
}
