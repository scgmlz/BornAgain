#include "Device/Histo/Histogram1D.h"
#include "Tests/GTestWrapper/google_test.h"
#include <memory>

class Histogram1DTest : public ::testing::Test {};

TEST_F(Histogram1DTest, FixedBinConstructor) {
    Histogram1D hist(5, 0.0, 5.0);

    EXPECT_EQ(size_t(1), hist.rank());
    EXPECT_EQ(size_t(5), hist.getTotalNumberOfBins());
    EXPECT_EQ(0.0, hist.getXmin());
    EXPECT_EQ(5.0, hist.getXmax());
    EXPECT_THROW(hist.yAxis(), std::runtime_error);
    for (size_t index = 0; index < hist.getTotalNumberOfBins(); ++index) {
        EXPECT_EQ(index, hist.getGlobalBin(index));
        EXPECT_EQ(index, hist.xAxisIndex(index));
    }
}

TEST_F(Histogram1DTest, FixedBinDefaultContent) {
    Histogram1D hist(5, 0.0, 5.0);

    // bin centers
    std::vector<double> bin_centers = {0.5, 1.5, 2.5, 3.5, 4.5};
    std::vector<double> centers = hist.binCenters();
    for (size_t index = 0; index < bin_centers.size(); ++index) {
        EXPECT_EQ(centers[index], bin_centers[index]);
        EXPECT_EQ(hist.xAxisValue(index), bin_centers[index]);
        EXPECT_EQ(hist.xAxis().binCenter(index), bin_centers[index]);
    }

    // default bin values
    std::vector<double> values = hist.binValues();
    for (size_t index = 0; index < bin_centers.size(); ++index) {
        EXPECT_EQ(hist.binContent(index), 0.0);
        EXPECT_EQ(values[index], 0.0);
    }

    // default bin errors
    std::vector<double> errors = hist.binErrors();
    for (size_t index = 0; index < bin_centers.size(); ++index) {
        EXPECT_EQ(hist.binError(index), 0.0);
        EXPECT_EQ(errors[index], 0.0);
    }

    // default bin entries
    for (size_t index = 0; index < bin_centers.size(); ++index) {
        EXPECT_EQ(hist.binNumberOfEntries(index), 0);
    }
}

TEST_F(Histogram1DTest, FixedBinFill) {
    Histogram1D hist(5, 0.0, 5.0);

    // filling two different bins

    hist.fill(0.5, 88.0);
    hist.fill(4.5, 99.0);
    EXPECT_EQ(hist.binContent(0), 88.0);
    EXPECT_EQ(hist.binNumberOfEntries(0), 1);
    EXPECT_EQ(hist.binError(0), 0.0);

    EXPECT_EQ(hist.binContent(4), 99.0);
    EXPECT_EQ(hist.binNumberOfEntries(4), 1);
    EXPECT_EQ(hist.binError(4), 0.0);

    std::vector<double> values = {88.0, 0.0, 0.0, 0.0, 99.0};
    for (size_t index = 0; index < hist.getTotalNumberOfBins(); ++index) {
        EXPECT_EQ(hist.binValues()[index], values[index]);
        EXPECT_EQ(hist.binErrors()[index], 0.0);
    }

    // resetting histograms
    hist.reset();
    EXPECT_EQ(hist.binContent(0), 0.0);
    EXPECT_EQ(hist.binNumberOfEntries(0), 0);
    EXPECT_EQ(hist.binError(0), 0.0);
    EXPECT_EQ(hist.binContent(4), 0.0);
    EXPECT_EQ(hist.binNumberOfEntries(4), 0);
    EXPECT_EQ(hist.binError(4), 0.0);

    // another fill
    const double xvalue(1.5);
    const int xbin = 1;

    hist.fill(xvalue, 1.0);
    hist.fill(xvalue, 3.0);
    EXPECT_EQ(2, hist.binNumberOfEntries(xbin));
    EXPECT_EQ(4.0, hist.binContent(xbin));
    EXPECT_EQ(2.0, hist.binAverage(xbin));
    EXPECT_EQ(1.0, hist.binError(xbin));

    // another fill
    hist.reset();
    hist.fill(xvalue, 1.0);
    hist.fill(xvalue, 2.0);
    hist.fill(xvalue, 3.0);
    EXPECT_EQ(3, hist.binNumberOfEntries(xbin));
    EXPECT_EQ(6.0, hist.binContent(xbin));
    EXPECT_EQ(2.0, hist.binAverage(xbin));
    EXPECT_EQ(2.0 / 3.0, hist.binError(xbin) * hist.binError(xbin));
}

//     -1.0  -0.5        0.5   1.0        2.0  X

TEST_F(Histogram1DTest, crop) {
    std::vector<double> xedges = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> xvalues = {-0.75, 0.0, 0.75, 1.5};
    Histogram1D hist(4, xedges);

    for (size_t i = 0; i < xvalues.size(); ++i) {
        hist.fill(xvalues[i], i * 10.0);
    }

    std::unique_ptr<Histogram1D> crop(hist.crop(-0.49, 0.99));

    EXPECT_EQ(-0.5, crop->getXmin());
    EXPECT_EQ(1.0, crop->getXmax());

    EXPECT_EQ(10.0, crop->binContent(0));
    EXPECT_EQ(20.0, crop->binContent(1));
}

