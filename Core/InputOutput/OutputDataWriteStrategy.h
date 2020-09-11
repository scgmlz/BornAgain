// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataWriteStrategy.h
//! @brief    Defines classes IOutputDataWriteStrategy and OutputDataWriteStreamIMA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAWRITESTRATEGY_H
#define BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAWRITESTRATEGY_H

#include "Wrap/WinDllMacros.h"
#include <istream>

template <class T> class OutputData;

//! Strategy interface to write OututData in file
//! @ingroup input_output_internal

class BA_CORE_API_ IOutputDataWriteStrategy
{
public:
    IOutputDataWriteStrategy() {}
    virtual ~IOutputDataWriteStrategy() {}

    virtual void writeOutputData(const OutputData<double>& data, std::ostream& output_stream) = 0;
};

//! Strategy to write OutputData to special BornAgain ASCII format
//! @ingroup input_output_internal

class BA_CORE_API_ OutputDataWriteINTStrategy : public IOutputDataWriteStrategy
{
public:
    virtual void writeOutputData(const OutputData<double>& data, std::ostream& output_stream);
};

//! Strategy to write OutputData to simple ASCII file with the layout as in numpy.savetxt
//! @ingroup input_output_internal

class BA_CORE_API_ OutputDataWriteNumpyTXTStrategy : public IOutputDataWriteStrategy
{
public:
    virtual void writeOutputData(const OutputData<double>& data, std::ostream& output_stream);
};

#ifdef BORNAGAIN_TIFF_SUPPORT

class TiffHandler;

//! Strategy to write OutputData to tiff files
//! @ingroup input_output_internal

class BA_CORE_API_ OutputDataWriteTiffStrategy : public IOutputDataWriteStrategy
{
public:
    OutputDataWriteTiffStrategy();
    virtual ~OutputDataWriteTiffStrategy();
    virtual void writeOutputData(const OutputData<double>& data, std::ostream& output_stream);

private:
    TiffHandler* m_d;
};

#endif // BORNAGAIN_TIFF_SUPPORT

#endif // BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAWRITESTRATEGY_H
