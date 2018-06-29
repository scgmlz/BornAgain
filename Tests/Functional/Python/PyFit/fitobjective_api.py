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
        self.m_pars = pars

        ml = ba.MultiLayer()
        material = ba.HomogeneousMaterial("Shell", 0.0, 0.0)
        ml.addLayer(ba.Layer(material))
        ml.addLayer(ba.Layer(material))

        simulation = ba.GISASSimulation(ml)
        simulation.setDetectorParameters(self.m_ncol, 0.0, 1.0, self.m_nrow, 0.0, 1.0)
        return simulation

    def create_data(self):
        return np.full((self.m_nrow, self.m_ncol), 1, dtype=np.float64)



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
        self.assertEqual(list(builder.m_pars.values()), [0.0, 1.0])

        # checking arrays of experimental and simulated data
        expected_sim = np.full((builder.size()), 0, dtype=np.float64).tolist()
        expected_data = np.full((builder.size()), 1, dtype=np.float64).tolist()
        self.assertEqual(expected_sim, list(objective.simulation_array()))
        self.assertEqual(expected_data, list(objective.experimental_array()))



if __name__ == '__main__':
    unittest.main()
