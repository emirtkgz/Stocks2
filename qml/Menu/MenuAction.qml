import QtQuick
import QtQuick.Controls

Action {
    property string qml_file

    onTriggered: {
        stackView.replace(Qt.createComponent(qml_file))
    }
}
