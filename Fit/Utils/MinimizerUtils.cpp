// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/MinimizerUtils.cpp
//! @brief     Declares namespace MinimizerUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerUtils.h"
#include <sstream>
#include <algorithm>
#include <cmath>
#include <limits>

std::string MinimizerUtils::toString(const std::vector<std::string>& v, const std::string& delim)
{
    std::stringstream s;
    std::for_each(v.begin(), v.end(), [&s, &delim](const std::string& elem) {s << elem << delim; });
    return s.str();
}

//! Returns translation of GSL error code to string.

std::map<int, std::string> MinimizerUtils::gslErrorDescriptionMap()
{
    std::map<int, std::string> result;

    result[0] = std::string("OK, valid minimum");
    result[-2] = std::string("iteration has not converged");
    result[1] = std::string("input domain error, e.g sqrt(-1)");
    result[2] = std::string("output range error, e.g. exp(1e100)");
    result[3] = std::string("invalid pointer");
    result[4] = std::string("invalid argument supplied by user");
    result[5] = std::string("generic failure");
    result[6] = std::string("factorization failed");
    result[7] = std::string("sanity check failed - shouldn't happen");
    result[8] = std::string("malloc failed");
    result[9] = std::string("problem with user-supplied function");
    result[10] = std::string("iterative process is out of control");
    result[11] = std::string("exceeded max number of iterations");
    result[12] = std::string("tried to divide by zero");
    result[13] = std::string("user specified an invalid tolerance");
    result[14] = std::string("failed to reach the specified tolerance");
    result[15] = std::string("underflow");
    result[16] = std::string("overflow ");
    result[17] = std::string("loss of accuracy");
    result[18] = std::string("failed because of roundoff error");
    result[19] = std::string("matrix, vector lengths are not conformant");
    result[20] = std::string("matrix not square");
    result[21] = std::string("apparent singularity detected");
    result[22] = std::string("integral or series is divergent");
    result[23] = std::string("requested feature is not supported by the hardware");
    result[24] = std::string("requested feature not (yet) implemented");
    result[25] = std::string("cache limit exceeded");
    result[26] = std::string("table limit exceeded");
    result[27] = std::string("iteration is not making progress towards solution");
    result[28] = std::string("jacobian evaluations are not improving the solution");
    result[29] = std::string("cannot reach the specified tolerance in F");
    result[30] = std::string("cannot reach the specified tolerance in X");
    result[31] = std::string("cannot reach the specified tolerance in gradient");

    return result;
}

std::string MinimizerUtils::gslErrorDescription(int errorCode)
{
    static std::map<int, std::string> errorDescription = gslErrorDescriptionMap();

    auto it = errorDescription.find(errorCode);
    if(it!=errorDescription.end())
        return it->second;

    return std::string("Unknown error");
}

bool MinimizerUtils::numbersDiffer(double a, double b, double tol)
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    if (tol<1)
        throw std::runtime_error("MinimizerUtils::numbersDiffer() -> Error.Not intended for tol<1");
    return std::abs(a-b) > eps * std::max( tol*eps, std::abs(b) );
}

//! Returns horizontal line of 80 characters length with section name in it.

std::string MinimizerUtils::sectionString(const std::string& sectionName, int report_width)
{
    if(sectionName.empty())
        return std::string(report_width, '-') + "\n";
    // to make "--- SectionName ------------------------------"
    std::string prefix(3, '-');
    std::string body = std::string(" ") + sectionName + std::string(" ");
    std::string postfix(report_width - body.size() - prefix.size(), '-');
    std::ostringstream result;
    result << prefix << body << postfix << std::endl;
    return result.str();
}
