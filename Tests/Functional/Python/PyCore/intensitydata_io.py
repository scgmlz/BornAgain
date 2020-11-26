# Functional test: tests of IO operations with the IntensityData object

import math, numpy, os, sys, time, unittest

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba
from bornagain import deg, deg2rad, rad2deg


def fill_data(data):
    """
    Fills intensity data with some numbers
    """
    for i in range(0, data.getAllocatedSize()):
        data[i] = i


def is_the_same_data(data1, data2):
    """
    Checks if two data are identical
    """
    if data1.getAllocatedSize() != data2.getAllocatedSize():
        return False
    if data1.rank() != data2.rank():
        return False
    for i in range(0, data1.rank()):
        if data1.axis(i) != data2.axis(i):
            return False
    for i in range(0, data1.getAllocatedSize()):
        if data1[i] != data2[i]:
            return False
    return True


def get_boundaries_flat_in_sin(nbins, start, end):
    """
    Returns flat_in_sin binning of angle axis
    """
    result = []
    start_sin = math.sin(deg2rad(start))
    end_sin = math.sin(deg2rad(end))
    step = (end_sin - start_sin)/nbins
    for i in range(0, nbins + 1):
        result.append(rad2deg(math.asin(start_sin + step*i)))
    return result


class OutputDataIOTest(unittest.TestCase):
    """
    Test serialization of IntensityData
    """
    def test_01_FixedBinAxis_1D(self):
        data = ba.IntensityData()
        data.addAxis(ba.FixedBinAxis("axis0", 10, -1.00000001, 1.0))
        fill_data(data)
        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.int")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.int")
        self.assertTrue(is_the_same_data(data, newdata))

    def test_02_FixedBinAxis_2D(self):
        data = ba.IntensityData()
        data.addAxis(ba.FixedBinAxis("axis0", 9, -1.00000001, 1.0))
        data.addAxis(ba.FixedBinAxis("axis1", 3, -4.0, 5.0))
        fill_data(data)
        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.int")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.int")
        self.assertTrue(is_the_same_data(data, newdata))

    def test_03_FixedBinAxis_3D(self):
        data = ba.IntensityData()
        data.addAxis(ba.FixedBinAxis("axis0", 9, -1.00000001, 1.0))
        data.addAxis(ba.FixedBinAxis("axis1", 1, -4.0, 5.0))
        data.addAxis(ba.FixedBinAxis("axis2", 3, 0.0, 1.0))
        fill_data(data)
        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.int")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.int")
        self.assertTrue(is_the_same_data(data, newdata))

    def test_04_VariableBinAxis_1D(self):
        data = ba.IntensityData()
        data.addAxis(
            ba.VariableBinAxis("axis0", 10,
                               get_boundaries_flat_in_sin(10, -5.0, 5.0)))
        fill_data(data)
        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.int")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.int")
        self.assertTrue(is_the_same_data(data, newdata))

    def test_05_VariableBinAxis_2D(self):
        data = ba.IntensityData()
        data.addAxis(
            ba.VariableBinAxis("axis0", 10,
                               get_boundaries_flat_in_sin(10, -5.0, 5.0)))
        data.addAxis(
            ba.VariableBinAxis("axis1", 3,
                               get_boundaries_flat_in_sin(3, 0.0, 2.0)))
        fill_data(data)
        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.int")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.int")
        self.assertTrue(is_the_same_data(data, newdata))

    def test_06_VariableAndFixedMix(self):
        data = ba.IntensityData()
        data.addAxis(ba.FixedBinAxis("axis0", 10, -5.0, 5.0))
        data.addAxis(
            ba.VariableBinAxis("axis1", 3,
                               get_boundaries_flat_in_sin(3, 0.0, 2.0)))
        fill_data(data)
        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.int")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.int")
        self.assertTrue(is_the_same_data(data, newdata))

    def test_07_ConstKBinAxis_2D(self):
        data = ba.IntensityData()
        data.addAxis(ba.ConstKBinAxis("axis0", 9, -1.00000001*deg, 1.0*deg))
        data.addAxis(ba.ConstKBinAxis("axis1", 3, -4.0*deg, 5.0*deg))
        fill_data(data)
        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.int")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.int")
        self.assertTrue(is_the_same_data(data, newdata))

    def test_08_CustomBinAxis_2D(self):
        data = ba.IntensityData()
        data.addAxis(ba.CustomBinAxis("axis0", 9, -1.00000001*deg, 1.0*deg))
        data.addAxis(ba.CustomBinAxis("axis1", 3, -4.0*deg, 5.0*deg))
        fill_data(data)
        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.int")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.int")
        self.assertTrue(is_the_same_data(data, newdata))

    def test_SaveToINT(self):
        data = ba.IntensityData()
        data.addAxis(ba.FixedBinAxis("axis0", 10, 0.0, 10.0))
        data.addAxis(ba.FixedBinAxis("axis1", 5, 0.0, 5.0))
        fill_data(data)

        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.int")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.int")
        self.assertTrue(is_the_same_data(data, newdata))

        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.int.gz")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.int.gz")
        self.assertTrue(is_the_same_data(data, newdata))

        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.int.bz2")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.int.bz2")
        self.assertTrue(is_the_same_data(data, newdata))

    def test_SaveToTXT(self):
        data = ba.IntensityData()
        data.addAxis(ba.FixedBinAxis("axis0", 10, 0.0, 10.0))
        data.addAxis(ba.FixedBinAxis("axis1", 5, 0.0, 5.0))
        fill_data(data)

        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.txt")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.txt")
        self.assertTrue(is_the_same_data(data, newdata))

    def test_SaveNumpyArray_ReadOutputData(self):
        arr = numpy.array([[0.0, 1.0, 2.0, 3.0], [4.0, 5.0, 6.0, 7.0],
                           [8.0, 9.0, 10.0, 11.0]])
        numpy.savetxt('tmp.txt', arr)
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.txt")
        self.assertTrue(numpy.array_equal(newdata.getArray(), arr))

    def test_SaveNumpyArray_ReadRawDataVector(self):
        arr = numpy.array([[0.0, 1.0, 2.0, 3.0], [4.0, 5.0, 6.0, 7.0],
                           [8.0, 9.0, 10.0, 11.0]])
        numpy.savetxt('tmp.txt', arr)
        newdata = numpy.array(
            ba.IntensityDataIOFactory.readOutputData(
                "tmp.txt").getRawDataVector())
        expected = numpy.array(
            [8., 4., 0., 9., 5., 1., 10., 6., 2., 11., 7., 3.])
        self.assertTrue(numpy.array_equal(newdata, expected))

    def test_SaveOutputData_ReadNumpyArray(self):
        data = ba.IntensityData()
        data.addAxis(ba.FixedBinAxis("axis0", 10, 0.0, 10.0))
        data.addAxis(ba.FixedBinAxis("axis1", 5, 0.0, 5.0))
        fill_data(data)

        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.txt")
        arr = numpy.loadtxt("tmp.txt")

        self.assertTrue(numpy.array_equal(data.getArray(), arr))


if __name__ == '__main__':
    unittest.main()
