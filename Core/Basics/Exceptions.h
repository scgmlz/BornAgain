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

#include "Wrap/WinDllMacros.h"
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

class BA_CORE_API_ NotImplementedException : public std::logic_error
{
public:
    NotImplementedException(const std::string& message);
};

class BA_CORE_API_ NullPointerException : public std::logic_error
{
public:
    NullPointerException(const std::string& message);
};

class BA_CORE_API_ OutOfBoundsException : public std::logic_error
{
public:
    OutOfBoundsException(const std::string& message);
};

class BA_CORE_API_ ClassInitializationException : public std::runtime_error
{
public:
    ClassInitializationException(const std::string& message);
};

class BA_CORE_API_ UnknownClassRegistrationException : public std::runtime_error
{
public:
    UnknownClassRegistrationException(const std::string& message);
};

class BA_CORE_API_ ExistingClassRegistrationException : public std::runtime_error
{
public:
    ExistingClassRegistrationException(const std::string& message);
};

class BA_CORE_API_ LogicErrorException : public std::logic_error
{
public:
    LogicErrorException(const std::string& message);
};

class BA_CORE_API_ RuntimeErrorException : public std::runtime_error
{
public:
    RuntimeErrorException(const std::string& message);
};

class BA_CORE_API_ DivisionByZeroException : public std::runtime_error
{
public:
    DivisionByZeroException(const std::string& message);
};

class BA_CORE_API_ DomainErrorException : public std::domain_error
{
public:
    DomainErrorException(const std::string& message);
};

class BA_CORE_API_ FileNotIsOpenException : public std::runtime_error
{
public:
    FileNotIsOpenException(const std::string& message);
};

class BA_CORE_API_ FileIsBadException : public std::runtime_error
{
public:
    FileIsBadException(const std::string& message);
};

class BA_CORE_API_ FormatErrorException : public std::runtime_error
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
