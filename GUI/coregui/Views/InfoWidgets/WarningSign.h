// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/WarningSign.h
//! @brief     Defines class WarningSign
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_WARNINGSIGN_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_WARNINGSIGN_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class WarningSignWidget;
class QWidget;

//! The WarningSign controls appearance of WarningSignWidget on top of parent widget.

class WarningSign : public QObject
{
public:
    WarningSign(QWidget* parent);

    void clear();

    void setWarningHeader(const QString& warningHeader);

    void setWarningMessage(const QString& warningMessage);

    void setArea(QWidget* area);

    bool isShown() const;

protected:
    bool eventFilter(QObject* obj, QEvent* event);

private:
    void updateLabelGeometry();
    QPoint positionForWarningSign() const;

    QString m_warning_header;
    QString m_warning_message;
    WarningSignWidget* m_warningWidget;
    QWidget* m_area;
    bool m_clear_just_had_happened;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_WARNINGSIGN_H
