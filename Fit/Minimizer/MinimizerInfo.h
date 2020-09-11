// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerInfo.h
//! @brief     Declares class MinimizerInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_MINIMIZER_MINIMIZERINFO_H
#define BORNAGAIN_FIT_MINIMIZER_MINIMIZERINFO_H

#include "Wrap/WinDllMacros.h"
#include <string>
#include <vector>

//! A name and a description.
//! @ingroup fitting_internal

class BA_CORE_API_ AlgorithmInfo
{
public:
    AlgorithmInfo() = delete;
    AlgorithmInfo(const std::string& itemName, const std::string& itemDescription)
        : m_itemName(itemName), m_itemDescription(itemDescription)
    {
    }

    std::string name() const { return m_itemName; }
    std::string description() const { return m_itemDescription; }

private:
    std::string m_itemName;
    std::string m_itemDescription;
};

//! Info about a minimizer, including list of defined minimization algorithms.
//! @ingroup fitting_internal

class BA_CORE_API_ MinimizerInfo
{
public:
    MinimizerInfo() = delete;
    MinimizerInfo(const std::string& minimizerType, const std::string& minimizerDescription)
        : m_name(minimizerType), m_description(minimizerDescription)
    {
    }

    //! Sets currently active algorithm
    void setAlgorithmName(const std::string& algorithmName);

    std::string name() const { return m_name; }
    std::string description() const { return m_description; }

    std::string algorithmName() const { return m_current_algorithm; }

    std::vector<std::string> algorithmNames() const;
    std::vector<std::string> algorithmDescriptions() const;

    static MinimizerInfo buildMinuit2Info(const std::string& defaultAlgo = "");
    static MinimizerInfo buildGSLMultiMinInfo(const std::string& defaultAlgo = "");
    static MinimizerInfo buildGSLLMAInfo();
    static MinimizerInfo buildGSLSimAnInfo();
    static MinimizerInfo buildGeneticInfo();
    static MinimizerInfo buildTestMinimizerInfo();

private:
    void addAlgorithm(const AlgorithmInfo& algorithm);
    void addAlgorithm(const std::string& algorithmName, const std::string& algorithmDescription);

    std::string m_name;
    std::string m_description;
    std::vector<AlgorithmInfo> m_algorithms;
    std::string m_current_algorithm;
};

#endif // BORNAGAIN_FIT_MINIMIZER_MINIMIZERINFO_H
