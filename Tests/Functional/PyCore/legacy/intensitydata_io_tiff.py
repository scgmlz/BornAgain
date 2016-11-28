# Functional test: tests of IO operations with the IntensityData object

import math, numpy, os, sys, time, unittest

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import libBornAgainCore as ba


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
    if data1.getRank() != data2.getRank():
        return False
    for i in range(0, data1.getRank()):
        if data1.getAxis(i) != data2.getAxis(i):
            return False
    for i in range(0, data1.getAllocatedSize()):
        if data1[i] != data2[i]:
            return False
    return True


class OutputDataIOTiffTest(unittest.TestCase):
    """
    Test serialization of ba.IntensityData into TIFF format
    """
    def test_SaveToTiff(self):
        data = ba.IntensityData()
        data.addAxis(ba.FixedBinAxis("x", 10, 0.0, 10.0))
        data.addAxis(ba.FixedBinAxis("y", 5, 0.0, 5.0))
        fill_data(data)

        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.tif")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.tif")
        self.assertTrue(is_the_same_data(data, newdata))

        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.tif.gz")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.tif.gz")
        self.assertTrue(is_the_same_data(data, newdata))

        ba.IntensityDataIOFactory.writeOutputData(data, "tmp.tif.bz2")
        newdata = ba.IntensityDataIOFactory.readOutputData("tmp.tif.bz2")
        self.assertTrue(is_the_same_data(data, newdata))


if __name__ == '__main__':
    unittest.main()
