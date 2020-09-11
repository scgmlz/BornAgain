// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentPresenter.h
//! @brief     Defines class InstrumentPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTPRESENTER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTPRESENTER_H

#include "GUI/coregui/Views/CommonWidgets/ItemComboWidget.h"

//! Contains stack of instrument editors and the logic to show proper editor for certain type
//! of instrument (GISAS, OffSpec and Specular). Main component of InstrumentEditorWidget.

class BA_CORE_API_ InstrumentPresenter : public ItemComboWidget
{
    Q_OBJECT

public:
    explicit InstrumentPresenter(QWidget* parent = nullptr);

protected:
    QString itemPresentation() const override;
    QStringList activePresentationList(SessionItem* item) override;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTPRESENTER_H
