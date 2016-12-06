import numpy, os, sys, unittest

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba

class Histogram2DTest(unittest.TestCase):

    def test_constructFromNumpyInt(self):
        """
        Testing construction of 2D histogram from numpy array.
        Automatic convertion under Python3 is not working, that's why it is float64 and not int64
        """
        arr = numpy.array([[ 1,  2,  3,  4,  5],
                           [ 6,  7,  8,  9, 10],
                           [11, 12, 13, 14, 15]], numpy.float64)
        hist = ba.Histogram2D(arr)

        self.assertEqual(hist.getNbinsX(), 5)
        self.assertEqual(hist.getXmin(), 0.0)
        self.assertEqual(hist.getXmax(), 5.0)

        self.assertEqual(hist.getNbinsY(), 3)
        self.assertEqual(hist.getYmin(), 0.0)
        self.assertEqual(hist.getYmax(), 3.0)

        self.assertEqual(hist.getBinContent(0, 0), 11.0)
        self.assertEqual(hist.getBinContent(0, 1), 6.0)
        self.assertEqual(hist.getBinContent(4, 2), 5.0)

        arr_from_hist = hist.getArray()

        for (x, y), element in numpy.ndenumerate(arr):
            self.assertEqual(element, arr_from_hist[x][y])

    def test_constructFromNumpyDouble(self):
        """
        Testing construction of 2D histogram from numpy array
        """
        arr = numpy.array([[ 1.0,  2.0,  3.0,  4.0,  5.0],
                           [ 6.0,  7.0,  8.0,  9.0, 10.0],
                           [11.0, 12.0, 13.0, 14.0, 15.0]], dtype=numpy.float64)
        hist = ba.Histogram2D(arr)

        self.assertEqual(hist.getNbinsX(), 5)
        self.assertEqual(hist.getXmin(), 0.0)
        self.assertEqual(hist.getXmax(), 5.0)

        self.assertEqual(hist.getNbinsY(), 3)
        self.assertEqual(hist.getYmin(), 0.0)
        self.assertEqual(hist.getYmax(), 3.0)

        self.assertEqual(hist.getBinContent(0, 0), 11.0)
        self.assertEqual(hist.getBinContent(0, 1), 6.0)
        self.assertEqual(hist.getBinContent(4, 2), 5.0)

        arr_from_hist = hist.getArray()

        for (x, y), element in numpy.ndenumerate(arr):
            self.assertEqual(element, arr_from_hist[x][y])

    def test_constructAndAddFromNumpyInt(self):
        """
        Adding to the histogram content from numpy array
        """
        arr = numpy.array([[ 1,  2,  3,  4,  5],
                           [ 6,  7,  8,  9, 10],
                           [11, 12, 13, 14, 15]], dtype=numpy.float64)
        print(type(arr))
        hist = ba.Histogram2D(arr)
        # adding same content once again
        hist.addContent(arr)
        arr_from_hist = hist.getArray()

        for (x, y), element in numpy.ndenumerate(arr):
            self.assertEqual(element*2.0, arr_from_hist[x][y])

    def test_constructAndAddFromNumpyDouble(self):
        """
        Adding to the histogram content from numpy array
        """
        arr = numpy.array([[ 1.0,  2.0,  3.0,  4.0,  5.0],
                           [ 6.0,  7.0,  8.0,  9.0, 10.0],
                           [11.0, 12.0, 13.0, 14.0, 15.0]], dtype=numpy.float64)
        hist = ba.Histogram2D(arr)
        # adding same content once again
        hist.addContent(arr)
        arr_from_hist = hist.getArray()

        for (x, y), element in numpy.ndenumerate(arr):
            self.assertEqual(element*2.0, arr_from_hist[x][y])

    def create_histogram(self, arr):
        """
        Returns newly created object
        """
        return ba.IHistogram.createFrom(arr)

    def test_createFromInt(self):
        """
        Testing newly create object
        """
        arr = numpy.array([[ 1,  2,  3,  4,  5],
                           [ 6,  7,  8,  9, 10],
                           [11, 12, 13, 14, 15]], dtype=numpy.float64)
        hist = self.create_histogram(arr)
        arr_from_hist = hist.getArray()

        for (x, y), element in numpy.ndenumerate(arr):
            self.assertEqual(element, arr_from_hist[x][y])

    def test_createFromDouble(self):
        """
        Testing newly create object
        """
        arr = numpy.array([[ 1.0,  2.0,  3.0,  4.0,  5.0],
                           [ 6.0,  7.0,  8.0,  9.0, 10.0],
                           [11.0, 12.0, 13.0, 14.0, 15.0]], dtype=numpy.float64)
        hist = self.create_histogram(arr)
        arr_from_hist = hist.getArray()

        for (x, y), element in numpy.ndenumerate(arr):
            self.assertEqual(element, arr_from_hist[x][y])


if __name__ == '__main__':
    unittest.main()
