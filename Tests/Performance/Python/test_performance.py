#!/usr/bin/python
 # -*- coding: utf-8 -*-

## ************************************************************************** ##
##
##  BornAgain: simulate and fit scattering at grazing incidence
##
##! @file      test_performance.py
##! @brief     Defines class TestPerformance for logging performance changes
##!            For explanations, see the README file
##!
##! @homepage  http:##www.bornagainproject.org
##! @license   GNU General Public License v3 or higher (see COPYING)
##! @copyright Forschungszentrum Jülich GmbH 2016
##! @authors   Scientific Computing Group at MLZ Garching
##! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
##
## ************************************************************************** ##

from __future__ import print_function
import datetime
import sys
import platform
import timeit
from collections import OrderedDict
import math
from libBornAgainCore import *

# used for logging intermediate output
logfile = sys.stdout

# for code readability
get_wall_time = timeit.default_timer

# for code readability and portability, since resource is not guaranteed to be available
try:
    import resource
    record_cpu_time = True
    get_cpu_time = lambda: resource.getrusage(resource.RUSAGE_SELF)[0]
except:
    record_cpu_time = False
    get_cpu_time = lambda: None


# globals used in custom form factor
phi_min, phi_max = -1.0, 1.0
alpha_min, alpha_max = 0.0, 2.0

# user-defined custom form factor
class CustomFormFactor(IFormFactorBorn):
    """
    A custom defined form factor
    The form factor is V sech(q L) with
    V volume of particle
    L length scale which defines mean radius
    """
    def __init__(self, V, L):
        IFormFactorBorn.__init__(self)
        # parameters describing the form factor
        self.V = V
        self.L = L

    def clone(self):
        """
        IMPORTANT NOTE:
        The clone method needs to call transferToCPP() on the cloned object
        to transfer the ownership of the clone to the cpp code
        """
        cloned_ff = CustomFormFactor(self.V, self.L)
        cloned_ff.transferToCPP()
        return cloned_ff

    def evaluate_for_q(self, q):
        return self.V*1.0/math.cosh(q.mag()*self.L)

# class for performance test, constructed using sample factories
class FactoryTest:
    def __init__(self, name, simulation_name, sample_builder, nrepetitions):
        self.m_test_name = name
        self.m_simulation_name = simulation_name
        self.m_sample_builder_name = sample_builder
        self.m_nrepetitions = nrepetitions
        self.m_cpu_time = 0.0
        self.m_wall_time = 0.0

        self.m_sample = None

        if simulation_name != None and sample_builder != None:
            self.m_sample_factory = SampleBuilderFactory()
            self.m_simulation_factory = SimulationFactory()
            self.m_simulation = self.m_simulation_factory.createItem(self.m_simulation_name)
            self.m_sample = self.m_sample_factory.createSample(self.m_sample_builder_name)
        else:
            self.m_sample_factory = None
            self.m_simulation_factory = None
            self.m_simulation = None
            self.m_sample = None

    def prepare(self):
        pass

    # do the actual work
    def run_loop(self):
        # actual work is done here
        for i in range(self.m_nrepetitions):
            self.m_simulation.setSample(self.m_sample)
            self.m_simulation.runSimulation()

    def run(self):

        self.prepare()

        logfile.write("Running test: %-30s " % self.m_test_name)
        logfile.flush()

        # resource.getrusage is less accurate but returns user (cpu) time
        start_wall_time = get_wall_time()
        start_cpu_time = get_cpu_time()

        self.run_loop()

        end_wall_time = get_wall_time()
        end_cpu_time = get_cpu_time()

        # note that on multi-core system, cpu time can be higher than wall time
        self.m_wall_time = end_wall_time - start_wall_time

        if record_cpu_time:
            self.m_cpu_time = end_cpu_time - start_cpu_time
            logfile.write("OK: %-6.3f (wall sec), %-6.3f (cpu sec) \n" % (self.m_wall_time, self.m_cpu_time))
        else:
            logfile.write("OK: %-6.3f (wall sec)\n" % (self.m_wall_time))



# special performance test case: custom form factor
class CustomTest(FactoryTest):
    def __init__(self, name, nrepetitions):
        FactoryTest.__init__(self, name, None, None, nrepetitions)
        self.m_sample = None
        self.m_simulation = None

    def prepare(self):
        self.m_sample = self.get_sample()
        self.m_simulation = self.get_simulation()

    # do the actual work
    def run_loop(self):
        for i in range(self.m_nrepetitions):
            self.m_simulation.setSample(self.m_sample)
            self.m_simulation.runSimulation()

    def get_sample(self):
        """
        Build and return the sample to calculate custom form factor in Distorted Wave Born Approximation.
        """
        # defining materials
        m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
        m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
        m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

        # collection of particles
        ff = CustomFormFactor(343.0*nanometer, 7.0*nanometer)
        particle = Particle(m_particle, ff)
        particle_layout = ParticleLayout()
        particle_layout.addParticle(particle, 1.0)
        air_layer = Layer(m_ambience)
        air_layer.addLayout(particle_layout)
        substrate_layer = Layer(m_substrate)

        # assemble multilayer
        multi_layer = MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(substrate_layer)
        return multi_layer

    def get_simulation(self):
        """
        Create and return GISAXS simulation with beam and detector defined
        IMPORTANT NOTE:
        Multithreading should be deactivated by putting ThreadInfo.n_threads to -1
        """
        simulation = GISASSimulation()
        simulation.getOptions().setNumberOfThreads(-1)
        simulation.setDetectorParameters(100, phi_min*degree, phi_max*degree, 100, alpha_min*degree, alpha_max*degree)
        simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
        return simulation


