// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/FitElement.h
//! @brief     Defines class FitElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITELEMENT_H
#define FITELEMENT_H

#include "WinDllMacros.h"
#include <cstddef>

//! Measured ("real") and simulated scattering intensity value for one detector cell.
//! Used for chi2/residual calculations.
//! @ingroup fitting_internal

class BA_CORE_API_ FitElement
{
public:
    FitElement();
    FitElement(size_t index, double simul_value, double real_value, double weight = 1.0);
    FitElement(const FitElement& other);
    FitElement& operator=(const FitElement& other);

    size_t getIndex() const {  return m_index; }
    double getSimulValue() const { return m_simul_value; }
    double getRealValue() const { return m_real_value; }
    double getWeight() const { return m_weight; }
    double getSquaredDifference() const { return m_squared_difference; }
    void setSquaredDifference(double value) { m_squared_difference = value; }
    double getResidual() const { return m_residual; }
    void setResidual(double value) { m_residual = value; }

private:
    void swapContent(FitElement& other);
    size_t m_index;
    double m_simul_value;
    double m_real_value;
    double m_weight;
    double m_squared_difference;
    double m_residual;
};

#endif // FITELEMENT_H
