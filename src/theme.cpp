#include "theme.hpp"

#include "StQMLTypes.hpp"

Theme::Theme(const char* name, QObject* parent) :
    QObject(parent),
    m_isDarkTheme(false)
{
    // Register this singleton instance in qml
    ST_QML_REGISTER_SINGLETON_INSTANCE(Theme, name, this);
}

QColor Theme::firstColor() const {
    return m_firstColor;
}

void Theme::setFirstColor(const QColor &newFirstColor) {
    if (m_firstColor == newFirstColor)
        return;

    m_firstColor = newFirstColor;

    emit firstColorChanged();
}

QColor Theme::secondColor() const {
    return m_secondColor;
}

void Theme::setSecondColor(const QColor &newSecondColor) {
    if (m_secondColor == newSecondColor)
        return;

    m_secondColor = newSecondColor;

    emit secondColorChanged();
}

bool Theme::isDarkTheme() const {
    return m_isDarkTheme;
}

void Theme::setIsDarkTheme(bool newIsDarkTheme) {
    if (m_isDarkTheme == newIsDarkTheme)
        return;

    m_isDarkTheme = newIsDarkTheme;
    emit isDarkThemeChanged();
}
