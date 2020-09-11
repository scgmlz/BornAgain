// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/PropertyRepeater.h
//! @brief     Defines class PropertyRepeater
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_PROPERTYREPEATER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_PROPERTYREPEATER_H

#include "Wrap/WinDllMacros.h"
#include <QMap>
#include <QObject>
#include <QVector>

class SessionItem;

//! Tracks property change (axes range, units etc) for the collection of IntensityDataItems
//! and sets same properties for all of them.

class BA_CORE_API_ PropertyRepeater : public QObject
{
    Q_OBJECT
public:
    explicit PropertyRepeater(QObject* parent = nullptr, bool repeat_child_properties = false);
    ~PropertyRepeater();

    void addItem(SessionItem* sessionItem);

    void clear();

    void setActive(bool isActive);

private:
    void onPropertyChanged(SessionItem* item, const QString& propertyName);
    void setOnChildPropertyChange(SessionItem* item, const QString& propertyName);
    QVector<SessionItem*> targetItems(SessionItem* sourceItem);

    QVector<SessionItem*> m_dataItems;
    bool m_block_repeater;
    bool m_repeat_child_properties;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_PROPERTYREPEATER_H
