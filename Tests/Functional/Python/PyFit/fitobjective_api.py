"""
Testing python specific API for FitObjective related classes.
"""
import sys
import os
import unittest
import numpy as np

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba


class SimulationBuilder:
    def __init__(self):
        self.m_ncalls = 0
        self.m_pars = None
        self.m_nrow = 3
        self.m_ncol = 4

    def size(self):
        return self.m_nrow*self.m_ncol

    def build_simulation(self, pars):
        self.m_ncalls += 1
        self.m_pars = dict(pars)

        ml = ba.MultiLayer()
        material = ba.HomogeneousMaterial("Shell", 0.0, 0.0)
        ml.addLayer(ba.Layer(material))
        ml.addLayer(ba.Layer(material))

        simulation = ba.GISASSimulation()
        simulation.setSample(ml)
        simulation.setDetectorParameters(self.m_ncol, 0.0, 1.0, self.m_nrow, 0.0, 1.0)
        return simulation

    def create_data(self):
        return np.ones(shape=(self.m_nrow, self.m_ncol), dtype=np.float64)


class FitObserver:
    def __init__(self):
        self.m_ncalls = 0
        self.m_iterations = []

    def update(self, fit_objective):
        self.m_ncalls += 1
        self.m_iterations.append(fit_objective.iterationInfo().iterationCount())


class FitObjectiveAPITest(unittest.TestCase):

    def test_SimulationBuilderCallback(self):
        """
        Testing simulation construction using Python callback
        """
        pars = ba.Parameters()
        pars.add(ba.Parameter("par0", 0.0))
        pars.add(ba.Parameter("par1", 1.0))

        builder = SimulationBuilder()
        data = builder.create_data()

        # adding simulation callback and experimental data
        objective = ba.FitObjective()
        objective.addSimulationAndData(builder.build_simulation, data, 1.0)
        self.assertEqual(builder.m_ncalls, 0)
        self.assertEqual(objective.numberOfFitElements(), 0)

        # running objective function
        objective.evaluate(pars)
        self.assertEqual(builder.m_ncalls, 1)
        self.assertEqual(objective.numberOfFitElements(), builder.size())
        self.assertEqual(builder.m_pars["par0"], 0.0)
        self.assertEqual(builder.m_pars["par1"], 1.0)

        # checking arrays of experimental and simulated data
        expected_sim = []
        expected_data=[]
        for i in range(0, builder.size()):
            expected_sim.append(0.0)
            expected_data.append(1.0)
        self.assertEqual(expected_sim, list(objective.simulation_array()))
        self.assertEqual(expected_data, list(objective.experimental_array()))

    def test_FittingObserver(self):
        """
        Testing simulation construction using Python callback
        """
        pars = ba.Parameters()
        pars.add(ba.Parameter("par0", 0.0))
        pars.add(ba.Parameter("par1", 1.0))

        # adding simulation callback and experimental data
        builder = SimulationBuilder()
        data = builder.create_data()
        objective = ba.FitObjective()
        objective.addSimulationAndData(builder.build_simulation, data, 1.0)

        # adding observer
        observer = FitObserver()
        objective.initPlot(5, observer.update)

        # running objective function 11 times
        for i in range(0, 11):
            objective.evaluate(pars)

        self.assertEqual(observer.m_ncalls, 3)
        self.assertEqual(observer.m_iterations, [1, 6, 11])

    def test_IterationInfo(self):
        """
        Testing map of parameters obtained from IterationInfo
        """

        params = ba.Parameters()
        params.add("bbb", 1.0)
        params.add("aaa", 2.0)

        info = ba.IterationInfo()
        info.update(params, 3.0)
        par_map = info.parameterMap()

        expected_names = ["aaa", "bbb"]
        expected_values = [2.0, 1.0]
        names = []
        values = []
        for key in par_map:
            names.append(key)
            values.append(par_map[key])

        self.assertEqual(names, expected_names)
        self.assertEqual(values, expected_values)
        self.assertEqual(info.iterationCount(), 1)


if __name__ == '__main__':
    unittest.main()
