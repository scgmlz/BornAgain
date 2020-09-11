// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/DataFormatUtils.h
//! @brief     Defines class OutputDataIOFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INPUTOUTPUT_DATAFORMATUTILS_H
#define BORNAGAIN_CORE_INPUTOUTPUT_DATAFORMATUTILS_H

#include "Wrap/WinDllMacros.h"
#include <memory>
#include <string>
#include <vector>

class IAxis;
template <class T> class OutputData;

//! Utility functions for data input and output.

namespace DataFormatUtils
{
//! Returns true if name contains *.gz extension
BA_CORE_API_ bool isCompressed(const std::string& name);

//! Returns true if name contains *.gz extension
BA_CORE_API_ bool isGZipped(const std::string& name);

//! Returns true if name contains *.bz2 extension
BA_CORE_API_ bool isBZipped(const std::string& name);

//! Returns file extension after stripping '.gz' if any
BA_CORE_API_ std::string GetFileMainExtension(const std::string& name);

//! returns true if file name corresponds to BornAgain native format (compressed or not)
BA_CORE_API_ bool isIntFile(const std::string& file_name);

//! returns true if file name corresponds to tiff file (can be also compressed)
BA_CORE_API_ bool isTiffFile(const std::string& file_name);

BA_CORE_API_ std::unique_ptr<IAxis> createAxis(std::istream& input_stream);

BA_CORE_API_ void fillOutputData(OutputData<double>* data, std::istream& input_stream);

BA_CORE_API_ std::vector<double> parse_doubles(const std::string& str);

void readLineOfDoubles(std::vector<double>& buffer, std::istringstream& iss);
} // namespace DataFormatUtils

#endif // BORNAGAIN_CORE_INPUTOUTPUT_DATAFORMATUTILS_H
