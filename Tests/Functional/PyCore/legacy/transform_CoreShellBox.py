"""
BornAgain functional test.
Test of rotation/position of core shell particle.
Reference CoreShell particle is compared against the test CoreShell,
which has different dimensions but rotated/translated to be like the reference one.
Particles are placed in the center of middle layer.
"""

from __future__ import print_function
import os, sys, unittest

import utils
from libBornAgainCore import *

layer_thickness = 100.0

class TransformCoreShellBoxTest(unittest.TestCase):

    def get_sample(self, particle):
        mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
        mMiddle= HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9)
        mSubstrate = HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8)

        layout = ParticleLayout()
        layout.addParticle(particle)

        air_layer = Layer(mAmbience)
        middle_layer = Layer(mMiddle, layer_thickness)
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

    def test_SameMaterialCoreShellBox(self):
        """
        Box particle placed in the center of the middle layer is compared against CoreShell particle,
        where core and shell are made of the same material.
        """
        mCore = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)

        shell_length = 50.0
        shell_width = 20.0
        shell_height = 10.0
        particle = Particle(mCore, FormFactorBox(shell_length, shell_width, shell_height))
        particle.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0 - shell_height/2.0))

        reference_data = self.get_intensity_data(particle)

        core_length = shell_length/2.0
        core_width = shell_width/2.0
        core_height = shell_height/2.0
        shell = Particle(mCore, FormFactorBox(shell_length, shell_width, shell_height))
        core = Particle(mCore, FormFactorBox(core_length, core_width, core_height))
        coreshell = ParticleCoreShell(shell, core, kvector_t(0.0, 0.0, (shell_height-core_height)/2.0))
        coreshell.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0 - shell_height/2.0))

        data = self.get_intensity_data(coreshell)

        diff = getRelativeDifference(data, reference_data)
        print("test_SameMaterialCoreShell:", diff)
        self.assertLess(diff, 1e-10)

    def test_CoreShellBoxRotateZ(self):
        """
        Two CoreShell particles are compared against each other. Reference CoreShell particle has dimensions (20,50,10)
        and is placed in the center of middle layer. Second CoreShell particle has dimensions (50,20,10) with one
        rotationZ to be like the reference one.
        """
        mCore = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)
        mShell = HomogeneousMaterial("AgO2", 8.600e-6, 3.442e-7)

        # building reference CoreShell particle
        shell_length = 20.0
        shell_width = 50.0
        shell_height = 10.0
        core_length = shell_length/2.0
        core_width = shell_width/2.0
        core_height = shell_height/2.0

        core_ref = Particle(mCore, FormFactorBox(core_length, core_width, core_height))
        shell_ref = Particle(mShell, FormFactorBox(shell_length, shell_width, shell_height))
        coreshell_ref = ParticleCoreShell(shell_ref, core_ref, kvector_t(0.0, 0.0, (shell_height-core_height)/2.0))
        coreshell_ref.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0 - shell_height/2.0))  # center of coreshell in center of the layer

        reference_data = self.get_intensity_data(coreshell_ref)

        # building second CoreShell particle
        shell_length = 50.0
        shell_width = 20.0
        shell_height = 10.0
        core_length = shell_length/2.0
        core_width = shell_width/2.0
        core_height = shell_height/2.0

        core = Particle(mCore, FormFactorBox(core_length, core_width, core_height))
        shell = Particle(mShell, FormFactorBox(shell_length, shell_width, shell_height))
        coreshell = ParticleCoreShell(shell, core, kvector_t(0.0, 0.0, (shell_height-core_height)/2.0))
        coreshell.setRotation(RotationZ(90.0*degree))
        coreshell.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0 - shell_height/2.0))  # center of coreshell  in center of the layer

        data = self.get_intensity_data(coreshell)

        diff = getRelativeDifference(data, reference_data)
        print("test_CoreShellBoxRotateZ:", diff)
        self.assertLess(diff, 1e-10)

    def test_CoreShellBoxRotateY(self):
        """
        Two CoreShell particles are compared against each other. Reference CoreShell particle has dimensions (10,20,50)
        and is placed in the center of middle layer. Second CoreShell particle has dimensions (50,20,10) with one
        rotationZ to be like the reference one.
        """
        mCore = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)
        mShell = HomogeneousMaterial("AgO2", 8.600e-6, 3.442e-7)

        # building reference CoreShell particle
        shell_length = 10.0
        shell_width = 20.0
        shell_height = 50.0
        core_length = shell_length/2.0
        core_width = shell_width/2.0
        core_height = shell_height/2.0

        core_ref = Particle(mCore, FormFactorBox(core_length, core_width, core_height))
        shell_ref = Particle(mShell, FormFactorBox(shell_length, shell_width, shell_height))
        coreshell_ref = ParticleCoreShell(shell_ref, core_ref, kvector_t(0.0, 0.0, (shell_height-core_height)/2.0))
        coreshell_ref.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0 - shell_height/2.0))  # center of coreshell in center of the layer

        reference_data = self.get_intensity_data(coreshell_ref)

        # building second CoreShell particle
        shell_length = 50.0
        shell_width = 20.0
        shell_height = 10.0
        core_length = shell_length/2.0
        core_width = shell_width/2.0
        core_height = shell_height/2.0

        core = Particle(mCore, FormFactorBox(core_length, core_width, core_height))
        shell = Particle(mShell, FormFactorBox(shell_length, shell_width, shell_height))
        coreshell = ParticleCoreShell(shell, core, kvector_t(0.0, 0.0, (shell_height-core_height)/2.0))
        coreshell.setRotation(RotationY(90.*degree))
        coreshell.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0))  # center of coreshell  in center of the layer

        data = self.get_intensity_data(coreshell)

        # utils.plot_intensity_data(data)

        diff = getRelativeDifference(data, reference_data)
        print("test_CoreShellBoxRotateY:", diff)
        self.assertLess(diff, 1e-10)

    def test_CoreShellBoxRotateZandY(self):
        """
        Two CoreShell particles are compared against each other. Reference CoreShell particle has dimensions (10,50,20)
        and is placed in the center of middle layer. Second CoreShell particle has dimensions (50,20,10) with two
        rotations to be like the reference one.
        """
        mCore = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)
        mShell = HomogeneousMaterial("AgO2", 8.600e-6, 3.442e-7)

        # building reference CoreShell particle
        shell_length = 10.0
        shell_width = 50.0
        shell_height = 20.0
        core_length = shell_length/2.0
        core_width = shell_width/2.0
        core_height = shell_height/2.0

        core_ref = Particle(mCore, FormFactorBox(core_length, core_width, core_height))
        shell_ref = Particle(mShell, FormFactorBox(shell_length, shell_width, shell_height))
        coreshell_ref = ParticleCoreShell(shell_ref, core_ref, kvector_t(0.0, 0.0, (shell_height-core_height)/2.0))
        coreshell_ref.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0 - shell_height/2.0))  # center of coreshell in center of the layer

        reference_data = self.get_intensity_data(coreshell_ref)
        #IntensityDataIOFactory.writeIntensityData(reference_data, "ref_CoreShellBoxRotateZandY.int")

        # building second CoreShell particle
        shell_length = 50.0
        shell_width = 20.0
        shell_height = 10.0
        core_length = shell_length/2.0
        core_width = shell_width/2.0
        core_height = shell_height/2.0

        core = Particle(mCore, FormFactorBox(core_length, core_width, core_height))
        shell = Particle(mShell, FormFactorBox(shell_length, shell_width, shell_height))
        coreshell = ParticleCoreShell(shell, core, kvector_t(0.0, 0.0, (shell_height-core_height)/2.0))
        coreshell.setRotation(RotationZ(90.0*degree))
        coreshell.applyRotation(RotationY(90.0*degree))
        # rotation changes reference point, which now coincide with center of the volume
        coreshell.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0))  # center of coreshell  in center of the layer

        data = self.get_intensity_data(coreshell)

        diff = getRelativeDifference(data, reference_data)
        print("test_CoreShellBoxRotateZandY:", diff)
        self.assertLess(diff, 1e-10)


if __name__ == '__main__':
    unittest.main()
