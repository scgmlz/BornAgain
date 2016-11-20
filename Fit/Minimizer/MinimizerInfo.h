// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerInfo.h
//! @brief     Declares class MinimizerInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERINFO_H
#define MINIMIZERINFO_H

#include "WinDllMacros.h"
#include <string>
#include <vector>

//! A name and a description.
//! @ingroup fitting_internal

class BA_CORE_API_ InfoItem {
public:
    InfoItem(){}
    InfoItem(const std::string& itemName, const std::string& itemDescription)
        : m_itemName(itemName)
        , m_itemDescription(itemDescription) {}

    std::string name() const { return m_itemName; }
    std::string description() const { return m_itemDescription; }

private:
    std::string m_itemName;
    std::string m_itemDescription;
};


//! Info about a minimizer, including list of defined minimization algorithms.
//! @ingroup fitting_internal

class BA_CORE_API_ MinimizerInfo : public InfoItem {
public:
    using AlgorithmInfo = InfoItem;

    MinimizerInfo() {}
    MinimizerInfo(const std::string& minimizerType, const std::string& minimizerDescription);

    //! Sets currently active algorithm
    void setAlgorithmName(const std::string& algorithmName);
    std::string algorithmName() const;

    std::vector<std::string> algorithmNames() const;
    std::vector<std::string> algorithmDescriptions() const;

    static MinimizerInfo buildMinuit2Info(const std::string& defaultAlgo = std::string());
    static MinimizerInfo buildGSLMultiMinInfo(const std::string& defaultAlgo = std::string());
    static MinimizerInfo buildGSLLMAInfo();
    static MinimizerInfo buildGSLSimAnInfo();
    static MinimizerInfo buildGeneticInfo();
    static MinimizerInfo buildTestMinimizerInfo();

private:
    void addAlgorithm(const AlgorithmInfo& algorithm);
    void addAlgorithm(const std::string& algorithmName, const std::string& algorithmDescription);

    std::vector<AlgorithmInfo> m_algorithms;
    std::string m_current_algorithm;
};

#endif // MINIMIZERINFO_H
