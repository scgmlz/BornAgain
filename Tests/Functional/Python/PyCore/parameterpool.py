import numpy, os, sys, unittest

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba
from bornagain import nm


class ParameterPoolTest(unittest.TestCase):

    def test_parameterPoolAccess(self):
        """
        Checks values in particle's parameter pool
        """
        ff = ba.FormFactorCylinder(5*nm, 6*nm)
        particle = ba.Particle(ba.HomogeneousMaterial("Vacuum", 0.0, 0.0), ff)
        particle.setAbundance(1.0)
        particle.setPosition(2.0, 3.0, 4.0)

        # print(particle.parametersToString())
        # print(particle.treeToString())

        pool = particle.parameterPool()
        self.assertEqual(pool.size(), 4)
        self.assertEqual(pool.parameterNames(), ('Abundance', 'PositionX', 'PositionY', 'PositionZ'))

        expected = {'Abundance': 1.0, 'PositionX': 2.0, 'PositionY': 3.0, 'PositionZ': 4.0}
        for par in pool:
            print(par.value(), par.getName(), par.limits().toString())
            self.assertEqual(par.value(), expected[par.getName()])

    def test_parameterPoolModify(self):
        """
        Modification of particle parameters via parameter pool
        """
        ff = ba.FormFactorCylinder(5*nm, 6*nm)
        particle = ba.Particle(ba.HomogeneousMaterial("Vacuum", 0.0, 0.0), ff)
        particle.setAbundance(1.0)
        particle.setPosition(2.0, 3.0, 4.0)

        pool = particle.parameterPool()
        pool.setParameterValue('Abundance', 10.0)
        pool[1].setValue(20.0)  # PositionX
        pool.parameter('PositionY').setValue(30.0)

        expected = {'Abundance': 10.0, 'PositionX': 20.0, 'PositionY': 30.0, 'PositionZ': 4.0}

        for par in pool:
            self.assertEqual(par.value(), expected[par.getName()])

    def test_parameterTreeAccess(self):
        """
        Checks values in particle's parameter tree. Parameter tree is a pool with parameters of
        particle and its children (in given case, form factor of cylinder)
        """
        ff = ba.FormFactorCylinder(5*nm, 6*nm)
        particle = ba.Particle(ba.HomogeneousMaterial("Vacuum", 0.0, 0.0), ff)
        particle.setAbundance(1.0)
        particle.setPosition(2.0, 3.0, 4.0)

        pool = particle.createParameterTree()

        expected = {'/Particle/Abundance': 1.0, '/Particle/PositionX': 2.0,
                    '/Particle/PositionY': 3.0, '/Particle/PositionZ': 4.0,
                    '/Particle/Cylinder/Radius': 5.0, '/Particle/Cylinder/Height': 6.0}

        for par in pool:
            self.assertEqual(par.value(), expected[par.getName()])

    def test_parameterTreeModify(self):
        """
        Modifies values of particle's parameter tree.
        """
        ff = ba.FormFactorCylinder(5*nm, 6*nm)
        particle = ba.Particle(ba.HomogeneousMaterial("Vacuum", 0.0, 0.0), ff)
        particle.setAbundance(1.0)
        particle.setPosition(2.0, 3.0, 4.0)

        # print(particle.parametersToString())
        # print(particle.treeToString())

        pool = particle.createParameterTree()
        pool.setParameterValue('/Particle/Abundance', 10.0)
        pool[1].setValue(20.0)  # PositionX
        pool.parameter('/Particle/PositionY').setValue(30.0)
        pool.setMatchedParametersValue('*Cylinder*', 50.0)

        expected = {'/Particle/Abundance': 10.0, '/Particle/PositionX': 20.0,
                    '/Particle/PositionY': 30.0, '/Particle/PositionZ': 4.0,
                    '/Particle/Cylinder/Radius': 50.0, '/Particle/Cylinder/Height': 50.0}

        for par in pool:
            self.assertEqual(par.value(), expected[par.getName()])

    def test_parameterModify(self):
        """
        Modification of particle's parameters without intermediate access to parameter pool
        """
        ff = ba.FormFactorCylinder(5*nm, 6*nm)
        particle = ba.Particle(ba.HomogeneousMaterial("Vacuum", 0.0, 0.0), ff)
        particle.setAbundance(1.0)
        particle.setPosition(2.0, 3.0, 4.0)

        particle.setParameterValue('/Particle/Abundance', 10.0)
        particle.setParameterValue('PositionZ', 40.0)
        particle.setParameterValue('*Cylinder*', 50.0)

        self.assertEqual(particle.abundance(), 10.0)
        self.assertEqual(particle.position().z(), 40.0)


if __name__ == '__main__':
    unittest.main()