TEST_F(Histogram1DTest, CreateHistogram) {
    OutputData<double> data;
    data.addAxis("x-axis", 10, 0.0, 10.0);
    for (size_t i = 0; i < data.getAllocatedSize(); ++i) {
        data[i] = double(i);
    }

    std::unique_ptr<IHistogram> hist(IHistogram::createHistogram(data));
    EXPECT_EQ(size_t(1), hist->rank());
    EXPECT_EQ(data.getAllocatedSize(), hist->getNbinsX());
    EXPECT_EQ(data.axis(0).lowerBound(), hist->getXmin());
    EXPECT_EQ(data.axis(0).upperBound(), hist->getXmax());
    for (size_t i = 0; i < hist->getTotalNumberOfBins(); ++i) {
        EXPECT_EQ(data[i], hist->binContent(i));
        EXPECT_EQ(data[i], hist->binAverage(i));
        EXPECT_EQ(1, hist->binNumberOfEntries(i));
        EXPECT_EQ(0.0, hist->binError(i));
    }
}

TEST_F(Histogram1DTest, CreateOutputData) {
    Histogram1D hist(10, -5.0, 5.0);

    for (size_t i = 0; i < hist.getNbinsX(); ++i) {
        hist.fill(hist.xAxisValue(i), 1.0);
        hist.fill(hist.xAxisValue(i), 3.0);
    }

    std::unique_ptr<OutputData<double>> data(hist.createOutputData(IHistogram::DataType::INTEGRAL));
    EXPECT_EQ(size_t(1), data->rank());
    EXPECT_EQ(data->getAllocatedSize(), hist.getNbinsX());
    EXPECT_EQ(data->axis(0).lowerBound(), hist.getXmin());
    EXPECT_EQ(data->axis(0).upperBound(), hist.getXmax());
    for (size_t i = 0; i < data->getAllocatedSize(); ++i) {
        EXPECT_EQ(4.0, (*data)[i]);
    }

    data.reset(hist.createOutputData(IHistogram::DataType::AVERAGE));
    for (size_t i = 0; i < data->getAllocatedSize(); ++i) {
        EXPECT_EQ(2.0, (*data)[i]);
    }

    data.reset(hist.createOutputData(IHistogram::DataType::STANDARD_ERROR));
    for (size_t i = 0; i < data->getAllocatedSize(); ++i) {
        EXPECT_EQ(1.0, (*data)[i]);
    }

    data.reset(hist.createOutputData(IHistogram::DataType::NENTRIES));
    for (size_t i = 0; i < data->getAllocatedSize(); ++i) {
        EXPECT_EQ(2.0, (*data)[i]);
    }
}

TEST_F(Histogram1DTest, GetMaximumGetMinimum) {
    Histogram1D hist(10, -5.0, 5.0);
    hist.fill(-4.5, 10.);
    EXPECT_EQ(10.0, hist.getMaximum());
    EXPECT_EQ(size_t(0), hist.getMaximumBinIndex());
    EXPECT_EQ(0.0, hist.getMinimum());
    EXPECT_EQ(size_t(1), hist.getMinimumBinIndex());

    hist.fill(-3.5, 20.0);
    EXPECT_EQ(20.0, hist.getMaximum());
    EXPECT_EQ(size_t(1), hist.getMaximumBinIndex());
}

TEST_F(Histogram1DTest, Scale) {
    Histogram1D hist(10, -5.0, 5.0);

    for (size_t i = 0; i < hist.getTotalNumberOfBins(); ++i) {
        hist.fill(-4.5 + i, 1.0);
    }
    hist.scale(10.0);
    for (size_t i = 0; i < hist.getTotalNumberOfBins(); ++i) {
        EXPECT_EQ(10.0, hist.binContent(i));
    }
}

TEST_F(Histogram1DTest, Integral) {
    Histogram1D hist(10, -5.0, 5.0);

    for (size_t i = 0; i < hist.getTotalNumberOfBins(); ++i) {
        hist.fill(-4.5 + i, 1.0);
    }
    EXPECT_EQ(10.0, hist.integral());
}

TEST_F(Histogram1DTest, Addition) {
    Histogram1D hist1(10, -5.0, 5.0);
    for (size_t i = 0; i < hist1.getTotalNumberOfBins(); ++i) {
        hist1.fill(-4.5 + i, 1.0);
    }

    Histogram1D hist2(10, -5.0, 5.0);
    for (size_t i = 0; i < hist2.getTotalNumberOfBins(); ++i) {
        hist2.fill(-4.5 + i, 2.0);
    }

    hist1 += hist2;
    for (size_t i = 0; i < hist1.getTotalNumberOfBins(); ++i) {
        EXPECT_EQ(3.0, hist1.binContent(i));
    }
}
