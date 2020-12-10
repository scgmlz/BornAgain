"""
Test of rotation/position of box in the middle layer of 3 layers system.
FormFactorBox(50, 20, 10), is rotated around Z, then around Y, then shifted up and then
compared with FormFactorBox(10, 50, 20)
"""

from __future__ import print_function
import os, sys, unittest

import utils
import bornagain as ba
from bornagain import deg, kvector_t

layer_thickness = 100


class BoxTransformationsTest(unittest.TestCase):
    def get_sample(self, particle):
        mAmbience = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
        mMiddle = ba.HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9)
        mSubstrate = ba.HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8)

        layout = ba.ParticleLayout()
        layout.addParticle(particle)

        vacuum_layer = ba.Layer(mAmbience)
        middle_layer = ba.Layer(mMiddle, layer_thickness)
        middle_layer.addLayout(layout)
        substrate = ba.Layer(mSubstrate)

        multi_layer = ba.MultiLayer()
        multi_layer.addLayer(vacuum_layer)
        multi_layer.addLayer(middle_layer)
        multi_layer.addLayer(substrate)
        return multi_layer

    def get_result(self, particle):
        sample = self.get_sample(particle)
        simulation = utils.get_simulation_MiniGISAS(sample)
        simulation.runSimulation()
        return simulation.result()

    def testBoxTransform(self):
        """
        Reference box of (10,50,20) size is compared against the box (50,20,10) with two rotations applied to get
        reference one
        """
        mParticle = ba.HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)

        # reference box
        length = 10
        width = 50
        height = 20

        box = ba.Particle(mParticle, ba.FormFactorBox(length, width, height))
        box.setPosition(kvector_t(0, 0, -layer_thickness/2 - height/2))
        reference_data = self.get_result(box)
        #IntensityDataIOFactory.writeIntensityData(reference_data, "ref_TransformBox.int")

        # second box
        length = 50
        width = 20
        height = 10
        box = ba.Particle(mParticle, ba.FormFactorBox(length, width, height))
        box.setRotation(ba.RotationZ(90*deg))
        box.rotate(ba.RotationY(90*deg))
        box.setPosition(kvector_t(0, 0, -layer_thickness/2))

        data = self.get_result(box)

        diff = ba.RelativeDifference(data, reference_data)
        print(diff)
        self.assertLess(diff, 1e-10)


if __name__ == '__main__':
    unittest.main()
