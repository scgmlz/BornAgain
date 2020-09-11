// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/Histogram2D.cpp
//! @brief     Implements class Histogram2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Intensity/Histogram2D.h"
#include "Core/Binning/VariableBinAxis.h"
#include "Core/Intensity/ArrayUtils.h"
#include "Core/Intensity/Histogram1D.h"
#include <memory>

Histogram2D::Histogram2D(int nbinsx, double xlow, double xup, int nbinsy, double ylow, double yup)
{
    m_data.addAxis(FixedBinAxis("x-axis", nbinsx, xlow, xup));
    m_data.addAxis(FixedBinAxis("y-axis", nbinsy, ylow, yup));
}

Histogram2D::Histogram2D(int nbinsx, const std::vector<double>& xbins, int nbinsy,
                         const std::vector<double>& ybins)
{
    m_data.addAxis(VariableBinAxis("x-axis", nbinsx, xbins));
    m_data.addAxis(VariableBinAxis("y-axis", nbinsy, ybins));
}

Histogram2D::Histogram2D(const IAxis& axis_x, const IAxis& axis_y) : IHistogram(axis_x, axis_y) {}

Histogram2D::Histogram2D(const OutputData<double>& data)
{
    init_from_data(data);
}

// IMPORTANT intentionally passed by copy to avoid problems on Python side
Histogram2D::Histogram2D(std::vector<std::vector<double>> data)
{
    initFromShape(data);
    this->setContent(data);
}

Histogram2D* Histogram2D::clone() const
{
    return new Histogram2D(*this);
}

int Histogram2D::fill(double x, double y, double weight)
{
    if (x < getXaxis().getMin() || x >= getXaxis().getMax())
        return -1;
    if (y < getYaxis().getMin() || y >= getYaxis().getMax())
        return -1;
    size_t index = m_data.findGlobalIndex({x, y});
    m_data[index].add(weight);
    return (int)index;
}

Histogram1D* Histogram2D::projectionX()
{
    return create_projectionX(0, static_cast<int>(getXaxis().size()) - 1);
}

Histogram1D* Histogram2D::projectionX(double yvalue)
{
    int ybin_selected = static_cast<int>(getYaxis().findClosestIndex(yvalue));
    return create_projectionX(ybin_selected, ybin_selected);
}

Histogram1D* Histogram2D::projectionX(double ylow, double yup)
{
    int ybinlow = static_cast<int>(getYaxis().findClosestIndex(ylow));
    int ybinup = static_cast<int>(getYaxis().findClosestIndex(yup));
    return create_projectionX(ybinlow, ybinup);
}

Histogram1D* Histogram2D::projectionY()
{
    return create_projectionY(0, static_cast<int>(getXaxis().size()) - 1);
}

Histogram1D* Histogram2D::projectionY(double xvalue)
{
    int xbin_selected = static_cast<int>(getXaxis().findClosestIndex(xvalue));
    return create_projectionY(xbin_selected, xbin_selected);
}

Histogram1D* Histogram2D::projectionY(double xlow, double xup)
{
    int xbinlow = static_cast<int>(getXaxis().findClosestIndex(xlow));
    int xbinup = static_cast<int>(getXaxis().findClosestIndex(xup));
    return create_projectionY(xbinlow, xbinup);
}

Histogram2D* Histogram2D::crop(double xmin, double ymin, double xmax, double ymax)
{
    const std::unique_ptr<IAxis> xaxis(getXaxis().createClippedAxis(xmin, xmax));
    const std::unique_ptr<IAxis> yaxis(getYaxis().createClippedAxis(ymin, ymax));

    Histogram2D* result = new Histogram2D(*xaxis, *yaxis);
    OutputData<CumulativeValue>::const_iterator it_origin = m_data.begin();
    OutputData<CumulativeValue>::iterator it_result = result->m_data.begin();
    while (it_origin != m_data.end()) {
        double x = m_data.getAxisValue(it_origin.getIndex(), 0);
        double y = m_data.getAxisValue(it_origin.getIndex(), 1);
        if (result->getXaxis().contains(x) && result->getYaxis().contains(y)) {
            *it_result = *it_origin;
            ++it_result;
        }
        ++it_origin;
    }
    return result;
}

void Histogram2D::setContent(const std::vector<std::vector<double>>& data)
{
    reset();
    addContent(data);
}

void Histogram2D::addContent(const std::vector<std::vector<double>>& data)
{
    auto shape = ArrayUtils::getShape(data);
    const size_t nrows = shape.first;
    const size_t ncols = shape.second;

    if (nrows != m_data.getAxis(1).size() || ncols != m_data.getAxis(0).size()) {
        std::ostringstream ostr;
        ostr << "Histogram2D::addContent() -> Shape of input array [" << nrows << ", " << ncols
             << "] doesn't mach histogram axes. "
             << "X-axis size: " << m_data.getAxis(0).size()
             << "Y-axis size: " << m_data.getAxis(1).size();
        throw Exceptions::LogicErrorException(ostr.str());
    }

    for (size_t row = 0; row < nrows; ++row) {
        for (size_t col = 0; col < ncols; ++col) {
            size_t globalbin = nrows - row - 1 + col * nrows;
            m_data[globalbin].add(data[row][col]);
        }
    }
}

Histogram1D* Histogram2D::create_projectionX(int ybinlow, int ybinup)
{
    Histogram1D* result = new Histogram1D(this->getXaxis());

    for (size_t index = 0; index < getTotalNumberOfBins(); ++index) {

        int ybin = static_cast<int>(getYaxisIndex(index));

        if (ybin >= ybinlow && ybin <= ybinup) {
            result->fill(getXaxisValue(index), getBinContent(index));
        }
    }
    return result;
}

Histogram1D* Histogram2D::create_projectionY(int xbinlow, int xbinup)
{
    Histogram1D* result = new Histogram1D(this->getYaxis());

    for (size_t index = 0; index < getTotalNumberOfBins(); ++index) {

        int xbin = static_cast<int>(getXaxisIndex(index));

        if (xbin >= xbinlow && xbin <= xbinup) {
            result->fill(getYaxisValue(index), getBinContent(index));
        }
    }
    return result;
}
