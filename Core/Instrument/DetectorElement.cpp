// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectorElement.cpp
//! @brief     Implements class DetectorElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DetectorElement.h"
#include "IPixel.h"


DetectorElement::DetectorElement(IPixel* p_pixel, Eigen::Matrix2cd analyzer_operator)
    : m_specular(false)
    , mP_pixel(p_pixel)
    , m_analyzer_operator(analyzer_operator)
{}

void DetectorElement::setSpecular(bool specular)
{
    m_specular = specular;
}

bool DetectorElement::isSpecular() const
{
    return m_specular;
}

std::unique_ptr<IPixel> DetectorElement::pixel() const
{
    return std::unique_ptr<IPixel>(mP_pixel->clone());
}
