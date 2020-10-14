// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/swig/libBornAgainParam.i
//! @brief     SWIG interface file for libBornAgainParam
//!
//!            Configuration is done in Param/CMakeLists.txt
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1", moduleimport="import $module") "libBornAgainParam"

%include "commons.i"

%include "../../auto/Wrap/doxygenParam.i"

%include "ignoreBase.i"

%feature("director") IParameterized;     // needed by ISampleBuilder
%feature("director") INode;              // needed by ISample

%nodefaultctor ParameterPool;

%{
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include "Param/Base/IParameterized.h"

#include "Param/Node/INode.h"
#include "Param/Node/INodeVisitor.h"

#include "Param/Distrib/Distributions.h"
#include "Param/Distrib/ParameterDistribution.h"
#include "Param/Varia/ParameterSample.h"
#include "Param/Distrib/RangedDistributions.h"

%}

%import(module="libBornAgainBase") "Base/Types/Complex.h"
%import(module="libBornAgainBase") "Base/Types/ICloneable.h"
%import(module="libBornAgainBase") "Base/Vector/BasicVector3D.h"
%import(module="libBornAgainBase") "Base/Vector/Vectors3D.h"
%include "fromBase.i"

%ignore IParameterized::addParametersToExternalPool(const std::string&, ParameterPool*, int) const;
%ignore IParameterized::addParametersToExternalPool(const std::string&, ParameterPool*) const;
%ignore RangedDistribution;

%template(swig_dummy_type_inode_vector) std::vector<INode*>;
%template(swig_dummy_type_const_inode_vector) std::vector<const INode*>;

%include "Param/Base/IParameter.h"
%template(IParameterReal) IParameter<double>; // needed to avoid warning 401?

%include "Param/Base/RealParameter.h"
%include "Param/Base/ParameterPool.h"
%include "Param/Base/IParameterized.h"

%include "Param/Node/INode.h"
%include "Param/Node/INodeVisitor.h"

%include "Param/Distrib/Distributions.h"
%include "Param/Distrib/Distributions.h"
%include "Param/Distrib/ParameterDistribution.h"
%include "Param/Distrib/RangedDistributions.h"

%include "Param/Varia/ParameterSample.h"
%template(ParameterSampleVector) std::vector<ParameterSample>;

// --- ParameterPool accessors

%pythoncode %{
class ParameterPoolIterator(object):

    def __init__(self, pool):
        self.pool = pool
        self.index = -1

    def __iter__(self):
        return self

    def next(self):
        self.index += 1
        if self.index < self.pool.size():
            return self.pool[self.index]
        else:
            raise StopIteration

    def __next__(self):
        return self.next()
%}


%extend ParameterPool {
    const RealParameter* __getitem__(size_t index) const
    {
        return (*($self))[index];
    }

%pythoncode {
    def __iter__(self):
        return ParameterPoolIterator(self)
}
};
