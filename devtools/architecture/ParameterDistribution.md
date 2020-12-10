## Parameter distributions

Analysis of BornAgain develop, per 3dec20.

It seems there are two different ways for handling parameter distributions,
the one specifically for particle distributions, the other one more generic.

### Particle distribution

#### Typical use

Typical use of parameter distributions is described in
`Examples/Python/sim01_Particles/CylindersWithSizeDistribution.py`:
```
def get_sample():
    # Define materials and form factor ...

    # Define particles
    particle = ba.Particle(material_Particle, ff)

    # Define particles with parameter following a distribution
    distr_1 = ba.DistributionGaussian(5.0*nm, 1.0*nm)
    par_distr_1 = ba.ParameterDistribution(
        "/Particle/Cylinder/Radius", distr_1, 100, 2.0)
    particle_distrib = ba.ParticleDistribution(particle, par_distr_1)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle_distrib, 1.0)

    # Define layers
    layer = ba.Layer(material_Vacuum)
    layer.addLayout(layout)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer)

    return sample


def get_simulation():
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, 0.0*deg, 2.0*deg, 200, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    return simulation


def run_simulation():
    simulation = get_simulation()
    simulation.setSample(get_sample())
    simulation.runSimulation()
    return simulation.result()
```

#### What goes on behind the scenes?

Class hierarchy:
```
IParametricComponent
- INode
  - ISampleNode
    - IAbstractParticle
      - ParticleDistribution (final)
      - IParticle
        - Particle (final)
        - ParticleCoreShell (final)
        ... (all final)
- ISampleBuilder
- DistributionHandler (final)
- ParameterDistribution (final)
```

As we see from the `CylindersWithSizeDistribution` example,
a `ParticleDistribution` is bound to a `ParticleLayout`.
The drawing of `IParticle`s from the distribution happens here:

```
SafePointerVector<IParticle> ParticleLayout::particles() const {
    SafePointerVector<IParticle> particle_vector;
    for (const auto* particle : m_particles) {
        if (const auto* p_part_distr = dynamic_cast<const ParticleDistribution*>(particle)) {
            SafePointerVector<IParticle> generated_particles = p_part_distr->generateParticles();
            for (const IParticle* particle : generated_particles)
                particle_vector.push_back(particle->clone());
        } else if (const auto* p_iparticle = dynamic_cast<const IParticle*>(particle)) {
            particle_vector.push_back(p_iparticle->clone());
        }
    }
    return particle_vector;
}
```

### Generic distribution handler

This mechanism acts almost on top of the simulation model hierarchy.

`ISimulation` has member `DistributionHandler m_distribution_handler`.
It is modified through `ISimulation::addParameterDistribution`.
This function is called explicitly by some standard simulations and Python scripts
(e.g. `sim03_Structures/Interference2DLatticeSumOfRotated.py`),
but not in the above simple example.


```
void ISimulation::runSimulation() {
    ...
    size_t param_combinations = m_distribution_handler.getTotalNumberOfSamples();
    std::unique_ptr<ParameterPool> param_pool(createParameterTree());
    for (size_t index = 0; index < param_combinations; ++index) {
        double weight = m_distribution_handler.setParameterValues(param_pool.get(), index);
        runSingleSimulation(batch_start, batch_size, weight);
    }
    m_distribution_handler.setParameterToMeans(param_pool.get());
    ...
}
```
