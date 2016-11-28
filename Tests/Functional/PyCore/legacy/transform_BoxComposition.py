"""
BornAgain functional test.
Test of rotation/position of particle composition.
The composition consists of two boxes made of the same material.
It is compared against reference single box made of the same material.
Composition might be rotated to get reference shape.
Both, reference box and composition are placed in the center of middle layer of 3 layers system.
"""

from __future__ import print_function
import os, sys, unittest

import utils
from libBornAgainCore import *

layer_thickness = 100.0
comp_length = 50.0
comp_width = 20.0
comp_height = 10.0
particle_material = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)

class TransformBoxCompositionTest(unittest.TestCase):

    def get_sample(self, particle):
        mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
        mMiddle= HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9)
        mSubstrate = HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8)

        layout = ParticleLayout()
        layout.addParticle(particle)

        air_layer = Layer(mAmbience)
        middle_layer = Layer(mMiddle, layer_thickness)
        # air_layer.addLayout(layout)
        middle_layer.addLayout(layout)
        substrate = Layer(mSubstrate)

        multi_layer = MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(middle_layer)
        multi_layer.addLayer(substrate)
        return multi_layer

    def get_intensity_data(self, particle):
        sample = self.get_sample(particle)
        simulation = utils.get_simulation_MiniGISAS(sample)
        simulation.runSimulation()
        return simulation.getIntensityData()

    def test_BoxComposition(self):
        """
        Compares simple box with the one composed from two smaller boxes of the same material to get same size
        """
        # reference box
        length = 50.0
        width = 20.0
        height = 10.0
        particle = Particle(particle_material, FormFactorBox(length, width, height))
        particle.setPosition(kvector_t(0, 0, -layer_thickness/2.0 - height/2.0))

        reference_data = self.get_intensity_data(particle)
        #IntensityDataIOFactory.writeIntensityData(reference_data, "ref_BoxComposition.int")

        # composition
        box = Particle(particle_material, FormFactorBox(comp_length/2.0, comp_width, comp_height))
        composition = ParticleComposition()
        # composition = ParticleComposition(box, positions)
        composition.addParticle(box, kvector_t(0.0, 0.0, 0.0))
        composition.addParticle(box, kvector_t(comp_length/2.0, 0.0, 0.0))
        composition.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0 - comp_height/2.0))

        data = self.get_intensity_data(composition)

        diff = getRelativeDifference(data, reference_data)
        print("test_BoxComposition:", diff)
        self.assertLess(diff, 1e-10)
        # utils.plot_intensity_data(reference_data)

    def test_BoxCompositionRotateX(self):
        """
        Compares simple box with the one composed from two smaller boxes of the same material to get same size.
        Composed box is rotated around X, to get same orientation as the original box.
        """
        # reference box
        length = 50.0
        width = 10.0
        height = 20.0
        particle = Particle(particle_material, FormFactorBox(length, width, height))
        particle.setPosition(kvector_t(0, 0, -layer_thickness/2.0 - height/2.0))

        reference_data = self.get_intensity_data(particle)
        #IntensityDataIOFactory.writeIntensityData(reference_data, "ref_BoxCompositionRotateX.int")

        # composition
        box = Particle(particle_material, FormFactorBox(comp_length/2.0, comp_width, comp_height))
        composition = ParticleComposition()
        composition.addParticle(box, kvector_t(0.0, 0.0, 0.0))
        composition.addParticle(box, kvector_t(comp_length/2.0, 0.0, 0.0))
        composition.setRotation(RotationX(90*deg))
        composition.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.))

        data = self.get_intensity_data(composition)

        diff = getRelativeDifference(data, reference_data)
        print("test_BoxCompositionRotateX:", diff)
        self.assertLess(diff, 1e-10)

    def test_BoxCompositionRotateY(self):
        """
        Compares simple box with the one composed from two smaller boxes of the same material to get same size.
        Composed box is rotated around Y, to get same orientation as the original box.
        """
        # reference box
        length = 10.0
        width = 20.0
        height = 50.0
        particle = Particle(particle_material, FormFactorBox(length, width, height))
        particle.setPosition(kvector_t(0, 0, -layer_thickness/2.0 - height/2.0))

        reference_data = self.get_intensity_data(particle)
        #IntensityDataIOFactory.writeIntensityData(reference_data, "ref_BoxCompositionRotateY.int")

        # composition
        box = Particle(particle_material, FormFactorBox(comp_length/2.0, comp_width, comp_height))
        composition = ParticleComposition()
        composition.addParticle(box, kvector_t(0.0, 0.0, 0.0))
        composition.addParticle(box, kvector_t(comp_length/2.0, 0.0, 0.0))
        composition.setRotation(RotationY(90*deg))
        composition.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2. + comp_length/4.))

        data = self.get_intensity_data(composition)

        diff = getRelativeDifference(data, reference_data)
        print("test_BoxCompositionRotateY:", diff)
        self.assertLess(diff, 1e-10)

    def test_BoxCompositionRotateZ(self):
        """
        Compares simple box with the one composed from two smaller boxes of the same material to get same size.
        Composed box is rotated around Z, to get same orientation as the original box.
        """
        # reference box
        length = 20.0
        width = 50.0
        height = 10.0
        particle = Particle(particle_material, FormFactorBox(length, width, height))
        particle.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0 - height/2.0))

        reference_data = self.get_intensity_data(particle)
        #IntensityDataIOFactory.writeIntensityData(reference_data, "ref_BoxCompositionRotateZ.int")

        # composition
        box = Particle(particle_material, FormFactorBox(comp_length/2.0, comp_width, comp_height))
        composition = ParticleComposition()
        composition.addParticle(box, kvector_t(0.0, 0.0, 0.0))
        composition.addParticle(box, kvector_t(comp_length/2.0, 0.0, 0.0))
        composition.setRotation(RotationZ(90*deg))
        composition.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0 - comp_height/2.0))

        data = self.get_intensity_data(composition)

        diff = getRelativeDifference(data, reference_data)
        print("test_BoxCompositionRotateZ:", diff)
        self.assertLess(diff, 1e-10)

    def test_BoxCompositionRotateZandY(self):
        """
        Compares simple box with the one composed from two smaller boxes of the same material to get same size.
        Composed box is rotated around Y, to get same orientation as the original box.
        """
        # reference box
        length = 10.0
        width = 50.0
        height = 20.0
        particle = Particle(particle_material, FormFactorBox(length, width, height))
        particle.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0 - height/2.0))

        reference_data = self.get_intensity_data(particle)
        #IntensityDataIOFactory.writeIntensityData(reference_data, "ref_BoxCompositionRotateZandY.int")

        # composition
        box = Particle(particle_material, FormFactorBox(comp_length/2.0, comp_width, comp_height))
        composition = ParticleComposition()
        composition.addParticle(box, kvector_t(0.0, 0.0, 0.0))
        composition.addParticle(box, kvector_t(comp_length/2.0, 0.0, 0.0))
        composition.setRotation(RotationZ(90*deg))
        composition.applyRotation(RotationY(90*deg))
        composition.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.))

        data = self.get_intensity_data(composition)

        diff = getRelativeDifference(data, reference_data)
        print("test_BoxCompositionRotateZandY:", diff)
        self.assertLess(diff, 1e-10)

    def test_BoxStackComposition(self):
        """
        2 different boxes are first rotated and then combined into the composition. Composition is then rotated.
        Composition is compared against reference box.
        """
        # reference box
        length = 10.0
        width = 20.0
        height = 50.0
        particle = Particle(particle_material, FormFactorBox(length, width, height))
        particle.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0 - height/2.0))
        reference_data = self.get_intensity_data(particle)
        #IntensityDataIOFactory.writeIntensityData(reference_data, "ref_BoxStackComposition.int")

        # composition
        composition = ParticleComposition()

        # box1 (20,50,5), rotatedZ
        box1_length = 20.0
        box1_width = 50.0
        box1_height = 5.0
        box1 = Particle(particle_material, FormFactorBox(box1_length, box1_width, box1_height))
        box1.setRotation(RotationZ(90*deg))

        # box2 (5,20,50), rotatedY
        box2_length = 5.0
        box2_width = 20.0
        box2_height = 50.0
        box2 = Particle(particle_material, FormFactorBox(box2_length, box2_width, box2_height))
        box2.setRotation(RotationY(90*deg))
        box2.setPosition(kvector_t(-box2_height/2.0, 0.0, box2_length/2.0))

        composition.addParticle(box1, kvector_t(0.0, 0.0, 0.0))
        composition.addParticle(box2, kvector_t(0.0, 0.0, box1_height))
        composition.setRotation(RotationY(90*deg))
        composition.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.))

        data = self.get_intensity_data(composition)

        diff = getRelativeDifference(data, reference_data)
        print("test_BoxStackComposition:", diff)
        self.assertLess(diff, 1e-10)


if __name__ == '__main__':
    unittest.main()
