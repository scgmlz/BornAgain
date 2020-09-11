// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/WarningSignWidget.h
//! @brief     Defines class WarningSignWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_WARNINGSIGNWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_WARNINGSIGNWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QPixmap>
#include <QString>
#include <QWidget>

//! The WarningSignWidget is an transparent widget with warning sign pixmap intended to be
//! overlayed onto other widget at some arbitrary position.
class WarningSignWidget : public QWidget
{
public:
    WarningSignWidget(QWidget* parent = 0);

    void setPosition(int x, int y);

    void setWarningHeader(const QString& message);
    void setWarningMessage(const QString& message) { m_warning_message = message; }

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    QPixmap m_pixmap;
    QString m_warning_header;
    QString m_warning_message;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_WARNINGSIGNWIDGET_H
