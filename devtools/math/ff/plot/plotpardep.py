# script to plot the form factor
# after the ROOT window with plots appear,
# just save the picture in that format which you need

import ROOT
from libBornAgainCore import *

# define a form factor, I recommend a 10--20 nm diameter
#ff = FormFactorFullSphere(10.0*nanometer)
ff05 =  FormFactorSphere(10.0*nanometer, 5.0*nanometer)
ff10 =  FormFactorSphere(10.0*nanometer, 10.0*nanometer)
ff15 =  FormFactorSphere(10.0*nanometer, 15.0*nanometer)

# zero q vector
zero = cvector_t(0,0,0)
# volume of particles
V05 = abs(ff05.evaluate_for_q(zero))
V10 = abs(ff10.evaluate_for_q(zero))
V15 = abs(ff15.evaluate_for_q(zero))


# number of bins for qx, qy, qz
# I recommend to put at least 400 for a better picture quality
nqy = 100
nqz = 100
nqx = 100

# minimum and maximum values for qx, qy qz
qymin = -2.0
qymax = 2.0
qzmin = -2.0
qzmax = 2.0
qxmin = -2.0
qxmax = 2.0

# first and last bin for the projection slice
# if number of bins=400, then fbin should be set to 200 and lbin to 201
#fbin=50
#lbin=51

# step for qx, qy, qz
stepqy = (qymax - qymin)/(nqy-1)
stepqz = (qzmax - qzmin)/(nqz-1)
stepqx = (qxmax - qxmin)/(nqx-1)

# define style of the diagram
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(0);
ROOT.gStyle.SetOptTitle(1);
ROOT.gStyle.SetLabelSize(0.06, "xyz");
ROOT.gStyle.SetTitleSize(0.06, "xyz");
ROOT.gStyle.SetTitleFontSize(0.1);
#ROOT.gStyle.SetPadRightMargin(0.19)
ROOT.gStyle.SetPadLeftMargin(0.18)
ROOT.gStyle.SetPadBottomMargin(0.18)
ROOT.gStyle.SetTitleX(0.3);
#ROOT.gStyle.SetTitleW(0.5);


#t = ROOT.TText()
# create ROOT histograms 
h05 = ROOT.TH2D("h05nm","H = 5 nm",nqy,qymin,qymax, nqz, qzmin, qzmax)
h10 = ROOT.TH2D("h10nm","H = 10 nm",nqy,qymin,qymax, nqz, qzmin, qzmax)
h15 = ROOT.TH2D("h15nm","H = 15 nm",nqy,qymin,qymax, nqz, qzmin, qzmax)

# and fill them with the values
for i in range(nqy):
	qy = qymin + i*stepqy
	for j in range(nqz):
		qz = qzmin + j*stepqz
		k = cvector_t(0,qy,qz)
		h05.Fill(qy,qz,(abs(ff05.evaluate_for_q(k))/V05)**2)
		h10.Fill(qy,qz,(abs(ff10.evaluate_for_q(k))/V10)**2)
		h15.Fill(qy,qz,(abs(ff15.evaluate_for_q(k))/V15)**2)



# create a ROOT canvas and put all plots on it
c = ROOT.TCanvas("FormfactorSphere","Formfactor Sphere", 1200,400)

c.Divide(3,1)
h05.SetMinimum(5e-8)
#h05.SetMaximum(V05**2)
h05.SetMaximum(1)
h10.SetMinimum(5e-8)
#h10.SetMaximum(V10**2)
h10.SetMaximum(1)
h15.SetMinimum(5e-8)
#h15.SetMaximum(V15**2)
h15.SetMaximum(1)
h05.SetContour(50)
h10.SetContour(50)
h15.SetContour(50)
#h05.GetZaxis().SetTitle(" |F|^{2} ")
#h10.GetZaxis().SetTitle(" |F|^{2} ")
#h15.GetZaxis().SetTitle(" |F|^{2} ")


c.cd(1)
ROOT.gPad.SetLogz()
h05.GetXaxis().SetTitle(" q_{y} [nm^{-1}] ")
h05.GetXaxis().CenterTitle()
h05.GetXaxis().SetTitleOffset(1.1)
h05.GetYaxis().SetTitle(" q_{z} [nm^{-1}] ")
h05.GetYaxis().CenterTitle()
h05.GetYaxis().SetTitleOffset(1.4)
h05.GetZaxis().SetTitleOffset(1.3)
h05.Draw("col")
#t.SetNDC(1)
#t.SetTextSize(8.0e-2)
#t.DrawText(0.1, 0.01, "H = 5 nm")

c.cd(2)
ROOT.gPad.SetLogz()
h10.GetXaxis().SetTitle(" q_{y} [nm^{-1}] ")
h10.GetXaxis().CenterTitle()
h10.GetXaxis().SetTitleOffset(1.1)
h10.GetYaxis().SetTitle(" q_{z} [nm^{-1}] ")
h10.GetYaxis().CenterTitle()
h10.GetYaxis().SetTitleOffset(1.4)
h10.GetZaxis().SetTitleOffset(1.3)
h10.Draw("col")
#t.SetNDC(1)
#t.SetTextSize(8.0e-2)
#t.DrawText(0.1, 0.01, "H = 10 nm")

c.cd(3)
ROOT.gPad.SetLogz()
h15.GetXaxis().SetTitle(" q_{y} [nm^{-1}] ")
h15.GetXaxis().CenterTitle()
h15.GetXaxis().SetTitleOffset(1.1)
h15.GetYaxis().SetTitle(" q_{z} [nm^{-1}] ")
h15.GetYaxis().CenterTitle()
h15.GetYaxis().SetTitleOffset(1.4)
h15.GetZaxis().SetTitleOffset(1.3)
h15.Draw("col")
#t.SetNDC(1)
#t.SetTextSize(8.0e-2)
#t.DrawText(0.1, 0.01, "H = 15 nm")

# draw projections
#c.cd(4)
#ROOT.gPad.SetLogy()
#p05 = h05.ProjectionX("p05", fbin, lbin, 'o')
#p05.GetYaxis().SetTitle(" |F|^{2} ")
#p05.GetYaxis().SetTitleOffset(1.3)
#p05.Draw()
#t.DrawText(0.1, 0.01, "d")

#c.cd(5)
#ROOT.gPad.SetLogy()
#p10 = h10.ProjectionX("p10", fbin, lbin, 'o')
#p10.GetYaxis().SetTitle(" |F|^{2} ")
#p10.GetYaxis().SetTitleOffset(1.3)
#p10.Draw()
#t.DrawText(0.1, 0.01, "e")

#c.cd(6)
#ROOT.gPad.SetLogy()
#p15 = h15.ProjectionX("p15", fbin, lbin, 'o')
#p15.GetYaxis().SetTitle(" |F|^{2} ")
#p15.GetYaxis().SetTitleOffset(1.3)
#p15.Draw()
#t.DrawText(0.1, 0.01, "f")



c.Update()
ROOT.gApplication.Run()



