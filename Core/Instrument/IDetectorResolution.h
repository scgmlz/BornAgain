// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IDetectorResolution.h
//! @brief     Defines class IDetectorResolution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IDETECTORRESOLUTION_H
#define IDETECTORRESOLUTION_H

#include "ICloneable.h"
#include "IParameterized.h"
#include "OutputData.h"

//! @class IDetectorResolution
//! @ingroup algorithms_internal
//! @brief Interface for detector resolution algorithms

class BA_CORE_API_ IDetectorResolution : public ICloneable, public IParameterized
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

#endif // IDETECTORRESOLUTION_H
