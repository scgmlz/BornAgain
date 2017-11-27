// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/StandardTestService.h
//! @brief     Defines class StandardTestService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDARDTESTSERVICE_H
#define STANDARDTESTSERVICE_H

#include "WinDllMacros.h"
#include <string>
#include <memory>
class IFunctionalTest;
class Simulation;

//! @class StandardTestServiceBase
//! @ingroup standard_samples
//! @brief Main class to run standard functional test from standalone executable.

class BA_CORE_API_ StandardTestServiceBase
{
public:
    virtual ~StandardTestServiceBase() = default;
    bool execute(int argc, char** argv);

private:
    virtual IFunctionalTest* createTest(const std::string& name, const std::string& description,
                                        const Simulation& simulation,
                                        double threshold) = 0;
};


//! @class StandardTestService
//! @ingroup standard_samples
//! @brief Extends main class to run standard functional test from standalone executable.
//! Concrete test type is templated.

template<typename T>
class StandardTestService : public StandardTestServiceBase
{

private:
    virtual IFunctionalTest* createTest(const std::string& name, const std::string& description,
                                        const Simulation&  simulation,
                                        double threshold)
    {
        return createStandardTest(name, description, simulation, threshold);
    }

    T* createStandardTest(const std::string& name, const std::string& description,
                          const Simulation&  simulation, double threshold) {
        return new T(name, description, simulation, threshold);
    }
};

#endif // STANDARDTESTSERVICE_H
