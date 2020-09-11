// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ISpecularScan.cpp
//! @brief     Implements ISpecularScan abstract class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Instrument/ISpecularScan.h"

ISpecularScan::ISpecularScan(SPECULAR_DATA_TYPE data_type) : m_data_type(data_type) {}

ISpecularScan::~ISpecularScan() = default;
