import QtQuick
import QtQuick.Controls

import Stocks

MenuBar {
    id: menuBar
    background: Rectangle {
        anchors.fill: parent
        color: StTheme.secondColor
    }

    anchors.top: parent.top

    width: parent.width
    height: parent.height / 12

    Menu {
        title: "Browse"
        MenuAction {
            text: "Browse Symbols"
            qml_file: "qrc:qml/Pages/Browse.qml"
        }
        MenuAction {
            text: "Heat Maps"
        }
        MenuAction {
            text: "Discover"
        }
    }
    Menu {
        title: "Portfolio"
        MenuAction {
            text: "My Portfolio"
            qml_file: "qrc:qml/Pages/Portfolio.qml"
        }
        Action {text: "Transactions"}
    }
    Menu {
        title: "Alarms"
        Action {text: "Action"}
    }
    Menu {
        title: "Tools"
        Action {text: "Action"}
    }
    Menu {
        title: "Settings"
        Action {text: "Action"}
    }
}
