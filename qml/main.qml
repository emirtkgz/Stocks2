import QtQuick.Controls
import QtQuick.Layouts
import QtQuick

import "Menu"
import "Pages"
import "Pages/Login"

ApplicationWindow {
    id: mainWindow

    width: 640
    height: 480
    visible: true
    title: qsTr("Stocks2")

    // StackView for the Main Window
    StackView {
        id: stackView

        anchors.fill: parent

        initialItem: Login{}
    }

    // The MenuBar
    menuBar: StMenuBar {}
}
