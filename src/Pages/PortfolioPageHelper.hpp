#pragma once

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
public:
    PortfolioPageHelper(QObject* parent = nullptr);
    ~PortfolioPageHelper();

    // ~~ Q_PROPERTY Setters/Getters ~~
    QPieSeries* pieSeries() const;
    void setPieSeries(QPieSeries *newPieSeries);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    QStandardItemModel *portfolioModel() const;
    void setPortfolioModel(QStandardItemModel *newPortfolioModel);

public slots:
    void updatePieSlices();
    void updatePortfolioModel();

private:
    QPieSeries* m_pieSeries              = nullptr;
    QStandardItemModel* m_portfolioModel = nullptr;
};
