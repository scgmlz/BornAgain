#!/usr/bin/env python3
"""
Large cylinders in DWBA.

This example demonstrates that for large particles (~1000nm) the form factor
oscillates rapidly within one detector bin and analytical calculations
(performed for the bin center) give completely wrong intensity pattern.
In this case Monte-Carlo integration over detector bin should be used.
"""
import bornagain as ba
from bornagain import deg, angstrom, nm
import ba_plot
from matplotlib import pyplot as plt

default_cylinder_radius = 10*nm
default_cylinder_height = 20*nm


def get_sample(cylinder_radius, cylinder_height):
    """
    Returns a sample with cylindrical particles on a substrate.
    """
    # defining materials
    m_vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(cylinder_radius, cylinder_height)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)

    vacuum_layer = ba.Layer(m_vacuum)
    vacuum_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(vacuum_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(sample, integration_flag):
    """
    Returns a GISAXS simulation with defined beam and detector.
    If integration_flag=True, the simulation will integrate over detector bins.
    """
    beam = ba.Beam(1, 1.0*angstrom, ba.Direction(0.2*deg, 0*deg))
    det = ba.SphericalDetector(200, -2*deg, 2*deg, 200, 0*deg, 2*deg)
    simulation = ba.GISASSimulation(beam, sample, det)
    simulation.getOptions().setMonteCarloIntegration(integration_flag, 50)
    if not "__no_terminal__" in globals():
        simulation.setTerminalProgressMonitor()
    return simulation


def simulate_and_plot():
    """
    Run simulation and plot results 4 times: for small and large cylinders,
    with and without integration
    """

    fig = plt.figure(figsize=(12.80, 10.24))

    # conditions to define cylinders scale factor and integration flag
    conditions = [{
        'title': "Small cylinders, analytical calculations",
        'scale': 1,
        'integration': False,
        'zmin': 1e-5,
        'zmax': 1e2
    }, {
        'title': "Small cylinders, Monte-Carlo integration",
        'scale': 1,
        'integration': True,
        'zmin': 1e-5,
        'zmax': 1e2
    }, {
        'title': "Large cylinders, analytical calculations",
        'scale': 100,
        'integration': False,
        'zmin': 1e-5,
        'zmax': 1e10
    }, {
        'title': "Large cylinders, Monte-Carlo integration",
        'scale': 100,
        'integration': True,
        'zmin': 1e-5,
        'zmax': 1e10
    }]

    # run simulation 4 times and plot results
    for i_plot, condition in enumerate(conditions):
        scale = condition['scale']
        integration_flag = condition['integration']

        sample = get_sample(default_cylinder_radius*scale,
                            default_cylinder_height*scale)
        simulation = get_simulation(sample, integration_flag)
        simulation.runSimulation()
        result = simulation.result()

        # plotting results
        plt.subplot(2, 2, i_plot + 1)
        plt.subplots_adjust(wspace=0.3, hspace=0.3)

        zmin = condition['zmin']
        zmax = condition['zmax']
        ba_plot.plot_colormap(result, intensity_min=zmin, intensity_max=zmax)

        plt.text(0.0,
                 2.1,
                 conditions[i_plot]['title'],
                 horizontalalignment='center',
                 verticalalignment='center',
                 fontsize=12)
    plt.show()


if __name__ == '__main__':
    simulate_and_plot()
