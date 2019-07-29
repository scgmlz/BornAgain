// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SimulationElement/PolarizationHandler.cpp
//! @brief     Implements class PolarizationHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PolarizationHandler.h"

PolarizationHandler::PolarizationHandler()
{
    m_polarization = Eigen::Matrix2cd::Identity();
    m_analyzer_operator = Eigen::Matrix2cd::Identity();
}

void PolarizationHandler::swapContent(PolarizationHandler& other)
{
    std::swap(m_polarization, other.m_polarization);
    std::swap(m_analyzer_operator, other.m_analyzer_operator);
}
