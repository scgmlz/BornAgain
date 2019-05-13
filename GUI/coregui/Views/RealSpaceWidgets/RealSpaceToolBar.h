// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceToolBar.h
//! @brief     Defines class RealSpaceWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef REALSPACETOOLBAR_H
#define REALSPACETOOLBAR_H

#include "StyledToolBar.h"

class QToolButton;
class QCheckBox;

//! Thin toolbar on top of RealSpaceWidget.

class BA_CORE_API_ RealSpaceToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    RealSpaceToolBar(QWidget* parent = nullptr);

signals:
    void defaultViewAction();
    void sideViewAction();
    void topViewAction();
    void lockViewAction(bool);
    void changeLayerSizeAction(double);
    void savePictureAction();

private:
    QToolButton* m_defaultViewButton;
    QToolButton* m_sideViewButton;
    QToolButton* m_topViewButton;
    QCheckBox* m_lockViewCheckBox;

    QToolButton* m_increaseLayerSizeButton;
    QToolButton* m_decreaseLayerSizeButton;
    QToolButton* m_savePictureButton;
};

#endif // REALSPACETOOLBAR_H
