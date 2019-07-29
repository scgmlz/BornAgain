// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/MinimizerTestCases.h
//! @brief     Defines classes from MinimizerTest family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MINIMIZERTESTCASES_H
#define MINIMIZERTESTCASES_H

//! Collection of minimizer tests.

#include "MinimizerTest.h"

class MinuitTestV1 : public MinimizerTest
{
public:
    MinuitTestV1();
};

class MinuitTestV2 : public MinimizerTest
{
public:
    MinuitTestV2();
};

class MinuitTestV3 : public MinimizerTest
{
public:
    MinuitTestV3();
};

class SteepestDescentTestV1 : public MinimizerTest
{
public:
    SteepestDescentTestV1();
};

class SteepestDescentTestV2 : public MinimizerTest
{
public:
    SteepestDescentTestV2();
};

class ConjugateFRTestV1 : public MinimizerTest
{
public:
    ConjugateFRTestV1();
};

class ConjugateFRTestV2 : public MinimizerTest
{
public:
    ConjugateFRTestV2();
};

class ConjugatePRTestV1 : public MinimizerTest
{
public:
    ConjugatePRTestV1();
};

class ConjugatePRTestV2 : public MinimizerTest
{
public:
    ConjugatePRTestV2();
};

class BfgsTestV1 : public MinimizerTest
{
public:
    BfgsTestV1();
};

class BfgsTestV2 : public MinimizerTest
{
public:
    BfgsTestV2();
};

class Bfgs2TestV1 : public MinimizerTest
{
public:
    Bfgs2TestV1();
};

class Bfgs2TestV2 : public MinimizerTest
{
public:
    Bfgs2TestV2();
};

class GSLSimAnTestV1 : public MinimizerTest
{
public:
    GSLSimAnTestV1();
};

class GSLSimAnTestV2 : public MinimizerTest
{
public:
    GSLSimAnTestV2();
};

class GeneticTestV1 : public MinimizerTest
{
public:
    GeneticTestV1();
};

class GeneticTestV2 : public MinimizerTest
{
public:
    GeneticTestV2();
};

class FumiliTestV3 : public MinimizerTest
{
public:
    FumiliTestV3();
};

class LevenbergMarquardtV3 : public MinimizerTest
{
public:
    LevenbergMarquardtV3();
};

class TestMinimizerV1 : public MinimizerTest
{
public:
    TestMinimizerV1();
};

#endif //   MINIMIZERTESTCASES_H
