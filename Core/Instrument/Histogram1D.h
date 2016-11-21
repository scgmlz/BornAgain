// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/Histogram1D.h
//! @brief     Defines class Histogram1D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef HISTOGRAM1D_H
#define HISTOGRAM1D_H

#include "IHistogram.h"

//! One dimensional histogram.
//! @ingroup tools

class BA_CORE_API_ Histogram1D : public IHistogram
{
public:
    //! Constructor for fix bin size histograms.
    //! @param nbinsx number of bins
    //! @param xlow low edge of the first bin
    //! @param xup upper edge of the last bin
    Histogram1D(int nbinsx, double xlow, double xup);

    //! Constructor for variable bin size histograms.
    //! @param nbinsx number of bins
    //! @param xbins Array of size nbins+1 containing low-edges for each
    //! bin and upper edge of last bin.
    Histogram1D(int nbinsx, const std::vector<double>& xbins);

    //! Constructor for 1D histogram with custom axis
    Histogram1D(const IAxis& axis);

    //! Constructor for 1D histograms from basic OutputData object
    Histogram1D(const OutputData<double>& data);

    //! Returns clone of other histogram
    Histogram1D* clone() const;

    //! Returns the number of histogram dimensions
    size_t getRank() const { return 1;}

    //! Increment bin with abscissa x with a weight.
    int fill(double x, double weight = 1.0);

    //! returns vector of histogram bin centers
    std::vector<double> getBinCenters() const;

    //! returns vector of bin content (the value accumulated by bins)
    std::vector<double> getBinValues() const;

    //! returns vector of bin errors
    std::vector<double> getBinErrors() const;

#ifdef BORNAGAIN_PYTHON
    PyObject* getBinCentersNumpy() const;
    PyObject* getBinValuesNumpy() const;
    PyObject* getBinErrorsNumpy() const;
#endif

    //! Create new histogram by applying crop on axis.
    Histogram1D* crop(double xmin, double xmax);

};


#endif // HISTOGRAM1D_H
