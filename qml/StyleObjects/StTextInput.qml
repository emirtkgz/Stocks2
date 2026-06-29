import QtQuick 2.15

import Stocks

TextInput {
    selectByMouse: true
    selectionColor: "lightblue"
    selectedTextColor: StTheme.isDarkTheme ? "white" : "black"
    clip: true
    horizontalAlignment: TextInput.AlignLeft

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
