#include "PortfolioPageHelper.hpp"

#include <nlohmann/json.hpp>

#include "InvestmentType.hpp"
#include "API/DataFetchers.hpp"
#include "API/ServerAPI.hpp"
#include "Settings.hpp"
#include "Utils/JSON.hpp"

using json = nlohmann::json;

enum PortfolioModelRoles {
    Name           = Qt::UserRole + 1,
    Type           = Qt::UserRole + 2,
    AveragePrice   = Qt::UserRole + 3,
    Currency       = Qt::UserRole + 4,
    Amount         = Qt::UserRole + 5,
    Profit         = Qt::UserRole + 6,
    IsPriceCurrent = Qt::UserRole + 7,
    Price          = Qt::UserRole + 8,
    ProfitPercent  = Qt::UserRole + 9
};

PortfolioPageHelper::PortfolioPageHelper(QObject* parent) :
    QObject(parent), m_totalProfit(0), m_totalValue(0)
{
    // Initialize the item model that will display the portfolio
    m_portfolioModel = new QStandardItemModel();
    // Set roles
    m_portfolioModel->setItemRoleNames({
        {PortfolioModelRoles::Name,           "name"},
        {PortfolioModelRoles::Type,           "type"},
        {PortfolioModelRoles::AveragePrice,   "averagePrice"},
        {PortfolioModelRoles::Currency,       "currency"},
        {PortfolioModelRoles::Amount,         "amount"},
        {PortfolioModelRoles::Profit,         "profit"},
        {PortfolioModelRoles::IsPriceCurrent, "isPriceCurrent"},
        {PortfolioModelRoles::Price,          "price"},
        {PortfolioModelRoles::ProfitPercent,  "profitPercent"}
    });
}

PortfolioPageHelper::~PortfolioPageHelper() {}

// Patches data in server API whenever user edits the portfolio data
void PortfolioPageHelper::patchNewData(QJSValue data) {
    auto string_data = qjsvalueToNlohmann(data).dump();

    ServerAPI.patch("api/portfolio/data", cpr::Body{string_data});
    updatePage();
}

// Put a new entry to the server API
void PortfolioPageHelper::putNewData(QJSValue data) {
    auto string_data = qjsvalueToNlohmann(data).dump();

    ServerAPI.put("api/portfolio/data", cpr::Body{string_data});
    updatePage();
}

void PortfolioPageHelper::updatePage() {
    auto r = ServerAPI.get("api/portfolio/data");

    if(ServerAPI.checkErrors(r))
        return;

    const auto portfolio = r["Data"];

    // Group each investment type
    std::unordered_map<InvestmentType, qreal> investments;

    // Clear the previous model data and pie series (if any)
    m_portfolioModel->clear();
    m_pieSeries->clear();

    qreal total_profit = 0.0;
    qreal total_value = 0.0;

    // Iterate for each entry in portfolio
    for(auto& entry : portfolio) {

        // Fetch the price
        qreal price = entry["lastPrice"]["price"];

        // Calculate the preferred price
        qreal preferred_price = price;
        qreal parity = 0.0;

        const std::string currency = entry["currency"];
        if(currency != Settings::currency) {
            try {
                // Use yfinance to fetch
                parity = DataFetchers::getCurrentPrice(currency + Settings::currency + "=X");
                preferred_price *= parity;
            } catch(...) {
                preferred_price = 0;
            }
        }

        // TODO: handle this
        bool isPriceCurrent = true;

        // Calculate the basic data
        const qreal amount           = entry["amount"];
        const qreal avg_price        = entry["avg_price"];
        const qreal unit_profit      = (price - avg_price);
        const qreal profit           = amount * unit_profit;
        const qreal profit_percent   = unit_profit / avg_price * 100;
        const qreal preferred_value  = amount * preferred_price;
        const qreal preferred_profit = profit * parity; // TODO: Not a correct calculation
        const InvestmentType type    = entry["type"];

        // String data
        const QString s_type     = QString::fromStdString(InvestmentTypeLookup(entry["type"]));
        const QString s_currency = QString::fromStdString(currency);
        const QString name       = QString::fromStdString(entry["name"]);

        // Add to the totals
        total_profit += preferred_profit;
        total_value  += preferred_value;

        // Check if that investment type already exists
        auto it = investments.find(type);
        if(it != investments.end()) {
            // If exists, add it to the total
            it->second += preferred_value;
        }
        else {
            // If not, create a new pair
            investments.emplace(type, preferred_value);
        }

        // ~~~~ Portfolio Model ~~~~
        // Fill the item
        QStandardItem* item = new QStandardItem();
        item->setData(name,           PortfolioModelRoles::Name);
        item->setData(type,           PortfolioModelRoles::Type);
        item->setData(avg_price,      PortfolioModelRoles::AveragePrice);
        item->setData(s_currency,     PortfolioModelRoles::Currency);
        item->setData(amount,         PortfolioModelRoles::Amount);
        item->setData(profit,         PortfolioModelRoles::Profit);
        item->setData(isPriceCurrent, PortfolioModelRoles::IsPriceCurrent);
        item->setData(price,          PortfolioModelRoles::Price);
        item->setData(profit_percent, PortfolioModelRoles::ProfitPercent);

        m_portfolioModel->appendRow(item);
    }

    // ~~~~ Pie Chart ~~~~
    // Generate pie slices
    for(auto& investment : investments) {
        std::string_view label = InvestmentTypeLookup(investment.first);
        qreal percentage       = investment.second / total_value;

        QPieSlice* slice = new QPieSlice();
        slice->setValue(investment.second);
        slice->setLabel(
            QString("%1 (%2%)")
                .arg(label)
                .arg(percentage * 100, 0, 'f', 2)
            );

        m_pieSeries->append(slice);
    }

    // Update the totals
    setTotalProfit(total_profit);
    setTotalValue(total_value);
}

// ~~ Q_PROPERTY Setters/Getters ~~
QPieSeries* PortfolioPageHelper::pieSeries() const {
    return m_pieSeries;
}

void PortfolioPageHelper::setPieSeries(QPieSeries* newPieSeries) {
    m_pieSeries = newPieSeries;
}

QStandardItemModel *PortfolioPageHelper::portfolioModel() const {
    return m_portfolioModel;
}

void PortfolioPageHelper::setPortfolioModel(QStandardItemModel* newPortfolioModel) {
    m_portfolioModel = newPortfolioModel;
}

qreal PortfolioPageHelper::totalProfit() const {
    return m_totalProfit;
}

qreal PortfolioPageHelper::totalValue() const {
    return m_totalValue;
}

void PortfolioPageHelper::setTotalValue(qreal new_total_value) noexcept{
    if(m_totalValue == new_total_value)
        return;

    m_totalValue = new_total_value;
    emit totalValueChanged();
}

void PortfolioPageHelper::setTotalProfit(qreal new_total_profit) noexcept {
    if(m_totalProfit == new_total_profit)
        return;

    m_totalProfit = new_total_profit;
    emit totalProfitChanged();
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


