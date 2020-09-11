// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/FourierTransform.cpp
//! @brief     Implements class FourierTransform.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Core/Instrument/FourierTransform.h"
#include "Core/Basics/Exceptions.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdexcept>

FourierTransform::FourierTransform() = default;

FourierTransform::Workspace::Workspace()
    : h_src(0), w_src(0), h_fftw(0), w_fftw(0), in_src(0), out_fftw(0), p_forw_src(nullptr)
{
}

FourierTransform::Workspace::~Workspace()
{
    clear();
}

void FourierTransform::Workspace::clear()
{
    // rows (h) and columns (w) of the input 'source'
    h_src = 0;
    w_src = 0;

    if (in_src)
        delete[] in_src;
    in_src = 0;

    if (out_fftw)
        fftw_free((fftw_complex*)out_fftw);
    out_fftw = 0;

    if (p_forw_src != nullptr)
        fftw_destroy_plan(p_forw_src);

    fftw_cleanup();
}

/* ************************************************************************* */
// Fourier Transform in 2D
/* ************************************************************************* */
void FourierTransform::fft(const double2d_t& source, double2d_t& result)
{
    // rows (h) and columns (w) of the input 'source'
    int h_src = static_cast<int>(source.size());
    int w_src = static_cast<int>((source.size() ? source[0].size() : 0));

    // initialisation
    init(h_src, w_src);

    // Compute the forward FT
    fftw_forward_FT(source);

    double* ptr = ws.out_fftw;
    result.clear();

    // Resize the array for holding the FT output to correct dimensions
    result.resize(static_cast<size_t>(ws.h_fftw),
                  std::vector<double>(static_cast<size_t>(ws.w_fftw)));

    // Storing FT output
    for (size_t i = 0; i < static_cast<size_t>(ws.h_fftw); i++) {
        size_t k = static_cast<size_t>(ws.h_fftw) - i;
        if (i == 0)
            k -= static_cast<size_t>(ws.h_fftw);
        for (size_t j = 0; j < static_cast<size_t>(ws.w_fftw / 2 + 1); j++) {
            result[i][j] = *ptr;
            size_t l = static_cast<size_t>(ws.w_fftw) - j;
            if (j != 0)
                result[k][l] = result[i][j];
            ptr += 2; // Only interested in the magnitudes of the complex Fourier coefficients
        }
    }
}

/* ************************************************************************* */
// Fourier Transform 2D shift - center array around zero frequency
/* ************************************************************************* */
void FourierTransform::fftshift(double2d_t& result)
{
    // Centering FT around zero frequency
    size_t row_shift;
    if (result.size() % 2 == 0)
        row_shift = result.size() / 2;
    else
        row_shift = result.size() / 2 + 1;

    size_t col_shift;
    if (result[0].size() % 2 == 0)
        col_shift = result[0].size() / 2;
    else
        col_shift = result[0].size() / 2 + 1;

    // First, shifting the rows
    std::rotate(result.begin(), result.begin() + static_cast<int>(row_shift), result.end());

    // Second, shifting the cols
    for (size_t i = 0; i < static_cast<size_t>(ws.h_fftw); i++) {
        std::rotate(result[i].begin(), result[i].begin() + static_cast<int>(col_shift),
                    result[i].end());
    }
}

/* ************************************************************************* */
// Fourier Transform in 1D
/* ************************************************************************* */
void FourierTransform::fft(const double1d_t& source, double1d_t& result)
{
    // we simply create 2d arrays with length of first dimension equal to 1, and call 2d FT
    double2d_t source2d;
    source2d.push_back(source);

    double2d_t result2d;
    fft(source2d, result2d);

    if (result2d.size() != 1)
        throw Exceptions::RuntimeErrorException("FourierTransform::fft -> Panic in 1d");

    result = result2d[0];
}

/* ************************************************************************* */
// Fourier Transform 1D shift - center around zero frequency
/* ************************************************************************* */
void FourierTransform::fftshift(double1d_t& result)
{
    // Centering FT around zero frequency
    size_t col_shift;
    if (result.size() % 2 == 0)
        col_shift = result.size() / 2;
    else
        col_shift = result.size() / 2 + 1;

    std::rotate(result.begin(), result.begin() + static_cast<int>(col_shift), result.end());
}

/* ************************************************************************************ */
// initialise input and output arrays in workspace for fast Fourier transformation (fftw)
/* ************************************************************************************ */
void FourierTransform::init(int h_src, int w_src)
{
    if (!h_src || !w_src) {
        std::ostringstream os;
        os << "FourierTransform::init() -> Panic! Wrong dimensions " << h_src << " " << w_src
           << std::endl;
        throw Exceptions::RuntimeErrorException(os.str());
    }

    ws.clear();
    ws.h_src = h_src;
    ws.w_src = w_src;

    ws.h_fftw = h_src;
    ws.w_fftw = w_src;

    ws.in_src = new double[static_cast<size_t>(ws.h_fftw * ws.w_fftw)];
    ws.out_fftw = static_cast<double*>(
        fftw_malloc(sizeof(fftw_complex) * static_cast<size_t>(ws.h_fftw * (ws.w_fftw / 2 + 1))));

    // Initialization of the plans
    ws.p_forw_src = fftw_plan_dft_r2c_2d(ws.h_fftw, ws.w_fftw, ws.in_src,
                                         (fftw_complex*)ws.out_fftw, FFTW_ESTIMATE);
    // ws.p_forw_src = fftw_plan_dft_r2c_2d(ws.h_fftw, ws.w_fftw, ws.in_src,
    //                                     static_cast<double*>(ws.out_src), FFTW_ESTIMATE);

    if (ws.p_forw_src == nullptr)
        throw Exceptions::RuntimeErrorException(
            "FourierTransform::init() -> Error! Can't initialise p_forw_src plan.");
}

/* ************************************************************************* */
// initialise input and output arrays for fast Fourier transformation
/* ************************************************************************* */

void FourierTransform::fftw_forward_FT(const double2d_t& src)
{
    if (ws.h_fftw <= 0 || ws.w_fftw <= 0)
        throw Exceptions::RuntimeErrorException(
            "FourierTransform::fftw_forward_FT() -> Panic! Initialisation is missed.");

    double *ptr, *ptr_end;

    // Initializing the content of ws.in_src to zero for all elements
    for (ptr = ws.in_src, ptr_end = ws.in_src + ws.h_fftw * ws.w_fftw; ptr != ptr_end; ++ptr)
        *ptr = 0.0;

    // Building the input signal for fftw algorithm
    for (size_t row = 0; row < static_cast<size_t>(ws.h_src); ++row)
        for (size_t col = 0; col < static_cast<size_t>(ws.w_src); ++col)
            ws.in_src[(static_cast<int>(row) % ws.h_fftw) * ws.w_fftw
                      + (static_cast<int>(col) % ws.w_fftw)] += src[row][col];

    // Computing the FFT with fftw plan
    fftw_execute(ws.p_forw_src);

    double re_out, im_out;
    for (ptr = ws.out_fftw, ptr_end = ws.out_fftw + 2 * ws.h_fftw * (ws.w_fftw / 2 + 1);
         ptr != ptr_end; ++ptr) {
        re_out = *ptr;
        im_out = *(++ptr);

        // magnitude
        *(ptr - 1) = sqrt(re_out * re_out + im_out * im_out);
        // phase
        *ptr = atan2(im_out, re_out);
    }
}
