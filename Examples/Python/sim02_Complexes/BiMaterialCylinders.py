"""
Cylindrical particle made from two materials.
Particle crosses air/substrate interface.
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t


def get_composition(top_material,
                    bottom_material,
                    top_height=4.0,
                    bottom_height=10.0):
    """
    Returns cylindrical particle made of two different materials.
    """

    cylinder_radius = 10*nm

    topPart = ba.Particle(top_material,
                          ba.FormFactorCylinder(cylinder_radius, top_height))
    bottomPart = ba.Particle(
        bottom_material, ba.FormFactorCylinder(cylinder_radius, bottom_height))

    result = ba.ParticleComposition()
    result.addParticle(topPart, ba.kvector_t(0.0, 0.0, bottom_height))
    result.addParticle(bottomPart)

    return result


def get_sample():
    """
    Returns a multi layer with substrate/air layers.
    Vacuum layer contains cylindrical particles made of two materials.
    Particle shifted down to cross interface.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("Ag", 1.245e-05, 5.419e-07)
    material_3 = ba.HomogeneousMaterial("Teflon", 2.9e-06, 6.019e-09)
    material_4 = ba.HomogeneousMaterial("Substrate", 3.212e-06, 3.244e-08)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_4)

    # Define form factors
    formFactor_1 = ba.FormFactorCylinder(10.0*nm, 4.0*nm)
    formFactor_2 = ba.FormFactorCylinder(10.0*nm, 10.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_2, formFactor_1)
    particle_1_position = kvector_t(0.0*nm, 0.0*nm, 10.0*nm)
    particle_1.setPosition(particle_1_position)
    particle_2 = ba.Particle(material_3, formFactor_2)

    # Define composition of particles at specific positions
    particleComposition_1 = ba.ParticleComposition()
    particleComposition_1.addParticle(particle_1)
    particleComposition_1.addParticle(particle_2)
    particleComposition_1_position = kvector_t(0.0*nm, 0.0*nm, -10.0*nm)
    particleComposition_1.setPosition(particleComposition_1_position)

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particleComposition_1, 1.0)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(1)

    # Add layouts to layers
    layer_1.addLayout(layout_1)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)
    multiLayer_1.addLayer(layer_2)

    return multiLayer_1


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg, 100, 0.0*deg,
                                     2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1.0e+08)
    return simulation


def run_simulation():
    """
    Runs simulation and returns resulting intensity map.
    """
    simulation = get_simulation()
    simulation.setSample(get_sample())
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')
