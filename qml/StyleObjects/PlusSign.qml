import QtQuick 2.15

Item {
    id: plusSign
    property string color: "red"
    property int radius: 10

    // Plus Sign
    Rectangle {
        id: rectangle1
        anchors.verticalCenter: rectangle2.verticalCenter
        radius: plusSign.radius
        width: plusSign.width
        height: plusSign.height
        color: plusSign.color
    }

    Rectangle {
        id: rectangle2
        anchors.horizontalCenter: rectangle1.horizontalCenter
        radius: plusSign.radius
        width: plusSign.height
        height: plusSign.width
        color: plusSign.color
    }
}
