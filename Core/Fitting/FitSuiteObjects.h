// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteObjects.h
//! @brief     Defines class FitSuiteObjects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITSUITEOBJECTS_H
#define FITSUITEOBJECTS_H

#include "FitObject.h"

class IChiSquaredModule;
class IHistogram;

//! Holds vector of FitObject's (simulation and real data) to fit
//! @ingroup fitting_internal

class BA_CORE_API_ FitSuiteObjects : public INode
{
public:
    typedef SafePointerVector<FitObject> FitObjects_t;
    typedef FitObjects_t::iterator iterator;

    FitSuiteObjects();
    virtual ~FitSuiteObjects();

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    //! Adds to kit pair of (simulation, real data) for consecutive simulation
    FitObject* add(const Simulation& simulation, const OutputData<double>& real_data,
             double weight = 1.0);

    //! Returns total number of data points (number of all non-masked channels in all fit objects)
    size_t getSizeOfDataSet() const;

    //! Replaces default ChiSquaredModule with new one
    void setChiSquaredModule(const IChiSquaredModule &chi2_module);

    //! Returns simulated data from corresponding FitObject
    //! @param i_item Index of FitObject
    const OutputData<double>& getSimulationData(size_t i_item = 0) const;

    //! run all simulation defined in fit pairs
    void runSimulations();

    //! Returns chi2 calculated over whole dataset
    double getChiSquaredValue() const { return m_chi_squared_value; }

    //! Returns residuals for single data element
    //! @param global_index index across all element in FitElement vector
    double getResidualValue(size_t global_index);

    void setNfreeParameters(int nfree_parameters) { m_nfree_parameters = nfree_parameters; }

    //! clear all data
    void clear();

    size_t size() const { return m_fit_objects.size(); }
    iterator begin() { return m_fit_objects.begin(); }
    iterator end() { return m_fit_objects.end(); }

    std::vector<const INode*> getChildren() const;

#ifndef SWIG
    //! Returns real data from corresponding FitObject. ROI is taken into account.
    //! @param i_item Index of FitObject
    std::unique_ptr<IHistogram> createRealDataHistogram(size_t i_item = 0) const;

    //! Returns simulated data from corresponding FitObject.  ROI is taken into account.
    //! @param i_item Index of FitObject
    std::unique_ptr<IHistogram> createSimulationHistogram(size_t i_item = 0) const;

    //! Returns new chi-squared map from corresponding FitObject. ROI is taken into account.
    //! @param i_item Index of FitObject
    std::unique_ptr<IHistogram> createChiSquaredHistogram(size_t i_item = 0) const;

#endif

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters() {}

    double calculateChiSquaredValue();

private:
    inline size_t check_index(size_t index) const;

    std::vector<FitElement>::const_iterator getStart(size_t i_item) const;
    std::vector<FitElement>::const_iterator getEnd(size_t i_item) const;

    FitObjects_t m_fit_objects;
    double m_total_weight;
    int m_nfree_parameters;
    double m_chi_squared_value;
    std::vector<FitElement> m_fit_elements;
    std::unique_ptr<IChiSquaredModule> m_chi2_module;
    size_t m_fit_elements_count;
};

#endif // FITSUITEOBJECTS_H
