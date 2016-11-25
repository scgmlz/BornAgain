// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataWriteStrategy.h
//! @brief     Defines classes IOutputDataWriteStrategy and OutputDataWriteStreamIMA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAWRITESTRATEGY_H
#define OUTPUTDATAWRITESTRATEGY_H

#include "WinDllMacros.h"
#include <istream>

template <class T> class OutputData;

//! @class IOutputDataWriteStrategy
//! @ingroup input_output_internal
//! @brief Strategy interface to write OututData in file

class BA_CORE_API_ IOutputDataWriteStrategy
{
public:
    IOutputDataWriteStrategy() {}
    virtual ~IOutputDataWriteStrategy() {}

    virtual void writeOutputData(const OutputData<double>& data, std::ostream& output_stream) = 0;
};

//! @class OutputDataWriteINTStrategy
//! @ingroup input_output_internal
//! @brief Strategy to write OutputData to special BornAgain ASCII format
class OutputDataWriteINTStrategy : public IOutputDataWriteStrategy
{
public:
    virtual void writeOutputData(const OutputData<double>& data, std::ostream& output_stream);
};

//! @class OutputDataWriteNumpyTXTStrategy
//! @ingroup input_output_internal
//! @brief Strategy to write OutputData to simple ASCII file with the layout as in numpy.savetxt
class OutputDataWriteNumpyTXTStrategy : public IOutputDataWriteStrategy
{
public:
    virtual void writeOutputData(const OutputData<double>& data, std::ostream& output_stream);
};

#ifdef BORNAGAIN_TIFF_SUPPORT

class TiffHandler;

//! @class OutputDataWriteTiffStrategy
//! @ingroup input_output_internal
//! @brief Strategy to write OutputData to tiff files
class OutputDataWriteTiffStrategy : public IOutputDataWriteStrategy
{
public:
    OutputDataWriteTiffStrategy();
    virtual ~OutputDataWriteTiffStrategy();
    virtual void writeOutputData(const OutputData<double>& data, std::ostream& output_stream);

private:
    TiffHandler* m_d;
};

#endif // BORNAGAIN_TIFF_SUPPORT

#endif // OUTPUTDATAWRITESTRATEGY_H
