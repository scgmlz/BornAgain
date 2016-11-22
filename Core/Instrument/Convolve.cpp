// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/Convolve.cpp
//! @brief     Implements class Convolve.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Convolve.h"
#include "Exceptions.h"
#include <iostream>
#include <sstream>
#include <stdexcept> // need overlooked by g++ 5.4

Convolve::Convolve() : m_mode(FFTW_UNDEFINED)
{
    // storing favorite fftw3 prime factors
    const size_t FFTW_FACTORS[] = {13,11,7,5,3,2};
    m_implemented_factors.assign(
        FFTW_FACTORS, FFTW_FACTORS + sizeof(FFTW_FACTORS)/sizeof(FFTW_FACTORS[0]));
}

Convolve::Workspace::Workspace() :
    h_src(0), w_src(0), h_kernel(0), w_kernel(0), w_fftw(0), h_fftw(0),
    in_src(0), out_src(0), in_kernel(0), out_kernel(0), dst_fft(0), h_dst(0), w_dst(0),
    //dst(0),
    h_offset(0), w_offset(0),
    p_forw_src(nullptr), p_forw_kernel(nullptr), p_back(nullptr)
{
}

Convolve::Workspace::~Workspace()
{
    clear();
}

void Convolve::Workspace::clear()
{
    h_src=0;
    w_src=0;
    h_kernel=0;
    w_kernel = 0;
    if(in_src) delete[] in_src;
    in_src = 0;

    if(out_src) fftw_free((fftw_complex*)out_src);
    out_src = 0;

    if(in_kernel) delete[] in_kernel;
    in_kernel=0;

    if(out_kernel) fftw_free((fftw_complex*)out_kernel);
    out_kernel=0;

    if(dst_fft) delete[] dst_fft;
    dst_fft=0;

    //if(dst) delete[] dst;
    //dst=0;

    h_offset = 0;
    w_offset = 0;

    if(p_forw_src != nullptr) fftw_destroy_plan(p_forw_src);
    if(p_forw_kernel != nullptr) fftw_destroy_plan(p_forw_kernel);
    if(p_back != nullptr)  fftw_destroy_plan(p_back);

    // this returns fftw3 into completely initial state but is dramatically slow
    //fftw_cleanup();
}


/* ************************************************************************* */
// convolution in 2d
/* ************************************************************************* */
void Convolve::fftconvolve(
    const double2d_t& source, const double2d_t& kernel, double2d_t& result)
{
    // set default convolution mode, if not defined
    if(m_mode == FFTW_UNDEFINED)
        setMode(FFTW_LINEAR_SAME);

    int h_src = (int)source.size();
    int w_src = (int)(source.size() ? source[0].size() : 0);
    int h_kernel = (int)kernel.size();
    int w_kernel = (kernel.size() ? (int)kernel[0].size() : 0);

    // initialisation
    init(h_src, w_src, h_kernel, w_kernel);
    // Compute the circular convolution
    fftw_circular_convolution(source, kernel);

    // results
    result.clear();
    result.resize(ws.h_dst);
    for(int i=0; i<ws.h_dst; i++) {
        result[i].resize(ws.w_dst,0);
        for(int j=0; j<ws.w_dst; j++) {
            //result[i][j]=ws.dst[i*ws.w_dst+j];
            if(m_mode == FFTW_CIRCULAR_SAME_SHIFTED) {
                result[i][j] = ws.dst_fft[
                    ((i+int(ws.h_kernel/2.0))%ws.h_fftw)*ws.w_fftw+
                    (j+int(ws.w_kernel/2.0))%ws.w_fftw];
            } else {
                result[i][j] = ws.dst_fft[(i+ws.h_offset)*ws.w_fftw+j+ws.w_offset];
            }
        }
    }

}


/* ************************************************************************* */
// convolution in 1d
/* ************************************************************************* */
void Convolve::fftconvolve(
    const double1d_t& source, const double1d_t& kernel, double1d_t& result)
{
    // we simply create 2d arrays with length of first dimension equal to 1, and call 2d convolution
    double2d_t source2d, kernel2d;
    source2d.push_back(source);
    kernel2d.push_back(kernel);

    double2d_t result2d;
    fftconvolve(source2d, kernel2d, result2d);
    if(result2d.size() != 1)
        throw Exceptions::RuntimeErrorException(
            "Convolve::fftconvolve -> Panic in 1d");
    result = result2d[0];
}


