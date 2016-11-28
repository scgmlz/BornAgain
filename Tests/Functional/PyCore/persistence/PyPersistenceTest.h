// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/persistence/PyPersistenceTest.h
//! @brief     Defines class PyPersistenceTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYPERSISTENCETEST_H
#define PYPERSISTENCETEST_H

#include "IReferencedTest.h"
#include "OutputData.h"
#include <map>
#include <string>

namespace YAML {
    class Node;
}

//! A functional test that runs a Python script and compares its output with a reference.
//!   Invoked from RunPyPersistenceTest.
//!   Output and reference directories will be determined from environment variables
//!     PYPERSIST_OUT_DIR and PYPERSIST_REF_DIR set by CMake.
//!   Output and reference file names are obtained by globbing the directories;
//!     the stem must be the script name; the extension is arbitrary.
//!   One script may generate several output files, which must have different extensions.

class PyPersistenceTest : public IReferencedTest
{
public:
    PyPersistenceTest(const std::string& path, const std::string& name, double threshold);
    ~PyPersistenceTest() final {}

    bool runTest() final;

private:
    std::string m_path;

    static std::map<const std::string, const std::string>
        glob2map(const std::string& dir, const std::string& stem);

    bool compareFileMaps(
        const std::map<const std::string, const std::string>& dat,
        const std::map<const std::string, const std::string>& ref);
    bool compareFilePair(
        const std::string& dat_fname, const std::string& ref_fname) const;
    bool compareIntensityPair(
        const std::string& dat_fname, const std::string& ref_fname) const;
    static bool compareYamlPair(
        const std::string& dat_fname, const std::string& ref_fname);
    static bool compareYamlNode(
        const YAML::Node& dat, const YAML::Node& ref);
};

#endif // PYPERSISTENCETEST_H
