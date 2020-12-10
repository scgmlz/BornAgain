//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/PyFmt.cpp
//! @brief     Implements functions from namespace pyfmt.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Export/PyFmt.h"
#include "Base/Const/Units.h" // printDegrees
#include "Base/Math/Constants.h"
#include "Base/Utils/Algorithms.h"
#include <iomanip>

namespace pyfmt {

std::string scriptPreamble() {
    return "import numpy, sys\n"
           "import bornagain as ba\n"
           "from bornagain import angstrom, deg, micrometer, nm, nm2, kvector_t\n\n\n";
}

std::string printBool(double value) {
    return value ? "True" : "False";
}

std::string printDouble(double input) {
    std::ostringstream inter;
    inter << std::setprecision(12);
    if (std::abs(input) < std::numeric_limits<double>::epsilon()) {
        inter << "0.0";
        return inter.str();
    }
    inter << input;
    if (inter.str().find('e') == std::string::npos && inter.str().find('.') == std::string::npos)
        inter << ".0";
    return inter.str();
}

std::string printNm(double input) {
    std::ostringstream inter;
    inter << std::setprecision(12);
    inter << printDouble(input) << "*nm";
    return inter.str();
}

std::string printNm2(double input) {
    std::ostringstream inter;
    inter << std::setprecision(12);
    inter << printDouble(input) << "*nm2";
    return inter.str();
}

// 1.000000e+07 -> 1.0e+07
std::string printScientificDouble(double input) {
    std::ostringstream inter;
    inter << std::scientific;
    inter << input;

    std::string::size_type pos = inter.str().find('e');
    if (pos == std::string::npos)
        return inter.str();

    std::string part1 = inter.str().substr(0, pos);
    std::string part2 = inter.str().substr(pos, std::string::npos);

    part1.erase(part1.find_last_not_of('0') + 1, std::string::npos);
    if (part1.back() == '.')
        part1 += "0";

    return part1 + part2;
}

std::string printDegrees(double input) {
    std::ostringstream inter;
    inter << std::setprecision(11) << Units::rad2deg(input);
    if (inter.str().find('e') == std::string::npos && inter.str().find('.') == std::string::npos)
        inter << ".0";
    inter << "*deg";
    return inter.str();
}

std::string printValue(double value, const std::string& units) {
    if (units == "rad")
        return printDegrees(value);
    else if (units == "nm")
        return printNm(value);
    else if (units == "")
        return printDouble(value);
    else
        throw std::runtime_error("pyfmt::printValue() -> Error. Unknown units '" + units + "'");
}

std::string printString(const std::string& value) {
    std::ostringstream result;
    result << "\"" << value << "\"";
    return result.str();
}

bool isSquare(double length1, double length2, double angle) {
    return length1 == length2 && algo::almostEqual(angle, M_PI_2);
}

bool isHexagonal(double length1, double length2, double angle) {
    return length1 == length2 && algo::almostEqual(angle, M_TWOPI / 3.0);
}

std::string printKvector(const kvector_t value) {
    std::ostringstream result;
    result << "kvector_t(" << printDouble(value.x()) << ", " << printDouble(value.y()) << ", "
           << printDouble(value.z()) << ")";
    return result.str();
}

std::string indent(size_t width) {
    return std::string(width, ' ');
}

} // namespace pyfmt
