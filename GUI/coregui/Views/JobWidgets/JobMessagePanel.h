// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobMessagePanel.h
//! @brief     Defines class JobMessagePanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBMESSAGEPANEL_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBMESSAGEPANEL_H

#include "GUI/coregui/Views/CommonWidgets/InfoPanel.h"
#include <QColor>

class QTextEdit;

//! The JobMessagePanel class shows log messages from FitActivityPanel at the
//! bottom part of JobView.

class BA_CORE_API_ JobMessagePanel : public InfoPanel
{
    Q_OBJECT
public:
    JobMessagePanel(QWidget* parent = 0);

public slots:
    void onClearLog();
    void onMessage(const QString& message, const QColor& color = QColor(Qt::black));

private:
    QTextEdit* m_plainLog;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBMESSAGEPANEL_H
