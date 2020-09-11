// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/main/appoptions.h
//! @brief     Collection of utilities to parse command line options
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_MAIN_APPOPTIONS_H
#define BORNAGAIN_GUI_MAIN_APPOPTIONS_H

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>

#include <string>

class QSize;

namespace bpo = boost::program_options;

//! @class ApplicationOptions
//! @ingroup tools_internal
//! @brief Handles command line and config file program options

class ApplicationOptions
{
public:
    ApplicationOptions(int argc = 0, char** argv = 0);

    //! access to variable with given name defined in variables container
    const bpo::variable_value& operator[](const std::string& s) const;

    //! Returns true if option with given name has been set
    bool find(std::string name) const;

    //! Returns true if options are consistent (no conflicts, no --help request)
    bool isConsistent() const;

    //! Parses command line arguments
    void parseCommandLine(int argc, char** argv);

    //! Returns reference to the variables container
    bpo::variables_map& getVariables();

    //! Returns reference to the options description
    bpo::options_description& getOptions();

    void processOptions();

    void printHelpMessage() const;

    QSize mainWindowSize() const;

    bool disableHighDPISupport();

private:
    //! true if options are consistent (no conflicts, no --help request)
    bool m_options_is_consistent;
    //! options description, to be filled with add() from different program modules
    bpo::options_description m_options;
    //! positional options description, to be filled with addPositional() from main module
    bpo::positional_options_description m_positional_options;
    bpo::variables_map m_variables_map; //! parsed variables
};

#endif // BORNAGAIN_GUI_MAIN_APPOPTIONS_H
