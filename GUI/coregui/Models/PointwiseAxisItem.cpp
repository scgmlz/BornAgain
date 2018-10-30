// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/PointwiseAxisItem.cpp
//! @brief     Implements pointwise axis item
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PointwiseAxisItem.h"
#include "InstrumentItems.h"
#include "IntensityDataIOFactory.h"
#include "IUnitConverter.h"
#include "OutputData.h"
#include "PointwiseAxis.h"

namespace {
std::unique_ptr<OutputData<double>> makeOutputData(const IAxis& axis);
}

const QString PointwiseAxisItem::P_NATIVE_UNITS = "NativeUnits";
const QString PointwiseAxisItem::P_FILE_NAME = "FileName";

PointwiseAxisItem::PointwiseAxisItem()
    : BasicAxisItem(Constants::PointwiseAxisType)
    , m_instrument(nullptr)
{
    getItem(P_MIN)->setEnabled(false);
    getItem(P_NBINS)->setEnabled(false);
    getItem(P_MAX)->setEnabled(false);
    addProperty(P_FILE_NAME, QStringLiteral("undefined"))->setVisible(false);
    addProperty(P_NATIVE_UNITS, Constants::UnitsNbins)->setVisible(false);

    setLastModified(QDateTime::currentDateTime());
    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_FILE_NAME)
            setLastModified(QDateTime::currentDateTime());
    });
}

PointwiseAxisItem::~PointwiseAxisItem() = default;

void PointwiseAxisItem::init(const IAxis& axis, const QString& units_label)
{
    setLastModified(QDateTime::currentDateTime());
    m_axis = std::unique_ptr<IAxis>(axis.clone());
    setItemValue(P_NATIVE_UNITS, units_label);
    findInstrument();
    updateIndicators();
}

const IAxis* PointwiseAxisItem::getAxis() const
{
    return m_axis.get();
}

const QString PointwiseAxisItem::getUnitsLabel() const
{
    return getItemValue(P_NATIVE_UNITS).toString();
}

std::unique_ptr<IAxis> PointwiseAxisItem::createAxis(double scale) const
{
    if (!checkValidity())
        return nullptr;

    const auto converter = m_instrument->createUnitConverter();
    const auto converted_axis = converter->createConvertedAxis(0, AxesUnits::DEGREES);

    //applying scaling
    std::vector<double> centers = converted_axis->getBinCenters();
    std::for_each(centers.begin(), centers.end(), [scale](double& value) { value *= scale; });

    return std::make_unique<PointwiseAxis>(converted_axis->getName(), std::move(centers));
}

bool PointwiseAxisItem::load(const QString& projectDir)
{
    QString filename = SaveLoadInterface::fileName(projectDir);
    auto data = IntensityDataIOFactory::readOutputData(filename.toStdString());
    if (!data)
        return false;

    m_axis = std::unique_ptr<IAxis>(data->getAxis(0).clone());
    findInstrument();
    setLastModified(QDateTime::currentDateTime());
    return true;
}

bool PointwiseAxisItem::save(const QString& projectDir)
{
    if (!containsNonXMLData())
        return false;

    IntensityDataIOFactory::writeOutputData(*makeOutputData(*m_axis),
                                            SaveLoadInterface::fileName(projectDir).toStdString());
    return true;
}

bool PointwiseAxisItem::containsNonXMLData() const
{
    return static_cast<bool>(m_axis);
}

QDateTime PointwiseAxisItem::lastModified() const
{
    return m_last_modified;
}

QString PointwiseAxisItem::fileName() const
{
    return getItemValue(PointwiseAxisItem::P_FILE_NAME).toString();
}

void PointwiseAxisItem::setLastModified(const QDateTime& dtime)
{
    m_last_modified = dtime;
}

bool PointwiseAxisItem::checkValidity() const
{
    return m_axis && m_instrument && getUnitsLabel() != Constants::UnitsNbins;
}

void PointwiseAxisItem::findInstrument()
{
    SessionItem* parent_item = parent();
    while (parent_item && parent_item->modelType() != Constants::SpecularInstrumentType)
        parent_item = parent_item->parent();
    m_instrument = static_cast<SpecularInstrumentItem*>(parent_item);
}

void PointwiseAxisItem::updateIndicators()
{
    if (!checkValidity())
        return;

    const auto converter = m_instrument->createUnitConverter();
    getItem(P_MIN)->setValue(converter->calculateMin(0, AxesUnits::DEGREES));
    getItem(P_MAX)->setValue(converter->calculateMax(0, AxesUnits::DEGREES));
    getItem(P_NBINS)->setValue(static_cast<int>(m_axis->size()));

    emitDataChanged();
}

namespace {
std::unique_ptr<OutputData<double>> makeOutputData(const IAxis& axis)
{
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    result->addAxis(axis);
    return result;
}
}
