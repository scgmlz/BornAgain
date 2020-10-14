// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataFFTPresenter.cpp
//! @brief     Defines class IntensityDataFFTPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataFFTPresenter.h"
#include "Core/Instrument/IntensityDataFunctions.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QAction>
#include <QApplication>
#include <QWidget>

IntensityDataFFTPresenter::IntensityDataFFTPresenter(QWidget* parent)
    : QObject(parent), m_fftAction(nullptr), m_fftModel(new SessionModel("TempFFTModel", this)),
      m_fftItem(nullptr), m_in_fft_mode(false)
{
    m_fftItem = dynamic_cast<IntensityDataItem*>(m_fftModel->insertNewItem("IntensityData"));

    m_fftAction = new QAction(this);
    m_fftAction->setText("Fourier");
    m_fftAction->setIcon(QIcon(":/images/alpha-f-box.svg"));
    m_fftAction->setToolTip("Get the Fourier Transform of current intensity map");
    connect(m_fftAction, &QAction::triggered, this, &IntensityDataFFTPresenter::onFFTActionRequest);
}

void IntensityDataFFTPresenter::reset()
{
    m_in_fft_mode = false;
}

IntensityDataItem* IntensityDataFFTPresenter::fftItem(IntensityDataItem* origItem)
{
    if (!origItem)
        throw GUIHelpers::Error("IntensityDataFFTPresenter::fftItem() -> Error. Empty item.");

    QApplication::setOverrideCursor(Qt::WaitCursor);

    m_fftItem->setOutputData(
        IntensityDataFunctions::createFFT(*origItem->getOutputData()).release());

    QApplication::restoreOverrideCursor();

    return m_fftItem;
}

QList<QAction*> IntensityDataFFTPresenter::actionList()
{
    return QList<QAction*>() << m_fftAction;
}

bool IntensityDataFFTPresenter::inFFTMode() const
{
    return m_in_fft_mode;
}

void IntensityDataFFTPresenter::onFFTActionRequest()
{
    m_in_fft_mode = !m_in_fft_mode;
    fftActionRequest();
}
