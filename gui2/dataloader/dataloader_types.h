//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/dataloader/dataloader_types.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_DATALOADER_DATALOADER_TYPES_H
#define BORNAGAIN_GUI2_DATALOADER_DATALOADER_TYPES_H

#include "darefl_export.h"
#include <functional>
#include <string>
#include <vector>

namespace gui2 {

//! Parser options to process multi column ASCII files.

struct DAREFLCORE_EXPORT ParserOptions {    // #import Here the options for the default parser are defined
    std::string m_header_prefix = "#"; //!< prefix denoting header line
    std::string m_separator = " ";     //!< column separator
    std::string m_skip_index_pattern;  //!< pattern denoting line to skip (i.e. '1,10-12,42')
};

//! Info about the column as defined by the user via ImportTableWidget.

struct DAREFLCORE_EXPORT ColumnInfo {
    int column{-1};
    std::string type_name;
    std::string units;
    double multiplier{0.0};
};

//! Function to define if given index satisfies criteria.
using accept_int_t = std::function<bool(int)>;

//! Function to define if given string should be accepted for further consideration.
using accept_string_t = std::function<bool(const std::string& line)>;

//! Function to define line splitter according to some criteria.
using line_splitter_t = std::function<std::vector<std::string>(const std::string& line)>;

} // namespace gui2

#endif // BORNAGAIN_GUI2_DATALOADER_DATALOADER_TYPES_H
