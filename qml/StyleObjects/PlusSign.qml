import QtQuick 2.15

Item {
    id: plusSign

    property string color: "red"
    property int radius: 10
    required property int size

    width: size
    height: size

    // Horizontal Rectangle
    Rectangle {
        id: rectangle1
        anchors.verticalCenter: rectangle2.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        radius: plusSign.radius
        width: plusSign.size
        height: plusSign.size / 3
        color: plusSign.color
    }

    // Vertical Rectangle
    Rectangle {
        id: rectangle2
        anchors.horizontalCenter: rectangle1.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        radius: plusSign.radius
        width: plusSign.size / 3
        height: plusSign.size
        color: plusSign.color
    }
}
