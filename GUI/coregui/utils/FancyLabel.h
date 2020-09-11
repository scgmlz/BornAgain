// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/FancyLabel.h
//! @brief     Defines class FancyLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_UTILS_FANCYLABEL_H
#define BORNAGAIN_GUI_COREGUI_UTILS_FANCYLABEL_H

#include "Wrap/WinDllMacros.h"
#include <QLabel>

//! The FancyLabel class is QLabel-like class with trivail animation, when text slowly
//! appears on the screen from left to right pretending to be typed
class BA_CORE_API_ FancyLabel : public QLabel
{
    Q_OBJECT
public:
    FancyLabel(const QString& text, QWidget* parent = 0);
    FancyLabel(QWidget* parent = 0);

    void setTextAnimated(const QString& animated_text);

private slots:
    void timeout();

private:
    void init_fancy_label();

    QString m_text;
    QTimer* m_timer;
    int m_total_effect_duration;
    int m_current_index;
};

#endif // BORNAGAIN_GUI_COREGUI_UTILS_FANCYLABEL_H
