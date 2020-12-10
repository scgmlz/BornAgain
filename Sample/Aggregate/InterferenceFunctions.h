//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/InterferenceFunctions.h
//! @brief     Includes all interference function definitions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONS_H
#define BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONS_H

#include "Sample/Aggregate/InterferenceFunction1DLattice.h"
#include "Sample/Aggregate/InterferenceFunction2DLattice.h"
#include "Sample/Aggregate/InterferenceFunction2DParaCrystal.h"
#include "Sample/Aggregate/InterferenceFunction2DSuperLattice.h"
#include "Sample/Aggregate/InterferenceFunction3DLattice.h"
#include "Sample/Aggregate/InterferenceFunctionFinite2DLattice.h"
#include "Sample/Aggregate/InterferenceFunctionFinite3DLattice.h"
#include "Sample/Aggregate/InterferenceFunctionHardDisk.h"
#include "Sample/Aggregate/InterferenceFunctionNone.h"
#include "Sample/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Sample/Aggregate/InterferenceFunctionTwin.h"

#endif // BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONS_H
#endif // USER_API
