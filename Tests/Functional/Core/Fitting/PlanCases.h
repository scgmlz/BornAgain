// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/PlanCases.h
//! @brief     Defines collection of PlanCases classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_PLANCASES_H
#define BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_PLANCASES_H

#include "Tests/Functional/Core/Fitting/Plan.h"

//! Two parameter fit: cylinders in BA with mini GISAS simulation.

class CylindersInBAPlan : public Plan
{
public:
    CylindersInBAPlan();
};

//! Two parameter fit: cylinders in BA with mini GISAS simulation.
//! Large tolerance on expected parameter values to help stocastic minimizers to converge fatser.

class CylindersInBAEasyPlan : public Plan
{
public:
    CylindersInBAEasyPlan();
};

//! Two parameter fit: cylinders in BA with mini GISAS simulation.
//! Residual like objective function is used

class CylindersInBAResidualPlan : public Plan
{
public:
    CylindersInBAResidualPlan();
};

//! Two parameter fit: cylinders in BA with mini GISAS simulation.
//! Rectangular detector.

class RectDetPlan : public Plan
{
public:
    RectDetPlan();
    ~RectDetPlan();

protected:
    std::unique_ptr<Simulation> createSimulation(const Fit::Parameters&) const;
};

//! Plan for fitting reflectometry curve on Ti/Ni multilayer

class SpecularPlan : public Plan
{
public:
    SpecularPlan();
};

//! Plan for fitting reflectometry curve on Ti/Ni multilayer (q-defined beam)

class SpecularPlanQ : public Plan
{
public:
    SpecularPlanQ();
};

//! The same as SpecularPlan, but with two (identical) datasets

class MultipleSpecPlan : public Plan
{
public:
    MultipleSpecPlan();
    ~MultipleSpecPlan() override;

protected:
    std::unique_ptr<FitObjective> createFitObjective() const override;
};

//! Fit for off-specular experiment

class OffSpecPlan : public Plan
{
public:
    OffSpecPlan();
    ~OffSpecPlan() override = default;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_PLANCASES_H
