// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/FitObjective/FitObjectiveTestCases.h
//! @brief     Defines classes from FitObjectiveTest family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITOBJECTIVETESTCASES_H
#define FITOBJECTIVETESTCASES_H

//! Collection of FitObjective tests.

#include "FitObjectiveTest.h"

class MigradCylindersInBA : public FitObjectiveTest
{
public:
    MigradCylindersInBA();
};

class MigradResidualCylindersInBA : public FitObjectiveTest
{
public:
    MigradResidualCylindersInBA();
};

class BfgsCylindersInBA : public FitObjectiveTest
{
public:
    BfgsCylindersInBA();
};

class SteepestDescentCylindersInBA : public FitObjectiveTest
{
public:
    SteepestDescentCylindersInBA();
};

class FumuliCylindersInBA : public FitObjectiveTest
{
public:
    FumuliCylindersInBA();
};

class LevenbergMarquardtCylindersInBA : public FitObjectiveTest
{
public:
    LevenbergMarquardtCylindersInBA();
};

class SimAnCylindersInBA : public FitObjectiveTest
{
public:
    SimAnCylindersInBA();
};

class GeneticCylindersInBA : public FitObjectiveTest
{
public:
    GeneticCylindersInBA();
};

class RectDetectorFit : public FitObjectiveTest
{
public:
    RectDetectorFit();
};

class AdjustMinimizerFit : public FitObjectiveTest
{
public:
    AdjustMinimizerFit();
};

//--------------reflectometry-------------------

class SpecularFitTest : public FitObjectiveTest
{
public:
    SpecularFitTest();
};

class SpecularFitTestQ : public FitObjectiveTest
{
public:
    SpecularFitTestQ();
};

class MultipleSpecFittingTest : public FitObjectiveTest
{
public:
    MultipleSpecFittingTest();
};

//--------------off-spec-------------------

class OffSpecFitTest : public FitObjectiveTest
{
public:
    OffSpecFitTest();
};

#endif //   MINIMIZERTESTCASES_H
