// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteObjects.h
//! @brief     Defines class FitSuiteObjects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEOBJECTS_H
#define FITSUITEOBJECTS_H

#include "FitObject.h"

class IChiSquaredModule;

//! Holds vector of FitObject's (simulation and real data) to fit
//! @ingroup fitting_internal

class BA_CORE_API_ FitSuiteObjects : public IParameterized, public INoncopyable
{
public:
    typedef SafePointerVector<FitObject> FitObjects_t;

    FitSuiteObjects();
    virtual ~FitSuiteObjects();

    //! Adds to kit pair of (simulation, real data) for consecutive simulation
    void
    add(const GISASSimulation& simulation, const OutputData<double>& real_data,
        double weight = 1.0);

    //! Returns number of fit objects (simulation/real data pairs)
    size_t getNumberOfFitObjects() const { return m_fit_objects.size(); }

    //! Returns total number of data points (number of all non-masked channels in all fit objects)
    size_t getSizeOfDataSet() const;

    //! Replaces default ChiSquaredModule with new one
    void setChiSquaredModule(const IChiSquaredModule& chi2_module);

    //! Returns real data from corresponding FitObject
    //! @param i_item Index of FitObject
    const OutputData<double>& getRealData(size_t i_item = 0) const;

    //! Returns simulated data from corresponding FitObject
    //! @param i_item Index of FitObject
    const OutputData<double>& getSimulationData(size_t i_item = 0) const;

    //! Returns new chi-squared map from corresponding FitObject
    //! @param i_item Index of FitObject
    const OutputData<double>& getChiSquaredMap(size_t i_item = 0) const;

    //! run all simulation defined in fit pairs
    void runSimulations();

    //! Returns chi2 calculated over whole dataset
    double getChiSquaredValue() const { return m_chi_squared_value; }

    //! Returns residuals for single data element
    //! @param global_index index accross all element in FitElement vector
    double getResidualValue(size_t global_index);

    //! Adds parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(
        const std::string& path, ParameterPool* external_pool, int copy_number = -1) const;

    void setNfreeParameters(int nfree_parameters) { m_nfree_parameters = nfree_parameters; }

    //! clear all data
    void clear();

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters() {}

    double calculateChiSquaredValue();

private:
    inline size_t check_index(size_t index) const;

    FitObjects_t m_fit_objects;
    double m_total_weight;
    int m_nfree_parameters;
    double m_chi_squared_value;
    std::vector<FitElement> m_fit_elements;
    std::unique_ptr<IChiSquaredModule> m_chi2_module;
    size_t m_fit_elements_count;
};

#endif // FITSUITEOBJECTS_H
