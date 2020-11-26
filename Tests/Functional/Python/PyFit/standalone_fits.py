"""
Fitting scalar and residual based objective functions
"""
import sys
import os
import unittest

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba
import numpy as np


class Rosenbrock:
    def __init__(self):
        self.m_expected_minimum = 0.0
        self.m_expected_params = [1.0, 1.0]
        pass

    def objective_function(self, params):
        """
        Returns the value of Rosenbrock function
        """
        x = params["x"].value
        y = params["y"].value
        tmp1 = y - x*x
        tmp2 = 1 - x
        return 100*tmp1*tmp1 + tmp2*tmp2


def decaying_sin(params, x):
    amp = params['amp'].value
    phaseshift = params['phase'].value
    freq = params['frequency'].value
    decay = params['decay'].value
    return amp*np.sin(x*freq + phaseshift)*np.exp(-x*x*decay)


class DecayingSin:
    def __init__(self):
        self.m_x = np.linspace(0.0, 10.0, 100)
        self.m_params = ba.Parameters()
        self.m_params.add(ba.Parameter('amp', 10.0))
        self.m_params.add(ba.Parameter('decay', 0.05))
        self.m_params.add(ba.Parameter('phase', 1.0))
        self.m_params.add(ba.Parameter('frequency', 4.0))
        self.m_eps_data = np.linspace(0.0, 10.0, 100)
        self.m_eps_data.fill(0.01)
        self.m_data = decaying_sin(self.m_params, self.m_x)

    def objective_function(self, params):
        model = decaying_sin(params, self.m_x)
        return (self.m_data - model)/self.m_eps_data


class StandaloneFitTest(unittest.TestCase):
    def test_RosenbrockFit(self):
        """
        Testing fit of rosenbrock function
        """
        params = ba.Parameters()
        params.add(
            ba.Parameter("x", -1.2, ba.AttLimits.limited(-5.0, 5.0), 0.01))
        params.add(ba.Parameter("y", 1.0, ba.AttLimits.limited(-5.0, 5.0),
                                0.01))

        model = Rosenbrock()
        minimizer = ba.Minimizer()
        result = minimizer.minimize(model.objective_function, params)

        print(result.toString())

        # check found parameter values
        np.testing.assert_almost_equal(result.parameters().values(),
                                       model.m_expected_params, 3)

        # check found minimum
        np.testing.assert_almost_equal(result.minValue(),
                                       model.m_expected_minimum, 3)

    def test_DecayingSinFit(self):
        params = ba.Parameters()
        params.add(ba.Parameter('amp', 1, ba.AttLimits.positive()))
        params.add(ba.Parameter('decay', 0.1, ba.AttLimits.positive()))
        params.add(ba.Parameter('phase', 0.1, ba.AttLimits.limited(0.0, 3.1)))
        params.add(ba.Parameter('frequency', 1.0, ba.AttLimits.positive()))

        model = DecayingSin()
        minimizer = ba.Minimizer()
        result = minimizer.minimize(model.objective_function, params)

        print(result.toString())

        # check found parameter values
        np.testing.assert_almost_equal(result.parameters().values(),
                                       model.m_params.values(), 3)


if __name__ == '__main__':
    unittest.main()
