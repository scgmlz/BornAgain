// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/FitObjective/FitPlanCases.h
//! @brief     Defines collection of FitPlanCases classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITPLANCASES_H
#define FITPLANCASES_H

#include "FitPlan.h"

//! Two parameter fit: cylinders in BA with mini GISAS simulation.

class CylindersInBAPlan : public FitPlan
{
public:
    CylindersInBAPlan();
};

//! Two parameter fit: cylinders in BA with mini GISAS simulation.
//! Large tolerance on expected parameter values to help stocastic minimizers to converge fatser.

class CylindersInBAEasyPlan : public FitPlan
{
public:
    CylindersInBAEasyPlan();
};

//! Two parameter fit: cylinders in BA with mini GISAS simulation.
//! Residual like objective function is used

class CylindersInBAResidualPlan : public FitPlan
{
public:
    CylindersInBAResidualPlan();
};

//! Two parameter fit: cylinders in BA with mini GISAS simulation.
//! Rectangular detector.

class RectDetPlan : public FitPlan
{
public:
    RectDetPlan();
    ~RectDetPlan();

protected:
    std::unique_ptr<Simulation> createSimulation(const Fit::Parameters&) const;
};

//! Plan for fitting reflectometry curve on Ti/Ni multilayer

class SpecularPlan : public FitPlan
{
public:
    SpecularPlan();
    ~SpecularPlan() override;
};

//! Plan for fitting reflectometry curve on Ti/Ni multilayer (q-defined beam)

class SpecularPlanQ : public FitPlan
{
public:
    SpecularPlanQ();
    ~SpecularPlanQ() override;
};

//! The same as SpecularPlan, but with two (identical) datasets

class MultipleSpecPlan : public FitPlan
{
public:
    MultipleSpecPlan();
    ~MultipleSpecPlan() override;

protected:
    std::unique_ptr<FitObjective> createFitObjective() const override;
};

//! Fit for off-specular experiment

class OffSpecFitPlan : public FitPlan
{
public:
    OffSpecFitPlan();
    ~OffSpecFitPlan() override = default;
};

#endif //  FITPLANCASES_H
