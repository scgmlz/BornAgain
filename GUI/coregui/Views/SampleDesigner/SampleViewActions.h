// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewActions.h
//! @brief     Defines class SampleViewActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWACTIONS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWACTIONS_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class SampleModel;
class QItemSelectionModel;
class SampleView;

//! Holds all actions of SampleView.

class SampleViewActions : public QObject
{
    Q_OBJECT
public:
    SampleViewActions(SampleModel* model, SampleView* parent);

    void setSelectionModel(QItemSelectionModel* selection_model);

    SampleModel* sampleModel();

    QItemSelectionModel* selectionModel();

public slots:
    void onToggleRealSpaceView();

private:
    SampleModel* m_model;
    SampleView* m_sampleView;
    QItemSelectionModel* m_selection_model;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWACTIONS_H
