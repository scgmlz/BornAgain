"""
Functional test to check slicing mechanism for spherical particles
when they are crossing an interface.
"""

from __future__ import print_function
import os, sys, unittest

import utils
import bornagain as ba
from bornagain import deg, kvector_t

mSubstrate = ba.HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8)
mAmbience = ba.HomogeneousMaterial("Air", 0.0, 0.0)

class SlicedSpheresTest(unittest.TestCase):

    def get_sample(self, particle_to_air=None, particle_to_substrate=None):
        """
        Helper function returning a multilayer (air, substrate) using particles provided
        by the user.
        """

        air_layer = ba.Layer(mAmbience)
        if particle_to_air:
            layout = ba.ParticleLayout()
            layout.addParticle(particle_to_air)
            air_layer.addLayout(layout)

        substrate = ba.Layer(mSubstrate)
        if particle_to_substrate:
            layout = ba.ParticleLayout()
            layout.addParticle(particle_to_substrate)
            substrate.addLayout(layout)

        multi_layer = ba.MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(substrate)
        return multi_layer

    def get_result(self, particle_to_air=None, particle_to_substrate=None):
        sample = self.get_sample(particle_to_air, particle_to_substrate)
        simulation = utils.get_simulation_MiniGISAS(sample)
        simulation.runSimulation()
        return simulation.result()

    def testSphericalCupOnTopOfSubstrate(self):
        """
        Compares two simulation intended to  provide identical results.
        Simulation #1: truncated sphere on top of substrate.
        Simulation #2: spherical particle crossing the interface.
        Both particles are made of same material as substrate. From scattering point of view,
        both cases should look like a truncated sphere on top of substrate.
        """

        sphere_radius = 10.0
        sphere_shift = 4.0  # shift beneath interface in absolute units

        # truncated sphere on top of substrate with height 16nm
        truncatedSphere = ba.Particle(mSubstrate, ba.FormFactorTruncatedSphere(sphere_radius, sphere_radius*2 - sphere_shift, 0))
        reference = self.get_result(truncatedSphere)

        # sphere crossing interface to look like truncated sphere above
        sphere = ba.Particle(mSubstrate, ba.FormFactorFullSphere(sphere_radius))
        sphere.setPosition(0, 0, -sphere_shift)
        data = self.get_result(sphere)

        diff = ba.RelativeDifference(data, reference)
        print(diff)
        self.assertLess(diff, 1e-10)

    def testSphericalLacuneInSubstrate(self):
        """
        Similar to previous. Truncated sphere and sphere are made of air material.
        From scattering point of view, both cases should look like an air lacune in substrate.
        """

        sphere_radius = 10.0
        sphere_shift = 4.0  # shift beneath interface in absolute units

        # Sphere truncated from top. Intended to go below interface.
        truncatedSphere = ba.Particle(mAmbience, ba.FormFactorTruncatedSphere(sphere_radius, sphere_radius*2, sphere_radius*2 - sphere_shift))
        truncatedSphere.setPosition(0, 0, -sphere_shift)
        reference = self.get_result(truncatedSphere)

        # sphere crossing interface to look like truncated sphere above
        sphere = ba.Particle(mAmbience, ba.FormFactorFullSphere(sphere_radius))
        sphere.setPosition(0, 0, -sphere_shift)
        data = self.get_result(sphere)

        diff = ba.RelativeDifference(data, reference)
        print(diff)
        self.assertLess(diff, 1e-10)

    def testSpheresCrossingInterface(self):
        """
        Compares two simulation intended to  provide identical results.
        Simulation #1: full sphere inserted in air layer to cross interface
        Simulation #2: full sphere inserted in substrate layer to cross interface
        Both spheres are made of same material.
        """
        mParticle = ba.HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)

        sphere_radius = 10.0
        sphere_shift = 4.0  # shift beneath interface in absolute units

        # Sphere intended for air layer and crossing interface
        sphere1 = ba.Particle(mParticle, ba.FormFactorFullSphere(sphere_radius))
        sphere1.setPosition(0, 0, -sphere_shift)
        reference = self.get_result(particle_to_air=sphere1)

        # Sphere intended for substrate layer and crossing interface
        sphere2 = ba.Particle(mParticle, ba.FormFactorFullSphere(sphere_radius))
        sphere2.setPosition(0, 0, -sphere_shift)
        data = self.get_result(particle_to_substrate=sphere2)

        diff = ba.RelativeDifference(data, reference)
        print(diff)
        self.assertLess(diff, 1e-10)


if __name__ == '__main__':
    unittest.main()
