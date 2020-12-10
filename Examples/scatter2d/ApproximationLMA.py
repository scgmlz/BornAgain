"""
Cylinders of two different sizes in Local Monodisperse Approximation
"""
import numpy, sys
import bornagain as ba
from bornagain import angstrom, deg, micrometer, nm, nm2, kvector_t


def get_sample():
    """
    Returns a sample with cylinders of two different sizes on a substrate.
    The cylinder positions are modelled in Local Monodisperse Approximation.
    """

    # Define materials
    material_Particle = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)

    # Define form factors
    ff_1 = ba.FormFactorCylinder(5.0*nm, 5.0*nm)
    ff_2 = ba.FormFactorCylinder(8.0*nm, 8.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_Particle, ff_1)
    particle_2 = ba.Particle(material_Particle, ff_2)

    # Define interference functions
    iff_1 = ba.InterferenceFunctionRadialParaCrystal(16.8*nm, 1000.0*nm)
    iff_1_pdf = ba.FTDistribution1DGauss(3.0*nm)
    iff_1.setProbabilityDistribution(iff_1_pdf)
    iff_2 = ba.InterferenceFunctionRadialParaCrystal(22.8*nm, 1000.0*nm)
    iff_2_pdf = ba.FTDistribution1DGauss(3.0*nm)
    iff_2.setProbabilityDistribution(iff_2_pdf)

    # Define particle layouts
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particle_1, 0.8)
    layout_1.setInterferenceFunction(iff_1)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(0.01)
    layout_2 = ba.ParticleLayout()
    layout_2.addParticle(particle_2, 0.2)
    layout_2.setInterferenceFunction(iff_2)
    layout_2.setWeight(1)
    layout_2.setTotalParticleSurfaceDensity(0.01)

    # Define layers
    layer_1 = ba.Layer(material_Vacuum)
    layer_1.addLayout(layout_1)
    layer_1.addLayout(layout_2)
    layer_2 = ba.Layer(material_Substrate)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer_1)
    sample.addLayer(layer_2)

    return sample


def get_simulation():
    beam = ba.Beam(1.0, 0.1*nm, ba.Direction(0.2*deg, 0.0*deg))
    nbin = 200
    detector = ba.SphericalDetector(nbin, 2.0*deg, 1.0*deg, 1.0*deg)

    simulation = ba.GISASSimulation(beam, get_sample(), detector)
    return simulation


def run_simulation():
    simulation = get_simulation()
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, *sys.argv[1:])
