//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/dataloader/parserinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_DATALOADER_PARSERINTERFACE_H
#define BORNAGAIN_GUI2_DATALOADER_PARSERINTERFACE_H

#include "darefl_export.h"
#include <string>
#include <vector>

namespace gui2 {

//! Interface for all classes capable of parsing ASCII data into multicolumn presentation.

class DAREFLCORE_EXPORT ParserInterface {       // #import Here is where the data gets parsed
public:
    virtual ~ParserInterface() = default;

    //! Parse data representing content of ASCII file.
    virtual void process(const std::vector<std::string>& raw_data) = 0;

    //! Returns total number of lines in raw data.
    virtual size_t totalLineCount() const = 0;

    //! Returns original line.
    virtual std::string getLine(size_t index) const = 0;

    //! Returns parsed text for given line index. If line was skipped during parsing, returns empty
    //! vector.
    virtual std::vector<std::string> parseResults(size_t index) const = 0;

    //! Returns 2D vector representing parsed text. Skipped lines are not present.
    virtual std::vector<std::vector<std::string>> parsedData() const = 0;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_DATALOADER_PARSERINTERFACE_H