/* ************************************************************************* */
// initialise input and output arrays for fast Fourier transformation
/* ************************************************************************* */
void Convolve::init(int h_src, int w_src, int h_kernel, int w_kernel)
{
    if(!h_src || !w_src || !h_kernel || !w_kernel) {
        std::ostringstream os;
        os << "Convolve::init() -> Panic! Wrong dimensions " <<
            h_src << " " << w_src << " " << h_kernel << " " << w_kernel << std::endl;
        throw Exceptions::RuntimeErrorException(os.str());
    }

    ws.clear();
    ws.h_src = h_src;
    ws.w_src = w_src;
    ws.h_kernel = h_kernel;
    ws.w_kernel = w_kernel;
    switch(m_mode)
    {
    case FFTW_LINEAR_FULL:
        // Full Linear convolution
        ws.h_fftw = find_closest_factor(h_src + h_kernel - 1);
        ws.w_fftw = find_closest_factor(w_src + w_kernel - 1);
        ws.h_dst = h_src + h_kernel-1;
        ws.w_dst = w_src + w_kernel-1;
        // Here we just keep the first [0:h_dst-1 ; 0:w_dst-1] real part elements of out_src
        ws.h_offset = 0;
        ws.w_offset = 0;
        break;
    case FFTW_LINEAR_SAME_UNPADDED:
        // Same Linear convolution
        ws.h_fftw = h_src + int(h_kernel/2.0);
        ws.w_fftw = w_src + int(w_kernel/2.0);
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        // Here we just keep the first [h_filt/2:h_filt/2+h_dst-1 ; w_filt/2:w_filt/2+w_dst-1]
        // real part elements of out_src
        ws.h_offset = int(ws.h_kernel/2.0);
        ws.w_offset = int(ws.w_kernel/2.0);
        break;
    case FFTW_LINEAR_SAME:
        // Same Linear convolution
        ws.h_fftw = find_closest_factor(h_src + int(h_kernel/2.0));
        ws.w_fftw = find_closest_factor(w_src + int(w_kernel/2.0));
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        // Here we just keep the first [h_filt/2:h_filt/2+h_dst-1 ; w_filt/2:w_filt/2+w_dst-1]
        // real part elements of out_src
        ws.h_offset = int(ws.h_kernel/2.0);
        ws.w_offset = int(ws.w_kernel/2.0);
        break;
    case FFTW_LINEAR_VALID:
        // Valid Linear convolution
        if(ws.h_kernel > ws.h_src || ws.w_kernel > ws.w_src)
        {
            ws.h_fftw = 0;
            ws.w_fftw = 0;
            ws.h_dst = 0;
            ws.w_dst = 0;
            std::cout << "The 'valid' convolution results in an empty matrix" << std::endl;
            throw std::runtime_error("The 'valid' convolution results in an empty matrix");
        } else {
            ws.h_fftw = find_closest_factor(h_src);
            ws.w_fftw = find_closest_factor(w_src);
            ws.h_dst = h_src - h_kernel+1;
            ws.w_dst = w_src - w_kernel+1;
        }
        // Here we just take [h_dst x w_dst] elements starting at [h_kernel-1;w_kernel-1]
        ws.h_offset = ws.h_kernel - 1;
        ws.w_offset = ws.w_kernel - 1;
        break;
    case FFTW_CIRCULAR_SAME:
        // Circular convolution, modulo N
        // We don't padd with zeros because if we do, we need to padd with at least h_kernel/2;
        // w_kernel/2 elements plus the wrapp around, which in facts leads to too much
        // computations compared to the gain obtained with the optimal size
        ws.h_fftw = h_src;
        ws.w_fftw = w_src;
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        // We copy the first [0:h_dst-1 ; 0:w_dst-1] real part elements of out_src
        ws.h_offset = 0;
        ws.w_offset = 0;
        break;
    case FFTW_CIRCULAR_SAME_SHIFTED:
        // Circular convolution, modulo N, shifted by M/2
        // We don't padd with zeros because if we do, we need to padd with at least h_kernel/2;
        // w_kernel/2 elements plus the wrapp around, which in facts leads to too much
        // computations compared to the gain obtained with the optimal size
        ws.h_fftw = h_src;
        ws.w_fftw = w_src;
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        // We copy the [h_kernel/2:h_kernel/2+h_dst-1 ; w_kernel/2:w_kernel/2+w_dst-1]
        // real part elements of out_src
        ws.h_offset = 0;
        ws.w_offset = 0;
        break;
    default:
        std::cout << "Unrecognized convolution mode, possible modes are " <<
            "FFTW_LINEAR_FULL, FFTW_LINEAR_SAME, FFTW_LINEAR_SAME_UNPADDED, FFTW_LINEAR_VALID, " <<
            "FFTW_CIRCULAR_SAME, FFTW_CIRCULAR_SHIFTED " << std::endl;
        break;
    }

    ws.in_src = new double[ws.h_fftw * ws.w_fftw];
    ws.out_src = (double*) fftw_malloc(sizeof(fftw_complex) * ws.h_fftw * (ws.w_fftw/2+1));
    ws.in_kernel = new double[ws.h_fftw * ws.w_fftw];
    ws.out_kernel = (double*) fftw_malloc(sizeof(fftw_complex) * ws.h_fftw * (ws.w_fftw/2+1));

    ws.dst_fft = new double[ws.h_fftw * ws.w_fftw];
    //ws.dst = new double[ws.h_dst * ws.w_dst];

    // Initialization of the plans
    ws.p_forw_src = fftw_plan_dft_r2c_2d(ws.h_fftw, ws.w_fftw, ws.in_src,
                                         (fftw_complex*)ws.out_src, FFTW_ESTIMATE);
    if( ws.p_forw_src == nullptr )
        throw Exceptions::RuntimeErrorException(
            "Convolve::init() -> Error! Can't initialise p_forw_src plan.");

    ws.p_forw_kernel = fftw_plan_dft_r2c_2d(ws.h_fftw, ws.w_fftw, ws.in_kernel,
                                            (fftw_complex*)ws.out_kernel, FFTW_ESTIMATE);
    if( ws.p_forw_kernel == nullptr )
        throw Exceptions::RuntimeErrorException(
            "Convolve::init() -> Error! Can't initialise p_forw_kernel plan.");

    // The backward FFT takes ws.out_kernel as input
    ws.p_back = fftw_plan_dft_c2r_2d(
        ws.h_fftw, ws.w_fftw, (fftw_complex*)ws.out_kernel, ws.dst_fft, FFTW_ESTIMATE);
    if( ws.p_back == nullptr )
        throw Exceptions::RuntimeErrorException(
            "Convolve::init() -> Error! Can't initialise p_back plan.");
}


