// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProcessedLayout.h
//! @brief     Defines class ProcessedLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_PROCESSEDLAYOUT_H
#define BORNAGAIN_CORE_COMPUTATION_PROCESSEDLAYOUT_H

#include <map>
#include <memory>
#include <vector>

class FormFactorCoherentSum;
struct HomogeneousRegion;
class IFresnelMap;
class IInterferenceFunction;
class ILayout;
class IParticle;
class Slice;

//! Data structure that contains preprocessed data for a single layout.
//!
//! If particles in the layout crossed the limits of the layer slices, these particles will
//! be sliced themselves.
//!
//! @ingroup algorithms_internal

class ProcessedLayout
{
public:
    ProcessedLayout(const ILayout& layout, const std::vector<Slice>& slices, double z_ref,
                    const IFresnelMap* p_fresnel_map, bool polarized);
    ProcessedLayout(ProcessedLayout&& other);
    ~ProcessedLayout();

    size_t numberOfSlices() const;
    double surfaceDensity() const;
    const std::vector<FormFactorCoherentSum>& formFactorList() const;
    const IInterferenceFunction* interferenceFunction() const;
    std::map<size_t, std::vector<HomogeneousRegion>> regionMap() const;

private:
    void collectFormFactors(const ILayout& layout, const std::vector<Slice>& slices, double z_ref);
    FormFactorCoherentSum ProcessParticle(const IParticle& particle,
                                          const std::vector<Slice>& slices, double z_ref);
    void mergeRegionMap(const std::map<size_t, std::vector<HomogeneousRegion>>& region_map);
    const IFresnelMap* mp_fresnel_map;
    bool m_polarized;
    size_t m_n_slices;
    double m_surface_density;
    std::vector<FormFactorCoherentSum> m_formfactors;
    std::unique_ptr<IInterferenceFunction> mP_iff;
    std::map<size_t, std::vector<HomogeneousRegion>> m_region_map;
};

#endif // BORNAGAIN_CORE_COMPUTATION_PROCESSEDLAYOUT_H
