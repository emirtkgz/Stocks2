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
    Q_PROPERTY(QColor headerTextColor READ headerTextColor WRITE setHeaderTextColor NOTIFY headerTextColorChanged)
    Q_PROPERTY(QColor bodyTextColor READ bodyTextColor WRITE setBodyTextColor NOTIFY bodyTextColorChanged)
    Q_PROPERTY(bool isDarkTheme READ isDarkTheme WRITE setIsDarkTheme NOTIFY isDarkThemeChanged)

    QColor firstColor() const;
    void setFirstColor(const QColor &newFirstColor);

    QColor secondColor() const;
    void setSecondColor(const QColor &newSecondColor);

    bool isDarkTheme() const;
    void setIsDarkTheme(bool newIsDarkTheme);

    QColor headerTextColor() const;
    void setHeaderTextColor(const QColor &newHeaderTextColor);

    QColor bodyTextColor() const;
    void setBodyTextColor(const QColor &newBodyTextColor);

signals:
    void firstColorChanged();
    void secondColorChanged();
    void isDarkThemeChanged();

    void headerTextColorChanged();

    void bodyTextColorChanged();

private:
    QColor m_firstColor;
    QColor m_secondColor;
    bool m_isDarkTheme;
    QColor m_headerTextColor;
    QColor m_bodyTextColor;
};

