// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/FileSystemUtils.cpp
//! @brief     Implements namespace FileSystemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FileSystemUtils.h"
#include "Exceptions.h"
#include <boost/filesystem.hpp>
#include <cassert>
#include <boost/regex.hpp>
#include <stdexcept>

//! Returns extension of given filename.
std::string FileSystemUtils::extension(const std::string& name)
{
    return boost::filesystem::extension(name.c_str());
}

bool FileSystemUtils::createDirectory(const std::string& dir_name)
{
    assert(dir_name!="");
    return boost::filesystem::create_directory(dir_name);
}

//! Returns filenames of files in directory
std::vector<std::string> FileSystemUtils::filesInDirectory(const std::string& dir_name)
{
    std::vector<std::string> ret;
    if (!boost::filesystem::exists(dir_name))
        throw std::runtime_error(
            "FileSystemUtils::filesInDirectory '" + dir_name + "' does not exist");
    boost::filesystem::directory_iterator end_it; // default construction yields past-the-end
    for ( boost::filesystem::directory_iterator it( dir_name );
          it != boost::filesystem::directory_iterator(); ++it ) {
        if( !boost::filesystem::is_regular_file( it->status() ) )
            continue;
        ret.push_back( it->path().filename().string() );
    }
    return ret;
}

std::string FileSystemUtils::jointPath(const std::string& spath1, const std::string& spath2)
{
    assert(spath1!="");
    assert(spath2!="");
    boost::filesystem::path path1(spath1);
    boost::filesystem::path path2(spath2);
    boost::filesystem::path full_path = path1 / path2;

    return full_path.string();
}

//! Returns path without directory part ("Foo/Bar/Doz.int.gz" -> "Doz.int.gz")
std::string FileSystemUtils::filename(const std::string& path)
{
    return boost::filesystem::path(path).filename().string();
}

//! Returns file names that agree with a regex glob pattern.
std::vector<std::string> FileSystemUtils::glob(const std::string& dir, const std::string& pattern)
{
    std::vector<std::string> ret;
    for (const std::string& fname: filesInDirectory(dir))
        if (boost::regex_match(fname, boost::regex(pattern)))
            ret.push_back(fname);
    return ret;
}
