//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Py/PyObject.h
//! @brief     PyObvject forward declaration.
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
#ifndef BORNAGAIN_BASE_PY_PYOBJECT_H
#define BORNAGAIN_BASE_PY_PYOBJECT_H

#ifdef BORNAGAIN_PYTHON
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif
#endif

#endif // BORNAGAIN_BASE_PY_PYOBJECT_H
#endif // USER_API
