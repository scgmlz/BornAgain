// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/ExternalProperty.h
//! @brief     Defines class ExternalProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_EXTERNALPROPERTY_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_EXTERNALPROPERTY_H

#include "Wrap/WinDllMacros.h"
#include <QColor>
#include <QMetaType>
#include <QPixmap>
#include <QString>
#include <QVariant>

//! The ExternalProperty class defines custom QVariant property to carry the text, color and
//! an identifier.

class BA_CORE_API_ ExternalProperty
{
public:
    explicit ExternalProperty();

    QString text() const;
    void setText(const QString& name);

    QColor color() const;
    void setColor(const QColor& color);

    QString identifier() const;
    void setIdentifier(const QString& identifier);

    QPixmap pixmap() const;

    bool isValid() const;

    QVariant variant() const;

    bool operator==(const ExternalProperty& other) const;
    bool operator!=(const ExternalProperty& other) const;
    bool operator<(const ExternalProperty& other) const;

private:
    QString m_text;
    QColor m_color;
    QString m_identifier;
};

Q_DECLARE_METATYPE(ExternalProperty)

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_EXTERNALPROPERTY_H
