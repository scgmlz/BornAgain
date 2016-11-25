// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SphericalDetector.cpp
//! @brief     Implements class SphericalDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SphericalDetector.h"
#include "BornAgainNamespace.h"
#include "IDetectorResolution.h"
#include "IPixelMap.h"
#include "MathConstants.h"
#include "SimulationElement.h"
#include "Units.h"

SphericalDetector::SphericalDetector()
{
    setName(BornAgain::SphericalDetectorType);
    init_parameters();
}

SphericalDetector::SphericalDetector(
    size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min,
    double alpha_max)
{
    setName(BornAgain::SphericalDetectorType);
    init_parameters();
    setDetectorParameters(n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max);
}

SphericalDetector::SphericalDetector(const SphericalDetector& other) : IDetector2D(other)
{
    setName(BornAgain::SphericalDetectorType);
    init_parameters();
}

SphericalDetector* SphericalDetector::clone() const { return new SphericalDetector(*this); }

std::string SphericalDetector::addParametersToExternalPool(
    const std::string& path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string new_path =
        IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the resolution function
    if (mP_detector_resolution)
        mP_detector_resolution->addParametersToExternalPool(new_path, external_pool, -1);
    return new_path;
}

std::vector<IDetector2D::EAxesUnits> SphericalDetector::getValidAxesUnits() const
{
    std::vector<IDetector2D::EAxesUnits> result = IDetector2D::getValidAxesUnits();
    std::vector<IDetector2D::EAxesUnits> addon = { IDetector2D::RADIANS, IDetector2D::DEGREES,
                                                   IDetector2D::QYQZ };
    result.insert(result.end(), addon.begin(), addon.end());
    return result;
}

IDetector2D::EAxesUnits SphericalDetector::getDefaultAxesUnits() const
{
    return IDetector2D::RADIANS;
}

IPixelMap* SphericalDetector::createPixelMap(size_t index) const
{
    const IAxis& phi_axis = getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis& alpha_axis = getAxis(BornAgain::Y_AXIS_INDEX);
    size_t phi_index = getAxisBinIndex(index, BornAgain::X_AXIS_INDEX);
    size_t alpha_index = getAxisBinIndex(index, BornAgain::Y_AXIS_INDEX);

    Bin1D alpha_bin = alpha_axis.getBin(alpha_index);
    Bin1D phi_bin = phi_axis.getBin(phi_index);
    return new AngularPixelMap(alpha_bin, phi_bin);
}

void SphericalDetector::print(std::ostream& ostr) const
{
    ostr << "SphericalDetector: '" << getName() << "' " << getParameterPool();
    for (size_t i = 0; i < m_axes.size(); ++i)
        ostr << "    IAxis:" << *m_axes[i] << std::endl;
}

IAxis* SphericalDetector::createAxis(size_t index, size_t n_bins, double min, double max) const
{
    if (max <= min)
        throw Exceptions::LogicErrorException(
            "SphericalDetector::createAxis() -> Error! max <= min");
    if (n_bins == 0)
        throw Exceptions::LogicErrorException(
            "SphericalDetector::createAxis() -> Error! Number n_bins can't be zero.");
    return new FixedBinAxis(getAxisName(index), n_bins, min, max);
}

void SphericalDetector::calculateAxisRange(
    size_t axis_index, const Beam& beam, IDetector2D::EAxesUnits units, double& amin,
    double& amax) const
{
    amin = 0.0;
    amax = 0.0;
    if (units == DEGREES) {
        amin = getAxis(axis_index).getMin() / Units::degree;
        amax = getAxis(axis_index).getMax() / Units::degree;
    } else if (units == RADIANS) {
        amin = getAxis(axis_index).getMin();
        amax = getAxis(axis_index).getMax();
    } else {
        IDetector2D::calculateAxisRange(axis_index, beam, units, amin, amax);
    }
}

std::string SphericalDetector::getAxisName(size_t index) const
{
    switch (index) {
    case 0:
        return BornAgain::PHI_AXIS_NAME;
    case 1:
        return BornAgain::ALPHA_AXIS_NAME;
    default:
        throw Exceptions::LogicErrorException(
            "SphericalDetector::getAxisName(size_t index) -> Error! index > 1");
    }
}

size_t SphericalDetector::getIndexOfSpecular(const Beam& beam) const
{
    if (getDimension() != 2)
        return getTotalSize();
    double alpha = beam.getAlpha();
    double phi = beam.getPhi();
    const IAxis& phi_axis = getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis& alpha_axis = getAxis(BornAgain::Y_AXIS_INDEX);
    size_t phi_index = phi_axis.findIndex(phi);
    size_t alpha_index = alpha_axis.findIndex(alpha);
    if (phi_index < phi_axis.size() && alpha_index < alpha_axis.size()) {
        return getGlobalIndex(phi_index, alpha_index);
    }
    return getTotalSize();
}

AngularPixelMap::AngularPixelMap(Bin1D alpha_bin, Bin1D phi_bin)
    : m_alpha(alpha_bin.m_lower)
    , m_phi(phi_bin.m_lower)
    , m_dalpha(alpha_bin.getBinSize())
    , m_dphi(phi_bin.getBinSize())
{
    m_solid_angle = std::abs(m_dphi * (std::sin(m_alpha + m_dalpha) - std::sin(m_alpha)));
}

AngularPixelMap* AngularPixelMap::clone() const
{
    Bin1D alpha_bin(m_alpha, m_alpha + m_dalpha);
    Bin1D phi_bin(m_phi, m_phi + m_dphi);
    return new AngularPixelMap(alpha_bin, phi_bin);
}

AngularPixelMap* AngularPixelMap::createZeroSizeMap(double x, double y) const
{
    double phi = m_phi + x * m_dphi;
    double alpha = m_alpha + y * m_dalpha;
    Bin1D alpha_bin(alpha, alpha);
    Bin1D phi_bin(phi, phi);
    return new AngularPixelMap(alpha_bin, phi_bin);
}

kvector_t AngularPixelMap::getK(double x, double y, double wavelength) const
{
    double phi = m_phi + x * m_dphi;
    double alpha = m_alpha + y * m_dalpha;
    return vecOfLambdaAlphaPhi(wavelength, alpha, phi);
}

double AngularPixelMap::getIntegrationFactor(double /* x */, double y) const
{
    if (m_dalpha == 0.0)
        return 1.0;
    double alpha = m_alpha + y * m_dalpha;
    return std::cos(alpha) * m_dalpha / (std::sin(m_alpha + m_dalpha) - std::sin(m_alpha));
}

double AngularPixelMap::getSolidAngle() const
{
    if (m_solid_angle <= 0.0)
        return 1.0;
    return m_solid_angle;
}
