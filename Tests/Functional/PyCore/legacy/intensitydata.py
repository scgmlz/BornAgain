# Functional test: tests of IntensityData object

import numpy, os, sys, unittest

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import libBornAgainCore as ba


class IntensityDataTest(unittest.TestCase):
    """
    Test creation of ba.IntensityData object and different ways of accessing its data
    """
    def test_empty_data(self):
        data = ba.IntensityData()
        self.assertEqual(1, data.getAllocatedSize())
        self.assertEqual(0, data.getRank())

    def test_create_1d_object(self):
        axis0 = ba.FixedBinAxis("angle", 20, 0.0, 20.)
        self.assertEqual(20, axis0.size())
        self.assertEqual(0.0, axis0.getMin())
        self.assertEqual(20.0, axis0.getMax())
        data = ba.IntensityData()
        data.addAxis(axis0)
        self.assertEqual(20, data.getAllocatedSize())
        self.assertEqual(1, data.getRank())

    def test_create_2d_object(self):
        data = ba.IntensityData()
        data.addAxis("axis0", 10, 0.0, 10.0)
        data.addAxis("axis1", 20, 0.0, 20.0)
        self.assertEqual(200, data.getAllocatedSize())
        self.assertEqual(2, data.getRank())
        data.setAllTo(1.0)

    def test_access_simulation_intensity(self):
        simulation = ba.GISASSimulation()
        simulation.setDetectorParameters(10, -1.0, 1.0, 100, 0.0, 2.0)
        data = simulation.getIntensityData()
        self.assertEqual(1000, data.getTotalNumberOfBins())
        self.assertEqual(2, data.getRank())
        self.assertEqual(0, data.integral())
        self.assertEqual(10, data.getXaxis().size())

    def test_numpy_array(self):
        data = ba.IntensityData()
        data.addAxis("axis0", 10, 0.0, 10.0)
        data.addAxis("axis1", 20, 0.0, 20.0)
        data.setAllTo(1)
        self.assertEqual((20, 10), data.getArray().shape)


if __name__ == '__main__':
    unittest.main()
