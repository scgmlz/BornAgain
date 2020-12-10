//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Multilayer/RoughnessModels.h
//! @brief     Define RoughnessModels enumerator and Python wrapper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_MULTILAYER_ROUGHNESSMODELS_H
#define BORNAGAIN_SAMPLE_MULTILAYER_ROUGHNESSMODELS_H

#include <string>

// workaround for SWIG (instead of just writing enum class RoughnessModel ...)
struct RoughnessModelWrap {
    enum RoughnessModel { DEFAULT, TANH, NEVOT_CROCE };
#ifndef SWIG
    // TODO: to automatize enum to string convertion, one can possibly use this solution
    // https://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c#202511
    static std::string roughnessModelName(RoughnessModel model);
#endif
};
typedef RoughnessModelWrap::RoughnessModel RoughnessModel;

#endif // BORNAGAIN_SAMPLE_MULTILAYER_ROUGHNESSMODELS_H
