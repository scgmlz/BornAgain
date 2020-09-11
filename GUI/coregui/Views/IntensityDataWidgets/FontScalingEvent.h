// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/FontScalingEvent.h
//! @brief     Defines class FontScalingEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_FONTSCALINGEVENT_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_FONTSCALINGEVENT_H

#include "Wrap/WinDllMacros.h"
#include <QFont>
#include <QMap>
#include <QObject>

class QEvent;
class ScientificPlot;

//! Provides event filter for ScientificPlot. Its goal is to make font size adjustments
//! on resize events.

class BA_CORE_API_ FontScalingEvent : public QObject
{
    Q_OBJECT

public:
    explicit FontScalingEvent(ScientificPlot* plot, QWidget* parent);

protected:
    bool eventFilter(QObject* obj, QEvent* event);

private:
    void backupFonts();
    void restoreFonts();
    void scaleFonts(double factor);
    void setTickLabelFont(const QFont& font);

    ScientificPlot* m_plot;
    QMap<QString, QFont> m_fonts;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_FONTSCALINGEVENT_H
