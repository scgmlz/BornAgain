//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/InputOutput/boost_streams.h
//! @brief     Contains boost streams related headers
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_DEVICE_INPUTOUTPUT_BOOST_STREAMS_H
#define BORNAGAIN_DEVICE_INPUTOUTPUT_BOOST_STREAMS_H

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#endif
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BORNAGAIN_DEVICE_INPUTOUTPUT_BOOST_STREAMS_H
#endif // USER_API
