// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IIntensityNormalizer.cpp
//! @brief     Implements class IntensityNormalizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IIntensityNormalizer.h"

void IntensityNormalizer::init_parameters()
{
    registerParameter("scale", &m_scale);
    registerParameter("shift", &m_shift);
}

IntensityNormalizer* IntensityNormalizer::clone() const
{
    IntensityNormalizer* result = new IntensityNormalizer(m_scale, m_shift);
    result->setMaximumIntensity(m_max_intensity);
    result->setName(getName());
    return result;
}

OutputData<double>* IntensityNormalizer::createNormalizedData(const OutputData<double>& data) const
{
    OutputData<double>* normalized_data = data.clone();
    apply(*normalized_data);
    return normalized_data;
}

void IntensityNormalizer::apply(OutputData<double>& data) const
{
    double factor = m_max_intensity;
    if (factor == 0) {
        // using self maximum amplitude for normalization
        OutputData<double>::const_iterator it = std::max_element(data.begin(), data.end());
        factor = *it;
    }
    if (factor == 0)
        throw Exceptions::DivisionByZeroException("IntensityNormalizer::apply() -> "
                                                  "Error! Maximum intensity is 0.");

    for (auto& value : data) {
        value = m_scale * (value / factor) + m_shift;
    }
}
