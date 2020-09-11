// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorPropertyPanel.h
//! @brief     Defines class MaskEditorPropertyPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORPROPERTYPANEL_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORPROPERTYPANEL_H

#include "GUI/coregui/Views/MaskWidgets/MaskEditorFlags.h"
#include <QModelIndex>
#include <QWidget>

class QListView;
class SessionModel;
class ComponentEditor;
class QItemSelection;
class QItemSelectionModel;
class IntensityDataItem;
class AccordionWidget;

//! Tool widget for MaskEditor

class MaskEditorPropertyPanel : public QWidget
{
    Q_OBJECT
public:
    MaskEditorPropertyPanel(QWidget* parent = nullptr);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    void setMaskContext(SessionModel* model, const QModelIndex& maskContainerIndex,
                        IntensityDataItem* intensityItem);

    void resetContext();

    QItemSelectionModel* selectionModel();

    void setPanelHidden(bool value);

signals:
    void itemContextMenuRequest(const QPoint& point);

private slots:
    void onSelectionChanged(const QItemSelection& selected, const QItemSelection&);
    void onCustomContextMenuRequested(const QPoint& point);

private:
    void setup_MaskStack(AccordionWidget* accordion);
    void setup_MaskProperties(AccordionWidget* accordion);
    void setup_PlotProperties(AccordionWidget* accordion);

    QListView* m_listView;
    ComponentEditor* m_maskPropertyEditor;
    ComponentEditor* m_plotPropertyEditor;
    AccordionWidget* m_accordion;
    SessionModel* m_maskModel;
    QModelIndex m_rootIndex;
    IntensityDataItem* m_intensityDataItem;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORPROPERTYPANEL_H
