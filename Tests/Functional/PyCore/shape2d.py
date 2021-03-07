import numpy, os, sys, unittest
import bornagain as ba


class Shape2DTest(unittest.TestCase):
    def test_constructPolygonFromList(self):
        """
        Testing construction of polygon from two Numpy arrays
        """

        # initializing from list
        x = [-1, 2, 2, -1.0]
        y = [-0.5, -0.5, 1.5, 1.5]
        p = ba.Polygon(x, y)
        self.assertTrue(p.contains(-0.75, -0.25))
        self.assertTrue(p.contains(1.5, 1))

        # initializing from list inline
        p2 = ba.Polygon([-1, 2, 2, -1.0], [-0.5, -0.5, 1.5, 1.5])
        self.assertTrue(p2.contains(-0.75, -0.25))
        self.assertTrue(p2.contains(1.5, 1))

        # initialization from 2D list inline
        p3 = ba.Polygon([[-1, -0.5], [2, -0.5], [2, 1.5], [-1, 1.5]])
        self.assertTrue(p3.contains(-0.75, -0.25))
        self.assertTrue(p3.contains(1.5, 1))

    def test_constructPolygonFromNumpy(self):
        """
        Testing construction of polygon from two Numpy arrays
        """

        # initialization from numpy array
        points = numpy.array([[-1, -0.5], [2, -0.5], [2, 1.5],
                              [-1, 1.5]])

        p = ba.Polygon(points)
        self.assertTrue(p.contains(-0.75, -0.25))
        self.assertTrue(p.contains(1.5, 1))


if __name__ == '__main__':
    unittest.main()
