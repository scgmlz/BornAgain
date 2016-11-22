// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/persistence/PyPersistenceTest.cpp
//! @brief     Implements class PyPersistenceTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyPersistenceTest.h"
#include "FileSystemUtils.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "PythonFormatting.h"
#include "SimulationFactory.h"
#include "StringUtils.h"
#include <yaml-cpp/yaml.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <iomanip>

PyPersistenceTest::PyPersistenceTest(
    const std::string& directory, const std::string& name)
    : IReferencedTest(name, "persistence test on script "+name, 2e-10)
    , m_directory(directory)
{}

//! Runs a Python script, and returns true if the output of the script agrees with reference data.
bool PyPersistenceTest::runTest()
{
    // Remove old output
    for (const std::string& fname:
             FileSystemUtils::glob(PYPERSIST_OUT_DIR, getName()+"\\.\\w+\\..+")) {
        std::remove( fname.c_str() );
        std::cout << "Removed old output " << fname.c_str() << "\n";
    }

    // Run Python script
    std::string pyscript_filename = FileSystemUtils::jointPath(m_directory, getName()+".py");
    std::string dat_stem = FileSystemUtils::jointPath(PYPERSIST_OUT_DIR, getName());
    if (!runPython(pyscript_filename + " " + dat_stem))
        return false;

    // Retrieve new output and reference files
    std::map<const std::string, const std::string> dat = glob2map(PYPERSIST_OUT_DIR, getName());
    std::map<const std::string, const std::string> ref = glob2map(PYPERSIST_REF_DIR, getName());
    if (dat.size()==0) {
        std::cerr << "There is no test output of form " << dat_stem << ".*.*\n";
        return false;
    }
    // Compare the keys in the file names
    if (!compareFileMaps(dat, ref))
        return false;

    // Compare files one by one
    for (auto const& it: dat)
        if (!compareFilePair(
                FileSystemUtils::jointPath(PYPERSIST_OUT_DIR, it.second),
                FileSystemUtils::jointPath(PYPERSIST_REF_DIR, ref[it.first])))
            return false;
    return true;
}

//! Globs for files of form *.<key1>.<key2>[.*], and returns a map with keys of the form
//! <key1>.<key2>, and values containing full file paths.
std::map<const std::string, const std::string>
PyPersistenceTest::glob2map(const std::string& dir, const std::string& stem)
{
    std::map<const std::string, const std::string> ret;
    for (const std::string& fname: FileSystemUtils::glob(dir, stem+"\\.\\w+\\..+")) {
        std::vector<std::string> fname_segments =
            StringUtils::split(FileSystemUtils::filename(fname), ".");
        ret.insert(make_pair(fname_segments[1]+"."+fname_segments[2], fname));
    }
    return ret;
}

//! Returns true if two file maps have the same set of keys.
bool PyPersistenceTest::compareFileMaps(
    const std::map<const std::string, const std::string>& dat,
    const std::map<const std::string, const std::string>& ref)
{
    bool success = true;
    // All dat files present in ref?
    for (auto const& it: dat) {
        if (ref.find(it.first)==ref.end()) {
            std::cerr << "For test output " << it.second
                      << " there is no reference file in " << PYPERSIST_REF_DIR << "\n";
            success = false;
        }
    }
    // All ref files present in dat?
    for (auto const& it: ref) {
        if (dat.find(it.first)==dat.end()) {
            std::cerr << "For reference file " << it.second
                      << " there is no test output in " << PYPERSIST_OUT_DIR << "\n";
            success = false;
        }
    }
    return success;
}

//! Returns true if test output and reference file agree.
bool PyPersistenceTest::compareFilePair(
    const std::string& dat_fpath, const std::string& ref_fpath)
{
    std::cout << "Comparing dat='" << dat_fpath << "' with ref='" << ref_fpath << "':\n";
    const std::string extension = StringUtils::split(FileSystemUtils::filename(dat_fpath), ".")[2];
    if ( extension=="int" )
        return compareIntensityPair( dat_fpath, ref_fpath );
    if ( extension=="yaml" )
        return compareYamlPair( dat_fpath, ref_fpath );
    std::cerr << "Failed: Unsupported file type '" << extension << "'\n";
    return false;
}

//! Returns true if intensity maps from test output and reference file agree reasonably.
bool PyPersistenceTest::compareIntensityPair(
    const std::string& dat_fpath, const std::string& ref_fpath)
{
    const OutputData<double>* dat = IntensityDataIOFactory::readOutputData( dat_fpath );
    const OutputData<double>* ref = IntensityDataIOFactory::readOutputData( ref_fpath );
    return compareIntensityMaps(*dat, *ref);
}

//! Returns true if YAML files from test output and reference agree.
bool PyPersistenceTest::compareYamlPair(
    const std::string& dat_fpath, const std::string& ref_fpath)
{
    std::fstream fdat(dat_fpath);
    std::fstream fref(ref_fpath);
    return compareYamlNode( YAML::Load(fdat), YAML::Load(fref) );
}

//! Returns true if all entries of the two YAML files agree.
//! Floating-point entries must agree within a certain tolerance.
//! The investigation is performed recursively, iterating over all lists and maps.
bool PyPersistenceTest::compareYamlNode(const YAML::Node& dat, const YAML::Node& ref)
{
    if (dat.Type() != ref.Type()) {
        std::cerr << "YAML node type differs: " << dat.Type() << " vs " << ref.Type() << "\n";
        return false;
    }
    if      (dat.Type()==YAML::NodeType::Undefined)
        throw std::runtime_error("Invalid node type 'Undefined' in YAML tree");
    else if (dat.Type()==YAML::NodeType::Null)
        throw std::runtime_error("Invalid node type 'Null' in YAML tree");
    else if (dat.Type()==YAML::NodeType::Sequence) {
        if (dat.size()!=ref.size()) {
            std::cerr << "lists have different length\n";
            return false;
        }
        for (size_t i=0; i<dat.size(); ++i) {
            if (!compareYamlNode(dat[i], ref[i])) {
                std::cerr << "at list position " << i << "\n";
                return false;
            }
        }
    } else if (dat.Type()==YAML::NodeType::Map) {
        for (const auto& it_ref: ref) {
            const YAML::Node& datval = dat[it_ref.first.as<std::string>()];
            if (!datval) {
                std::cerr << "map entry [" << it_ref.first << "] has no correspondence in dat\n";
                return false;
            }
        }
        for (const auto& it_dat: dat) {
            const YAML::Node& refval = ref[it_dat.first.as<std::string>()];
            if (!refval) {
                std::cerr << "map entry [" << it_dat.first << "] has no correspondence in ref\n";
                return false;
            }
            if (!compareYamlNode(it_dat.second, refval)) {
                std::cerr << "at map entry [" << it_dat.first << "]\n";
                return false;
            }
        }
        return true;
    } else if (dat.Type()==YAML::NodeType::Scalar) {
        if (dat.as<std::string>() == ref.as<std::string>())
            return true;
        try {
            double d = dat.as<double>();
            double r = ref.as<double>();
            const double tol = 1e-1;
            if (std::abs(d-r)>(std::abs(d)+std::abs(r))*tol) {
                std::cerr << "numbers differ: " << dat << " vs " << ref << "\n";
                return false;
            }
            return true;
        } catch(...) {
            std::cerr << "scalar entries differ: '" << dat << "' vs '" << ref << "'\n";
            return false;
        }
    } else
        throw std::runtime_error("Bug in PyPersistenceTest::compareYamlNode: unexpected node type");
    return true;
}
