// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/ConvolutionDetectorResolution.h
//! @brief     Defines class ConvolutionDetectorResolution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_DETECTOR_CONVOLUTIONDETECTORRESOLUTION_H
#define BORNAGAIN_CORE_DETECTOR_CONVOLUTIONDETECTORRESOLUTION_H

#include "Core/Detector/IDetectorResolution.h"
#include "Core/Detector/IResolutionFunction2D.h"

//! Convolutes the intensity in 1 or 2 dimensions with a resolution function.
//! @ingroup detector

//! Limitation: this class assumes that the data points are evenly distributed on each axis

class BA_CORE_API_ ConvolutionDetectorResolution : public IDetectorResolution
{
public:
    typedef double (*cumulative_DF_1d)(double);

    //! Constructor taking a 1 dimensional resolution function as argument.
    ConvolutionDetectorResolution(cumulative_DF_1d res_function_1d);

    //! Constructor taking a 2 dimensional resolution function as argument.
    ConvolutionDetectorResolution(const IResolutionFunction2D& p_res_function_2d);

    virtual ~ConvolutionDetectorResolution();

    //! Convolve given intensities with the encapsulated resolution.
    virtual void applyDetectorResolution(OutputData<double>* p_intensity_map) const;

    virtual ConvolutionDetectorResolution* clone() const;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    const IResolutionFunction2D* getResolutionFunction2D() const;

    std::vector<const INode*> getChildren() const;

protected:
    ConvolutionDetectorResolution(const ConvolutionDetectorResolution& other);

private:
    void setResolutionFunction(const IResolutionFunction2D& resFunc);
    void apply1dConvolution(OutputData<double>* p_intensity_map) const;
    void apply2dConvolution(OutputData<double>* p_intensity_map) const;
    double getIntegratedPDF1d(double x, double step) const;
    double getIntegratedPDF2d(double x, double step_x, double y, double step_y) const;

    size_t m_dimension;
    cumulative_DF_1d m_res_function_1d;
    std::unique_ptr<IResolutionFunction2D> mp_res_function_2d;
};

inline const IResolutionFunction2D* ConvolutionDetectorResolution::getResolutionFunction2D() const
{
    return mp_res_function_2d.get();
}

#endif // BORNAGAIN_CORE_DETECTOR_CONVOLUTIONDETECTORRESOLUTION_H
