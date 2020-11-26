"""
Square lattice of half spheres on substrate with usage of average material
and slicing
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t

sphere_radius = 5*nm
n_slices = 10


def get_sample():
    """
    Returns a sample with cylinders on a substrate.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("Particle", 3e-05, 2e-08)
    material_3 = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_1.setNumberOfSlices(10)
    layer_2 = ba.Layer(material_3)

    # Define form factors
    formFactor_1 = ba.FormFactorTruncatedSphere(5.0*nm, 5.0*nm, 0.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_2, formFactor_1)

    # Define 2D lattices
    lattice2D_1 = ba.BasicLattice2D(10.0*nm, 10.0*nm, 90.0*deg, 0.0*deg)

    # Define interference functions
    interference_1 = ba.InterferenceFunction2DLattice(lattice2D_1)
    interference_1_pdf = ba.FTDecayFunction2DCauchy(100.0*nm, 100.0*nm, 0.0*deg)
    interference_1.setDecayFunction(interference_1_pdf)

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particle_1, 1.0)
    layout_1.setInterferenceFunction(interference_1)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(0.01)

    # Add layouts to layers
    layer_1.addLayout(layout_1)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)
    multiLayer_1.addLayer(layer_2)

    return multiLayer_1


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -2.0*deg, 2.0*deg, 100, 0.0*deg,
                                     2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.getOptions().setUseAvgMaterials(True)
    return simulation


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')
