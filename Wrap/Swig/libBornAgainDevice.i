// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/swig/libBornAgainDevice.i
//! @brief     SWIG interface file for libBornAgainDevice
//!
//!            Configuration is done in Device/CMakeLists.txt
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1", moduleimport="import $module") "libBornAgainDevice"

%include "commons.i"

%include "../../auto/Wrap/doxygenDevice.i"

%include "ignoreBase.i"

// deprecations:
%rename(getArrayObsolete) IHistogram::getArray;
%extend IHistogram {
    %pythoncode %{
         @deprecated("Deprecated. Use array() instead.")
         def getArray(self):
             return self.getArrayObsolete()
    %}
 };

%{
#include "Param/Distrib/ParameterDistribution.h"
#include "Device/Beam/Beam.h"
#include "Device/Beam/FootprintGauss.h"
#include "Device/Beam/FootprintSquare.h"
#include "Device/Data/DataUtils.h"
#include "Device/Data/OutputData.h"
#include "Device/Detector/DetectorMask.h"
#include "Device/Detector/IDetector2D.h"
#include "Device/Detector/IsGISAXSDetector.h"
#include "Device/Detector/RectangularDetector.h"
#include "Device/Detector/SphericalDetector.h"
#include "Device/Histo/HistoUtils.h"
#include "Device/Histo/Histogram1D.h"
#include "Device/Histo/Histogram2D.h"
#include "Device/Histo/IHistogram.h"
#include "Device/Histo/IntensityDataIOFactory.h"
#include "Device/Histo/SimulationResult.h"
#include "Device/Mask/Ellipse.h"
#include "Device/Mask/IShape2D.h"
#include "Device/Mask/Line.h"
#include "Device/Mask/Polygon.h"
#include "Device/Mask/Rectangle.h"
#include "Device/Resolution/IDetectorResolution.h"
#include "Device/Resolution/IResolutionFunction2D.h"
#include "Device/Resolution/ResolutionFunction2DGaussian.h"
#include "Device/Resolution/ScanResolution.h"
%}

%import(module="libBornAgainFit") "Fit/Param/AttLimits.h"
%import(module="libBornAgainFit") "Fit/Param/Attributes.h"
%import(module="libBornAgainFit") "Fit/Param/RealLimits.h"
%import(module="libBornAgainFit") "Fit/Param/Parameters.h"
%import(module="libBornAgainFit") "Fit/Param/Parameter.h"

%include "fromBase.i"
%include "fromParam.i"

// ownership
%newobject ScanResolution::scanRelativeResolution;
%newobject ScanResolution::scanAbsoluteResolution;

%newobject SimulationResult::histogram2d(Axes::Units units_type = Axes::Units::DEFAULT) const;

%newobject IntensityDataIOFactory::readOutputData(const std::string& file_name);
%newobject IntensityDataIOFactory::readIntensityData(const std::string& file_name);

%newobject DetectorMask::createHistogram() const;

%newobject DataUtils::importArrayToOutputData;
%newobject IHistogram::createFrom(const std::string& filename);
%newobject IHistogram::createFrom(const std::vector<std::vector<double>>& data);

%include "Device/Data/OutputData.h"
%template(IntensityData) OutputData<double>;
%include "Device/Data/DataUtils.h"

%include "Device/Beam/Beam.h"
%include "Device/Beam/IFootprintFactor.h"
%include "Device/Beam/FootprintGauss.h"
%include "Device/Beam/FootprintSquare.h"
%include "Device/Mask/IShape2D.h"
%include "Device/Mask/Ellipse.h"
%include "Device/Mask/Line.h"
%include "Device/Mask/Polygon.h"
%include "Device/Mask/Rectangle.h"
%include "Device/Resolution/IDetectorResolution.h"
%include "Device/Resolution/IResolutionFunction2D.h"
%include "Device/Resolution/ResolutionFunction2DGaussian.h"
%include "Device/Resolution/ScanResolution.h"

%include "Device/Unit/IUnitConverter.h"

%include "Device/Detector/DetectorMask.h"
%include "Device/Detector/IDetector.h"
%include "Device/Detector/IDetector2D.h"
%include "Device/Detector/RectangularDetector.h"
%include "Device/Detector/SphericalDetector.h"
%include "Device/Detector/IsGISAXSDetector.h"

%include "Device/Histo/HistoUtils.h"
%include "Device/Histo/IHistogram.h"
%include "Device/Histo/Histogram1D.h"
%include "Device/Histo/Histogram2D.h"
%include "Device/Histo/IntensityDataIOFactory.h"
%include "Device/Histo/SimulationResult.h"

%extend OutputData<double> {
    double __getitem__(unsigned int i) { return (*($self))[i]; }
    double __setitem__(unsigned int i, double value)
    {
        (*($self))[i] = value;
        return (*($self))[i];
    }
};

%extend SimulationResult {
    double __getitem__(unsigned int i) { return (*($self))[i]; }
    double __setitem__(unsigned int i, double value)
    {
        (*($self))[i] = value;
        return (*($self))[i];
    }
};

// fancy names for ScanResolution static functions
%pythoncode %{
    def ScanRelativeResolution(distribution, rel_dev):
        """
        Creates a scan resolution from the given distribution and
        relative deviation values (that is, the ratios of standard
        deviations and means).
        :param distribution: bornagain.IRangedDistribution object
        :param rel_dev: either single-valued or a numpy array.
                        In the latter case should coinside in
                        size with later used mean values array.
        :return: bornagain.ScanResolution object
        """
        return ScanResolution_scanRelativeResolution(distribution, rel_dev)

    def ScanAbsoluteResolution(distribution, std_dev):
        """
        Creates a scan resolution from the given distribution and
        standard deviation values.
        :param distribution: bornagain.IRangedDistribution object
        :param std_dev: either single-valued or a numpy array.
                        In the latter case should coinside in
                        size with later used mean values array.
        :return: bornagain.ScanResolution object
        """
        return ScanResolution_scanAbsoluteResolution(distribution, std_dev)
%}
