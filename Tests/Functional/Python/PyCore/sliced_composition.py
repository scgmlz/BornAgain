"""
Functional test to check slicing mechanism for particle compositions
when they are crossing an interface.
"""

from __future__ import print_function
import os, sys, unittest

import utils
import bornagain as ba
from bornagain import deg, kvector_t, nm

mSubstrate = ba.HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8)
mAmbience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
mParticle = ba.HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)
sphere_radius = 10.0
bottom_cup_height = 4.0


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

    def get_composition(self, top_material, bottom_material):
        """
        Returns particle composition representing sphere made of two different materials.
        Origin of new object is at the bottom of resulting sphere.
        """

        topCup = ba.Particle(top_material, ba.FormFactorTruncatedSphere(sphere_radius, sphere_radius*2 - bottom_cup_height, 0))
        bottomCup = ba.Particle(bottom_material, ba.FormFactorTruncatedSphere(sphere_radius, sphere_radius*2, sphere_radius*2 - bottom_cup_height))

        #  origin of resulting sphere will be at the bottom
        result = ba.ParticleComposition()
        result.addParticle(topCup, kvector_t(0.0, 0.0, bottom_cup_height))
        result.addParticle(bottomCup, kvector_t(0.0, 0.0, 0.0))

        return result

    def get_composition_v2(self, top_material, bottom_material):
        """
        Returns particle composition representing sphere made of two different materials.
        Alternative to previous method.
        Rotation is used to get bottom part
        """

        topCup = ba.Particle(top_material, ba.FormFactorTruncatedSphere(sphere_radius, sphere_radius*2 - bottom_cup_height, 0))
        bottomCup = ba.Particle(bottom_material, ba.FormFactorTruncatedSphere(sphere_radius, bottom_cup_height, 0))
        bottomCup.setRotation(ba.RotationX(180*deg))

        #  origin of resulting sphere will be at the bottom
        result = ba.ParticleComposition()
        result.addParticle(topCup, kvector_t(0.0, 0.0, bottom_cup_height))
        result.addParticle(bottomCup, kvector_t(0.0, 0.0, bottom_cup_height))

        return result

    def testComposition(self):
        """
        Compares two simulation intended to  provide identical results.
        Simulation #1: spherical particle on top of substrate
        Simulation #2: spherical composition on top of substrate, where top and bottom are made of same material
        """

        # spherical particle
        sphere = ba.Particle(mParticle, ba.FormFactorFullSphere(sphere_radius))
        reference = self.get_result(sphere)

        # spherical composition
        composition = self.get_composition(mParticle, mParticle)
        data = self.get_result(composition)

        diff = ba.RelativeDifference(data, reference)
        print(diff)
        self.assertLess(diff, 1e-10)

    def testCompositionBuilds(self):
        """
        Compares two simulation intended to  provide identical results.
        Simulation #1: spherical particle composition on top of substrate
        Simulation #2: same, but made using rotation
        """

        composition = self.get_composition(mParticle, mSubstrate)
        reference = self.get_result(composition)

        # spherical composition
        composition2 = self.get_composition_v2(mParticle, mSubstrate)
        data = self.get_result(composition2)

        diff = ba.RelativeDifference(data, reference)
        print(diff)
        self.assertLess(diff, 1e-10)


    def testInvisibleComposition(self):
        """
        Compares two simulation intended to  provide identical results.
        Simulation #1: no particles at all
        Simulation #2: spherical composition on top of substrate crossing the interface
        Bottom part of composition is made of substrate material, top part from air layer material
        """

        shift = bottom_cup_height

        # Scattering from empty multilayer
        reference = self.get_result()

        # spherical composition
        composition = self.get_composition(mAmbience, mSubstrate)
        composition.setPosition(0, 0, -shift)
        data = self.get_result(composition)

        diff = ba.RelativeDifference(data, reference)
        print(diff)
        self.assertLess(diff, 1e-10)

    def testSlicedComposition(self):
        """
        Compares two simulation intended to  provide identical results.
        Simulation #1: spherical particle on top of substrate
        Simulation #2: spherical composition on top of substrate, where top and bottom are made of same material
        Both particles are inserted in air layer with shift to go below interface
        """

        shift = 3*nm

        # spherical particle
        sphere = ba.Particle(mParticle, ba.FormFactorFullSphere(sphere_radius))
        sphere.setPosition(0, 0, -shift)
        reference = self.get_result(sphere)

        # spherical composition
        composition = self.get_composition(mParticle, mParticle)
        composition.setPosition(0, 0, -shift)
        data = self.get_result(composition)

        diff = ba.RelativeDifference(data, reference)
        print(diff)
        self.assertLess(diff, 1e-10)

    def testSphericalCupOnTopOfSubstrate(self):
        """
        Compares two simulation intended to  provide identical results.
        Simulation #1: truncated sphere on top of substrate.
        Simulation #2: spherical particle composition crossing the interface.
        Bottom part of composition is made from substrate material.
        both cases should look like a truncated sphere on top of substrate.
        """

        # truncated sphere on top of substrate with height 16nm
        truncatedSphere = ba.Particle(mParticle, ba.FormFactorTruncatedSphere(sphere_radius, sphere_radius*2 - bottom_cup_height, 0))
        reference = self.get_result(truncatedSphere)

        # Particle composition, top part made of same material, as particle. Bottom part made of same material as substrate.
        composition = self.get_composition(mParticle, mSubstrate)

        composition_shift = bottom_cup_height
        composition.setPosition(0, 0, -composition_shift)
        data = self.get_result(composition)

        diff = ba.RelativeDifference(data, reference)
        print(diff)
        self.assertLess(diff, 1e-10)


if __name__ == '__main__':
    unittest.main()
