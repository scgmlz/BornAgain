// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/IFootprintFactor.h
//! @brief     Defines class IFootprintFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BEAM_IFOOTPRINTFACTOR_H
#define BORNAGAIN_CORE_BEAM_IFOOTPRINTFACTOR_H

#include "Core/Basics/ICloneable.h"
#include "Core/Parametrization/INode.h"

class MultiLayer;
class Beam;

//! Abstract base for classes that calculate the beam footprint factor
//! @ingroup beam

class BA_CORE_API_ IFootprintFactor : public ICloneable, public INode
{
public:
    IFootprintFactor(const NodeMeta& meta, const std::vector<double>& PValues);
    IFootprintFactor() = delete;
    virtual ~IFootprintFactor();

    virtual IFootprintFactor* clone() const = 0;

    void setWidthRatio(double width_ratio);
    double widthRatio() const { return m_width_ratio; }

    //! Calculate footprint correction coefficient from the beam incident angle _alpha_.
    virtual double calculate(double alpha) const = 0;

    //! Print python-formatted footprint definition
    virtual std::string print() const = 0;

protected:
    const double& m_width_ratio; //! Beam to sample width ratio

private:
    void initialize();
};

inline std::ostream& operator<<(std::ostream& os, const IFootprintFactor& f_factor)
{
    return os << f_factor.print();
}

#endif // BORNAGAIN_CORE_BEAM_IFOOTPRINTFACTOR_H
