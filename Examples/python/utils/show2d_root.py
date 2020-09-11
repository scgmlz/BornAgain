#!/usr/bin/env python3
# Draws two dimensional numpy array using ROOT
# Usage: python show2d.py file_name

from __future__ import print_function
import argparse
import os
import numpy
import ROOT
from pylab import *


def PlotNumpyArrayWithROOT(a, zmin = 1, zmax = None):
    nx = a.shape[0]
    ny = a.shape[1]
    hist = ROOT.TH2D("hist","hist",nx,0,nx, ny, 0, ny)
    for (x,y), value in numpy.ndenumerate(a):
        hist.Fill(x,y,value)

    c1 = ROOT.TCanvas("c1","numpy array", 1024,768)
    c1.SetLogz()
    hist.SetMinimum(zmin)
    hist.Draw("CONT4Z")
    c1.Update()
    ROOT.gApplication.Run()
    #Interrupt = False
    #while not Interrupt:
        #Interrupt = ROOT.gSystem.ProcessEvents()
        #ROOT.gSystem.Sleep(10)


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

    PlotNumpyArrayWithROOT(a, zmin, zmax)

        
