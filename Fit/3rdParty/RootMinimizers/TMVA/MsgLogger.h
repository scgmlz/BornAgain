// @(#)root/tmva $Id$
// Author: Attila Krasznahorkay, Andreas Hoecker, Joerg Stelzer, Eckhard von Toerne

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  : MsgLogger                                                             *
 * Web    : http://tmva.sourceforge.net                                           *
 *                                                                                *
 * Description:                                                                   *
 *      TMVA output logger class producing nicely formatted log messages          *
 *                                                                                *
 * Author:                                                                        *
 *      Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch> - CERN, Switzerland   *
 *      Andreas Hoecker       <Andreas.Hocker@cern.ch> - CERN, Switzerland        *
 *      Joerg Stelzer         <stelzer@cern.ch>        - DESY, Germany            *
 *      Eckhard v. Toerne     <evt@uni-bonn.de>        - U of Bonn, Germany       *
 *                                                                                *
 * Copyright (c) 2005-2011:                                                       *
 *      CERN, Switzerland                                                         *
 *      U. of Victoria, Canada                                                    *
 *      MPI-K Heidelberg, Germany                                                 *
 *      U. of Bonn, Germany                                                       *
 *                                                                                *
 * Redistribution and use in source and binary forms, with or without             *
 * modification, are permitted according to the terms listed in LICENSE           *
 * (http://tmva.sourceforge.net/LICENSE)                                          *
 **********************************************************************************/

#ifndef ROOT_TMVA_MsgLogger
#define ROOT_TMVA_MsgLogger

#include "TMVA/Types.h"
#include "TObject.h"
#include <iostream>
#include <sstream>
#include <string>

namespace TMVA
{

class MsgLogger : public std::ostringstream, public TObject
{

public:
    MsgLogger(const std::string& source)
        : fStrSource(source)
    {
    }

    MsgLogger& operator<<(MsgLogger& (*_f)(MsgLogger&));
    MsgLogger& operator<<(std::ostream& (*_f)(std::ostream&));
    MsgLogger& operator<<(std::ios& (*_f)(std::ios&));

    // Accept message type specification
    MsgLogger& operator<<(EMsgType type);

    // For all the "conventional" inputs
    template <class T> MsgLogger& operator<<(T arg)
    {
        *(std::ostringstream*)this << arg;
        return *this;
    }

private:
    std::string fStrSource;
};

inline MsgLogger& MsgLogger::operator<<(MsgLogger& (*_f)(MsgLogger&)) { return (_f)(*this); }

inline MsgLogger& MsgLogger::operator<<(std::ostream& (*_f)(std::ostream&))
{
    (_f)(*this);
    return *this;
}

inline MsgLogger& MsgLogger::operator<<(std::ios& (*_f)(std::ios&))
{
    (_f)(*this);
    return *this;
}

inline MsgLogger& MsgLogger::operator<<(EMsgType type) { *(std::ostringstream*)this << type << " "; return *this; }

inline MsgLogger& Endl(MsgLogger& ml)
{
    ml << "\n";
    return ml;
}
}

#endif // TMVA_MsgLogger
