#include "Core/Instrument/SpectrumUtils.h"
#include "Core/Intensity/Histogram2D.h"
#include "Tests/GTestWrapper/google_test.h"
#include "tspectrum.h"
#include <iostream>

class SpectrumTest : public ::testing::Test
{
};

TEST_F(SpectrumTest, arrayPeaks)
{
    std::vector<std::vector<double>> data = {{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                                             {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                                             {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                                             {1.0, 1.0, 1.0, 1.0, 10.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                                             {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                                             {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}};

    tspectrum::Spectrum2D finder;
    auto peaks = finder.find_peaks(data, 3, "nomarkov", 0.1);
    EXPECT_EQ(peaks.size(), 1u);
    EXPECT_NEAR(peaks[0].first, 3.0, 0.01);  // rows
    EXPECT_NEAR(peaks[0].second, 4.0, 0.01); // cols
}

TEST_F(SpectrumTest, histogramPeaks)
{
    std::vector<std::vector<double>> data = {{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                                             {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                                             {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                                             {1.0, 1.0, 1.0, 1.0, 10.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                                             {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                                             {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}};

    Histogram2D hist(10, 10.0, 110.0, 6, 0.0, 60.0);
    hist.setContent(data);

    EXPECT_EQ(hist.getBinContent(4, 2), 10.0);

    auto peaks = SpectrumUtils::FindPeaks(hist, 3, "nomarkov", 0.1);
    EXPECT_NEAR(peaks[0].first, 55.0, 0.01);  // center of histogram x-axis bin with index=4
    EXPECT_NEAR(peaks[0].second, 25.0, 0.01); // center of histogram y-axis bin with index=2
}
