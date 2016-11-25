// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitObject.h
//! @brief     Defines class FitObject.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITOBJECT_H
#define FITOBJECT_H

#include "IParameterized.h"
#include "OutputData.h"
#include <INoncopyable.h>
#include <memory>

class FitElement;
class GISASSimulation;
class IIntensityNormalizer;

//! Holds simulation description and real data to run the fit.
//! @ingroup fitting_internal

class BA_CORE_API_ FitObject : public IParameterized, public INoncopyable
{
public:
    //! FitObject constructor
    //! @param simulation The simulation to run
    //! @param real_data The real data
    //! @param weight Weight of dataset in chi2 calculations
    //! @param adjust_detector_to_data Detector axes will be adjusted to real data axes, if true
    FitObject(
        const GISASSimulation& simulation, const OutputData<double>& real_data, double weight = 1);

    virtual ~FitObject();

    //! Returns real (experimental) data.
    const OutputData<double>& realData() const;

    //! Returns simulated data.
    const OutputData<double>& simulationData() const;

    //! Returns chi2 map.
    const OutputData<double>& chiSquaredMap() const;

    //! Returns simulation
    const GISASSimulation& simulation() const;

    //! Returns weight of data set in chi2 calculations.
    double weight() const { return m_weight; }

    //! Returns the size of the data. It is equal to the number of non-masked detector channels
    //! which will participate in chi2 calculations.
    size_t numberOfFitElements() const;

    void prepareFitElements(
        std::vector<FitElement>& fit_elements, double weight, IIntensityNormalizer* normalizer = 0);

    void transferToChi2Map(
        std::vector<FitElement>::const_iterator first,
        std::vector<FitElement>::const_iterator last) const;

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(
        const std::string& path, ParameterPool* external_pool, int copy_number = -1) const;

protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters() {}

private:
    void init_dataset(const OutputData<double>& real_data);
    void process_realdata(const OutputData<double>& real_data);

    std::unique_ptr<GISASSimulation> m_simulation;
    std::unique_ptr<OutputData<double>> m_real_data;
    std::unique_ptr<OutputData<double>> m_simulation_data;
    std::unique_ptr<OutputData<double>> m_chi2_data;
    double m_weight;
    size_t m_fit_elements_count;
};

#endif // FITOBJECT_H
