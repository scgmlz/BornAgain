#!/usr/bin/env python3
# Draws two dimensional numpy array using matplotlib
# Usage: python show2d.py file_name

from __future__ import print_function
from pylab import *
from matplotlib.colors import LogNorm
import argparse
import os


# Define a nice colormap
cdict = {'red':   ((0.0, 0.0, 0.0), (0.5, 0.0, 0.0), (1.0, 1.0, 1.0)),
         'green': ((0.0, 0.0, 0.0), (0.5, 0.0, 0.0), (1.0, 1.0, 1.0)),
         'blue':  ((0.0, 0.0, 0.0), (0.5, 1.0, 1.0), (1.0, 1.0, 1.0))}
blue_cmap = matplotlib.colors.LinearSegmentedColormap('blue_map', cdict, 256)


def PlotNumpyArray(a, zmin = 1, zmax = None):
    # Make a plot of the data
    #print( "plotting..." )
    amax=a.flatten().max()
    amean=np.sum(a)/a.size
    aminplot=amean**2/amax
    a=np.maximum(a, zmin)
    dataarray=np.flipud(np.transpose(a))
    plt.xlabel(r'$\phi_f$', fontsize=20)
    plt.ylabel(r'$\alpha_f$', fontsize=20)
    # Use one of the predefined colormaps or the above defined 'blue_cmap':
    im=plt.imshow(dataarray, norm=LogNorm(), vmax=zmax, cmap=cm.jet) #, interpolation='none')
    plt.gca().axes.get_xaxis().set_ticks([])
    plt.gca().axes.get_yaxis().set_ticks([])
    plt.colorbar(im)

    # Show the plot
    #print( "showing..." )
    # Uncomment the next lines to generate a pdf from the plot
    #extension = 'pdf'
    #plt.savefig(file_no_prefix + '.%s' %extension, format=extension)
    plt.show()


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    # Define the arguments to the script
    parser = argparse.ArgumentParser(description='Plot 2D data table on log scale.')
    parser.add_argument('-m', '--minz', dest='zmin', metavar='MINZ',
        help='minimum z-value to display [default: 1]',
        default='1')
    parser.add_argument('-M', '--maxz', dest='zmax', metavar='MAXZ',
        help='maximum z-value to display [default: maximum value of data set]',
        default=None)
    parser.add_argument('filename', metavar='filename',
        help='filename of the data file')

    # Parse the script's arguments
    args = parser.parse_args()
    zmin = float(args.zmin)
    if (args.zmax):
        zmax = float(args.zmax)
    else:
        zmax = None
    filename = args.filename

    # Load the file's data
    print( "loading..." )
    a=np.loadtxt(filename)
    file_no_prefix = os.path.splitext(os.path.basename(filename))[0]
    print('Filename: ', file_no_prefix)
    print('Data shape: ', a.shape)
    print('Minimum value of data: ', a.flatten().min())
    print('Maximum value of data: ', a.flatten().max())

    PlotNumpyArray(a, zmin, zmax)
