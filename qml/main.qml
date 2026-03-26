import QtQuick.Controls
import QtQuick.Layouts
import QtQuick

import "Menu"
import "Pages"

ApplicationWindow {
    id: mainWindow

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    // StackView for the Main Window
    StackView {
        id: stackView

        anchors.fill: parent

        initialItem: WelcomePage {}
    }

    // The MenuBar
    menuBar: StMenuBar {}
}
