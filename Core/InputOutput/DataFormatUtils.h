// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/DataFormatUtils.h
//! @brief     Defines class OutputDataIOFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DATAFORMATUTILS_H
#define DATAFORMATUTILS_H

#include "WinDllMacros.h"
#include <string>
#include <vector>

class IAxis;
template <class T> class OutputData;

//! Utility functions for data input and output.

namespace DataFormatUtils {

const std::string FixedBinAxisType = "FixedBinAxis";
const std::string VariableBinAxisType = "VariableBinAxis";
const std::string ConstKBinAxisType = "ConstKBinAxis";
const std::string CustomBinAxisType = "CustomBinAxis";
const std::string GzipExtention = ".gz";
const std::string BzipExtention = ".bz2";
const std::string IntExtention = ".int";
const std::string TxtExtention = ".txt";
const std::string TiffExtention = ".tif";

//! Returns true if name contains *.gz extension
BA_CORE_API_ bool isCompressed(const std::string& name);

//! Returns true if name contains *.gz extension
BA_CORE_API_ bool isGZipped(const std::string& name);

//! Returns true if name contains *.bz2 extension
BA_CORE_API_ bool isBZipped(const std::string& name);

//! Returns file extension after stripping '.gz' if any
BA_CORE_API_ std::string GetFileMainExtension(const std::string& name);

//! returns true if file name corresponds to a binary file
BA_CORE_API_ bool isBinaryFile(const std::string& file_name);

//! returns true if file name corresponds to BornAgain native format (compressed or not)
BA_CORE_API_ bool isIntFile(const std::string& file_name);

//! returns true if file name corresponds to simple numpy-style ASCII file
BA_CORE_API_ bool isTxtFile(const std::string& file_name);

//! returns true if file name corresponds to tiff file (can be also compressed)
BA_CORE_API_ bool isTiffFile(const std::string& file_name);

BA_CORE_API_ bool isSimilarToFixedBinAxisType(const std::string& line);
BA_CORE_API_ bool isVariableBinAxisType(const std::string& line);

BA_CORE_API_ IAxis *createAxis(std::istream& input_stream);
BA_CORE_API_ IAxis *createFixedBinAxis(std::string line);
BA_CORE_API_ IAxis *createVariableBinAxis(std::string line);

BA_CORE_API_ void fillOutputData(OutputData<double>* data, std::istream& input_stream);

std::vector<double> parse_doubles(const std::string& str);

void readLineOfDoubles(std::vector<double>& buffer, std::istringstream& iss);
}

#endif // DATAFORMATUTILS_H
