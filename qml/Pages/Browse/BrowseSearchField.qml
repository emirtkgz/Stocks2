import QtQuick
import QtQuick.Controls
import QtCharts

import Stocks

SearchField {
    id: symbolSearch

    required property BrowsePageHelper helper

    // Update the series when enter is pressed
    Keys.onReturnPressed: helper.updateSeries(symbolSearch.text)

    // Upload the search model whenever something is typed
    onTextEdited: helper.uploadSearchModel(symbolSearch.text)

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
