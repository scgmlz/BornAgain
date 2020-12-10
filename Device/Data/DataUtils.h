//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Data/DataUtils.h
//! @brief     Defines namespace DataUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_DATA_DATAUTILS_H
#define BORNAGAIN_DEVICE_DATA_DATAUTILS_H

#include "Device/Data/OutputData.h"
#include <memory>

namespace DataUtils {

//! Returns relative difference between two data sets sum(dat[i] - ref[i])/ref[i]).
double relativeDataDifference(const OutputData<double>& dat, const OutputData<double>& ref);

//! Returns true is relative difference is below threshold; prints informative output
bool checkRelativeDifference(const OutputData<double>& dat, const OutputData<double>& ref,
                             const double threshold);

//! Transforms coordinate on axis into the bin-fraction-coordinate.
double coordinateToBinf(double coordinate, const IAxis& axis);

//! Transforms bin-fraction-coordinate into axis coordinate.
double coordinateFromBinf(double value, const IAxis& axis);

//! Transforms x,y coordinate from OutputData axes coordinates to bin-fraction-coordinates.
void coordinateToBinf(double& x, double& y, const OutputData<double>& data);

//! Transforms x,y coordinate from bin-fraction-coordinates to OutputData's axes coordinates.
void coordinateFromBinf(double& x, double& y, const OutputData<double>& data);

//! Creates a vector of vectors of double (2D Array) from OutputData.
std::vector<std::vector<double>> create2DArrayfromOutputData(const OutputData<double>& data);

//! Reads 1D array of doubles to Python, for use in persistence test
OutputData<double>* importArrayToOutputData(const std::vector<double>& vec);
//! Reads 2D array of doubles to Python, for use in persistence test
OutputData<double>* importArrayToOutputData(const std::vector<std::vector<double>>& vec);

#ifndef SWIG

std::unique_ptr<OutputData<double>>
createRelativeDifferenceData(const OutputData<double>& data, const OutputData<double>& reference);

//! Returns new object with input data rotated by
//! n*90 deg counterclockwise (n > 0) or clockwise (n < 0)
//! Axes are swapped if the data is effectively rotated by 90 or 270 degrees
//! Applicable to 2D arrays only
std::unique_ptr<OutputData<double>> createRearrangedDataSet(const OutputData<double>& data, int n);

//! Returns new IntensityData objects which axes clipped to represent the specified rectangle.
std::unique_ptr<OutputData<double>>
createClippedDataSet(const OutputData<double>& origin, double x1, double y1, double x2, double y2);

//! Creates OutputData from a 2D Array.
std::unique_ptr<OutputData<double>>
createOutputDatafrom2DArray(const std::vector<std::vector<double>>& array_2d);

//! Creates Fourier Transform (OutputData format) of intensity map (OutputData format).
std::unique_ptr<OutputData<double>> createFFT(const OutputData<double>& data);

#endif // USER_API

} // namespace DataUtils

#endif // BORNAGAIN_DEVICE_DATA_DATAUTILS_H
