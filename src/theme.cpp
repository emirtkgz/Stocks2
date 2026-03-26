#include "theme.hpp"

#include "Package.hpp"

Theme::Theme(const char* name, QObject* parent) : QObject(parent) {
    // Register this singleton instance in qml
    qmlRegisterSingletonInstance<Theme>(StPackage::name, StPackage::majorVersion, StPackage::minorVersion, name, this);
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
