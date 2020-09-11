// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/swig/libBornAgainFit.i
//! @brief     SWIG interface file for libBornAgainFit
//!
//!            Configuration is done in Fit/CMakeLists.txt
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1", moduleimport="import $module") "libBornAgainFit"

%feature("autodoc");

%include "stdint.i"
%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_shared_ptr.i"

%include "shared_pointers.i"

%include "warnings.i"
%include "ignores.i"
%include "renameFit.i"
%include "directors.i"

%include "auto/Wrap/doxygen_fit.i"

%template(vdouble1d_t) std::vector<double>;
%template(vdouble2d_t) std::vector< std::vector<double> >;
%template(vector_integer_t) std::vector<int >;
%template(vector_longinteger_t) std::vector<unsigned long int >;
%template(vector_complex_t) std::vector< std::complex<double> >;
%template(vector_string_t) std::vector<std::string>;

#define SWIG_FILE_WITH_INIT

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
%}

%include "numpy.i"
%init %{
import_array();
%}

#ifndef BORNAGAIN_PYTHON
#define BORNAGAIN_PYTHON
#endif

%import "Wrap/WinDllMacros.h"

%{
#include "Fit/Tools/RealLimits.h"
#include "Fit/Tools/AttLimits.h"
#include "Fit/Kernel/Parameter.h"
#include "Fit/Kernel/Parameters.h"
#include "Fit/Minimizer/IMinimizer.h"
#include "Fit/Minimizer/MinimizerCatalog.h"
#include "Fit/Minimizer/MinimizerFactory.h"

#include "Fit/Kernel/PyCallback.h"
#include "Fit/Kernel/MinimizerResult.h"
#include "Fit/Kernel/Minimizer.h"
%}

// The following goes verbatim from libBornAgainFit.i to libBornAgainFit_wrap.cxx.
// Note that the order matters, as base classes must be included before derived classes.

%include "Fit/Tools/RealLimits.h"
%include "Fit/Tools/AttLimits.h"
%include "Fit/Kernel/Parameter.h"
%include "Fit/Kernel/Parameters.h"
%include "Fit/Kernel/PyCallback.h"
%include "Fit/Kernel/MinimizerResult.h"
%include "Fit/Kernel/Minimizer.h"
%include "Fit/Minimizer/IMinimizer.h"
%include "Fit/Minimizer/MinimizerCatalog.h"
%include "Fit/Minimizer/MinimizerFactory.h"

%include "extendFit.i"
