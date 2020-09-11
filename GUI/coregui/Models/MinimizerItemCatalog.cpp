// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MinimizerItemCatalog.cpp
//! @brief     Implements MinimizerItemCatalog class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/MinimizerItemCatalog.h"
#include "Fit/Minimizer/MinimizerFactory.h"
#include "GUI/coregui/utils/GUIHelpers.h"

//! Returns ComboProperty representing list of algorithms defined for given minimizerType.

ComboProperty MinimizerItemCatalog::algorithmCombo(const QString& minimizerType)
{
    ComboProperty result = ComboProperty() << algorithmNames(minimizerType);
    result.setToolTips(algorithmDescriptions(minimizerType));
    return result;
}

//! Returns list of algorithm names defined for given minimizer.

QStringList MinimizerItemCatalog::algorithmNames(const QString& minimizerType)
{
    std::vector<std::string> algos =
        MinimizerFactory::catalog().algorithmNames(minimizerType.toStdString());
    return GUIHelpers::fromStdStrings(algos);
}

//! Returns list of algoritm descriptions defined for given minimizer.

QStringList MinimizerItemCatalog::algorithmDescriptions(const QString& minimizerType)
{
    std::vector<std::string> descr =
        MinimizerFactory::catalog().algorithmDescriptions(minimizerType.toStdString());
    return GUIHelpers::fromStdStrings(descr);
}