# class for running all of the tests and collecting results
class PerformanceTests:
    def __init__(self, filename=None):
        self.m_tests = []
        self.m_datime = ""
        self.m_hostname = ""
        self.m_sysinfo = ""
        self.m_pyversion = ""
        self.m_filename = filename

        self.add("MultiLayer",         "MaxiGISAS",    "MultiLayerWithRoughnessBuilder", 1)
        self.add("CylindersInDWBA",    "MaxiGISAS",    "CylindersInDWBABuilder", 10)
        self.add("RotatedPyramids",    "MaxiGISAS",    "RotatedPyramidsBuilder", 10)
        self.add("CoreShell",          "MaxiGISAS",    "CoreShellParticleBuilder", 10)
        self.add("SquareLattice",      "MaxiGISAS",    "SquareLatticeBuilder", 10)
        self.add("RadialParaCrystal",  "MaxiGISAS",    "RadialParaCrystalBuilder", 10)
        self.add("HexParaCrystal",     "BasicGISAS",   "HexParaCrystalBuilder", 1)
        self.add("SSCA",               "MaxiGISAS",    "SizeDistributionSSCAModelBuilder", 10)
        self.add("Mesocrystal",        "MaxiGISAS",    "MesoCrystalBuilder", 2)
        self.add("PolMagCyl",          "MaxiGISAS00",  "MagneticCylindersBuilder", 10)

        # custom form factor is a special case since it's not in the registry
        self.m_tests.append(CustomTest("Custom FF", 10))

        logfile.write("\nPreparing to run %d performance tests.\n\n" % len(self.m_tests))

    def add(self, name, simulation_name, sample_builder, nrepetitions):
        self.m_tests.append(FactoryTest(name, simulation_name, sample_builder, nrepetitions))

    # execute all performance tests
    def execute(self):
        self.init_sysinfo()
        for test in self.m_tests: test.run()
        self.write_results()


    # write out system information and test results to file
    def write_results(self):

        if ( self.m_filename != None ):
            try:
                write_file = open(self.m_filename, "a")
            except:
                sys.stderr.write("Could not open filed '%' for writing. Writing to stdout instead.\n" % self.m_filename)
                write_file = sys.stdout
                self.m_filename = None

        else:
            write_file = sys.stdout

        logfile.write("\nWriting output to %s...\n\n" % write_file.name)

        # record results into an ordered dict, which is used by pretty_write() below
        dictionary = OrderedDict()

        dictionary["date"] = self.m_datime
        dictionary["hostname"] = self.m_hostname
        dictionary["sysinfo"] = self.m_sysinfo
        dictionary["python"] = self.m_pyversion

        sum_wall = 0.0
        sum_cpu = 0.0

        for test in self.m_tests:
            sum_wall += test.m_wall_time
            sum_cpu += test.m_cpu_time

        if record_cpu_time: dictionary["total cpu"] = "%-.4f" % sum_cpu
        dictionary["total wall"] = "%-.4f" % sum_wall

        for test in self.m_tests:
            dictionary[test.m_test_name] = "%-.4f" % test.m_wall_time

        write_file.write("\n")
        pretty_write(dictionary, write_file)
        write_file.write("\n")
        write_file.flush()

        if ( self.m_filename != None ):
            write_file.close()

    # determine platform, architecture, python version, etc.
    def init_sysinfo(self):
        system, node, release, version, machine, processor = platform.uname()
        self.m_datime = datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d %H:%M:%S')
        self.m_hostname = node
        self.m_sysinfo = "%s %s" % (system, machine)
        self.m_pyversion = "%d.%d" % (sys.version_info[:2])

# used for writing the summary with proper formatting
def pretty_write(dictionary, file):
    header = "|"
    footer = "|"

    for key in dictionary:
        value = dictionary[key]
        length = max(len(key), len(value))
        format_str = " {0:" + str(length) + "} |"
        header += format_str.format(key)
        footer += format_str.format(value)

    file.write(header + "\n")
    file.write(footer + "\n")

if __name__ == '__main__':

    if ( len(sys.argv) > 2 ):
        print("Usage: test_performance.py [output file]")
        exit(0)

    if (len(sys.argv) == 2):
        filename = sys.argv[1]
    else:
        filename = None

    tests = PerformanceTests(filename)
    tests.execute()
