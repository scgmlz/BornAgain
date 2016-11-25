// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitObject.cpp
//! @brief     Implements class FitObject.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitObject.h"
#include "BornAgainNamespace.h"
#include "DetectorFunctions.h"
#include "FitElement.h"
#include "GISASSimulation.h"
#include "IIntensityNormalizer.h"
#include "SimulationArea.h"

FitObject::FitObject(
    const GISASSimulation& simulation, const OutputData<double>& real_data, double weight)
    : m_simulation(simulation.clone()), m_weight(weight), m_fit_elements_count(0)

{
    setName("FitObject");
    m_fit_elements_count =
        m_simulation->getInstrument().getDetector()->numberOfSimulationElements();
    init_dataset(real_data);
}

FitObject::~FitObject() {}

const OutputData<double>& FitObject::realData() const { return *m_real_data.get(); }

const OutputData<double>& FitObject::simulationData() const { return *m_simulation_data.get(); }

const OutputData<double>& FitObject::chiSquaredMap() const { return *m_chi2_data.get(); }

const GISASSimulation& FitObject::simulation() const { return *m_simulation.get(); }

//! Adds parameters from local pool to external pool

std::string FitObject::addParametersToExternalPool(
    const std::string& path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string new_path =
        IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the simulation
    if (m_simulation)
        m_simulation->addParametersToExternalPool(new_path, external_pool, -1);

    return new_path;
}

//! Initialize detector, if necessary, to match experimental data
void FitObject::init_dataset(const OutputData<double>& real_data)
{
    process_realdata(real_data);

    m_chi2_data.reset(m_simulation->getInstrument().createDetectorMap());
    //    bool put_masked_areas_to_zero(true);
    //    m_real_data = DetectorFunctions::createDataSet(m_simulation->getInstrument(), real_data,
    //                                                   put_masked_areas_to_zero);
}

//! Adapt real data to use with fitting.
// If real_data and the detector have the same size, real_data will be croped to the ROI
// If size of real_data and the detector is different, it is assumed that it is already cropped
void FitObject::process_realdata(const OutputData<double>& real_data)
{
    const IDetector2D* detector = m_simulation->getInstrument().getDetector();
    if (!DetectorFunctions::hasSameDimensions(*detector, real_data)) {
        std::unique_ptr<OutputData<double>> detectorMap(
            m_simulation->getInstrument().createDetectorMap());

        if (detectorMap->hasSameDimensions(real_data)) {
            detectorMap->setRawDataVector(real_data.getRawDataVector());
            m_real_data.reset(detectorMap.release());
        } else {

            std::ostringstream message;
            message << "FitObject::check_realdata() -> Error. Axes of the real data doesn't match "
                    << "the detector. Real data:" << DetectorFunctions::axesToString(real_data)
                    << ", detector:" << DetectorFunctions::axesToString(*detector) << ".";
            throw Exceptions::RuntimeErrorException(message.str());
        }
    } else {
        bool put_masked_areas_to_zero(false);
        m_real_data = DetectorFunctions::createDataSet(
            m_simulation->getInstrument(), real_data, put_masked_areas_to_zero);
    }
}

size_t FitObject::numberOfFitElements() const { return m_fit_elements_count; }

//! Runs simulation and put results (the real and simulated intensities) into external vector.
//! Masked channels will be excluded from the vector.

void FitObject::prepareFitElements(
    std::vector<FitElement>& fit_elements, double weight, IIntensityNormalizer* normalizer)
{
    m_simulation->runSimulation();
    m_simulation_data.reset(m_simulation->getDetectorIntensity());

    if (normalizer)
        normalizer->apply(*m_simulation_data.get());

    SimulationArea area(m_simulation->getInstrument().getDetector());
    for (SimulationArea::iterator it = area.begin(); it != area.end(); ++it) {
        FitElement element(
            it.roiIndex(), (*m_simulation_data)[it.roiIndex()], (*m_real_data)[it.roiIndex()],
            weight);
        fit_elements.push_back(element);
    }
}

//! Updates ChiSquared map from external vector and returns const reference to it. Used from
//! Python in FitSuiteDrawObserver.

void FitObject::transferToChi2Map(
    std::vector<FitElement>::const_iterator first,
    std::vector<FitElement>::const_iterator last) const
{
    m_chi2_data->setAllTo(0.0);
    for (std::vector<FitElement>::const_iterator it = first; it != last; ++it)
        (*m_chi2_data)[it->getIndex()] = it->getSquaredDifference();
}
