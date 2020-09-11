// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/IDetectorResolution.h
//! @brief     Defines class IDetectorResolution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_DETECTOR_IDETECTORRESOLUTION_H
#define BORNAGAIN_CORE_DETECTOR_IDETECTORRESOLUTION_H

#include "Core/Basics/ICloneable.h"
#include "Core/Intensity/OutputData.h"
#include "Core/Parametrization/INode.h"

//! Interface for detector resolution algorithms
//! @ingroup algorithms_internal

class BA_CORE_API_ IDetectorResolution : public ICloneable, public INode
{
public:
    virtual ~IDetectorResolution() {}
    //! Apply the resolution function to the intensity data
    virtual void applyDetectorResolution(OutputData<double>* p_intensity_map) const = 0;
#ifndef SWIG
    //! Applies the detector resolution to the matrix-valued intensity data
    void applyDetectorResolutionPol(OutputData<Eigen::Matrix2d>* p_matrix_intensity) const;
#endif
    virtual IDetectorResolution* clone() const = 0;
};

#endif // BORNAGAIN_CORE_DETECTOR_IDETECTORRESOLUTION_H
