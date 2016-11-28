"""
Test of rotation/positioning of simple cubic particle. Original particle is compared with the one obtained
"""

from __future__ import print_function
import os, sys, unittest

import utils
from libBornAgainCore import *


class RotationsCubeTest(unittest.TestCase):
    """
    Test of rotations and translations of simple cube in three layers system
    """
    def get_sample(self, formfactor, rot = None, pos = None, layout_rot = None, layout_pos = None, add_to="air"):
        mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
        mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8)
        mMiddle= HomogeneousMaterial("MidleLayer", 5e-5, 2e-8)
        mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)

        particle = Particle(mParticle, formfactor)
        if pos:
            particle.setPosition(pos)
        if rot:
            particle.setRotation(rot)

        layout = ParticleLayout()
        if layout_rot and layout_pos:
            layout.addParticle(particle, 1.0, layout_pos, layout_rot)
        elif layout_rot and not layout_pos:
            layout.addParticle(particle, 1.0, kvector_t(0, 0, 0), layout_rot)
        elif not layout_rot and layout_pos:
            layout.addParticle(particle, 1.0, layout_pos)
        else:
            layout.addParticle(particle)

        air_layer = Layer(mAmbience)
        middle_layer = Layer(mSubstrate, 50.0)
        substrate = Layer(mSubstrate)

        if add_to == "air":
            air_layer.addLayout(layout)
        else:
            middle_layer.addLayout(layout)

        multi_layer = MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayer(middle_layer)
        multi_layer.addLayer(substrate)
        return multi_layer

    def get_intensity_data(self, data, add_to="air"):
        ff = data[0]
        rot = data[1]
        pos = data[2]
        layout_rot = data[3]
        layout_pos = data[4]
        sample = self.get_sample(ff, rot, pos, layout_rot, layout_pos, add_to)
        # simulation = self.get_simulation(sample)
        simulation = utils.get_simulation_MiniGISAS(sample)
        simulation.runSimulation()
        return simulation.getIntensityData()

    def get_difference(self, reference_data, test_data, add_to="air"):
        intensity = self.get_intensity_data(test_data, add_to)
        return getRelativeDifference(reference_data, intensity)

    def testRotationZ(self):
        """
        Cube is Z-rotated either through setRotation method or through particle layout. The result is compared
        with unrotated cube.
        """
        box = FormFactorBox(10, 10, 10)

        data_to_test = [
            # ff  rot                     pos                    layout_rot              layout_pos
            (box, None,                   None,                  None,                   None),  # reference
            (box, RotationZ(90.*degree),  None,                  None,                   None),  # rotating particle
            (box, RotationZ(-90.*degree), None,                  None,                   None),
            (box, RotationZ(180.*degree), None,                  None,                   None),
            (box, None,                   None,                  RotationZ(90.*degree),  None),  # rotating through layout
            (box, RotationZ(45.*degree),  None,                  RotationZ(45.*degree),  None),  # cumulative rotation
        ]

        reference_data = self.get_intensity_data(data_to_test[0])

        isSuccess = True
        for i in range(1, len(data_to_test)):
            diff = self.get_difference(reference_data, data_to_test[i])
            print("{0}    #{1}   diff {2:.2e}".format(self.testRotationZ.__name__, i, diff))
            if(diff > 1e-10) : isSuccess=False

        self.assertTrue(isSuccess)

    def testRotationY(self):
        """
        Cube is Y-rotated either through setRotation method or through particle layout. Additional translation is
        applied if necessary. The result is compared with unrotated cube.
        """
        box = FormFactorBox(10, 10, 10)

        data_to_test = [
            # ff  rot                     pos                    layout_rot              layout_pos
            (box, None,                   None,                  None,                   None),  # reference
            (box, RotationY(90.*degree),  kvector_t(0,0,5.0),    None,                   None),  # rotating and translating
            (box, None,                   None,                  RotationY(90.*degree),  kvector_t(0,0,5.0)),  # rotating and translating
            (box, RotationY(90.*degree),  None,                  None,                   kvector_t(0,0,5.0)),  # rotating and translating
            (box, RotationY(45.*degree),  kvector_t(0,0,0.0),    RotationY(45.*degree),  kvector_t(0,0,5.0)),  # rotating and translating
        ]

        reference_data = self.get_intensity_data(data_to_test[0])

        isSuccess = True
        for i in range(1, len(data_to_test)):
            diff = self.get_difference(reference_data, data_to_test[i])
            print("{0}    #{1}   diff {2:.2e}".format(self.testRotationY.__name__, i, diff))
            if(diff > 1e-10) : isSuccess=False

        self.assertTrue(isSuccess)

    def testRotationX(self):
        """
        Cube is Z-rotated either through setRotation method or through particle layout. Additional translation is
        applied if necessary. The result is compared with unrotated cube.
        """
        box = FormFactorBox(10, 10, 10)

        data_to_test = [
            # ff  rot                     pos                    layout_rot              layout_pos
            (box, None,                   None,                  None,                   None),  # reference
            (box, RotationX(90.*degree),  kvector_t(0,0,5.0),    None,                   None),  # rotating and translating
            (box, None,                   None,                  RotationX(90.*degree),  kvector_t(0,0,5.0)),  # rotating and translating
            (box, RotationX(90.*degree),  None,                  None,                   kvector_t(0,0,5.0)),  # rotating and translating
            (box, RotationX(45.*degree),  kvector_t(0,0,0.0),    RotationX(45.*degree),  kvector_t(0,0,5.0)),  # rotating and translating
        ]

        reference_data = self.get_intensity_data(data_to_test[0])

        isSuccess = True
        for i in range(1, len(data_to_test)):
            diff = self.get_difference(reference_data, data_to_test[i])
            print("{0}    #{1}   diff {2:.2e}".format(self.testRotationX.__name__, i, diff))
            if(diff > 1e-10) : isSuccess=False

        self.assertTrue(isSuccess)

    def testRotationsInMiddleLayer(self):
        """
        """
        box = FormFactorBox(10, 10, 10)

        data_to_test = [
            # ff  rot                     pos                    layout_rot              layout_pos
            (box, None,                   kvector_t(0,0,-25.0),  None,                   None),  # reference
            (box, RotationX(90.*degree),  kvector_t(0,0,-20.0),  None,                   None),  # rotating and translating
        ]

        reference_data = self.get_intensity_data(data_to_test[0], "add_to_middle")

        isSuccess = True
        for i in range(1, len(data_to_test)):
            diff = self.get_difference(reference_data, data_to_test[i], "add_to_middle")
            print("{0}    #{1}   diff {2:.2e}".format(self.testRotationX.__name__, i, diff))
            if(diff > 1e-10) : isSuccess=False

        self.assertTrue(isSuccess)


if __name__ == '__main__':
    unittest.main()
