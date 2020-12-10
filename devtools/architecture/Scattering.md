## How does BornAgain compute scattering?

Analysis of BornAgain develop, per 18nov,
after merge of https://github.com/scgmlz/BornAgain/pull/1105.

### Simulation computes an incoherent sum

We consider a GISAS simulation, handled by class `GISASSimulation < ISimulation2D < ISimulation`
(where `<` indicates inheritance).

The function `ISimulation::runSimulation`
- calls `prepareSimulation`;
- loops over parameter combinations, thereby performing an incoherent summation:
  - for each parameter set, `runSingleSimulation`;
- calls `moveDataFromCache` to collect results.
  - also calls `transferResultsToIntensityMap`, which does nothing except for `OffSpecSimulation`.

`GISASSimulation::prepareSimulation` seems to be mostly concerned with `SampleBuilder`s.

`ISimulation::runSingleSimulation` handles the multithreaded parallel computation
for batches of detector pixels (`SimulationElement`s). It
- uses `ISimulation2D::generateSingleThreadedComputation` to create instances of `DWBAComputation < IComputation`;
- for each instance, runs `IComputation.run`;
- calls `ISimulation2D::normalize`;
- calls `ISimulation2D::addBackgroundIntensity`.

The `IComputation` constructor creates the member `ProcessedSample m_processed_sample`.

The `DWBAComputation` constructor populates the member `DWBASingleComputation m_single_computation`:
- For each `ProcessedLayout` in `m_processed_sample->layouts()`, the vector `DWBASingleComputation::m_layout_comps` is given a `new ParticleLayoutComputation` member;
- if `m_processed_sample->hasRoughness()`, then `DWBASingleComputation::m_roughness_comp` points to a `new RoughMultiLayerComputation`.

`IComputation::run` calls `DWBAComputation::runProtected`, which for each `SimulationElement` in the batch calls `m_single_computation.compute`.

`DWBASingleComputation::compute` performs an incoherent summation: it increments `SimulationElement::m_intensity` by contributions from each processed particle layouts, and from roughness.

### Scattering from a particle layout

For each processed particle layout, `DWBASingleComputation::compute` calls `ParticleLayoutComputation::compute`.

The `ParticleLayoutComputation` constructor points the member `m_interference_function_strategy` to a `new DecouplingApproximationStrategy`, unless we are simulating a radial paracrystal, for which the `SSCApproximationStrategy` is used.

`ParticleLayoutComputation::compute` increments `SimulationElement::m_intensity` by a scattering intensity times the `ProcessedLayout::surfaceDensity()`. The intensity is computed by `m_interference_function_strategy->evaluate`, which is implemented as `IInterferenceFunctionStrategy::evaluate`. Except for Monte-Carlo integration, this wraps just one call to `IInterferenceFunctionStrategy::evaluateSinglePoint`. For unpolarized scattering, and except for radial paracrystals, the next call goes to `DecouplingApproximationStrategy::scalarCalculation`.

`DecouplingApproximationStrategy::scalarCalculation` performs a coherent and an incoherent summation over scattering amplitudes `ff` obtained by calling `FormFactorCoherentSum::evaluate` on members of `ProcessedLayout::formFactorList()`. The mixed sum is sum

> |ff|^2 + |sum ff|^2 * (coherence_factor - 1)

where coherence_factor is computed by `IInterferenceFunction::evaluate`.

Except for superlattices, there is no "inner" structure, and therefore `IInterferenceFunction::evaluate` just wraps `IInterferenceFunction::iff_no_inner`, so that

> coherence_factor = DWfactor(q) * (iff_without_dw(q) * outer_iff - 1) + 1.

By default, outer_iff = 1, so that

> coherence_factor = DWfactor(q) * (iff_without_dw - 1) + 1.

For the simplest of all interference functions, `InterferenceFunctionNone::iff_without_dw` just returns 1, so that

> coherence_factor = 1.

### Computing the particle formfactor

`FormFactorCoherentSum::evaluate` returns the sum over `FormFactorCoherentPart::evaluate`.

`FormFactorCoherentPart` wraps an `IComputeFF` and additionally holds members `m_fresnel_map` and `m_layer_index` that are set by `FormFactorCoherentPart::setSpecularInfo`. This information is forwarded by calling `IComputeFF::setSpecularInfo`, which does nothing, unless overridden in `ComputeDWBA`.

After this preparation, `ComputeDWBA::evaluate` computes the coherent sum over the four DWBA terms. Each of them uses the scattering amplitude from `IFormFactor::evaluate`, which is pure virtual, overridden by `IFormFactorBorn::evaluate`, which calls `IFormFactorBorn::evaluate_for_q`, which is pure virtual, overriden by shape-specific classes like `FormFactorFullSphere`.
