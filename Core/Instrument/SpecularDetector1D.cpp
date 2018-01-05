// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SpecularDetector1D.h
//! @brief     Implements a detector for specular simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Beam.h"
#include "IPixel.h"
#include "SimulationArea.h"
#include "SimulationElement.h"
#include "SimulationElementsProvider.h"
#include "SpecularDetector1D.h"
#include "Units.h"

namespace {
class SpecularPixel : public IPixel
{
public:
    SpecularPixel(double alpha_i) : m_alpha_i(alpha_i) {}
    virtual ~SpecularPixel() = default;

    virtual SpecularPixel* clone() const override {return new SpecularPixel(m_alpha_i);}

    // SpecularPixel already has zero size
    virtual SpecularPixel* createZeroSizePixel(double, double) const override {return clone();}

    virtual kvector_t getK(double, double, double wavelength) const override
    {
        return vecOfLambdaAlphaPhi(wavelength, -m_alpha_i, 0.0);
    }

    virtual double getIntegrationFactor(double, double) const override {return 1;}
    virtual double getSolidAngle() const override {return 1;}

private:
    double m_alpha_i;
};
}

SpecularDetector1D::SpecularDetector1D(const IAxis& axis)
{
    addAxis(axis);
}

SpecularDetector1D::SpecularDetector1D(const SpecularDetector1D& detector) : IDetector(detector)
{
}

SpecularDetector1D::~SpecularDetector1D() = default;

SpecularDetector1D* SpecularDetector1D::clone() const {
    return new SpecularDetector1D(*this);
}

AxesUnits SpecularDetector1D::defaultAxesUnits() const {
    return AxesUnits::RADIANS;
}

std::vector<AxesUnits> SpecularDetector1D::validAxesUnits() const {
    std::vector<AxesUnits> result = IDetector::validAxesUnits();
    const std::vector<AxesUnits> addon = {AxesUnits::RADIANS, AxesUnits::DEGREES};
    result.insert(result.end(), addon.begin(), addon.end());
    return result;
}

double SpecularDetector1D::alphaI(size_t index) const
{
    const IAxis& axis = getAxis(BornAgain::X_AXIS_INDEX);
    const size_t axis_index = axisBinIndex(index, BornAgain::X_AXIS_INDEX);
    return axis.getBin(axis_index).getMidPoint();
}

std::unique_ptr<ISimulationElementsProvider> SpecularDetector1D::createSimulationElements(const Beam& beam)
{
    auto agent = std::make_unique<SimulationElementsProvider<SimulationElement>>();
    auto& elements = agent->getElementVector();

    const double wavelength = beam.getWavelength();
    const Eigen::Matrix2cd beam_polarization = beam.getPolarization();
    const Eigen::Matrix2cd analyzer_operator = detectionProperties().analyzerOperator();
    const double phi_i = 0; // Assuming that beam is always parallel to x-axis of the sample

    SimulationArea area(this);
    elements.reserve(area.totalSize());
    for (SimulationArea::iterator it = area.begin(); it != area.end(); ++it) {
        // opposite sign for alpha_i since e_{z_beam} = - e_{z_detector}
        const double alpha_i = -alphaI(it.detectorIndex());
        elements.emplace_back(wavelength, alpha_i, phi_i,
                            std::make_unique<SpecularPixel>(alpha_i));
        auto& sim_element = elements.back();
        sim_element.setPolarization(beam_polarization);
        sim_element.setAnalyzerOperator(analyzer_operator);
        sim_element.setSpecular();
    }

    return std::move(agent);
}

std::string SpecularDetector1D::axisName(size_t index) const
{
    if (index == 0) {
        return BornAgain::U_AXIS_NAME;
    } else
        throw std::runtime_error(
            "SpecularDetector1D::getAxisName(size_t index) -> Error! index > 0");
}

void SpecularDetector1D::calculateAxisRange(size_t axis_index, const Beam& beam, AxesUnits units,
                                            double& amin, double& amax) const
{
    if (units == AxesUnits::DEGREES) {
        amin = getAxis(axis_index).getMin() / Units::degree;
        amax = getAxis(axis_index).getMax() / Units::degree;
    } else if (units == AxesUnits::RADIANS) {
        amin = getAxis(axis_index).getMin();
        amax = getAxis(axis_index).getMax();
    } else {
        IDetector::calculateAxisRange(axis_index, beam, units, amin, amax);
    }
}
