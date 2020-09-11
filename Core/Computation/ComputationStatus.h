// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ComputationStatus.h
//! @brief     Defines and implements interface class ComputationStatus.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_COMPUTATIONSTATUS_H
#define BORNAGAIN_CORE_COMPUTATION_COMPUTATIONSTATUS_H

#include <string>

//! Completion status (flag and text) of a numeric computation.
//! @ingroup algorithms_internal

class ComputationStatus
{
public:
    ComputationStatus() : m_status(IDLE) {}

    bool isCompleted() const { return m_status == COMPLETED; }
    std::string errorMessage() const { return m_error_message; }

    void setRunning() { m_status = RUNNING; }
    void setCompleted() { m_status = COMPLETED; }
    void setFailed() { m_status = FAILED; }
    void setErrorMessage(const std::string& message) { m_error_message = message; }

private:
    enum ESimulationStatus { IDLE, RUNNING, COMPLETED, FAILED };

    ESimulationStatus m_status;
    std::string m_error_message;
};

#endif // BORNAGAIN_CORE_COMPUTATION_COMPUTATIONSTATUS_H
