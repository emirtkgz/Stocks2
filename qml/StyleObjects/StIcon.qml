import QtQuick 2.15
import QtQuick.Effects
import QtQuick.Controls

import Stocks

Image {
    // Make the icon white if dark theme, black if light theme
    property var image_color: StTheme.isDarkTheme ? "white" : "black"

    layer.enabled: true
    layer.effect: MultiEffect {
        colorization: 1.00
        colorizationColor: image_color
    }
}


