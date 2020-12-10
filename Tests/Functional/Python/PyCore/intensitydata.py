# Functional test: tests of IntensityData object

import numpy, os, sys, unittest
import bornagain as ba


class IntensityDataTest(unittest.TestCase):
    """
    Test creation of ba.IntensityData object and different ways of accessing its data
    """
    def test_empty_data(self):
        data = ba.IntensityData()
        self.assertEqual(1, data.getAllocatedSize())
        self.assertEqual(0, data.rank())
        self.assertEqual(0, data.totalSum())

    def test_create_1d_output_data_from_numpy(self):
        input = numpy.array([0, 1, 2, 3, 4, 5, 6], dtype=float)
        output_data = ba.importArrayToOutputData(input)
        output = output_data.getArray()
        self.assertEqual(input.size, output.size)
        numpy.testing.assert_allclose(input, output)

    def test_create_2d_output_data_from_numpy(self):
        input = numpy.array([[0, 1], [2, 3]], dtype=float)
        output_data = ba.importArrayToOutputData(input)
        output = output_data.getArray()
        self.assertEqual(input.size, output.size)
        numpy.testing.assert_allclose(input, output)

    def test_create_1d_object(self):
        axis0 = ba.FixedBinAxis("angle", 20, 0.0, 20.)
        self.assertEqual(20, axis0.size())
        self.assertEqual(0.0, axis0.lowerBound())
        self.assertEqual(20.0, axis0.upperBound())
        data = ba.IntensityData()
        data.addAxis(axis0)
        self.assertEqual(20, data.getAllocatedSize())
        self.assertEqual(1, data.rank())
        self.assertEqual(0, data.totalSum())

    def test_create_2d_object(self):
        data = ba.IntensityData()
        data.addAxis("axis0", 10, 0.0, 10.0)
        data.addAxis("axis1", 20, 0.0, 20.0)
        self.assertEqual(200, data.getAllocatedSize())
        self.assertEqual(2, data.rank())
        self.assertEqual(0, data.totalSum())
        data.setAllTo(1.0)
        self.assertEqual(200.0, data.totalSum())
        for i in range(0, data.getAllocatedSize()):
            data[i] = data[i]* -1.0
        self.assertEqual(-200.0, data.totalSum())

    def test_access_simulation_intensity(self):
        simulation = ba.GISASSimulation()
        simulation.setDetectorParameters(10, -1.0, 1.0, 100, 0.0, 2.0)
        data = simulation.result().histogram2d()
        self.assertEqual(1000, data.getTotalNumberOfBins())
        self.assertEqual(2, data.rank())
        self.assertEqual(0, data.integral())
        self.assertEqual(10, data.xAxis().size())

    def test_numpy_array(self):
        data = ba.IntensityData()
        data.addAxis("axis0", 10, 0.0, 10.0)
        data.addAxis("axis1", 20, 0.0, 20.0)
        data.setAllTo(1)
        self.assertEqual((20, 10), data.getArray().shape)
        self.assertEqual((data.totalSum()), numpy.sum(data.getArray()))


if __name__ == '__main__':
    unittest.main()
