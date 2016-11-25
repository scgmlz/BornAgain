// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataReadStrategy.h
//! @brief     Defines IOutputDataReadStrategy and related classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAREADSTRATEGY_H
#define OUTPUTDATAREADSTRATEGY_H

#include "WinDllMacros.h"
#include <istream>

template <class T> class OutputData;

//! @class IOutputDataReadStrategy
//! @ingroup input_output_internal
//! @brief Interface for reading strategy of OutputData from file
class BA_CORE_API_ IOutputDataReadStrategy
{
public:
    virtual ~IOutputDataReadStrategy() {}
    virtual OutputData<double>* readOutputData(std::istream& input_stream) = 0;
};


//! @class OutputDataReadINTStrategy
//! @ingroup input_output_internal
//! @brief Strategy to read BornAgain native IntensityData from ASCII file
class OutputDataReadINTStrategy : public IOutputDataReadStrategy
{
public:
    OutputData<double>* readOutputData(std::istream& input_stream);
};

//! @class OutputDataReadNumpyTXTStrategy
//! @ingroup input_output_internal
//! @brief Strategy to read OutputData from simple ASCII file with the layout as in numpy.savetxt
class OutputDataReadNumpyTXTStrategy : public IOutputDataReadStrategy
{
public:
    OutputData<double>* readOutputData(std::istream& input_stream);
};


#ifdef BORNAGAIN_TIFF_SUPPORT

class TiffHandler;

//! @class OutputDataReadTiffStrategy
//! @ingroup input_output_internal
//! @brief Reads tiff files

class BA_CORE_API_ OutputDataReadTiffStrategy : public IOutputDataReadStrategy
{
public:
    OutputDataReadTiffStrategy();
    virtual ~OutputDataReadTiffStrategy();
    virtual OutputData<double>* readOutputData(std::istream& input_stream);

private:
    TiffHandler* m_d;
};
#endif // BORNAGAIN_TIFF_SUPPORT

#endif // OUTPUTDATAREADSTRATEGY_H
