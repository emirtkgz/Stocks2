#include "BrowsePageHelper.hpp"

BrowsePageHelper::BrowsePageHelper() {}

void BrowsePageHelper::uploadSearchModel() {

}

QAbstractItemModel *BrowsePageHelper::getSearchModel() {
    return static_cast<QAbstractItemModel*>(searchModel.get());
}
