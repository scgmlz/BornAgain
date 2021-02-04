//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/dataloader/defaultparser.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_DATALOADER_DEFAULTPARSER_H
#define BORNAGAIN_GUI2_DATALOADER_DEFAULTPARSER_H

#include "darefl_export.h"
#include "gui2/dataloader/dataloader_types.h"
#include "gui2/dataloader/parserinterface.h"
#include <map>

namespace gui2 {

//! Provides basic algorirthm for parsing multi-string data representing content
//! of multi-column ASCII file.
//! + Skips empty lines or lines matching the prefix.
//! + Skips lines matching given line number pattern.
//! + Parse data in columns of basing on given separator value.

// #import Here is a parser implementation (the only present parser so far)
class DAREFLCORE_EXPORT DefaultParser : public ParserInterface {
public:
    DefaultParser(const ParserOptions& options);

    void process(const std::vector<std::string>& raw_data) override;

    size_t totalLineCount() const override;

    std::string getLine(size_t index) const override;

    std::vector<std::string> parseResults(size_t index) const override;

    std::vector<std::vector<std::string>> parsedData() const override;

private:
    accept_int_t m_isSkipLineNumber;
    accept_string_t m_isValidLineContent;
    line_splitter_t m_line_splitter;
    std::vector<std::string> m_rawData;
    //!< correspondence of parsed data to original line index
    std::map<size_t, std::vector<std::string>> m_parsedData;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_DATALOADER_DEFAULTPARSER_H
