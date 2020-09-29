// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/Exceptions.h
//! @brief     Defines many exception classes in namespace Exceptionss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BASICS_EXCEPTIONS_H
#define BORNAGAIN_CORE_BASICS_EXCEPTIONS_H

#include <stdexcept>
#include <string>

#ifdef _WIN32
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4275)
#endif
#endif

//! Different exceptions, all inheriting from std::exception.

namespace Exceptions
{

class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException(const std::string& message);
};

class NullPointerException : public std::logic_error
{
public:
    NullPointerException(const std::string& message);
};

class OutOfBoundsException : public std::logic_error
{
public:
    OutOfBoundsException(const std::string& message);
};

class ClassInitializationException : public std::runtime_error
{
public:
    ClassInitializationException(const std::string& message);
};

class UnknownClassRegistrationException : public std::runtime_error
{
public:
    UnknownClassRegistrationException(const std::string& message);
};

class ExistingClassRegistrationException : public std::runtime_error
{
public:
    ExistingClassRegistrationException(const std::string& message);
};

class LogicErrorException : public std::logic_error
{
public:
    LogicErrorException(const std::string& message);
};

class RuntimeErrorException : public std::runtime_error
{
public:
    RuntimeErrorException(const std::string& message);
};

class DivisionByZeroException : public std::runtime_error
{
public:
    DivisionByZeroException(const std::string& message);
};

class DomainErrorException : public std::domain_error
{
public:
    DomainErrorException(const std::string& message);
};

class FileNotIsOpenException : public std::runtime_error
{
public:
    FileNotIsOpenException(const std::string& message);
};

class FileIsBadException : public std::runtime_error
{
public:
    FileIsBadException(const std::string& message);
};

class FormatErrorException : public std::runtime_error
{
public:
    FormatErrorException(const std::string& message);
};

void LogExceptionMessage(const std::string& message);

} // namespace Exceptions

#ifdef _WIN32
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif

#endif // BORNAGAIN_CORE_BASICS_EXCEPTIONS_H
