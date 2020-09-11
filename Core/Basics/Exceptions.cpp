// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/Exceptions.cpp
//! @brief     Implements class Exceptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Basics/Exceptions.h"
#include <iostream>

namespace Exceptions
{

void LogExceptionMessage(const std::string&)
{
    //    std::cerr << message << std::endl;
}

NotImplementedException::NotImplementedException(const std::string& message)
    : std::logic_error(message)
{
    LogExceptionMessage(message);
}

NullPointerException::NullPointerException(const std::string& message) : std::logic_error(message)
{
    LogExceptionMessage(message);
}

OutOfBoundsException::OutOfBoundsException(const std::string& message) : std::logic_error(message)
{
    LogExceptionMessage(message);
}

ClassInitializationException::ClassInitializationException(const std::string& message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

UnknownClassRegistrationException::UnknownClassRegistrationException(const std::string& message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

ExistingClassRegistrationException::ExistingClassRegistrationException(const std::string& message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

LogicErrorException::LogicErrorException(const std::string& message) : std::logic_error(message)
{
    LogExceptionMessage(message);
}

RuntimeErrorException::RuntimeErrorException(const std::string& message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

DivisionByZeroException::DivisionByZeroException(const std::string& message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

DomainErrorException::DomainErrorException(const std::string& message) : std::domain_error(message)
{
    LogExceptionMessage(message);
}

FileNotIsOpenException::FileNotIsOpenException(const std::string& message)
    : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

FileIsBadException::FileIsBadException(const std::string& message) : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

FormatErrorException::FormatErrorException(const std::string& message) : std::runtime_error(message)
{
    LogExceptionMessage(message);
}

} // namespace Exceptions
