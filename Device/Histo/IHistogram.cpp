//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Histo/IHistogram.cpp
//! @brief     Implements class IntensityDataObject.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Base/Math/Numeric.h"
#include "Device/Histo/Histogram1D.h"
#include "Device/Histo/Histogram2D.h"
#include "Device/Histo/IntensityDataIOFactory.h" // TODO rm
#include <memory>

IHistogram::IHistogram() = default;

IHistogram::IHistogram(const IHistogram& other) {
    m_data.copyFrom(other.m_data);
}

IHistogram::IHistogram(const IAxis& axis_x) {
    m_data.addAxis(axis_x);
}

IHistogram::IHistogram(const IAxis& axis_x, const IAxis& axis_y) {
    m_data.addAxis(axis_x);
    m_data.addAxis(axis_y);
}

size_t IHistogram::getTotalNumberOfBins() const {
    return m_data.getAllocatedSize();
}

const IAxis& IHistogram::xAxis() const {
    check_x_axis();
    return m_data.axis(0);
}

const IAxis& IHistogram::yAxis() const {
    check_y_axis();
    return m_data.axis(1);
}

double IHistogram::getXmin() const {
    return xAxis().lowerBound();
}

double IHistogram::getXmax() const {
    return xAxis().upperBound();
}

size_t IHistogram::getNbinsX() const {
    return xAxis().size();
}

double IHistogram::getYmin() const {
    return yAxis().lowerBound();
}

double IHistogram::getYmax() const {
    return yAxis().upperBound();
}

size_t IHistogram::getNbinsY() const {
    return yAxis().size();
}

size_t IHistogram::getGlobalBin(size_t binx, size_t biny) const {
    std::vector<unsigned> axes_indices;
    axes_indices.push_back(static_cast<unsigned>(binx));
    if (rank() == 2)
        axes_indices.push_back(static_cast<unsigned>(biny));
    return m_data.toGlobalIndex(axes_indices);
}

size_t IHistogram::findGlobalBin(double x, double y) const {
    std::vector<double> coordinates;
    coordinates.push_back(x);
    if (rank() == 2)
        coordinates.push_back(y);
    return m_data.findGlobalIndex(coordinates);
}

size_t IHistogram::xAxisIndex(size_t i) const {
    return m_data.getAxisBinIndex(i, 0);
}

size_t IHistogram::yAxisIndex(size_t i) const {
    return m_data.getAxisBinIndex(i, 1);
}

double IHistogram::xAxisValue(size_t i) {
    check_x_axis();
    return m_data.getAxisValue(i, 0);
}

double IHistogram::yAxisValue(size_t i) {
    check_y_axis();
    return m_data.getAxisValue(i, 1);
}

const OutputData<CumulativeValue>& IHistogram::getData() const {
    return m_data;
}

OutputData<CumulativeValue>& IHistogram::getData() {
    return m_data;
}

double IHistogram::binContent(size_t i) const {
    return m_data[i].getContent();
}

double IHistogram::binContent(size_t binx, size_t biny) const {
    return binContent(getGlobalBin(binx, biny));
}

void IHistogram::setBinContent(size_t i, double value) {
    m_data[i].setContent(value);
}

void IHistogram::addBinContent(size_t i, double value) {
    m_data[i].add(value);
}

double IHistogram::binError(size_t i) const {
    return m_data[i].getRMS();
}

double IHistogram::binError(size_t binx, size_t biny) const {
    return binError(getGlobalBin(binx, biny));
}

double IHistogram::binAverage(size_t i) const {
    return m_data[i].getAverage();
}

double IHistogram::binAverage(size_t binx, size_t biny) const {
    return binAverage(getGlobalBin(binx, biny));
}

int IHistogram::binNumberOfEntries(size_t i) const {
    return m_data[i].getNumberOfEntries();
}

int IHistogram::binNumberOfEntries(size_t binx, size_t biny) const {
    return binNumberOfEntries(getGlobalBin(binx, biny));
}

double IHistogram::getMaximum() const {
    OutputData<CumulativeValue>::const_iterator it = std::max_element(m_data.begin(), m_data.end());
    return it->getContent();
}

size_t IHistogram::getMaximumBinIndex() const {
    OutputData<CumulativeValue>::const_iterator it = std::max_element(m_data.begin(), m_data.end());
    return std::distance(m_data.begin(), it);
}

double IHistogram::getMinimum() const {
    OutputData<CumulativeValue>::const_iterator it = std::min_element(m_data.begin(), m_data.end());
    return it->getContent();
}

size_t IHistogram::getMinimumBinIndex() const {
    return std::distance(m_data.begin(), std::min_element(m_data.begin(), m_data.end()));
}

void IHistogram::scale(double value) {
    for (size_t index = 0; index < getTotalNumberOfBins(); ++index) {
        m_data[index].setContent(value * m_data[index].getContent());
    }
}

double IHistogram::integral() const {
    double result(0.0);
    for (size_t index = 0; index < getTotalNumberOfBins(); ++index) {
        result += m_data[index].getContent();
    }
    return result;
}

#ifdef BORNAGAIN_PYTHON
PyObject* IHistogram::array(DataType dataType) const {
    const std::unique_ptr<OutputData<double>> data(createOutputData(dataType));
    return data->getArray();
}

PyObject* IHistogram::getArray(DataType dataType) const {
    return array(dataType);
}
#endif // BORNAGAIN_PYTHON

