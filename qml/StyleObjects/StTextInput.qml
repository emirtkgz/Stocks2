import QtQuick 2.15
import QtQuick.Layouts

import Stocks

RowLayout {
    property font font
    property color color
    // Base text that cannot be edited
    property string baseText

    property alias text: textInput.text
    property alias readOnly: textInput.readOnly

    Text {
        text: baseText
        font: parent.font
        color: parent.color
    }

    TextInput {
        id: textInput

        selectByMouse: true
        selectionColor: "lightblue"
        selectedTextColor: StTheme.isDarkTheme ? "white" : "black"
        clip: true
        horizontalAlignment: TextInput.AlignLeft

        Layout.fillWidth: true

        font: parent.font
        color: parent.color

        onAccepted: {
            // Stop editing when enter is pressed
            focus = false
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.IBeamCursor

            // Pass mouse clicks to the TextInput to ensure it focuses correctly
            acceptedButtons: Qt.NoButton
        }
    }
}






