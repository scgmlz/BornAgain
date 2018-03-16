# Mixture of cylinders and prisms without interference (IsGISAXS example ex-1)

from mpi4py import MPI # this line has to be first
import numpy
import matplotlib
import pylab
from libBornAgainCore import *

comm = MPI.COMM_WORLD
world_size = comm.Get_size()
world_rank = comm.Get_rank()


def get_sample():
    """
    Build and return the sample representing cylinders and pyramids on top of
    substrate without interference.
    """
    # defining materials
    m_air = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(m_particle, cylinder_ff)
    prism_ff = FormFactorPrism3(10*nanometer, 5*nanometer)
    prism = Particle(m_particle, prism_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 0.5)
    particle_layout.addParticle(prism, 0.5)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(m_air)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    sample = get_sample()
    simulation.setSample(sample)

    return simulation


def run_simulation():
    """
    Run simulation and plot results
    """
    simulation = get_simulation()

    if(world_size == 1):
        print("Not a MPI environment, run with 'mpirun -n 4 python ompi_sim_example.py'")
        exit(0)

    if(world_rank != 0):
        options = simulation.getOptions()
        thread_info = ThreadInfo()
        thread_info.n_threads = options.getNumberOfThreads()
        thread_info.n_batches = world_size - 1
        thread_info.current_batch = world_rank - 1
        options.setThreadInfo(thread_info)
        simulation.setOptions(options)
        print("preparing to run ", thread_info.n_batches, thread_info.current_batch)
        simulation.runSimulation()
        print("preparing to send")
        comm.Send(simulation.result().array(), 0)

    if(world_rank == 0):
        sumresult = simulation.result().array()
        print(sumresult)
        sumresult = numpy.zeros(sumresult.shape)
        print(sumresult)

        print("preparing to receive")
        for i_proc in range(1, world_size):
            print("  ... receiving", i_proc)
            result = numpy.zeros(sumresult.shape)
            comm.Recv(result, i_proc)
            sumresult += result
        print(sumresult)

    if(world_rank == 0):
        print(sumresult)
        # pylab.imshow(sumresult + 1, norm=matplotlib.colors.LogNorm(), extent=[-1.0, 1.0, 0, 2.0])
        # pylab.show()


if __name__ == '__main__':
    run_simulation()



