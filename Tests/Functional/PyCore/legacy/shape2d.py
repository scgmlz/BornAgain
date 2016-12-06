import numpy, os, sys, unittest

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba

class Shape2DTest(unittest.TestCase):

    def test_constructPolygonFromList(self):
        """
        Testing construction of polygon from two Numpy arrays
        """

        # initializing from list
        x = [-1.0, 2.0, 2.0, -1.0]
        y = [-0.5, -0.5, 1.5, 1.5]
        p = ba.Polygon(x, y)
        self.assertTrue(p.contains(-0.75, -0.25))
        self.assertTrue(p.contains(1.5, 1.0))

        # initializing from list inline
        p2 = ba.Polygon([-1.0, 2.0, 2.0, -1.0], [-0.5, -0.5, 1.5, 1.5])
        self.assertTrue(p2.contains(-0.75, -0.25))
        self.assertTrue(p2.contains(1.5, 1.0))

        # initialization from 2D list inline
        p3 = ba.Polygon([[-1.0, -0.5], [2.0, -0.5], [2.0, 1.5], [-1.0, 1.5]])
        self.assertTrue(p3.contains(-0.75, -0.25))
        self.assertTrue(p3.contains(1.5, 1.0))

    def test_constructPolygonFromNumpy(self):
        """
        Testing construction of polygon from two Numpy arrays
        """

        # initialization from numpy array
        points = numpy.array([[-1.0, -0.5], [2.0, -0.5], [2.0, 1.5], [-1.0, 1.5]])

        p = ba.Polygon(points)
        self.assertTrue(p.contains(-0.75, -0.25))
        self.assertTrue(p.contains(1.5, 1.0))


if __name__ == '__main__':
    unittest.main()
