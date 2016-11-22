// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/Convolve.h
//! @brief     Defines class MathFunctions::Convolve.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CONVOLVE_H
#define CONVOLVE_H

#include "WinDllMacros.h"
#include <fftw3.h>
#include <vector>

//! Convolution of two real vectors (in 1D or 2D) using Fast Fourier Transform.
//!
//! Usage:
//! std::vector<double> signal, kernel, result;
//! Convolve cv;
//! cv.fftconvolve(signal, kernel, result)
//!
//! Given code rely on code from Jeremy Fix page, http://jeremy.fix.free.fr/spip.php?article15,
//! see also "Efficient convolution using the Fast Fourier Transform, Application in C++"
//! by Jeremy Fix, May 30, 2011
//!
//! @ingroup tools_internal
class BA_CORE_API_ Convolve
{
public:
    //! definition of 1d vector of double
    typedef std::vector<double > double1d_t;

    //! definition of 2d vector of double
    typedef std::vector<double1d_t > double2d_t;

    Convolve();

    //! convolution  modes
    //! use LINEAR_SAME or CIRCULAR_SAME_SHIFTED for maximum performance
    enum EConvolutionMode { FFTW_LINEAR_FULL, FFTW_LINEAR_SAME_UNPADDED,
                            FFTW_LINEAR_SAME, FFTW_LINEAR_VALID,
                            FFTW_CIRCULAR_SAME, FFTW_CIRCULAR_SAME_SHIFTED,
                            FFTW_UNDEFINED };

    //! convolution in 1D
    void fftconvolve(const double1d_t& source, const double1d_t& kernel, double1d_t& result);

    //! convolution in 2D
    void fftconvolve(const double2d_t& source, const double2d_t& kernel, double2d_t& result);

    //! prepare arrays for 2D convolution of given vectors
    void init(int h_src, int w_src, int h_kernel, int w_kernel);

    //! Sets convolution mode
    void setMode(EConvolutionMode mode) { m_mode = mode; }

private:
    //! compute circual convolution of source and kernel using fast Fourier transformation
    void fftw_circular_convolution(const double2d_t& source, const double2d_t& kernel);

    //! find closest number X>n that can be factorised according to fftw3 favorite factorisation
    int find_closest_factor(int n);

    //! if a number can be factorised using only favorite fftw3 factors
    bool is_optimal(int n);

    //! Workspace for Fourier convolution.

    //! Workspace contains input (source and kernel), intermediate and output
    //! arrays to run convolution via fft; 'source' it is our signal, 'kernel'
    //! it is our resolution function.
    //! Sizes of input arrays are adjusted; output arrays are alocated via
    //! fftw3 allocation for maximum performance.
    class Workspace
    {
    public:
        Workspace();
        ~Workspace();
        void clear();
        friend class Convolve;
    private:
        int h_src, w_src;                 // size of original 'source' array in 2 dimensions
        int h_kernel, w_kernel;           // size of original 'kernel' array in 2 dimensions
        // size of adjusted source and kernel arrays (in_src, out_src, in_kernel, out_kernel)
        int w_fftw, h_fftw;
        //! adjusted input 'source' array
        double *in_src;
        //! result of Fourier transformation of source
        double *out_src;
        //! adjusted input 'kernel' array
        double *in_kernel;
        //! result of Fourier transformation of kernel
        double *out_kernel;
        //! result of product of FFT(source) and FFT(kernel)
        double *dst_fft;
        int h_dst, w_dst;                 // size of resulting array
        int h_offset, w_offset;           // offsets to copy result into output arrays
        fftw_plan p_forw_src;
        fftw_plan p_forw_kernel;
        fftw_plan p_back;
    };

    //! input and output data for fftw3
    Workspace ws;
    //! convolution mode
    EConvolutionMode m_mode;
    std::vector<size_t > m_implemented_factors; // favorite factorization terms of fftw3
};

#endif // CONVOLVE_H
