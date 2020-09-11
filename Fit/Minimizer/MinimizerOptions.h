// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerOptions.h
//! @brief     Declares class MinimizerOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_MINIMIZER_MINIMIZEROPTIONS_H
#define BORNAGAIN_FIT_MINIMIZER_MINIMIZEROPTIONS_H

#include "Fit/Tools/OptionContainer.h"

//! Collection of internal minimizer settings.
//! @ingroup fitting_internal

class BA_CORE_API_ MinimizerOptions : public OptionContainer
{
public:
    //! Returns string with all options (i.e. "Strategy=1;Tolerance=0.01;")
    std::string toOptionString() const;

    //! Set options from their string representation
    void setOptionString(const std::string& options);

private:
    void processCommand(const std::string& command);
};

#endif // BORNAGAIN_FIT_MINIMIZER_MINIMIZEROPTIONS_H
