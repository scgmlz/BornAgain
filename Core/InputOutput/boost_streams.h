// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/boost_streams.h
//! @brief     Contains boost streams related headers
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INPUTOUTPUT_BOOST_STREAMS_H
#define BORNAGAIN_CORE_INPUTOUTPUT_BOOST_STREAMS_H

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

#endif // BORNAGAIN_CORE_INPUTOUTPUT_BOOST_STREAMS_H
