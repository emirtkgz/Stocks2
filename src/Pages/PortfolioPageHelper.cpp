#include "PortfolioPageHelper.hpp"

#include <nlohmann/json.hpp>

#include "InvestmentType.hpp"
#include "API/StockData.hpp"
#include "SQL/PortfolioSQL.hpp"
#include "Settings.hpp"

using json = nlohmann::json;

enum PortfolioModelRoles {
    Name           = Qt::UserRole + 1,
    Type           = Qt::UserRole + 2,
    AveragePrice   = Qt::UserRole + 3,
    Currency       = Qt::UserRole + 4,
    Amount         = Qt::UserRole + 5,
    Profit         = Qt::UserRole + 6,
    IsPriceCurrent = Qt::UserRole + 7,
    Price          = Qt::UserRole + 8
};

PortfolioPageHelper::PortfolioPageHelper(QObject* parent) :
    QObject(parent)
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
        {PortfolioModelRoles::Price,          "price"}
    });
}

PortfolioPageHelper::~PortfolioPageHelper() {}

void PortfolioPageHelper::updatePieSlices(const nlohmann::json& portfolio) {
    std::unordered_map<InvestmentType, qreal> investments;
    qreal total_value = 0;

    // Iterate for each entry in portfolio
    for(auto& entry : portfolio) {

        // Fetch the price
        qreal price = entry["lastPrice"]["price"];

        // Convert to preferred currency
        const std::string currency = entry["currency"];

        if(currency != Settings::currency) {
            try {
                // Use yfinance to fetch
                qreal parity = StockData::getCurrentPrice(currency + Settings::currency + "=X");
                price *= parity;
            } catch(...) {
                price = 0;
            }
        }

        const InvestmentType type  = entry["type"];
        const qreal amount         = entry["amount"];
        const qreal value          = amount * price;

        // Check if that investment type already exists
        auto it = investments.find(type);
        if(it != investments.end()) {
            // If exists add it to the total
            it->second += value;
        }
        else {
            // If not create a new pair
            investments.emplace(type, value);
        }

        // Add to the total
        total_value += value;
    }

    // Clear the previous data
    m_pieSeries->clear();

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
}

void PortfolioPageHelper::updatePortfolioModel(const nlohmann::json& portfolio) {
    // Create QStandardItem for each entry in portfolio
    for(auto& entry : portfolio) {

        // Fetch the price
        qreal price = entry["lastPrice"]["price"];
        bool isPriceCurrent = true; // TODO: handle this

        // Calculate the profit
        const qreal amount    = entry["amount"];
        const qreal avg_price = entry["avg_price"];
        const qreal profit    = amount * (price - avg_price);

        // Get the type as a string
        const QString type = QString::fromStdString(InvestmentTypeLookup(entry["type"]));

        // Other values
        const QString name     = QString::fromStdString(entry["name"]);
        const QString currency = QString::fromStdString(entry["currency"]);

        // Fill the item
        QStandardItem* item = new QStandardItem();
        item->setData(name,           PortfolioModelRoles::Name);
        item->setData(type,           PortfolioModelRoles::Type);
        item->setData(avg_price,      PortfolioModelRoles::AveragePrice);
        item->setData(currency,       PortfolioModelRoles::Currency);
        item->setData(amount,         PortfolioModelRoles::Amount);
        item->setData(profit,         PortfolioModelRoles::Profit);
        item->setData(isPriceCurrent, PortfolioModelRoles::IsPriceCurrent);
        item->setData(price,          PortfolioModelRoles::Price);

        m_portfolioModel->appendRow(item);
    }
}


void PortfolioPageHelper::updatePage() {
    auto portfolio = PortfolioSQL::query(Settings::username);

    updatePieSlices(portfolio);
    updatePortfolioModel(portfolio);
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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
