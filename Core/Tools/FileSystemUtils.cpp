// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/FileSystemUtils.cpp
//! @brief     Implements namespace FileSystemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Tools/FileSystemUtils.h"
#include "Core/Basics/Assert.h"
#include "Core/Basics/Exceptions.h"
#include <boost/filesystem.hpp>
#include <codecvt>
#include <locale>
#include <regex>
#include <stdexcept>

std::string FileSystemUtils::extension(const std::string& path)
{
    return boost::filesystem::extension(path.c_str());
}

std::string FileSystemUtils::extensions(const std::string& path)
{
    auto name = FileSystemUtils::filename(path);
    auto npos = name.find_first_of('.');
    return npos != std::string::npos ? name.substr(npos, name.size() - npos) : std::string();
}

bool FileSystemUtils::createDirectory(const std::string& dir_name)
{
#ifdef _WIN32
    boost::filesystem::path path(convert_utf8_to_utf16(dir_name));
#else
    boost::filesystem::path path(dir_name);
#endif
    return boost::filesystem::create_directory(dir_name);
}

bool FileSystemUtils::createDirectories(const std::string& dir_name)
{
#ifdef _WIN32
    boost::filesystem::path path(convert_utf8_to_utf16(dir_name));
#else
    boost::filesystem::path path(dir_name);
#endif
    return boost::filesystem::create_directories(path);
}

std::vector<std::string> FileSystemUtils::filesInDirectory(const std::string& dir_name)
{
    std::vector<std::string> ret;
    if (!boost::filesystem::exists(dir_name))
        throw std::runtime_error("FileSystemUtils::filesInDirectory '" + dir_name
                                 + "' does not exist");
    boost::filesystem::directory_iterator end_it; // default construction yields past-the-end
    for (boost::filesystem::directory_iterator it(dir_name);
         it != boost::filesystem::directory_iterator(); ++it) {
        if (!boost::filesystem::is_regular_file(it->status()))
            continue;
        ret.push_back(it->path().filename().string());
    }
    return ret;
}

std::string FileSystemUtils::jointPath(const std::string& spath1, const std::string& spath2)
{
    ASSERT(spath1 != "");
    ASSERT(spath2 != "");
    boost::filesystem::path path1(spath1);
    boost::filesystem::path path2(spath2);
    boost::filesystem::path full_path = path1 / path2;

    return full_path.string();
}

std::string FileSystemUtils::filename(const std::string& path)
{
    return boost::filesystem::path(path).filename().string();
}

std::vector<std::string> FileSystemUtils::glob(const std::string& dir, const std::string& pattern)
{
    std::vector<std::string> ret;
    for (const std::string& fname : filesInDirectory(dir))
        if (std::regex_match(fname, std::regex(pattern)))
            ret.push_back(fname);
    return ret;
}

std::string FileSystemUtils::stem(const std::string& path)
{
    return boost::filesystem::path(path).stem().string();
}

std::string FileSystemUtils::stem_ext(const std::string& path)
{
    auto name = FileSystemUtils::filename(path);
    auto npos = name.find_first_of('.');
    return npos != std::string::npos ? name.substr(0, npos) : std::string();
}

std::wstring FileSystemUtils::convert_utf8_to_utf16(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

bool FileSystemUtils::IsFileExists(const std::string& str)
{
#ifdef _WIN32
    boost::filesystem::path path(convert_utf8_to_utf16(str));
#else
    boost::filesystem::path path(str);
#endif
    return boost::filesystem::exists(path);
}
