// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Tools/MinimizerUtils.cpp
//! @brief     Declares namespace MinimizerUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Tools/MinimizerUtils.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>

std::string MinimizerUtils::toString(const std::vector<std::string>& v, const std::string& delim)
{
    std::stringstream s;
    std::for_each(v.begin(), v.end(),
                  [&s, &delim](const std::string& elem) { s << elem << delim; });
    return s.str();
}

//! Returns translation of GSL error code to string.

std::map<int, std::string> MinimizerUtils::gslErrorDescriptionMap()
{
    std::map<int, std::string> result;

    result[0] = "OK, valid minimum";
    result[-2] = "iteration has not converged";
    result[1] = "input domain error, e.g sqrt(-1)";
    result[2] = "output range error, e.g. exp(1e100)";
    result[3] = "invalid pointer";
    result[4] = "invalid argument supplied by user";
    result[5] = "generic failure";
    result[6] = "factorization failed";
    result[7] = "sanity check failed - shouldn't happen";
    result[8] = "malloc failed";
    result[9] = "problem with user-supplied function";
    result[10] = "iterative process is out of control";
    result[11] = "exceeded max number of iterations";
    result[12] = "tried to divide by zero";
    result[13] = "user specified an invalid tolerance";
    result[14] = "failed to reach the specified tolerance";
    result[15] = "underflow";
    result[16] = "overflow ";
    result[17] = "loss of accuracy";
    result[18] = "failed because of roundoff error";
    result[19] = "matrix, vector lengths are not conformant";
    result[20] = "matrix not square";
    result[21] = "apparent singularity detected";
    result[22] = "integral or series is divergent";
    result[23] = "requested feature is not supported by the hardware";
    result[24] = "requested feature not (yet) implemented";
    result[25] = "cache limit exceeded";
    result[26] = "table limit exceeded";
    result[27] = "iteration is not making progress towards solution";
    result[28] = "jacobian evaluations are not improving the solution";
    result[29] = "cannot reach the specified tolerance in F";
    result[30] = "cannot reach the specified tolerance in X";
    result[31] = "cannot reach the specified tolerance in gradient";

    return result;
}

std::string MinimizerUtils::gslErrorDescription(int errorCode)
{
    static std::map<int, std::string> errorDescription = gslErrorDescriptionMap();

    auto it = errorDescription.find(errorCode);
    if (it != errorDescription.end())
        return it->second;

    return "Unknown error";
}

bool MinimizerUtils::numbersDiffer(double a, double b, double tol)
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    if (tol < 1)
        throw std::runtime_error("MinimizerUtils::numbersDiffer() -> Error.Not intended for tol<1");
    return std::abs(a - b) > eps * std::max(tol * eps, std::abs(b));
}

//! Returns horizontal line of 80 characters length with section name in it.

std::string MinimizerUtils::sectionString(const std::string& sectionName, size_t report_width)
{
    if (sectionName.empty())
        return std::string(report_width, '-') + "\n";
    // to make "--- SectionName ------------------------------"
    std::string prefix(3, '-');
    std::string body = std::string(" ") + sectionName + " ";
    std::string postfix(report_width - body.size() - prefix.size(), '-');
    std::ostringstream result;
    result << prefix << body << postfix << std::endl;
    return result.str();
}
