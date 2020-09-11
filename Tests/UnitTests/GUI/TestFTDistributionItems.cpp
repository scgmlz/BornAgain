#include "Core/Correlations/FTDistributions1D.h"
#include "GUI/coregui/Models/FTDistributionItems.h"
#include "Tests/GTestWrapper/google_test.h"

class TestFTDistributionItems : public ::testing::Test
{
};

TEST_F(TestFTDistributionItems, test_FTDistribution1DCauchy)
{
    // to domain
    FTDistribution1DCauchyItem item;
    item.setItemValue(FTDistribution1DItem::P_OMEGA, 2.0);
    auto pdf = item.createFTDistribution();
    const FTDistribution1DCauchy* cauchy = dynamic_cast<FTDistribution1DCauchy*>(pdf.get());
    EXPECT_EQ(cauchy->omega(), 2.0);

    // from domain
    FTDistribution1DCauchy pdf2(3.0);
    FTDistribution1DCauchyItem item2;
    item2.setItemValue(FTDistribution1DGaussItem::P_OMEGA, pdf2.omega());
    EXPECT_EQ(item2.getItemValue(FTDistribution1DGaussItem::P_OMEGA), 3.0);
}
