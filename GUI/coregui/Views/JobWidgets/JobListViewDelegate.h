// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobListViewDelegate.h
//! @brief     Defines class JobListViewDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBLISTVIEWDELEGATE_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBLISTVIEWDELEGATE_H

#include "Wrap/WinDllMacros.h"
#include <QItemDelegate>
#include <QMap>
#include <QRect>

class JobItem;

//! ViewDelegate to show progress bar JobQueuListView
class BA_CORE_API_ JobListViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    JobListViewDelegate(QWidget* parent);

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const;

    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option,
                     const QModelIndex& index);

signals:
    void cancelButtonClicked(const QModelIndex& index);

private:
    QStyle::State m_buttonState;
    void drawCustomProjectBar(const JobItem* item, QPainter* painter,
                              const QStyleOptionViewItem& option) const;

    QRect getTextRect(QRect optionRect) const;
    QRect getProgressBarRect(QRect optionRect) const;
    QRect getButtonRect(QRect optionRect) const;

    QMap<QString, QColor> m_status_to_color;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBLISTVIEWDELEGATE_H
