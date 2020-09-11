// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemComboToolBar.h
//! @brief     Defines class ItemComboToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMCOMBOTOOLBAR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMCOMBOTOOLBAR_H

#include "GUI/coregui/mainwindow/StyledToolBar.h"
#include <QList>

class QAction;
class QComboBox;

//! The ItemComboToolBar class is a styled toolbar on top of ItemComboWidget. Contains
//! ComboBox to switch ItemComboWidget, and dynamic list of actions, which are updated
//! according to current state of ItemComboWidget.

class BA_CORE_API_ ItemComboToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit ItemComboToolBar(QWidget* parent = 0);

    void setPresentation(const QString& name);

    void setPresentationList(const QStringList& presentationList,
                             const QStringList& activeList = {});

    QString currentPresentation() const;

    void setActionList(const QList<QAction*>& actionList);

signals:
    void comboChanged(const QString& presentation);

private:
    void setComboConnected(bool value);
    void makeItemsEnabled(const QStringList& activePresentations);

    QComboBox* m_comboBox;
    QAction* m_comboBoxAction;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMCOMBOTOOLBAR_H
