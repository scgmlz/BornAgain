# script to plot the form factor
# after the ROOT window with plots appear,
# just save the picture in that format which you need

import ROOT
from libBornAgainCore import *

# define a form factor, I recommend a 10--20 nm diameter
#ff = FormFactorFullSphere(10.0*nanometer)
#ff =  FormFactorSphere(10.0*nanometer, 13.0*nanometer)
ff =  FormFactorPyramid(13*nanometer, 10.0*nanometer, 60*degree)


# volume
# I suggest, that the form factor evaluated for q=0 gives the volume
# please correct if not
zero = cvector_t(0,0,0)
V = abs(ff.evaluate_for_q(zero))


# number of bins for qx, qy, qz
# I recommend to put at least 400 for a better picture quality
nqy = 400
nqz = 400
nqx = 400

# minimum and maximum values for qx, qy qz
qymin = -2.0
qymax = 2.0
qzmin = -2.0
qzmax = 2.0
qxmin = -2.0
qxmax = 2.0

# first and last bin for the projection slice
# if number of bins=400, then fbin should be set to 200 and lbin to 201
#fbin=200
#lbin=201

# step for qx, qy, qz
stepqy = (qymax - qymin)/(nqy-1)
stepqz = (qzmax - qzmin)/(nqz-1)
stepqx = (qxmax - qxmin)/(nqx-1)

# define style of the diagram
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(0);
ROOT.gStyle.SetOptTitle(0);
ROOT.gStyle.SetLabelSize(0.06, "xyz");
ROOT.gStyle.SetTitleSize(0.06, "xyz");
#ROOT.gStyle.SetPadRightMargin(0.1)
ROOT.gStyle.SetPadLeftMargin(0.18)
ROOT.gStyle.SetPadBottomMargin(0.18)

t = ROOT.TText()
# create ROOT histograms
hist = ROOT.TH2D("hist","Sphere:H=R",nqy,qymin,qymax, nqz, qzmin, qzmax)
hist2 = ROOT.TH2D("hist2","Sphere:H=R",nqx,qxmin,qxmax, nqy, qymin, qymax)

# and fill them with the values
for i in range(nqy):
    qy = qymin + i*stepqy
    for j in range(nqz):
        qz = qzmin + j*stepqz
        k = cvector_t(0,qy,qz)
        hist.Fill(qy,qz,(abs(ff.evaluate_for_q(k)))**2+1)

for i in range(nqy):
    qy = qymin + i*stepqy
    for j in range(nqx):
        qx = qxmin + j*stepqx
        k = cvector_t(qx,qy,0)
        hist2.Fill(qx,qy,(abs(ff.evaluate_for_q(k)))**2+1)


# create a ROOT canvas and put all plots on it
c = ROOT.TCanvas("FormfactorSphere","Formfactor Sphere", 1000,500)

c.Divide(2,1)
hist.SetMinimum(1)
hist.SetMaximum(V**2)
hist2.SetMinimum(1)
hist2.SetMaximum(V**2)
hist.SetContour(50)
hist2.SetContour(50)
#hist.GetZaxis().SetTitle(" |F|^{2} ")
#hist2.GetZaxis().SetTitle(" |F|^{2} ")


c.cd(1)
ROOT.gPad.SetLogz()
hist.GetXaxis().SetTitle(" q_{y} [nm^{-1}] ")
hist.GetXaxis().CenterTitle()
hist.GetXaxis().SetTitleOffset(1.1)
hist.GetYaxis().SetTitle(" q_{z} [nm^{-1}] ")
hist.GetYaxis().CenterTitle()
hist.GetYaxis().SetTitleOffset(1.4)
hist.GetZaxis().SetTitleOffset(1.3)
hist.Draw("col")
#t.SetNDC(1)
#t.SetTextSize(8.0e-2)
#t.DrawText(0.1, 0.01, "a")

c.cd(2)
ROOT.gPad.SetLogz()
hist2.SetMinimum(1)
hist2.GetXaxis().SetTitle(" q_{x} [nm^{-1}] ")
hist2.GetXaxis().CenterTitle()
hist2.GetXaxis().SetTitleOffset(1.1)
hist2.GetYaxis().SetTitle(" q_{y} [nm^{-1}] ")
hist2.GetYaxis().CenterTitle()
hist2.GetYaxis().SetTitleOffset(1.4)
hist2.GetZaxis().SetTitleOffset(1.3)
hist2.Draw("col")
#t.DrawText(0.1, 0.004, "b")

#c.cd(3)
#ROOT.gPad.SetLogy()
#py = hist.ProjectionX("py", fbin, lbin, 'o')
#py.GetYaxis().SetTitle(" |F|^{2} ")
#py.GetYaxis().SetTitleOffset(1.3)
#py.Draw()

#t.DrawText(0.1, 0.01, "c")

#c.cd(4)
#ROOT.gPad.SetLogy()
#px = hist2.ProjectionX("px", fbin, lbin, 'o')
#px.GetYaxis().SetTitle(" |F|^{2} ")
#px.GetYaxis().SetTitleOffset(1.3)
#px.Draw()
#t.DrawText(0.1, 0.004, "d")

c.Update()
ROOT.gApplication.Run()



