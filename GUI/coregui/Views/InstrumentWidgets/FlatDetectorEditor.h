// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/FlatDetectorEditor.h
//! @brief     Defines class FlatDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FLATDETECTOREDITOR_H
#define FLATDETECTOREDITOR_H

#include "SessionItemWidget.h"
class FlatDetectorItem;
class ComponentEditor;
class QGridLayout;

class BA_CORE_API_ FlatDetectorEditor : public SessionItemWidget
{
    Q_OBJECT

public:
    FlatDetectorEditor(QWidget* parent = nullptr);

public slots:
    void onPropertyChanged(const QString& propertyName);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();
    FlatDetectorItem* detectorItem();

private:
    void create_editors();
    void init_editors();
    void init_alignment_editors();

    ComponentEditor* m_xAxisEditor;
    ComponentEditor* m_yAxisEditor;
    ComponentEditor* m_resolutionFunctionEditor;
    ComponentEditor* m_alignmentEditor;
    ComponentEditor* m_positionsEditor;
    ComponentEditor* m_normalEditor;
    ComponentEditor* m_directionEditor;
    QGridLayout* m_gridLayout;
};

#endif  // FLATDETECTOREDITOR_H
