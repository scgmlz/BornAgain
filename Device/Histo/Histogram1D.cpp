//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Histo/Histogram1D.cpp
//! @brief     Implements class Histogram1D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Histo/Histogram1D.h"
#include "Base/Axis/VariableBinAxis.h"
#include "Base/Py/PyUtils.h"
#include <memory>

Histogram1D::Histogram1D(int nbinsx, double xlow, double xup) {
    m_data.addAxis(FixedBinAxis("x-axis", nbinsx, xlow, xup));
}

Histogram1D::Histogram1D(int nbinsx, const std::vector<double>& xbins) {
    m_data.addAxis(VariableBinAxis("x-axis", nbinsx, xbins));
}

Histogram1D::Histogram1D(const IAxis& axis) : IHistogram(axis) {}

Histogram1D::Histogram1D(const OutputData<double>& data) {
    init_from_data(data);
}

Histogram1D* Histogram1D::clone() const {
    return new Histogram1D(*this);
}

int Histogram1D::fill(double x, double weight) {
    const IAxis& axis = xAxis();
    if (!axis.contains(x))
        return -1;
    size_t index = axis.findClosestIndex(x);
    m_data[index].add(weight);
    return (int)index;
}

std::vector<double> Histogram1D::binCenters() const {
    return xAxis().binCenters();
}

std::vector<double> Histogram1D::binValues() const {
    return IHistogram::getDataVector(IHistogram::DataType::INTEGRAL);
}

std::vector<double> Histogram1D::binErrors() const {
    return IHistogram::getDataVector(IHistogram::DataType::STANDARD_ERROR);
}

#ifdef BORNAGAIN_PYTHON

PyObject* Histogram1D::binCentersNumpy() const {
    return PyUtils::createNumpyArray(binCenters());
}

PyObject* Histogram1D::binValuesNumpy() const {
    return PyUtils::createNumpyArray(binValues());
}

PyObject* Histogram1D::binErrorsNumpy() const {
    return PyUtils::createNumpyArray(binErrors());
}

#endif // BORNAGAIN_PYTHON

Histogram1D* Histogram1D::crop(double xmin, double xmax) {
    const std::unique_ptr<IAxis> xaxis(xAxis().createClippedAxis(xmin, xmax));
    Histogram1D* result = new Histogram1D(*xaxis);
    OutputData<CumulativeValue>::const_iterator it_origin = m_data.begin();
    OutputData<CumulativeValue>::iterator it_result = result->m_data.begin();
    while (it_origin != m_data.end()) {
        double x = m_data.getAxisValue(it_origin.getIndex(), 0);
        if (result->xAxis().contains(x)) {
            *it_result = *it_origin;
            ++it_result;
        }
        ++it_origin;
    }
    return result;
}
