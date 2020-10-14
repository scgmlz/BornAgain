// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/swig/libBornAgainBase.i
//! @brief     SWIG interface file for libBornAgainBase
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1", moduleimport="import $module") "libBornAgainBase"

%include "commons.i"

%include "../../auto/Wrap/doxygenBase.i"

%include "ignoreBase.i"

%{
#include "Base/Types/Complex.h"
#include "Base/Types/ICloneable.h"
#include "Base/Const/Units.h"
#include "Base/Utils/ThreadInfo.h"

#include "Base/Vector/BasicVector3D.h"
#include "Base/Vector/Vectors3D.h"

#include "Base/Utils/MathFunctions.h"

#include "Base/Axis/Bin.h"
#include "Base/Axis/ConstKBinAxis.h"
#include "Base/Axis/CustomBinAxis.h"
#include "Base/Axis/FixedBinAxis.h"
#include "Base/Axis/VariableBinAxis.h"

#include "Base/Pixel/IPixel.h"

%}

%include "Base/Types/ICloneable.h"
%include "Base/Types/Complex.h"
%include "Base/Const/Units.h"

%include "Base/Utils/MathFunctions.h"
%include "Base/Utils/ThreadInfo.h"

%include "Base/Vector/BasicVector3D.h"
%include "Base/Vector/Vectors3D.h"

%include "Base/Axis/Bin.h"
%include "Base/Axis/IAxis.h"
%include "Base/Axis/VariableBinAxis.h"
%include "Base/Axis/ConstKBinAxis.h"
%include "Base/Axis/CustomBinAxis.h"
%include "Base/Axis/FixedBinAxis.h"

%include "Base/Pixel/IPixel.h"

%include "fromBase.i"

%extend FixedBinAxis {
    double __getitem__(unsigned int i) { return (*($self))[i]; }
};

%extend VariableBinAxis {
    double __getitem__(unsigned int i) { return (*($self))[i]; }
};
