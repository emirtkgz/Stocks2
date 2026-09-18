#pragma once

#include <nlohmann/json.hpp>

#include <QtQml/qqmlregistration.h>
#include <QObject>
#include <QQmlEngine>
#include <QList>
#include <QPieSeries>
#include <QStandardItemModel>

class PortfolioPageHelper : public QObject {
    Q_OBJECT
    Q_PROPERTY(QPieSeries* pieSeries READ pieSeries WRITE setPieSeries FINAL)
    Q_PROPERTY(QStandardItemModel* portfolioModel READ portfolioModel WRITE setPortfolioModel FINAL)
    Q_PROPERTY(qreal totalValue READ totalValue WRITE setTotalValue NOTIFY totalValueChanged FINAL)
    Q_PROPERTY(qreal totalProfit READ totalProfit WRITE setTotalProfit NOTIFY totalProfitChanged FINAL)
public:
    PortfolioPageHelper(QObject* parent = nullptr);
    ~PortfolioPageHelper();

    // ~~ Q_PROPERTY Setters/Getters ~~
    QPieSeries* pieSeries() const;
    void setPieSeries(QPieSeries *newPieSeries);

    QStandardItemModel *portfolioModel() const;
    void setPortfolioModel(QStandardItemModel *newPortfolioModel);

    qreal totalProfit() const;

    qreal totalValue() const;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public slots:
    void updatePage();
    void patchNewData(QJSValue data);
    void putNewData(QJSValue data);

signals:
    void totalProfitChanged();

    void totalValueChanged();
private:
    void setTotalValue(qreal new_total_value) noexcept;
    void setTotalProfit(qreal new_total_profit) noexcept;
private:
    QPieSeries* m_pieSeries              = nullptr;
    QStandardItemModel* m_portfolioModel = nullptr;
    qreal m_totalProfit;
    qreal m_totalValue;
};
