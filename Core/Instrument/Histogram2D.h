// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/Histogram2D.h
//! @brief     Defines class Histogram2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef HISTOGRAM2D_H
#define HISTOGRAM2D_H

#include "IHistogram.h"
#include "ArrayUtils.h"

#ifdef BORNAGAIN_PYTHON
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif
#endif

//! Two dimensional histogram.
//! @ingroup tools

class BA_CORE_API_ Histogram2D : public IHistogram
{
public:
    //! @brief Constructor for fix bin size histograms.
    //! @param nbinsx number of bins on X-axis
    //! @param xlow low edge of the first bin of X-axis
    //! @param xup upper edge of the last bin of X-axis
    //! @param nbinsy number of bins on Y axis
    //! @param ylow low edge of the first bin of Y-axis
    //! @param yup upper edge of the last bin of Y-axis
    Histogram2D(int nbinsx, double xlow, double xup, int nbinsy, double ylow, double yup);

    //! @brief Constructor for variable bin size histograms.
    //! @param nbinsx number of bins on X-axis
    //! @param xbins Array of size nbins+1 containing low-edges for each
    //! bin and upper edge of last bin.
    //! @param nbinsy number of bins on Y-axis
    //! @param ybins Array of size nbins+1 containing low-edges for each
    //! bin and upper edge of last bin.
    Histogram2D(int nbinsx, const std::vector<double>& xbins,
                int nbinsy, const std::vector<double>& ybins);

    //! Constructor for 2D histogram with custom axes
    Histogram2D(const IAxis& axis_x, const IAxis& axis_y);

    //! Constructor for 2D histograms from basic OutputData object
    Histogram2D(const OutputData<double>& data);

    //! Constructor for 2D histograms from numpy array (thanks to swig)
    Histogram2D(std::vector<std::vector<double>> data);

    //! Returns clone of other histogram
    Histogram2D* clone() const;

    //! Returns the number of histogram dimensions
    size_t getRank() const { return 2;}

    //! Increment bin with abscissa x and ordinate y with a weight.
    int fill(double x, double y, double weight = 1.0);

    //! Project a 2D histogram into 1D histogram along X. The projection is made
    //! from all bins along y-axis.
    Histogram1D* projectionX();

    //! @brief Project a 2D histogram into 1D histogram along X. The projection is made
    //! from the y-bin closest to given ordinate yvalue.
    //! @param yvalue the value on y-axis at which projection is taken
    Histogram1D* projectionX(double yvalue);

    //! @brief Project a 2D histogram into 1D histogram along X. The projection is made from
    //! all y-bins corresponding to ordinate between ylow and yup.
    //! @param ylow lower edje on y-axis
    //! @param yup upper edje on y-axis
    Histogram1D* projectionX(double ylow, double yup);

    //! Project a 2D histogram into 1D histogram along Y. The projection is made
    //! from all bins along x-axis.
    Histogram1D* projectionY();

    //! @brief Project a 2D histogram into 1D histogram along Y. The projection is made
    //! from the x-bin closest to given abscissa xvalue.
    //! @param xvalue the value on x-axis at which projection is taken
    Histogram1D* projectionY(double xvalue);

    //! @brief Project a 2D histogram into 1D histogram along Y. The projection is made from
    //! all x-bins corresponding to abscissa between xlow and xup.
    //! @param xlow lower edje on x-axis
    //! @param xup upper edje on x-axis
    Histogram1D* projectionY(double xlow, double xup);

    //! Create new histogram by applying rectangular clip.
    Histogram2D* crop(double xmin, double ymin, double xmax, double ymax);

    //! Sets the values in histograms channels from numpy array,
    void setContent(const std::vector<std::vector<double>>& data);

    //! Add to values in histograms channels from numpy array,
    void addContent(const std::vector<std::vector<double>>& data);

protected:
    template<typename T>
    void initFromShape(const T& data);

    //! Creates projection along X. The projections is made by collecting the data in the range
    //! between [ybinlow, ybinup].
    Histogram1D* create_projectionX(int ybinlow, int ybinup);

    //! Creates projection along Y. The projections is made by collecting the data in the range
    //! between [xbinlow, xbinup].
    Histogram1D* create_projectionY(int xbinlow, int xbinup);
};


template<typename T> void Histogram2D::initFromShape(const T& data)
{
    auto shape = ArrayUtils::getShape(data);
    const size_t nrows = shape.first;
    const size_t ncols = shape.second;

    if(nrows == 0 || ncols == 0)
        throw Exceptions::LogicErrorException("Histogram2D::Histogram2D() -> Error. "
                                              "Not a two-dimensional numpy array");

    m_data.addAxis(FixedBinAxis("x-axis", ncols, 0.0, static_cast<double>(ncols)));
    m_data.addAxis(FixedBinAxis("y-axis", nrows, 0.0, static_cast<double>(nrows)));

}

#endif // HISTOGRAM2D_H
