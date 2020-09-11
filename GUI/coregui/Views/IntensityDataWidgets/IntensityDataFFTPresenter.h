// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataFFTPresenter.h
//! @brief     Defines class IntensityDataFFTPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAFFTPRESENTER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAFFTPRESENTER_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class SessionModel;
class IntensityDataItem;
class QWidget;
class QAction;

//! Provides support in Fast Fourier transformation of IntensityDataItem.
//! Contains own model to hold IntensityDataItem with fft-transformed results.

class BA_CORE_API_ IntensityDataFFTPresenter : public QObject
{
    Q_OBJECT
public:
    IntensityDataFFTPresenter(QWidget* parent = nullptr);

    void reset();

    IntensityDataItem* fftItem(IntensityDataItem* origItem);

    QList<QAction*> actionList();

    bool inFFTMode() const;

signals:
    void fftActionRequest();

private slots:
    void onFFTActionRequest();

private:
    QAction* m_fftAction;
    SessionModel* m_fftModel;
    IntensityDataItem* m_fftItem;
    bool m_in_fft_mode;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAFFTPRESENTER_H
