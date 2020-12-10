"""
Testing python specific API for Minimizer related classes.
"""
import sys
import os
import unittest
import bornagain as ba


class TestMinimizerHelper:
    def __init__(self):
        self.m_ncalls = 0
        self.m_pars = None

    def objective_function(self, pars):
        self.m_ncalls += 1
        self.m_pars = pars
        return 42.0


class MinimizerAPITest(unittest.TestCase):
    def test_ParameterAttribute(self):
        """
        Testing p.value attribute
        """
        par = ba.Parameter("par", 1.0)
        self.assertEqual(par.value, 1.0)
        par.value = 42.0
        self.assertEqual(par.value, 42.0)

    def test_ParametersSetIterator(self):
        """
        Testing of python iterator over defined fit parameters.
        """

        pars = ba.Parameters()
        self.assertEqual(pars.size(), 0)

        pars.add(ba.Parameter("par0", 1.0, ba.AttLimits.limitless()))
        pars.add(ba.Parameter("par1", 2.0, ba.AttLimits.limitless()))
        expected_names = ["par0", "par1"]
        for index, p in enumerate(pars):
            self.assertEqual(p.name(), expected_names[index])

    def test_ParametersAdd(self):
        """
        Testing Parameters::add method
        """

        params = ba.Parameters()
        params.add("par0", 0.0)
        params.add("par1", 1.0, min=1.0)
        params.add("par2", 2.0, max=2.0)
        params.add("par3", 3.0, min=1.0, max=2.0)
        params.add("par4", 4.0, vary=False)

        self.assertTrue(params["par0"].limits().isLimitless())
        self.assertTrue(params["par1"].limits().isLowerLimited())
        self.assertEqual(params["par1"].limits().lowerLimit(), 1.0)
        self.assertTrue(params["par2"].limits().isUpperLimited())
        self.assertEqual(params["par2"].limits().upperLimit(), 2.0)

        self.assertTrue(params["par3"].limits().isLimited())
        self.assertEqual(params["par3"].limits().lowerLimit(), 1.0)
        self.assertEqual(params["par3"].limits().upperLimit(), 2.0)

        self.assertTrue(params["par4"].limits().isFixed())

    def test_SimpleMinimizer(self):
        minimizer = ba.Minimizer()
        minimizer.setMinimizer("Test")

        pars = ba.Parameters()
        pars.add(ba.Parameter("par0", 0.0))
        pars.add(ba.Parameter("par1", 1.0))
        pars.add(ba.Parameter("par2", 2.0))

        helper = TestMinimizerHelper()
        result = minimizer.minimize(helper.objective_function, pars)

        # return value of objective function was propagated to MinimizerResult
        self.assertEqual(result.minValue(), 42.0)

        # objective function was called twice
        #(once by test minimizer, and second time during return type deduction)
        self.assertEqual(helper.m_ncalls, 2)

        # starting values of fit parameters were correctly send to objective func
        self.assertEqual(list(helper.m_pars.values()), [0.0, 1.0, 2.0])


if __name__ == '__main__':
    unittest.main()
