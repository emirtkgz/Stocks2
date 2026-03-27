#pragma once

#include <QObject>
#include <QtQuick/QtQuick>
#include <QtQml/qqmlregistration.h>
#include <QtQmlIntegration/qqmlintegration.h>

class Theme : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    Theme(const char* name, QObject* parent = nullptr);

    Q_PROPERTY(QColor firstColor READ firstColor WRITE setFirstColor NOTIFY firstColorChanged)
    Q_PROPERTY(QColor secondColor READ secondColor WRITE setSecondColor NOTIFY secondColorChanged)
    Q_PROPERTY(bool isDarkTheme READ isDarkTheme WRITE setIsDarkTheme NOTIFY isDarkThemeChanged)

    QColor firstColor() const;
    void setFirstColor(const QColor &newFirstColor);

    QColor secondColor() const;
    void setSecondColor(const QColor &newSecondColor);

    bool isDarkTheme() const;
    void setIsDarkTheme(bool newIsDarkTheme);

signals:
    void firstColorChanged();
    void secondColorChanged();
    void isDarkThemeChanged();

private:
    QColor m_firstColor;
    QColor m_secondColor;
    bool m_isDarkTheme;
};

