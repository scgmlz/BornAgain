// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ComputationOutcome.h
//! @brief     Defines and implements interface class ComputationOutcome.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COMPUTATIONOUTCOME_H
#define COMPUTATIONOUTCOME_H

#include "WinDllMacros.h" // TODO can probably be removed here
#include <string>

//! Completion status (flag and text) of a numeric computation.
//! Pure virtual base class for our model evaluation routines.
//! Currently, the only child is Computations, which is the base for some more classes.
//! @ingroup algorithms_internal

class BA_CORE_API_ ComputationOutcome
{
public:
    ComputationOutcome() : m_status(IDLE) {}

    bool isCompleted() const { return m_status == COMPLETED; }
    std::string getRunMessage() const { return m_run_message; }

    void setRunning() { m_status = RUNNING; }
    void setCompleted() { m_status = COMPLETED; }
    void setFailed() { m_status = FAILED; }
    void setRunMessage(const std::string& message) { m_run_message = message; }

private:
    enum ESimulationStatus { IDLE, RUNNING, COMPLETED, FAILED };

    ESimulationStatus m_status;
    std::string m_run_message;
};

#endif // COMPUTATIONOUTCOME_H
