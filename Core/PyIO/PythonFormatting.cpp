// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/PyIO/PythonFormatting.cpp
//! @brief     Implements functions from namespace pyfmt2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/PyIO/PythonFormatting.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Basics/Units.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Binning/PointwiseAxis.h"
#include "Core/Mask/Ellipse.h"
#include "Core/Mask/InfinitePlane.h"
#include "Core/Mask/Line.h"
#include "Core/Mask/Polygon.h"
#include "Core/Mask/Rectangle.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/IParameterized.h"
#include "Core/Parametrization/ParameterDistribution.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Tools/PyFmt.h"
#include "Fit/TestEngine/Numeric.h"
#include "Fit/Tools/StringUtils.h"
#include <iomanip>

namespace pyfmt2
{

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
               << "ba.Polygon(points), " << pyfmt::printBool(mask_value) << ")\n";

    } else if (dynamic_cast<const InfinitePlane*>(ishape)) {
        result << indent << "simulation.maskAll()\n";

    } else if (const Ellipse* shape = dynamic_cast<const Ellipse*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.Ellipse(" << printValueFunc(shape->getCenterX()) << ", "
               << printValueFunc(shape->getCenterY()) << ", " << printValueFunc(shape->getRadiusX())
               << ", " << printValueFunc(shape->getRadiusY());
        if (shape->getTheta() != 0.0)
            result << ", " << pyfmt::printDegrees(shape->getTheta());
        result << "), " << pyfmt::printBool(mask_value) << ")\n";
    }

    else if (const Rectangle* shape = dynamic_cast<const Rectangle*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.Rectangle(" << printValueFunc(shape->getXlow()) << ", "
               << printValueFunc(shape->getYlow()) << ", " << printValueFunc(shape->getXup())
               << ", " << printValueFunc(shape->getYup()) << "), " << pyfmt::printBool(mask_value)
               << ")\n";
    }

    else if (const VerticalLine* shape = dynamic_cast<const VerticalLine*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.VerticalLine(" << printValueFunc(shape->getXpos()) << "), "
               << pyfmt::printBool(mask_value) << ")\n";
    }

    else if (const HorizontalLine* shape = dynamic_cast<const HorizontalLine*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.HorizontalLine(" << printValueFunc(shape->getYpos()) << "), "
               << pyfmt::printBool(mask_value) << ")\n";

    } else
        throw std::runtime_error("representShape2D(const IShape2D*) -> Error. Unknown shape");

    return result.str();
}

//! Returns parameter value, followed by its unit multiplicator (like "* nm").

std::string valueTimesUnit(const RealParameter* par)
{
    if (par->unit() == "rad")
        return pyfmt::printDegrees(par->value());
    return pyfmt::printDouble(par->value()) + (par->unit() == "" ? "" : ("*" + par->unit()));
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

std::string printParameterDistribution(const ParameterDistribution& par_distr,
                                       const std::string& distVarName, const std::string& units)
{
    std::ostringstream result;

    result << "ba.ParameterDistribution("
           << "\"" << par_distr.getMainParameterName() << "\""
           << ", " << distVarName << ", " << par_distr.getNbrSamples() << ", "
           << pyfmt::printDouble(par_distr.getSigmaFactor())
           << pyfmt::printRealLimitsArg(par_distr.getLimits(), units) << ")";

    return result.str();
}

std::string printAxis(const IAxis& axis, const std::string& units, size_t offset)
{
    std::ostringstream result;

    if (auto fixedAxis = dynamic_cast<const FixedBinAxis*>(&axis)) {
        result << "ba.FixedBinAxis(" << pyfmt::printString(fixedAxis->getName()) << ", "
               << fixedAxis->size() << ", " << pyfmt::printValue(fixedAxis->getMin(), units) << ", "
               << pyfmt::printValue(fixedAxis->getMax(), units) << ")";
    } else if (auto pointwise_axis = dynamic_cast<const PointwiseAxis*>(&axis)) {
        const std::string py_def_call = "numpy.asarray([";
        const size_t total_offset = offset + py_def_call.size();
        result << py_def_call;

        std::vector<double> points = pointwise_axis->getBinCenters();
        for (auto iter = points.begin(); iter != points.end() - 1; ++iter) {
            result << pyfmt::printValue(*iter, units) << ",\n";
            result << pyfmt::indent(total_offset);
        }
        result << pyfmt::printValue(points.back(), units) << "])";
    } else {
        throw std::runtime_error("pyfmt2::printAxis() -> Error. Unsupported axis");
    }

    return result.str();
}

} // namespace pyfmt2
