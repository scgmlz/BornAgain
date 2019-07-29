// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/PyEmbeddedUtils.cpp
//! @brief     IOmplements various functions from PyEmbeddedUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PyEmbeddedUtils.h"
#include "PythonCore.h"
#include "PythonFormatting.h"
#include "MultiLayer.h"
#include "SysUtils.h"
#include <stdexcept>
#include <iostream>


std::string PyEmbeddedUtils::toString(PyObject* obj)
{
    std::string result;
#if PY_MAJOR_VERSION >= 3
    PyObject* pyStr = PyUnicode_AsEncodedString(obj, "utf-8", "Error ~");
    result = std::string(PyBytes_AsString(pyStr));
    Py_DecRef(pyStr);
#else
    result = std::string(PyString_AsString(obj));
#endif

    return result;
}

std::vector<std::string> PyEmbeddedUtils::toVectorString(PyObject* obj)
{
    std::vector<std::string> result;

    if (PyTuple_Check(obj)) {
        for (Py_ssize_t i = 0; i < PyTuple_Size(obj); i++) {
            PyObject *value = PyTuple_GetItem(obj, i);
            result.push_back( toString(value) );
        }

    } else if (PyList_Check(obj)) {
        for (Py_ssize_t i = 0; i < PyList_Size(obj); i++) {
            PyObject *value = PyList_GetItem(obj, i);
            result.push_back( toString(value) );
        }

    } else {
        throw std::runtime_error("PyEmbeddedUtils::toVectorString() -> Error. Unexpected object.");
    }

    return result;
}


std::string PyEmbeddedUtils::toString(char* c)
{
    if (c)
        return std::string(c);
    else
        return std::string();
}


std::string PyEmbeddedUtils::toString(wchar_t* c)
{
    if (c) {
        std::wstring wstr(c);
        std::string result( wstr.begin(), wstr.end() );
        return result;
    } else {
        return std::string();
    }
}

void PyEmbeddedUtils::import_bornagain(const std::string& path)
{
    if (!Py_IsInitialized()) {
        Py_InitializeEx(0);

        if (!path.empty()) {
            PyObject *sysPath = PySys_GetObject((char*)"path");
            PyList_Append(sysPath, PyString_FromString(path.c_str()));
        }


        // Stores signal handler before numpy's mess it up.
        // This is to make ctrl-c working from terminal.
#ifndef _WIN32
        PyOS_sighandler_t sighandler;
        sighandler = PyOS_getsig(SIGINT);
#endif
        PyObject* pmod = PyImport_ImportModule("bornagain");
        if (!pmod) {
            PyErr_Print();
            throw std::runtime_error("Can't load bornagain");
        }

        // restores single handler to make ctr-c alive.
#ifndef _WIN32
        PyOS_setsig(SIGINT, sighandler);
#endif

    }

}

std::string PyEmbeddedUtils::pythonRuntimeInfo()
{
    Py_InitializeEx(0);

    std::stringstream result;

    // Runtime environment
    result << std::string(60, '=') << "\n";
    result << "PATH: " << SysUtils::getenv("PATH") << "\n";
    result << "PYTHONPATH: " << SysUtils::getenv("PYTHONPATH") << "\n";
    result << "PYTHONHOME: " << SysUtils::getenv("PYTHONHOME") << "\n";

    // Embedded Python details
    result << "Py_GetProgramName(): "
           << PyEmbeddedUtils::toString(Py_GetProgramName()) << "\n";
    result << "Py_GetProgramFullPath(): "
           << PyEmbeddedUtils::toString(Py_GetProgramFullPath()) << "\n";
    result << "Py_GetPath(): "
           << PyEmbeddedUtils::toString(Py_GetPath()) << "\n";
    result << "Py_GetPythonHome(): "
           << PyEmbeddedUtils::toString(Py_GetPythonHome()) << "\n";

    // Runtime Python's sys.path
    PyObject *sysPath = PySys_GetObject((char*)"path");
    auto content = PyEmbeddedUtils::toVectorString(sysPath);
    result << "sys.path: ";
    for (auto s : content)
        result << s << ",";
    result << "\n";

    return result.str();
}

// Attempt to retrieve Python stack trace
// https://stackoverflow.com/questions/1796510/accessing-a-python-traceback-from-the-c-api

std::string PyEmbeddedUtils::pythonStackTrace()
{
    std::stringstream result;

    if (PyErr_Occurred()) {
        PyObject *ptype, *pvalue, *ptraceback, *pystr;

        PyErr_Fetch(&ptype, &pvalue, &ptraceback);
        pystr = PyObject_Str(pvalue);
        if (char* str = PyString_AsString(pystr))
            result << std::string(str) << "\n";

        PyObject* module_name = PyString_FromString("traceback");
        PyObject* pyth_module = PyImport_Import(module_name);
        Py_DecRef(module_name);

        if (pyth_module) {
            result << "\n";
            PyObject* pyth_func = PyObject_GetAttrString(pyth_module, "format_exception");
            if (pyth_func && PyCallable_Check(pyth_func)) {
                PyObject* pyth_val = PyObject_CallFunctionObjArgs(pyth_func, ptype, pvalue, ptraceback, NULL);
                if (pyth_val) {
                    pystr = PyObject_Str(pyth_val);
                    if (char* str = PyString_AsString(pystr))
                        result << std::string(str);
                    Py_DecRef(pyth_val);
                }
            }
            result << "\n";
        }
    }

    result << "\n";
    result << pythonRuntimeInfo();
    result << "\n";

    return result.str();
}
