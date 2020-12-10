//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Utils/FileSystemUtils.h
//! @brief     Defines namespace FileSystemUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_BASE_UTILS_FILESYSTEMUTILS_H
#define BORNAGAIN_BASE_UTILS_FILESYSTEMUTILS_H

#include <string>
#include <vector>

//! Utility functions to deal with file system.

namespace FileSystemUtils {

//! Returns extension of given filename.
//! "/home/user/filename.int" -> ".int", "/home/user/filename.int.gz" -> ".gz"
std::string extension(const std::string& path);

//! Returns extension(s) of given filename.
//! "/home/user/filename.int" -> ".int", "/home/user/filename.int.gz" -> ".int.gz"
std::string extensions(const std::string& path);

//! Creates directory in current directory
bool createDirectory(const std::string& dir_name);

//! Creates directories in current directory for any element of dir_name which doesn't exist.
bool createDirectories(const std::string& dir_name);

//! Returns filenames of files in directory
std::vector<std::string> filesInDirectory(const std::string& dir_name);

//! Returns joint path name.
std::string jointPath(const std::string& path1, const std::string& path2);

//! Returns path without directory part ("Foo/Bar/Doz.int.gz" -> "Doz.int.gz")
std::string filename(const std::string& path);

//! Returns filename without (last) extension.
//! "/home/user/filename.int" -> "filename", "/home/user/filename.int.gz" -> "filename.int"
std::string stem(const std::string& path);

//! Returns filename without extension(s).
//! "/home/user/filename.int" -> "filename", "/home/user/filename.int.gz" -> "filename"
std::string stem_ext(const std::string& path);

//! Returns file names that agree with a regex glob pattern.
std::vector<std::string> glob(const std::string& dir, const std::string& pattern);

//! Converts utf8 string represented by std::string to utf16 string represented by std::wstring.
std::wstring convert_utf8_to_utf16(const std::string& str);

//! Returns true if file with given name exists on disk.
bool IsFileExists(const std::string& path);

} // namespace FileSystemUtils

#endif // BORNAGAIN_BASE_UTILS_FILESYSTEMUTILS_H
#endif // USER_API
