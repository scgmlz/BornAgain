// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorCanvas.h
//! @brief     Defines class MaskEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORCANVAS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORCANVAS_H

#include "GUI/coregui/Views/MaskWidgets/MaskEditorFlags.h"
#include <QWidget>

class MaskGraphicsScene;
class MaskGraphicsView;
class SessionModel;
class QItemSelectionModel;
class QModelIndex;
class MaskResultsPresenter;
class IntensityDataItem;
class PlotStatusLabel;
class IntensityDataItem;

//! Painting widget for MaskEditor, contains graphics scene and graphics view

class MaskEditorCanvas : public QWidget
{
    Q_OBJECT
public:
    MaskEditorCanvas(QWidget* parent = 0);

    void setMaskContext(SessionModel* model, const QModelIndex& maskContainerIndex,
                        IntensityDataItem* intensityItem);

    void resetContext();

    void setSelectionModel(QItemSelectionModel* model);

    MaskGraphicsScene* getScene();

signals:
    void changeActivityRequest(MaskEditorFlags::Activity);
    void deleteSelectedRequest();

public slots:
    void onPresentationTypeRequest(MaskEditorFlags::PresentationType presentationType);
    void onSavePlotRequest();
    void onResetViewRequest();

private:
    bool isAxisRangeMatchData() const;
    void setZoomToROI();

    MaskGraphicsScene* m_scene;
    MaskGraphicsView* m_view;
    IntensityDataItem* m_intensityDataItem;
    PlotStatusLabel* m_statusLabel;
    MaskResultsPresenter* m_resultsPresenter;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORCANVAS_H
