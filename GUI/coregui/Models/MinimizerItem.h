// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MinimizerItem.h
//! @brief     Defines MinimizerItem class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_MINIMIZERITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_MINIMIZERITEM_H

#include "GUI/coregui/Models/SessionItem.h"

class IMinimizer;
class ObjectiveMetric;

//! The MinimizerItem class is the base item to hold minimizer settings.

class BA_CORE_API_ MinimizerItem : public SessionItem
{
public:
    explicit MinimizerItem(const QString& model_type);
    virtual std::unique_ptr<IMinimizer> createMinimizer() const = 0;
};

//! The MinimizerContainerItem class holds collection of minimizers.

class BA_CORE_API_ MinimizerContainerItem : public MinimizerItem
{
public:
    static const QString P_MINIMIZERS;
    static const QString P_METRIC;
    static const QString P_NORM;

    MinimizerContainerItem();

    std::unique_ptr<IMinimizer> createMinimizer() const;
    std::unique_ptr<ObjectiveMetric> createMetric() const;
};

//! The MinuitMinimizerItem class represents settings for ROOT Minuit2 minimizer.

class BA_CORE_API_ MinuitMinimizerItem : public MinimizerItem
{
public:
    static const QString P_ALGORITHMS;
    static const QString P_STRATEGY;
    static const QString P_ERRORDEF;
    static const QString P_TOLERANCE;
    static const QString P_PRECISION;
    static const QString P_MAXFUNCTIONCALLS;

    MinuitMinimizerItem();
    std::unique_ptr<IMinimizer> createMinimizer() const;
};

//! The GSLMinimizerItem class represents settings for GSL MultiMin minimizer family.

class BA_CORE_API_ GSLMultiMinimizerItem : public MinimizerItem
{
public:
    static const QString P_ALGORITHMS;
    static const QString P_MAXITERATIONS;

    GSLMultiMinimizerItem();
    std::unique_ptr<IMinimizer> createMinimizer() const;
};

//! The GeneticMinimizerItem class represents settings for TMVA/Genetic minimizer.

class BA_CORE_API_ GeneticMinimizerItem : public MinimizerItem
{
public:
    static const QString P_TOLERANCE;
    static const QString P_MAXITERATIONS;
    static const QString P_POPULATIONSIZE;
    static const QString P_RANDOMSEED;

    GeneticMinimizerItem();
    std::unique_ptr<IMinimizer> createMinimizer() const;
};

//! The SimAnMinimizerItem class represents settings for GSL's simulated annealing minimizer.

class BA_CORE_API_ SimAnMinimizerItem : public MinimizerItem
{
public:
    static const QString P_MAXITERATIONS;
    static const QString P_ITERATIONSTEMP;
    static const QString P_STEPSIZE;
    static const QString P_BOLTZMANN_K;
    static const QString P_BOLTZMANN_TINIT;
    static const QString P_BOLTZMANN_MU;
    static const QString P_BOLTZMANN_TMIN;

    SimAnMinimizerItem();

    std::unique_ptr<IMinimizer> createMinimizer() const;
};

//! The GSLLMAMinimizerItem class represents settings for GSL's version of Levenberg-Marquardt.

class BA_CORE_API_ GSLLMAMinimizerItem : public MinimizerItem
{
public:
    static const QString P_TOLERANCE;
    static const QString P_MAXITERATIONS;

    GSLLMAMinimizerItem();
    std::unique_ptr<IMinimizer> createMinimizer() const;
};

//! The TestMinimizerItem class represents domain's TestMinimizer to test whole chain

class BA_CORE_API_ TestMinimizerItem : public MinimizerItem
{
public:
    TestMinimizerItem();
    std::unique_ptr<IMinimizer> createMinimizer() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_MINIMIZERITEM_H