void IHistogram::reset() {
    m_data.setAllTo(CumulativeValue());
}

IHistogram* IHistogram::createHistogram(const OutputData<double>& source) {
    if (source.rank() == 1) {
        return new Histogram1D(source);
    } else if (source.rank() == 2) {
        return new Histogram2D(source);
    } else {
        std::ostringstream message;
        message << "IHistogram::createHistogram(const OutputData<double>& source) -> Error. ";
        message << "The rank of source " << source.rank() << " ";
        message << "is not suitable for creation neither 1-dim nor 2-dim histograms.";
        throw std::runtime_error(message.str());
    }
}

IHistogram* IHistogram::createFrom(const std::string& filename) {
    return IntensityDataIOFactory::readIntensityData(filename);
}

IHistogram* IHistogram::createFrom(const std::vector<std::vector<double>>& data) {
    return new Histogram2D(data);
}

void IHistogram::check_x_axis() const {
    if (rank() < 1) {
        std::ostringstream message;
        message << "IHistogram::check_x_axis() -> Error. X-xis does not exist. ";
        message << "Rank of histogram " << rank() << "." << std::endl;
        throw std::runtime_error(message.str());
    }
}

void IHistogram::check_y_axis() const {
    if (rank() < 2) {
        std::ostringstream message;
        message << "IHistogram::check_y_axis() -> Error. Y-axis does not exist. ";
        message << "Rank of histogram " << rank() << "." << std::endl;
        throw std::runtime_error(message.str());
    }
}

void IHistogram::init_from_data(const OutputData<double>& source) {
    if (rank() != source.rank()) {
        std::ostringstream message;
        message << "IHistogram::IHistogram(const OutputData<double>& data) -> Error. ";
        message << "The dimension of this histogram " << rank() << " ";
        message << "is differ from the dimension of source " << m_data.rank() << std::endl;
        throw std::runtime_error(message.str());
    }

    m_data.copyShapeFrom(source);
    for (size_t i = 0; i < source.getAllocatedSize(); ++i) {
        m_data[i].add(source[i]);
    }
}

//! returns data of requested type for globalbin number
double IHistogram::binData(size_t i, IHistogram::DataType dataType) const {
    if (dataType == DataType::INTEGRAL) {
        return binContent(i);
    } else if (dataType == DataType::AVERAGE) {
        return binAverage(i);
    } else if (dataType == DataType::STANDARD_ERROR) {
        return binError(i);
    } else if (dataType == DataType::NENTRIES) {
        return binNumberOfEntries(i);
    } else
        throw std::runtime_error("IHistogram::binData() -> Error. Unknown data type.");
}

//! returns vector of values of requested DataType
std::vector<double> IHistogram::getDataVector(IHistogram::DataType dataType) const {
    std::vector<double> result;
    result.resize(getTotalNumberOfBins(), 0.0);
    for (size_t index = 0; index < getTotalNumberOfBins(); ++index) {
        result[index] = binData(index, dataType);
    }
    return result;
}

//! Copy content (but not the axes) from other histogram. Dimensions should be the same.
void IHistogram::copyContentFrom(const IHistogram& other) {
    if (!hasSameDimensions(other))
        throw std::runtime_error(
            "IHistogram::copyContentFrom() -> Error. Can't copy the data of different shape.");
    reset();
    for (size_t i = 0; i < getTotalNumberOfBins(); ++i) {
        m_data[i] = other.m_data[i];
    }
}

//! creates new OutputData with histogram's shape and put there values corresponding to DataType
OutputData<double>* IHistogram::createOutputData(IHistogram::DataType dataType) const {
    OutputData<double>* result = new OutputData<double>;
    result->copyShapeFrom(m_data);
    for (size_t i = 0; i < getTotalNumberOfBins(); ++i) {
        (*result)[i] = binData(i, dataType);
    }
    return result;
}

bool IHistogram::hasSameShape(const IHistogram& other) const {
    return m_data.hasSameShape(other.m_data);
}

bool IHistogram::hasSameDimensions(const IHistogram& other) const {
    return m_data.hasSameDimensions(other.m_data);
}

const IHistogram& IHistogram::operator+=(const IHistogram& right) {
    if (!hasSameDimensions(right))
        throw std::runtime_error(
            "IHistogram::operator+=() -> Error. Histograms have different dimension");
    for (size_t i = 0; i < getTotalNumberOfBins(); ++i)
        addBinContent(i, right.binContent(i));
    return *this;
}

IHistogram* IHistogram::relativeDifferenceHistogram(const IHistogram& rhs) {
    if (!hasSameDimensions(rhs))
        throw std::runtime_error("IHistogram::relativeDifferenceHistogram() -> Error. "
                                 "Histograms have different dimensions");

    IHistogram* result = this->clone();
    result->reset();

    for (size_t i = 0; i < getTotalNumberOfBins(); ++i) {
        double diff = Numeric::GetRelativeDifference(binContent(i), rhs.binContent(i));
        result->setBinContent(i, diff);
    }
    return result;
}

void IHistogram::save(const std::string& filename) {
    IntensityDataIOFactory::writeIntensityData(*this, filename);
}

void IHistogram::load(const std::string& filename) {
    const std::unique_ptr<IHistogram> hist(IntensityDataIOFactory::readIntensityData(filename));
    copyContentFrom(*hist);
}
