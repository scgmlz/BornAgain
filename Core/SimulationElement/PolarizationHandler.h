// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SimulationElement/PolarizationHandler.h
//! @brief     Defines class PolarizationHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SIMULATIONELEMENT_POLARIZATIONHANDLER_H
#define BORNAGAIN_CORE_SIMULATIONELEMENT_POLARIZATIONHANDLER_H

#include "Core/Vector/EigenCore.h"
#include "Wrap/WinDllMacros.h"

//! Convenience class for handling polarization density matrix and polarization analyzer operator
//! @ingroup simulation

class BA_CORE_API_ PolarizationHandler
{
public:
    PolarizationHandler();
    PolarizationHandler(const Eigen::Matrix2cd& polarization, const Eigen::Matrix2cd& analyzer);

    //! Sets the polarization density matrix (in spin basis along z-axis)
    void setPolarization(const Eigen::Matrix2cd& polarization) { m_polarization = polarization; }

    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getPolarization() const { return m_polarization; }

    //! Sets the polarization analyzer operator (in spin basis along z-axis)
    void setAnalyzerOperator(const Eigen::Matrix2cd& analyzer) { m_analyzer_operator = analyzer; }

    //! Gets the polarization analyzer operator (in spin basis along z-axis)
    Eigen::Matrix2cd getAnalyzerOperator() const { return m_analyzer_operator; }

    void swapContent(PolarizationHandler& other);

private:
    Eigen::Matrix2cd m_polarization;      //!< polarization density matrix
    Eigen::Matrix2cd m_analyzer_operator; //!< polarization analyzer operator
};

#endif // BORNAGAIN_CORE_SIMULATIONELEMENT_POLARIZATIONHANDLER_H
