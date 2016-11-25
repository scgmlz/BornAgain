// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ConvolutionDetectorResolution.h
//! @brief     Defines class ConvolutionDetectorResolution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CONVOLUTIONDETECTORRESOLUTION_H
#define CONVOLUTIONDETECTORRESOLUTION_H

#include "IDetectorResolution.h"
#include "IResolutionFunction2D.h"

//! Convolutes the intensity in 1 or 2 dimensions with a resolution function.
//! @ingroup simulation

//! Limitation: this class assumes that the data points are evenly distributed on each axis

class BA_CORE_API_ ConvolutionDetectorResolution : public IDetectorResolution
{
public:
    typedef double (*cumulative_DF_1d)(double);

    //! Constructor taking a 1 dimensional resolution function as argument.
    ConvolutionDetectorResolution(cumulative_DF_1d res_function_1d);

    //! Constructor taking a 2 dimensional resolution function as argument.
    ConvolutionDetectorResolution(IResolutionFunction2D* p_res_function_2d);
    ConvolutionDetectorResolution(const IResolutionFunction2D& p_res_function_2d);

    virtual ~ConvolutionDetectorResolution();

    //! Convolve given intensities with the encapsulated resolution.
    virtual void applyDetectorResolution(OutputData<double>* p_intensity_map) const;

    //! Adds parameters from local pool to external pool and recursively call children.
    virtual std::string addParametersToExternalPool(
        const std::string& path, ParameterPool* external_pool, int copy_number = -1) const;

    virtual ConvolutionDetectorResolution* clone() const;

    const IResolutionFunction2D* getResolutionFunction2D() const;

protected:
    ConvolutionDetectorResolution(const ConvolutionDetectorResolution& other);

    virtual void init_parameters();

private:
    void apply1dConvolution(OutputData<double>* p_intensity_map) const;
    void apply2dConvolution(OutputData<double>* p_intensity_map) const;
    double getIntegratedPDF1d(double x, double step) const;
    double getIntegratedPDF2d(double x, double step_x, double y, double step_y) const;

    size_t m_dimension;
    cumulative_DF_1d m_res_function_1d;
    IResolutionFunction2D* mp_res_function_2d;
};

inline const IResolutionFunction2D* ConvolutionDetectorResolution::getResolutionFunction2D() const
{
    return mp_res_function_2d;
}

#endif // CONVOLUTIONDETECTORRESOLUTION_H
