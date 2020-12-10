//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/PyFmt2.cpp
//! @brief     Implements functions from namespace pyfmt2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Export/PyFmt2.h"
#include "Base/Axis/FixedBinAxis.h"
#include "Base/Axis/PointwiseAxis.h"
#include "Base/Const/Units.h"
#include "Base/Math/Constants.h"
#include "Base/Utils/Algorithms.h"
#include "Base/Utils/StringUtils.h"
#include "Core/Export/PyFmt.h"
#include "Core/Export/PyFmtLimits.h"
#include "Device/Mask/Ellipse.h"
#include "Device/Mask/InfinitePlane.h"
#include "Device/Mask/Line.h"
#include "Device/Mask/Polygon.h"
#include "Device/Mask/Rectangle.h"
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include "Param/Distrib/Distributions.h"
#include "Param/Distrib/ParameterDistribution.h"
#include "Param/Distrib/RangedDistributions.h"
#include <iomanip>

namespace pyfmt2 {

//! Returns fixed Python code snippet that defines the function "runSimulation".

std::string representShape2D(const std::string& indent, const IShape2D* ishape, bool mask_value,
                             std::function<std::string(double)> printValueFunc) {
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

std::string valueTimesUnit(const RealParameter* par) {
    if (par->unit() == "rad")
        return pyfmt::printDegrees(par->value());
    return pyfmt::printDouble(par->value()) + (par->unit() == "" ? "" : ("*" + par->unit()));
}

//! Returns comma-separated list of parameter values, including unit multiplicator (like "* nm").

std::string argumentList(const IParametricComponent* ip) {
    std::vector<std::string> args;
    for (const auto* par : ip->parameterPool()->parameters())
        args.push_back(valueTimesUnit(par));
    return StringUtils::join(args, ", ");
}

//! Prints an axis.
std::string printAxis(const IAxis* axis, const std::string& unit) {
    std::ostringstream result;
    if (const auto* a = dynamic_cast<const FixedBinAxis*>(axis); a)
        result << "ba.FixedBinAxis(" << pyfmt::printString(a->getName()) << ", " << a->size()
               << ", " << pyfmt::printValue(a->lowerBound(), unit) << ", "
               << pyfmt::printValue(a->upperBound(), unit) << ")";
    else if (const auto* a = dynamic_cast<const PointwiseAxis*>(axis); a) {
        result << "numpy.asarray([";
        const std::vector<double>& points = a->binCenters();
        for (auto iter = points.begin(); iter != points.end() - 1; ++iter) {
            result << pyfmt::printValue(*iter, unit) << ",";
        }
        result << pyfmt::printValue(points.back(), unit) << "])\n";
    } else
        throw std::runtime_error("printAxis not implemented for current axis type");
    return result.str();
}

//! Prints distribution with constructor parameters in given units.
//! ba.DistributionGaussian(2.0*deg, 0.02*deg)

std::string printDistribution(const IDistribution1D& par_distr, const std::string& units) {
    std::unique_ptr<IDistribution1D> distr(par_distr.clone());
    distr->setUnits(units);

    std::ostringstream result;
    result << "ba." << distr->getName() << "(" << argumentList(distr.get()) << ")";
    return result.str();
}

std::string printParameterDistribution(const ParameterDistribution& par_distr,
                                       const std::string& distVarName, const std::string& units) {
    std::ostringstream result;

    result << "ba.ParameterDistribution("
           << "\"" << par_distr.getMainParameterName() << "\""
           << ", " << distVarName << ", " << par_distr.getNbrSamples() << ", "
           << pyfmt::printDouble(par_distr.getSigmaFactor())
           << pyfmt::printRealLimitsArg(par_distr.getLimits(), units) << ")";

    return result.str();
}

std::string printRangedDistribution(const IRangedDistribution& distr) {
    std::ostringstream result;
    result << pyfmt::indent() << "distribution = ba.";
    result << distr.name();
    result << "(" << distr.nSamples() << ", " << pyfmt::printDouble(distr.sigmaFactor());
    if (!distr.limits().isLimitless())
        result << pyfmt::printRealLimitsArg(distr.limits());
    result << ")";
    return result.str();
}

} // namespace pyfmt2
