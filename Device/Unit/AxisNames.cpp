//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Unit/AxisNames.cpp
//! @brief     Implements functions in namespace AxisNames.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Unit/AxisNames.h"
#include <map>

namespace AxisNames {
// For spherical detectors in GISAS simulations
std::map<Axes::Units, std::string> InitSphericalAxis0() {
    std::map<Axes::Units, std::string> result;
    result[Axes::Units::NBINS] = "X [nbins]";
    result[Axes::Units::RADIANS] = "phi_f [rad]";
    result[Axes::Units::DEGREES] = "phi_f [deg]";
    result[Axes::Units::QSPACE] = "Qy [1/nm]";
    result[Axes::Units::QXQY] = "Qx [1/nm]";
    return result;
}
std::map<Axes::Units, std::string> InitSphericalAxis1() {
    std::map<Axes::Units, std::string> result;
    result[Axes::Units::NBINS] = "Y [nbins]";
    result[Axes::Units::RADIANS] = "alpha_f [rad]";
    result[Axes::Units::DEGREES] = "alpha_f [deg]";
    result[Axes::Units::QSPACE] = "Qz [1/nm]";
    result[Axes::Units::QXQY] = "Qy [1/nm]";
    return result;
}
// For rectangular detectors in GISAS simulations
std::map<Axes::Units, std::string> InitRectangularAxis0() {
    std::map<Axes::Units, std::string> result;
    result[Axes::Units::NBINS] = "X [nbins]";
    result[Axes::Units::RADIANS] = "phi_f [rad]";
    result[Axes::Units::DEGREES] = "phi_f [deg]";
    result[Axes::Units::MM] = "X [mm]";
    result[Axes::Units::QSPACE] = "Qy [1/nm]";
    result[Axes::Units::QXQY] = "Qx [1/nm]";
    return result;
}
std::map<Axes::Units, std::string> InitRectangularAxis1() {
    std::map<Axes::Units, std::string> result;
    result[Axes::Units::NBINS] = "Y [nbins]";
    result[Axes::Units::RADIANS] = "alpha_f [rad]";
    result[Axes::Units::DEGREES] = "alpha_f [deg]";
    result[Axes::Units::MM] = "Y [mm]";
    result[Axes::Units::QSPACE] = "Qz [1/nm]";
    result[Axes::Units::QXQY] = "Qy [1/nm]";
    return result;
}
// For off-specular simulations (both spherical and rectangular detectors)
// Currently 'mm' is not supported for the y-axis
std::map<Axes::Units, std::string> InitOffSpecularAxis0() {
    std::map<Axes::Units, std::string> result;
    result[Axes::Units::NBINS] = "X [nbins]";
    result[Axes::Units::RADIANS] = "alpha_i [rad]";
    result[Axes::Units::DEGREES] = "alpha_i [deg]";
    return result;
}
std::map<Axes::Units, std::string> InitOffSpecularAxis1() {
    std::map<Axes::Units, std::string> result;
    result[Axes::Units::NBINS] = "Y [nbins]";
    result[Axes::Units::RADIANS] = "alpha_f [rad]";
    result[Axes::Units::DEGREES] = "alpha_f [deg]";
    return result;
}

std::map<Axes::Units, std::string> InitSpecAxis() {
    std::map<Axes::Units, std::string> result;
    result[Axes::Units::NBINS] = "X [nbins]";
    result[Axes::Units::RADIANS] = "alpha_i [rad]";
    result[Axes::Units::DEGREES] = "alpha_i [deg]";
    result[Axes::Units::QSPACE] = "Q [1/nm]";
    result[Axes::Units::RQ4] = "Q [1/nm]";
    return result;
}

std::map<Axes::Units, std::string> InitSpecAxisQ() {
    std::map<Axes::Units, std::string> result;
    result[Axes::Units::NBINS] = "X [nbins]";
    result[Axes::Units::QSPACE] = "Q [1/nm]";
    result[Axes::Units::RQ4] = "Q [1/nm]";
    return result;
}

// corner case: axis corresponding to the position
// across sample is accepts only bins and nanometers,
// but the units specified in dedicated unit
// converter correspond to inclination angular axis.
// For this reason depth axis map returns always
// nanometers except for bins.
std::map<Axes::Units, std::string> InitSampleDepthAxis() {
    std::map<Axes::Units, std::string> result;
    result[Axes::Units::NBINS] = "Y [nbins]";
    result[Axes::Units::RADIANS] = "Position [nm]";
    result[Axes::Units::DEGREES] = "Position [nm]";
    result[Axes::Units::QSPACE] = "Position [nm]";
    return result;
}

} // namespace AxisNames
