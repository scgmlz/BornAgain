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

#include "IntensityDataFFTPresenter.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataItem.h"
#include "SessionModel.h"
#include "GUIHelpers.h"
#include <QWidget>
#include <QApplication>
#include <QAction>

IntensityDataFFTPresenter::IntensityDataFFTPresenter(QWidget* parent)
    : QObject(parent)
    , m_fftAction(nullptr)
    , m_fftModel(new SessionModel("TempFFTModel", this))
    , m_fftItem(nullptr)
    , m_in_fft_mode(false)
{
    m_fftItem
        = dynamic_cast<IntensityDataItem*>(m_fftModel->insertNewItem(Constants::IntensityDataType));

    m_fftAction = new QAction(this);
    m_fftAction->setText("Fourier");
    m_fftAction->setIcon(QIcon(":/images/toolbar16light_fft.svg"));
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
