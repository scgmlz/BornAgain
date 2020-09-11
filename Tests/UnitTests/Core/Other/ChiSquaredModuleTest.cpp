#include "Core/Instrument/ChiSquaredModule.h"
#include "Core/Instrument/VarianceFunctions.h"
#include "Core/Intensity/OutputData.h"
#include "Tests/GTestWrapper/google_test.h"

// TODO revise test

class ChiSquaredModuleTest : public ::testing::Test
{
protected:
    ChiSquaredModule m_chi_empty;
    ChiSquaredModule m_chi_default;
    OutputData<double> m_real_data;
    OutputData<double> m_simul_data;
};

TEST_F(ChiSquaredModuleTest, InitialState)
{
    EXPECT_TRUE(dynamic_cast<const VarianceSimFunction*>(m_chi_empty.varianceFunction()));
    EXPECT_EQ(nullptr, m_chi_empty.getIntensityFunction());
}

TEST_F(ChiSquaredModuleTest, CloneOfEmpty)
{
    ChiSquaredModule* clone_of_empty = m_chi_empty.clone();
    EXPECT_TRUE(dynamic_cast<const VarianceSimFunction*>(clone_of_empty->varianceFunction()));
    EXPECT_EQ(nullptr, clone_of_empty->getIntensityFunction());
    delete clone_of_empty;
}
