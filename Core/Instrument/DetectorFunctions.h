// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectorFunctions.h
//! @brief     Defines namespace DetectorFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTORFUNCTIONS_H
#define DETECTORFUNCTIONS_H

#include "WinDllMacros.h"
#include "IDetector2D.h"
#include <string>
#include <memory>
template<class T> class OutputData;
class IDetector2D;
class Instrument;


//! Contains set of detector-related convenience functions.
//! @ingroup simulation

namespace DetectorFunctions {

//! Returns true if the data has same axes size (nx,ny) with the detector.
BA_CORE_API_ bool hasSameDimensions(const IDetector2D& detector, const OutputData<double>& data);

// TODO replace two functions below with the template function after change of
// OutputData::getAxis signature

//! Returns string representation of axes dimension in the form "(nx,ny)"
BA_CORE_API_ std::string axesToString(const IDetector2D& detector);

//! Returns string representation of axes dimension in the form "(nx,ny)"
BA_CORE_API_ std::string axesToString(const OutputData<double>& data);

//! Creates real data containing original user data clipped to the ROI area of the detector.
//! If put_masked_areas_to_zero==true:
//!     resulting data will have 0.0 in all masked areas
//! If put_masked_areas_to_zero==false:
//!     resulting data will be only cropped, masked areas will still contain intensities
//! TODO: what users will like more (this appears on FitSuitePlotObserver)?

BA_CORE_API_ std::unique_ptr<OutputData<double>> createDataSet(const Instrument& instrument,
    const OutputData<double> &data, bool put_masked_areas_to_zero=true,
    IDetector2D::EAxesUnits units=IDetector2D::DEFAULT);

}

#endif // DETECTORFUNCTIONS_H

