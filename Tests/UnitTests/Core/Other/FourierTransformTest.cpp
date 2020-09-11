#include "Core/Instrument/FourierTransform.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Intensity/OutputData.h"
#include "Tests/GTestWrapper/google_test.h"

class FourierTransformTest : public ::testing::Test
{
};

// Testing implementation of 1D FT with with low freuency centering
TEST_F(FourierTransformTest, fft1DTest)
{
    std::vector<double> signal_odd({0, 0, 1, 0, 0, 1, 1});     // odd # input size
    std::vector<double> signal_even({0, 0, 1, 0, 0, 1, 1, 2}); // even # input size
    std::vector<double> result_odd, result_even;

    FourierTransform ft_odd;
    ft_odd.fft(signal_odd, result_odd);
    ft_odd.fftshift(result_odd);
    std::vector<double> expected_result_odd(
        {0.55495813, 2.2469796, 0.80193774, 3., 0.80193774, 2.2469796, 0.55495813});

    for (size_t i = 0; i < signal_odd.size(); ++i)
        EXPECT_NEAR(result_odd[i], expected_result_odd[i], 1e-6);

    FourierTransform ft_even;
    ft_even.fft(signal_even, result_even);
    ft_even.fftshift(result_even);
    std::vector<double> expected_result_even(
        {1., 2.23606798, 2.23606798, 2.23606798, 5., 2.23606798, 2.23606798, 2.23606798});

    for (size_t i = 0; i < signal_even.size(); ++i)
        EXPECT_NEAR(result_even[i], expected_result_even[i], 1e-6);
}

// Testing implementation of 2D FT with low freuency centering for the following:

// 3x5 input of all zeros
TEST_F(FourierTransformTest, fft2DTest1)
{
    std::vector<std::vector<double>> signal({{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}});
    std::vector<std::vector<double>> result;
    std::vector<std::vector<double>> expected_result(
        {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}});

    FourierTransform ft;
    ft.fft(signal, result);
    ft.fftshift(result);

    for (size_t i = 0; i < signal.size(); ++i)
        for (size_t j = 0; j < signal[0].size(); ++j)
            EXPECT_NEAR(result[i][j], expected_result[i][j], 1e-6);
}

// 4x5 input of all zeros except for 1 element
TEST_F(FourierTransformTest, fft2DTest2)
{
    std::vector<std::vector<double>> signal(
        {{0, 0, 0, 0, 0}, {0, 0, 2, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}});
    std::vector<std::vector<double>> result;
    std::vector<std::vector<double>> expected_result(
        {{2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}});

    FourierTransform ft;
    ft.fft(signal, result);
    ft.fftshift(result);

    for (size_t i = 0; i < signal.size(); ++i)
        for (size_t j = 0; j < signal[0].size(); ++j)
            EXPECT_NEAR(result[i][j], expected_result[i][j], 1e-6);
}

// 6x6 input of all ones except for 1 element
TEST_F(FourierTransformTest, fft2DTest3)
{
    std::vector<std::vector<double>> signal({{1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 32},
                                             {1, 1, 1, 1, 1, 1}});
    std::vector<std::vector<double>> result;
    std::vector<std::vector<double>> expected_result({{31, 31, 31, 31, 31, 31},
                                                      {31, 31, 31, 31, 31, 31},
                                                      {31, 31, 31, 31, 31, 31},
                                                      {31, 31, 31, 67, 31, 31},
                                                      {31, 31, 31, 31, 31, 31},
                                                      {31, 31, 31, 31, 31, 31}});

    FourierTransform ft;
    ft.fft(signal, result);
    ft.fftshift(result);

    for (size_t i = 0; i < signal.size(); ++i)
        for (size_t j = 0; j < signal[0].size(); ++j)
            EXPECT_NEAR(result[i][j], expected_result[i][j], 1e-6);
}

// 3x5 input with 1 row of all zeros
TEST_F(FourierTransformTest, fft2DTest4)
{
    std::vector<std::vector<double>> signal({{1, 88, 0, 1, 0}, {0, 1, 1, 1, 0}, {0, 0, 0, 0, 0}});
    std::vector<std::vector<double>> result;
    std::vector<std::vector<double>> expected_result(
        {{87.56947917, 85.92017286, 88.53812738, 88.59651195, 86.95382846},
         {88.02055461, 88.00785173, 93., 88.00785173, 88.02055461},
         {86.95382846, 88.59651195, 88.53812738, 85.92017286, 87.56947917}});

    FourierTransform ft;
    ft.fft(signal, result);
    ft.fftshift(result);

    for (size_t i = 0; i < signal.size(); ++i)
        for (size_t j = 0; j < signal[0].size(); ++j)
            EXPECT_NEAR(result[i][j], expected_result[i][j], 1e-6);
}

// 4x4 input
TEST_F(FourierTransformTest, fft2DTest5)
{
    std::vector<std::vector<double>> signal(
        {{1, 0, 0, 5}, {1, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 1, 1}});
    std::vector<std::vector<double>> result;
    std::vector<std::vector<double>> expected_result(
        {{5., 5., 5., 5.},
         {3.60555128, 3.60555128, 3.60555128, 7.28010989},
         {5., 5., 13., 5.},
         {3.60555128, 7.28010989, 3.60555128, 3.60555128}});

    FourierTransform ft;
    ft.fft(signal, result);
    ft.fftshift(result);

    for (size_t i = 0; i < signal.size(); ++i)
        for (size_t j = 0; j < signal[0].size(); ++j)
            EXPECT_NEAR(result[i][j], expected_result[i][j], 1e-6);
}

// 7x7 input
TEST_F(FourierTransformTest, fft2DTest6)
{
    std::vector<std::vector<double>> signal{
        {1., 0., 0., 0., 0., 0., 0.}, {1., 0., 0., 0., 0., 0., 0.}, {1., 0., 5., 0., 0., 0., 0.},
        {1., 0., 0., 0., 0., 0., 0.}, {1., 0., 0., 0., 0., 5., 0.}, {1., 0., 0., 0., 0., 0., 0.},
        {1., 0., 0., 0., 0., 0., 0.}};

    std::vector<std::vector<double>> result;

    std::vector<std::vector<double>> expected_result(
        {{9.00968868, 6.23489802, 6.23489802, 9.00968868, 2.22520934, 10., 2.22520934},
         {9.00968868, 2.22520934, 10., 2.22520934, 9.00968868, 6.23489802, 6.23489802},
         {2.22520934, 9.00968868, 6.23489802, 6.23489802, 9.00968868, 2.22520934, 10.},
         {13.23489802, 2.00968868, 4.77479066, 17., 4.77479066, 2.00968868, 13.23489802},
         {10., 2.22520934, 9.00968868, 6.23489802, 6.23489802, 9.00968868, 2.22520934},
         {6.23489802, 6.23489802, 9.00968868, 2.22520934, 10., 2.22520934, 9.00968868},
         {2.22520934, 10., 2.22520934, 9.00968868, 6.23489802, 6.23489802, 9.00968868}});

    FourierTransform ft;
    ft.fft(signal, result);
    ft.fftshift(result);

    for (size_t i = 0; i < signal.size(); ++i)
        for (size_t j = 0; j < signal[0].size(); ++j)
            EXPECT_NEAR(result[i][j], expected_result[i][j], 1e-6);
}
