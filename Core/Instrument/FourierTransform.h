// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/FourierTransform.h
//! @brief     Defines class MathFunctions::FourierTransform.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INSTRUMENT_FOURIERTRANSFORM_H
#define BORNAGAIN_CORE_INSTRUMENT_FOURIERTRANSFORM_H

#include "Wrap/WinDllMacros.h"
#include <fftw3.h>
#include <vector>

//! Fourier transform of vectors (in 1D or 2D) using Fast Fourier Transform (fftw package).
//!
//! Usage:
//! std::vector<double> signal, result;
//! FourierTransform ft;
//! ft.fft(signal, result)
//!
//! Given code rely on code from Jeremy Fix page, http://jeremy.fix.free.fr/spip.php?article15,
//! see also "Efficient convolution using the Fast Fourier Transform, Application in C++"
//! by Jeremy Fix, May 30, 2011
//!
//! @ingroup tools_internal
class BA_CORE_API_ FourierTransform
{
public:
    //! definition of 1D vector of double
    typedef std::vector<double> double1d_t;

    //! definition of 2D vector of double
    typedef std::vector<double1d_t> double2d_t;

    FourierTransform();

    //! FT in 1D
    void fft(const double1d_t& source, double1d_t& result);

    //! Shift low frequency to the center of 1D FT array
    void fftshift(double1d_t& result);

    //! FT in 2D
    void fft(const double2d_t& source, double2d_t& result);

    //! Shift low frequency to the center of 2D FT array
    void fftshift(double2d_t& result);

    //! prepare arrays for 2D Fourier Transformation (FT) of the given vector
    void init(int h_src, int w_src);

private:
    //! compute FT of source using Fast Fourier transformation from fftw
    void fftw_forward_FT(const double2d_t& source);

    //! Workspace for Fourier Transform.

    //! Workspace contains input (src), intermediate and output (out)
    //! arrays to run FT via fft; 'source' is our signal
    //! Output arrays are allocated via fftw3 allocation for maximum performance.
    class Workspace
    {
    public:
        Workspace();
        ~Workspace();
        void clear();
        friend class FourierTransform;

    private:
        //! Here, h = height (# rows), w = width (# columns)
        int h_src, w_src;   // size of input 'source' array in 2D
        int h_fftw, w_fftw; // size of output 'FT' array in 2D

        double* in_src; // pointer to input 'source' array

        //! result of Fourier transformation of source
        double* out_fftw; // pointer to output 'FT' array

        fftw_plan p_forw_src;
    };

    //! input and output data for fftw3
    Workspace ws;
};

#endif // BORNAGAIN_CORE_INSTRUMENT_FOURIERTRANSFORM_H
