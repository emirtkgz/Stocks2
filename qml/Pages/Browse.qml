import QtQuick
import QtQuick.Controls
import QtCharts

import Stocks

Page {
    SearchField {
            id: symbolSearch
            x: 0
            y: 0
            width: 140
            height: 39
            anchors.horizontalCenter: parent.horizontalCenter

            Component.onCompleted: SearchSymbols.uploadSearchModel()

            onActivated: {
                SearchSymbols.setCode(symbolSearch.text)
                SearchSymbols.update(searchSymbolChart.series("series"), axisX, axisY, 0)
            }

            suggestionModel: SortFilterProxyModel {
                id: filterModel
                model: SearchSymbols.getSearchModel()
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
}
