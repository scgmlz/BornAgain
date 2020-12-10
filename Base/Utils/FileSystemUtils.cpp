//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Utils/FileSystemUtils.cpp
//! @brief     Implements namespace FileSystemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Base/Utils/FileSystemUtils.h"
#include "Base/Utils/Assert.h"
#include <codecvt>
#include <filesystem>
#include <locale>
#include <regex>
#include <stdexcept>

namespace fs = std::filesystem; // make the code more readable

std::string FileSystemUtils::extension(const std::string& path) {
    return fs::path(path).extension().string();
}

std::string FileSystemUtils::extensions(const std::string& path) {
    const auto name = FileSystemUtils::filename(path);
    if (name == "..")
        return {};

    const auto pos = name.find_first_of('.', 1); // 1: ignore any file-is-hidden dot
    return pos != std::string::npos ? name.substr(pos, name.size() - pos) : std::string();
}

bool FileSystemUtils::createDirectory(const std::string& dir_name) {
#ifdef _WIN32
    return fs::create_directory(convert_utf8_to_utf16(dir_name));
#else
    return fs::create_directory(dir_name);
#endif
}

bool FileSystemUtils::createDirectories(const std::string& dir_name) {
#ifdef _WIN32
    return fs::create_directories(convert_utf8_to_utf16(dir_name));
#else
    return fs::create_directories(dir_name);
#endif
}

std::vector<std::string> FileSystemUtils::filesInDirectory(const std::string& dir_name) {
    std::vector<std::string> ret;
    if (!fs::exists(dir_name))
        throw std::runtime_error("FileSystemUtils::filesInDirectory '" + dir_name
                                 + "' does not exist");

    for (const auto& entry : fs::directory_iterator(dir_name))
        if (entry.is_regular_file())
            ret.push_back(entry.path().filename().string());

    return ret;
}

std::string FileSystemUtils::jointPath(const std::string& path1, const std::string& path2) {
    ASSERT(path1 != "");
    ASSERT(path2 != "");

    return (fs::path(path1) / fs::path(path2)).string();
}

std::string FileSystemUtils::filename(const std::string& path) {
    return fs::path(path).filename().string();
}

std::vector<std::string> FileSystemUtils::glob(const std::string& dir, const std::string& pattern) {
    std::vector<std::string> ret;
    for (const std::string& fname : filesInDirectory(dir))
        if (std::regex_match(fname, std::regex(pattern)))
            ret.push_back(fname);
    return ret;
}

std::string FileSystemUtils::stem(const std::string& path) {
    return fs::path(path).stem().string();
}

std::string FileSystemUtils::stem_ext(const std::string& path) {
    const auto name = FileSystemUtils::filename(path);
    if (name == "..")
        return name;

    const auto pos = name.find_first_of('.', 1); // 1: ignore any file-is-hidden dot
    return pos != std::string::npos ? name.substr(0, pos) : name;
}

std::wstring FileSystemUtils::convert_utf8_to_utf16(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

bool FileSystemUtils::IsFileExists(const std::string& path) {
#ifdef _WIN32
    return fs::exists(convert_utf8_to_utf16(path));
#else
    return fs::exists(path);
#endif
}
