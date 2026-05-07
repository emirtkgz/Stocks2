import QtQuick
import QtQuick.Controls
import QtCharts

import Stocks

SearchField {
    id: symbolSearch

    required property BrowsePageHelper helper

    onTextEdited: {
        helper.uploadSearchModel(symbolSearch.text)
    }

    suggestionModel: helper.getSearchModel()
    delegate: ItemDelegate {

        onClicked: helper.updateSeries(symbol)

        background: Rectangle {
            color: StTheme.secondColor
        }

        Text {
            text: symbol
            color: "white"
        }
    }

}