/* ************************************************************************* */
// initialise input and output arrays for fast Fourier transformation
/* ************************************************************************* */

void Convolve::fftw_circular_convolution(
    const double2d_t& src, const double2d_t& kernel)
{
    if(ws.h_fftw <= 0 || ws.w_fftw <= 0)
        throw Exceptions::RuntimeErrorException(
            "Convolve::fftw_convolve() -> Panic! Initialisation is missed.");

    double * ptr, *ptr_end, *ptr2;

    // Reset the content of ws.in_src
    for(ptr = ws.in_src, ptr_end = ws.in_src + ws.h_fftw*ws.w_fftw ; ptr != ptr_end ; ++ptr)
        *ptr = 0.0;
    for(ptr = ws.in_kernel, ptr_end = ws.in_kernel + ws.h_fftw*ws.w_fftw ; ptr != ptr_end ; ++ptr)
        *ptr = 0.0;

    // Then we build our periodic signals
    //ptr = src;
    for(int i = 0 ; i < ws.h_src ; ++i)
        for(int j = 0 ; j < ws.w_src ; ++j, ++ptr)
            ws.in_src[(i%ws.h_fftw)*ws.w_fftw+(j%ws.w_fftw)] += src[i][j];

    //ptr = kernel;
    for(int i = 0 ; i < ws.h_kernel ; ++i)
        for(int j = 0 ; j < ws.w_kernel ; ++j, ++ptr)
            ws.in_kernel[(i%ws.h_fftw)*ws.w_fftw+(j%ws.w_fftw)] += kernel[i][j];

    // And we compute their packed FFT
    fftw_execute(ws.p_forw_src);
    fftw_execute(ws.p_forw_kernel);

    // Compute the element-wise product on the packed terms
    // Let's put the element wise products in ws.in_kernel
    double re_s, im_s, re_k, im_k;
    for(ptr = ws.out_src,
            ptr2 = ws.out_kernel,
            ptr_end = ws.out_src+2*ws.h_fftw * (ws.w_fftw/2+1); ptr != ptr_end ; ++ptr, ++ptr2)
    {
        re_s = *ptr;
        im_s = *(++ptr);
        re_k = *ptr2;
        im_k = *(++ptr2);
        *(ptr2-1) = re_s * re_k - im_s * im_k;
        *ptr2 = re_s * im_k + im_s * re_k;
    }

    // Compute the backward FFT
    // Carefull, The backward FFT does not preserve the output
    fftw_execute(ws.p_back);
    // Scale the transform
    for(ptr = ws.dst_fft, ptr_end = ws.dst_fft + ws.w_fftw*ws.h_fftw ; ptr != ptr_end ; ++ptr)
        *ptr /= double(ws.h_fftw*ws.w_fftw);

}


/* ************************************************************************* */
// find a number closest to the given one, which  can be factorised according
// to fftw3 favorite factorisation
/* ************************************************************************* */

int Convolve::find_closest_factor(int n)
{
    if(is_optimal(n) ) {
        return n;
    } else {
        int j = n+1;
        while( !is_optimal(j) ) ++j;
        return j;
    }
}


/* ************************************************************************* */
// if a number can be factorised using only favorite fftw3 factors
/* ************************************************************************* */
bool Convolve::is_optimal(int n)
{
    if(n==1)
        return false;
    int ntest = n;
    for(size_t i=0; i<m_implemented_factors.size(); i++){
        while( (ntest%m_implemented_factors[i]) == 0 ) {
            ntest = ntest/m_implemented_factors[i];
        }
    }
    return ntest==1;
}
