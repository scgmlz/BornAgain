// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/main/appoptions.cpp
//! @brief     Implements class ProgramOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/main/appoptions.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QSize>
#include <boost/program_options/config.hpp>
#include <boost/program_options/parsers.hpp>
#include <fstream>
#include <iostream>

namespace
{
const char* geometry = "geometry";
const char* nohighdpi = "nohighdpi";

//! Converts string "1600x1000" to QSize(1600, 1000)
QSize windowSize(const QString& size_string)
{
    auto list = size_string.split("x");

    if (list.size() != 2)
        return QSize();

    return QSize(list[0].toInt(), list[1].toInt());
}

//! Returns true if windows size makes sence.
bool isValid(const QSize& win_size)
{
    if (win_size.width() > 640 && win_size.height() > 480)
        return true;

    return false;
}

} // namespace

ApplicationOptions::ApplicationOptions(int argc, char** argv) : m_options_is_consistent(false)
{
    m_options.add_options()("help,h", "print help message");
    m_options.add_options()("with-debug", "run application with debug printout");
    m_options.add_options()("no-splash", "do not show splash screen");
    m_options.add_options()(geometry, bpo::value<std::string>(),
                            "Main window geometry, e.g. 1600x1000");
    m_options.add_options()(nohighdpi, "Run without high-dpi support");

    parseCommandLine(argc, argv);

    processOptions();
}

//! access variables

const bpo::variable_value& ApplicationOptions::operator[](const std::string& s) const
{
    return m_variables_map[s.c_str()];
}

bool ApplicationOptions::find(std::string name) const
{
    return (m_variables_map.count(name.c_str()) ? true : false);
}

bool ApplicationOptions::isConsistent() const
{
    return m_options_is_consistent;
}

//! parse command line arguments

void ApplicationOptions::parseCommandLine(int argc, char** argv)
{
    m_options_is_consistent = false;
    // parsing command line arguments
    try {
        // if positional option description is empty, no command line arguments
        // without '--' or '-' will be accepted
        // 'store' populates the variable map
        bpo::store(bpo::command_line_parser(argc, argv)
                       .options(m_options)
                       .positional(m_positional_options)
                       .run(),
                   m_variables_map);
        // bpo::store(bpo::parse_command_line(argc, argv, m_options), m_variables_map);

        // 'notify' raises any errors encountered
        bpo::notify(m_variables_map);

        m_options_is_consistent = true;
    } catch (std::exception& e) {
        // we get here if there is unrecognized options
        std::cout << "main() ->  " << e.what() << std::endl;
        std::cout << m_options << std::endl;
    }
}

boost::program_options::variables_map& ApplicationOptions::getVariables()
{
    return m_variables_map;
}

boost::program_options::options_description& ApplicationOptions::getOptions()
{
    return m_options;
}

void ApplicationOptions::processOptions()
{
    if (m_variables_map.count("help")) {
        printHelpMessage();
        m_options_is_consistent = false;
    }

    else if (m_variables_map.count("version")) {
        std::cout << "BornAgain-" << GUIHelpers::getBornAgainVersionString().toStdString()
                  << std::endl;
        m_options_is_consistent = false;
    }

    else if (m_variables_map.count(geometry)) {
        if (!isValid(mainWindowSize())) {
            std::cout << "Wrong window size, try --geometry=1600x900\n";
            m_options_is_consistent = false;
        }
    }
}

void ApplicationOptions::printHelpMessage() const
{
    std::cout << "BornAgain Graphical User Interface" << std::endl;
    std::cout << m_options << std::endl;
}

QSize ApplicationOptions::mainWindowSize() const
{
    QString size_str = QString::fromStdString(m_variables_map[geometry].as<std::string>());
    return windowSize(size_str);
}

bool ApplicationOptions::disableHighDPISupport()
{
    return find(nohighdpi);
}
