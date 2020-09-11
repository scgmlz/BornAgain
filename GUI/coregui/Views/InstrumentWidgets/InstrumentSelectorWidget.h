// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentSelectorWidget.h
//! @brief     Defines class InstrumentSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTSELECTORWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTSELECTORWIDGET_H

#include "GUI/coregui/Views/CommonWidgets/ItemSelectorWidget.h"

class InstrumentModel;

//! Instrument selector on the left side of InstrumentView.

class BA_CORE_API_ InstrumentSelectorWidget : public ItemSelectorWidget
{
    Q_OBJECT

public:
    InstrumentSelectorWidget(InstrumentModel* model = nullptr, QWidget* parent = nullptr);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTSELECTORWIDGET_H
