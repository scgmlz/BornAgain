// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitParameterWidget.h
//! @brief     Defines class FitParameterWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITPARAMETERWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITPARAMETERWIDGET_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"
#include <memory>

class JobItem;
class ParameterTuningWidget;
class QTreeView;
class QAction;
class QMenu;
class FitParameterProxyModel;
class ParameterItem;
class FitParameterItem;
class FitParameterLinkItem;
class QItemSelection;
class SessionModelDelegate;
class DeleteEventFilter;
class OverlayLabelController;

//! The FitParametersWidget class contains a tree view to set fit parameters (fix/release,
//! starting value, min/max bounds). It occupies buttom right corner of JobView.

class BA_CORE_API_ FitParameterWidget : public SessionItemWidget
{
    Q_OBJECT
public:
    FitParameterWidget(QWidget* parent = 0);

    void setParameterTuningWidget(ParameterTuningWidget* tuningWidget);

    //    QSize sizeHint() const;
    //    QSize minimumSizeHint() const;

public slots:
    void onTuningWidgetContextMenu(const QPoint& point);
    void onFitParameterTreeContextMenu(const QPoint& point);
    void onTuningWidgetSelectionChanged(const QItemSelection& selection);
    void onFitParametersSelectionChanged(const QItemSelection& selection);

private slots:
    void onCreateFitParAction();
    void onRemoveFromFitParAction();
    void onRemoveFitParAction();
    void onAddToFitParAction(int ipar);
    void onFitParameterModelChange();

protected:
    void contextMenuEvent(QContextMenuEvent* event);
    void subscribeToItem();

private:
    void init_actions();
    void initTuningWidgetContextMenu(QMenu& menu);
    void initFitParameterTreeContextMenu(QMenu& menu);

    void init_fit_model();

    bool canCreateFitParameter();
    bool canRemoveFromFitParameters();

    void setActionsEnabled(bool value);
    void connectTuningWidgetSelection(bool active);
    void connectFitParametersSelection(bool active);
    JobItem* jobItem();

    QVector<FitParameterItem*> selectedFitParameters();
    QVector<FitParameterItem*> emptyFitParameters();
    QVector<FitParameterLinkItem*> selectedFitParameterLinks();

    void spanParameters();
    void updateInfoLabel();

    QTreeView* m_treeView;
    ParameterTuningWidget* m_tuningWidget;
    QAction* m_createFitParAction;
    QAction* m_removeFromFitParAction;
    QAction* m_removeFitParAction;
    FitParameterProxyModel* m_fitParameterModel;
    SessionModelDelegate* m_delegate;
    DeleteEventFilter* m_keyboardFilter;
    OverlayLabelController* m_infoLabel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITPARAMETERWIDGET_H
