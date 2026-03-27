import QtQuick
import QtQuick.Controls
import QtCharts

import Stocks

SearchField {
    id: symbolSearch

    Component.onCompleted: BrowsePageHelper.uploadSearchModel()

    onActivated: {
        SearchSymbols.setCode(symbolSearch.text)
        SearchSymbols.update(searchSymbolChart.series("series"), axisX, axisY, 0)
    }

    suggestionModel: SortFilterProxyModel {
        id: filterModel
        model: BrowsePageHelper.getSearchModel()
        sorters: [
            RoleSorter {
                roleName: "code"
            }
        ]
        filters: [
            FunctionFilter {
                component CustomData: QtObject { property string code }
                property var regExp: new RegExp(symbolSearch.text, "i")
                onRegExpChanged: invalidate()

                function filter(data: CustomData): bool {
                    return regExp.test(data.code);
                }
            }
        ]
    }
}
