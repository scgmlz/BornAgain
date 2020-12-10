//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Resolution/IDetectorResolution.h
//! @brief     Defines interface IDetectorResolution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_DEVICE_RESOLUTION_IDETECTORRESOLUTION_H
#define BORNAGAIN_DEVICE_RESOLUTION_IDETECTORRESOLUTION_H

#include "Base/Types/ICloneable.h"
#include "Device/Data/OutputData.h"
#include "Param/Node/INode.h"

//! Interface for detector resolution algorithms
//! @ingroup algorithms_internal

class IDetectorResolution : public ICloneable, public INode {
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

#endif // BORNAGAIN_DEVICE_RESOLUTION_IDETECTORRESOLUTION_H
#endif // USER_API
