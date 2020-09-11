// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemComboWidget.h
//! @brief     Defines class ItemComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMCOMBOWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMCOMBOWIDGET_H

#include "Fit/TestEngine/IFactory.h"
#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"
#include "Wrap/WinDllMacros.h"
#include <QMap>
#include <QString>
#include <QWidget>

class SessionItem;
class SessionItemWidget;
class ItemComboToolBar;
class QStackedWidget;

//! The ItemComboWidget class combines stack of widgets with QComboBox controller to switch between
//! widgets. It is used in the case when one SessionItem can be presented with different widgets.

//! For example, in JobOutputDataWidget the results of the job can be presented with either
//! IntensityDataWidget or FitDataWidget, depending from the JobView's activity type.

class BA_CORE_API_ ItemComboWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    using factory_function_t = std::function<SessionItemWidget*()>;

    explicit ItemComboWidget(QWidget* parent = 0);

    void registerWidget(const QString& presentationType, factory_function_t);

    virtual void setPresentation(const QString& presentationType);

    void setToolBarVisible(bool value);

protected:
    virtual QStringList activePresentationList(SessionItem* item);
    virtual QStringList presentationList(SessionItem* item);
    virtual QString itemPresentation() const;
    QString selectedPresentation() const;
    //    SessionItem* currentItem();
    //    const SessionItem* currentItem() const;
    void subscribeToItem();

private slots:
    void onComboChanged(const QString& name);

private:
    void setSizeToCurrentWidget();

    ItemComboToolBar* m_toolBar;
    QStackedWidget* m_stackedWidget;
    //    SessionItem* m_currentItem;
    IFactory<QString, SessionItemWidget> m_widgetFactory;
    QMap<QString, SessionItemWidget*> m_presentationTypeToWidget;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMCOMBOWIDGET_H
