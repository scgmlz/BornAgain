//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Processed/ProcessedSample.h
//! @brief     Defines class ProcessedSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_PROCESSED_PROCESSEDSAMPLE_H
#define BORNAGAIN_SAMPLE_PROCESSED_PROCESSEDSAMPLE_H

#include "Sample/Slice/Slice.h"
#include <map>
#include <memory>
#include <vector>

struct HomogeneousRegion;
class IFresnelMap;
class LayerRoughness;
class MultiLayer;
class ProcessedLayout;
class SimulationOptions;

//! Data structure that contains all the necessary data for scattering calculations.
//!
//! If the usage of average materials is requested, layers and particles are sliced into multiple
//! slices and the average material is calculated for each slice.
//!
//! @ingroup algorithms_internal

class ProcessedSample {
public:
    ProcessedSample(const MultiLayer& sample, const SimulationOptions& options);
    ~ProcessedSample();

    size_t numberOfSlices() const;
    const std::vector<Slice>& slices() const;
    const std::vector<Slice>& averageSlices() const;
    const std::vector<ProcessedLayout>& layouts() const;
    const IFresnelMap* fresnelMap() const;
    double crossCorrelationLength() const;
    kvector_t externalField() const;
    const LayerRoughness* bottomRoughness(size_t i) const;
    double sliceTopZ(size_t i) const;
    double sliceBottomZ(size_t i) const;
    bool containsMagneticMaterial() const;
    bool hasRoughness() const;

    //! Fourier transform of the correlation function of roughnesses between
    //! the interfaces
    double crossCorrSpectralFun(const kvector_t kvec, size_t j, size_t k) const;

private:
    void initSlices(const MultiLayer& sample, const SimulationOptions& options);
    void initLayouts(const MultiLayer& sample);
    void addSlice(double thickness, const Material& material,
                  const LayerRoughness* p_roughness = nullptr);
    void addNSlices(size_t n, double thickness, const Material& material,
                    const LayerRoughness* p_roughness = nullptr);
    void initBFields();
    void mergeRegionMap(const std::map<size_t, std::vector<HomogeneousRegion>>& region_map);
    void initFresnelMap(const SimulationOptions& sim_options);

    std::unique_ptr<IFresnelMap> m_fresnel_map;
    std::vector<Slice> m_slices;
    double m_top_z;
    bool m_polarized;
    std::vector<ProcessedLayout> m_layouts;
    double m_crossCorrLength;
    kvector_t m_ext_field;
    std::map<size_t, std::vector<HomogeneousRegion>> m_region_map;
};

#endif // BORNAGAIN_SAMPLE_PROCESSED_PROCESSEDSAMPLE_H
#endif // USER_API
