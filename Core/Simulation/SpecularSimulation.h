// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SpecularSimulation.h
//! @brief     Defines class SpecularSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPECULARSIMULATION_H
#define SPECULARSIMULATION_H

#include "ICloneable.h"
#include "ILayerRTCoefficients.h"
#include "IParameterized.h"
#include "OutputData.h"
#include <memory>

class IAxis;
class ISample;
class IMultiLayerBuilder;
class MultiLayer;

//! Main class to run a specular simulation.
//! @ingroup simulation

class BA_CORE_API_ SpecularSimulation : public ICloneable, public IParameterized
{
public:
    typedef std::shared_ptr<const ILayerRTCoefficients> LayerRTCoefficients_t;
    typedef std::vector<LayerRTCoefficients_t> MultiLayerRTCoefficients_t;

    SpecularSimulation();
    SpecularSimulation(const ISample& sample);
    SpecularSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder);
    virtual ~SpecularSimulation();

    SpecularSimulation* clone() const;

    //! Run a simulation with the current parameter settings
    void runSimulation();

    //! Sets the sample to be tested
    void setSample(const ISample& sample);

    //! Returns the sample
    ISample* getSample() const { return mP_sample.get(); }

    //! Sets the sample builder
    void setSampleBuilder(std::shared_ptr<IMultiLayerBuilder> sample_builder);

    //! return sample builder
    std::shared_ptr<IMultiLayerBuilder> getSampleBuilder() const { return mP_sample_builder; }

    //! Sets beam parameters with alpha_i of the beam defined in the range
    void setBeamParameters(double lambda, const IAxis& alpha_axis);
    void setBeamParameters(double lambda, int nbins, double alpha_i_min, double alpha_i_max);

    //! set axis for evanescent wave axis
    void setEvanescentWaveAxis(const IAxis& z_axis);
    void setEvanescentWaveAxis(int nbins, double z_min, double z_max);

    //! returns alpha_i axis
    const IAxis* getAlphaAxis() const;

    //! returns vector of reflection coefficients for all alpha_i angles for given layer index
    std::vector<complex_t> getScalarR(size_t i_layer) const;

    //! returns vector of transmission coefficients for all alpha_i angles for given layer index
    std::vector<complex_t> getScalarT(size_t i_layer) const;

    //! returns vector of Kz coefficients for all alpha_i angles for given layer index
    std::vector<complex_t> getScalarKz(size_t i_layer) const;

    LayerRTCoefficients_t getLayerRTCoefficients(size_t i_alpha, size_t i_layer) const;

    //! Put into a clean state for running a simulation
    void prepareSimulation();

    //    OutputData<double>* getEvanescentWaveIntensity() const;

protected:
    SpecularSimulation(const SpecularSimulation& other);

    //! Registers some class members for later access via parameter pool
    void init_parameters() {}

    //! Update the sample by calling the sample builder, if present
    void updateSample();

    //! calculates RT coefficients for multilayer without magnetic materials
    void collectRTCoefficientsScalar(const MultiLayer* multilayer);

    //! calculates RT coefficients for multilayer with magnetic materials
    void collectRTCoefficientsMatrix(const MultiLayer* multilayer);

    //! calculates the intensity of evanescent wave
    //    void calculateEvanescentWaveIntensity();

    //! check if simulation was run already and has valid coefficients
    void checkCoefficients(size_t i_layer) const;

    //! update data axes
    void updateCoefficientDataAxes();

    std::unique_ptr<ISample> mP_sample;
    std::shared_ptr<IMultiLayerBuilder> mP_sample_builder;
    IAxis* m_alpha_i_axis;
    IAxis* m_z_axis;
    double m_lambda;

#ifndef SWIG
    OutputData<MultiLayerRTCoefficients_t> m_data;
    OutputData<double> m_ewave_intensity;
#endif
};

#endif // SPECULARSIMULATION_H
