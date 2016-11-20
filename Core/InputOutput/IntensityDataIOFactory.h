// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/IntensityDataIOFactory.h
//! @brief     Defines class IntensityDataIOFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAIOFACTORY_H
#define INTENSITYDATAIOFACTORY_H

#include "WinDllMacros.h"
#include <string>

template <class T> class OutputData;
class IHistogram;

//! Provides users with possibility to read and write IntensityData from/to files
//! in different format. Type of the file will be deduced from file name.
//! *.txt - ASCII file with 2D array [nrow][ncol], layout as in numpy.
//! *.int - BornAgain internal ASCII format.
//! *.tif - 32-bits tiff file.
//! If file name ends woth "*.gz" or "*.bz2" the file will be zipped on the fly using
//! appropriate algorithm.

//! @ingroup input_output

/*! Usage:
\code{.py}
# reading from ASCII file or g-zipped ASCII file
histogram = IntensityDataIOFactory.readIntensityData("filename.txt")
histogram = IntensityDataIOFactory.readIntensityData("filename.txt.gz")

# writing to 32-bits tiff file or b-zipped tiff file
IntensityDataIOFactory.writeIntensityData(histogram, "filename.tif")
IntensityDataIOFactory.writeIntensityData(histogram, "filename.tif.bz2")
\endcode
*/

class BA_CORE_API_ IntensityDataIOFactory
{
public:
    //! Reads file and returns newly created OutputData object
    static OutputData<double>* readOutputData(const std::string& file_name);

    //! Reads file and returns newly created Histogram object
    static IHistogram* readIntensityData(const std::string& file_name);

    //! Writes OutputData in file
    static void writeOutputData(const OutputData<double>& data, const std::string& file_name);

    //! Writes histogram in file
    static void writeIntensityData(const IHistogram &histogram, const std::string& file_name);
};

#endif // INTENSITYDATAIOFACTORY_H
