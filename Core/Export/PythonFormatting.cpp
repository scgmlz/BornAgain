// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/PythonFormatting.cpp
//! @brief     Implements functions from PythonFormatting namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PythonFormatting.h"
#include "BornAgainNamespace.h"
#include "Distributions.h"
#include "Ellipse.h"
#include "IParameterized.h"
#include "InfinitePlane.h"
#include "Line.h"
#include "MathConstants.h"
#include "Numeric.h"
#include "ParameterPool.h"
#include "ParameterDistribution.h"
#include "Polygon.h"
#include "RealParameter.h"
#include "Rectangle.h"
#include "StringUtils.h"
#include "Units.h"
#include "FixedBinAxis.h"
#include <iomanip>

namespace PythonFormatting
{

std::string scriptPreamble()
{
    const std::string result = "import numpy\n"
                               "import bornagain as ba\n"
                               "from bornagain import deg, angstrom, nm, kvector_t\n\n\n";

    return result;
}

std::string getSampleFunctionName()
{
    return "get_sample";
}


//! Returns fixed Python code snippet that defines the function "runSimulation".

std::string representShape2D(const std::string& indent, const IShape2D* ishape, bool mask_value,
                             std::function<std::string(double)> printValueFunc)
{
    std::ostringstream result;
    result << std::setprecision(12);

    if (const Polygon* shape = dynamic_cast<const Polygon*>(ishape)) {
        std::vector<double> xpos, ypos;
        shape->getPoints(xpos, ypos);
        result << indent << "points = [";
        for (size_t i = 0; i < xpos.size(); ++i) {
            result << "[" << printValueFunc(xpos[i]) << ", " << printValueFunc(ypos[i]) << "]";
            if (i != xpos.size() - 1)
                result << ", ";
        }
        result << "]\n";
        result << indent << "simulation.addMask("
               << "ba.Polygon(points), " << printBool(mask_value) << ")\n";

    } else if (dynamic_cast<const InfinitePlane*>(ishape)) {
        result << indent << "simulation.maskAll()\n";

    } else if (const Ellipse* shape = dynamic_cast<const Ellipse*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.Ellipse(" << printValueFunc(shape->getCenterX()) << ", "
               << printValueFunc(shape->getCenterY()) << ", " << printValueFunc(shape->getRadiusX())
               << ", " << printValueFunc(shape->getRadiusY());
        if (shape->getTheta() != 0.0)
            result << ", " << printDegrees(shape->getTheta());
        result << "), " << printBool(mask_value) << ")\n";
    }

    else if (const Rectangle* shape = dynamic_cast<const Rectangle*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.Rectangle(" << printValueFunc(shape->getXlow()) << ", "
               << printValueFunc(shape->getYlow()) << ", " << printValueFunc(shape->getXup())
               << ", " << printValueFunc(shape->getYup()) << "), " << printBool(mask_value)
               << ")\n";
    }

    else if (const VerticalLine* shape = dynamic_cast<const VerticalLine*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.VerticalLine(" << printValueFunc(shape->getXpos()) << "), "
               << printBool(mask_value) << ")\n";
    }

    else if (const HorizontalLine* shape = dynamic_cast<const HorizontalLine*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.HorizontalLine(" << printValueFunc(shape->getYpos()) << "), "
               << printBool(mask_value) << ")\n";

    } else
        throw std::runtime_error("representShape2D(const IShape2D*) -> Error. Unknown shape");

    return result.str();
}

std::string printBool(double value) { return value ? "True" : "False"; }

std::string printDouble(double input)
{
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

std::string printNm(double input)
{
    std::ostringstream inter;
    inter << std::setprecision(12);
    inter << printDouble(input) << "*nm";
    return inter.str();
}

// 1.000000e+07 -> 1.0e+07
std::string printScientificDouble(double input)
{
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

std::string printDegrees(double input)
{
    std::ostringstream inter;
    inter << std::setprecision(11) << Units::rad2deg(input);
    if (inter.str().find('e') == std::string::npos && inter.str().find('.') == std::string::npos)
        inter << ".0";
    inter << "*deg";
    return inter.str();
}

std::string printValue(double value, const std::string& units)
{
    if (units == BornAgain::UnitsRad)
        return printDegrees(value);
    else if (units == BornAgain::UnitsNm)
        return printNm(value);
    else if (units == BornAgain::UnitsNone)
        return printDouble(value);
    else
        throw std::runtime_error("PythonFormatting::printValue() -> Error. Unknown units '" + units
                                 + "'");
}

std::string printString(const std::string& value)
{
    std::ostringstream result;
    result << "\"" << value << "\"";
    return result.str();
}

bool isSquare(double length1, double length2, double angle)
{
    return length1 == length2 && Numeric::areAlmostEqual(angle, M_PI_2);
}

bool isHexagonal(double length1, double length2, double angle)
{
    return length1 == length2 && Numeric::areAlmostEqual(angle, M_TWOPI / 3.0);
}

std::string printKvector(const kvector_t value)
{
    std::ostringstream result;
    result << "kvector_t(" << printDouble(value.x()) << ", " << printDouble(value.y()) << ", "
           << printDouble(value.z()) << ")";
    return result.str();
}

//! returns true if it is (0, -1, 0) vector
bool isDefaultDirection(const kvector_t direction)
{
    return Numeric::areAlmostEqual(direction.x(), 0.0)
           && Numeric::areAlmostEqual(direction.y(), -1.0)
           && Numeric::areAlmostEqual(direction.z(), 0.0);
}

//! Returns parameter value, followed by its unit multiplicator (like "* nm").

std::string valueTimesUnit(const RealParameter* par)
{
    if (par->unit() == BornAgain::UnitsRad)
        return printDegrees(par->value());
    return printDouble(par->value()) + (par->unit() == "" ? "" : ("*" + par->unit()));
}

//! Returns comma-separated list of parameter values, including unit multiplicator (like "* nm").

std::string argumentList(const IParameterized* ip)
{
    std::vector<std::string> args;
    for (const auto* par : ip->parameterPool()->parameters())
        args.push_back(valueTimesUnit(par));
    return StringUtils::join(args, ", ");
}

//! Prints distribution with constructor parameters in given units.
//! ba.DistributionGaussian(2.0*deg, 0.02*deg)

std::string printDistribution(const IDistribution1D& par_distr, const std::string& units)
{
    std::unique_ptr<IDistribution1D> distr(par_distr.clone());
    distr->setUnits(units);

    std::ostringstream result;
    result << "ba." << distr->getName() << "(" << argumentList(distr.get()) << ")";
    return result.str();
}

std::string printRealLimits(const RealLimits& limits, const std::string& units)
{
    std::ostringstream result;

    if (limits.isLimitless()) {
        result << "RealLimits()";
    }

    else if (limits.isPositive()) {
        result << "RealLimits.positive()";
    }

    else if (limits.isNonnegative()) {
        result << "RealLimits.nonnegative()";
    }

    else if (limits.isLowerLimited()) {
        result << "RealLimits.lowerLimited(" << printValue(limits.getLowerLimit(), units) << ")";
    }

    else if (limits.isUpperLimited()) {
        result << "RealLimits.upperLimited(" << printValue(limits.getUpperLimit(), units) << ")";
    }

    else if (limits.isLimited()) {
        result << "RealLimits.limited(" << printValue(limits.getLowerLimit(), units) << ", "
               << printValue(limits.getUpperLimit(), units) << ")";
    }

    return result.str();
}

//! Prints RealLimits in the form of argument (in the context of ParameterDistribution and
//! similar). Default RealLimits will not be printed, any other will be printed as
//! ", ba.RealLimits.limited(1*deg, 2*deg)"

std::string printRealLimitsArg(const RealLimits& limits, const std::string& units)
{
    return limits.isLimitless() ? "" : ", ba." + printRealLimits(limits, units);
}

//! Prints ParameterDistribution.
//! distVarName is a string representing IDistribution1D variable, e.g. "distr_1"
//!
//! ba.ParameterDistribution("/Particle/Height", distr_1, 10, 0.0, ba.RealLimits.limited(1*nm,2*nm))

std::string printParameterDistribution(const ParameterDistribution& par_distr,
                                       const std::string& distVarName, const std::string& units)
{
    std::ostringstream result;

    result << "ba.ParameterDistribution("
           << "\"" << par_distr.getMainParameterName() << "\""
           << ", " << distVarName << ", " << par_distr.getNbrSamples() << ", "
           << printDouble(par_distr.getSigmaFactor())
           << printRealLimitsArg(par_distr.getLimits(), units) << ")";

    return result.str();
}

std::string printAxis(const IAxis& axis, const std::string& units)
{
    std::ostringstream result;

    if (auto fixedAxis = dynamic_cast<const FixedBinAxis*>(&axis)) {
        result << "ba.FixedBinAxis("
               << printString(fixedAxis->getName()) << ", "
               << fixedAxis->size() << ", "
               << printValue(fixedAxis->getMin(), units) << ", "
               << printValue(fixedAxis->getMax(), units) << ")";

    } else {
        throw std::runtime_error("PythonFormatting::printAxis() -> Error. Unsupported axis");
    }

    return result.str();
}

} // namespace PythonFormatting
