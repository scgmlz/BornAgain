// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyEmbedded/Tests.cpp
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "BABuild.h"
#include "BAVersion.h"
#include "Core/Export/ExportToPython.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/PyIO/PyEmbeddedUtils.h"
#include "Core/PyIO/PyImport.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Core/Tools/PyFmt.h"
#include "Core/Tools/PythonCore.h"
#include "Core/Tools/SysUtils.h"
#include "Tests/GTestWrapper/google_test.h"
#include <iostream>
#include <sstream>

class PyEmbedded : public ::testing::Test
{
};

//! Accessing to the information about Python used during the build, content of path.sys variable.

TEST_F(PyEmbedded, SysPath)
{
    // Python build info
    std::cout << "pythonExecutable(): " << BABuild::pythonExecutable() << std::endl;
    std::cout << "pythonInterpreterID(): " << BABuild::pythonInterpreterID() << std::endl;
    std::cout << "pythonVersionString(): " << BABuild::pythonVersionString() << std::endl;
    std::cout << "pythonLibraries(): " << BABuild::pythonLibraries() << std::endl;
    std::cout << "pythonIncludeDirs(): " << BABuild::pythonIncludeDirs() << std::endl;
    std::cout << "pythonSiteLib(): " << BABuild::pythonSiteLib() << std::endl;
    std::cout << "numpyIncludeDir(): " << BABuild::numpyIncludeDir() << std::endl;
    std::cout << "numpyVersionString(): " << BABuild::numpyVersionString() << std::endl;

    // BornAgain build
    std::cout << "buildLibDir(): " << BABuild::buildLibDir() << std::endl;

    // Runtime info
    auto content = PyEmbeddedUtils::pythonRuntimeInfo();

    EXPECT_TRUE(!content.empty());
}

//! Importing numpy and accessing its version string.

TEST_F(PyEmbedded, ImportNumpy)
{
    Py_Initialize();

    PyObject* pmod = PyImport_ImportModule("numpy");
    if (!pmod)
        throw std::runtime_error("Can't load numpy");

    PyObject* pvar = PyObject_GetAttrString(pmod, "__version__");
    Py_DecRef(pmod);
    if (!pvar)
        throw std::runtime_error("Can't get a variable");

    auto version_string = PyEmbeddedUtils::toString(pvar);
    Py_DecRef(pvar);
    std::cout << "numpy_version_string=" << version_string << std::endl;

    Py_Finalize();

    EXPECT_TRUE(!version_string.empty());
}

//! Comparing results of GetVersionNumber() function obtained in "embedded" and "native C++" ways.

TEST_F(PyEmbedded, FunctionCall)
{
    Py_Initialize();

    PyObject* sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath, PyString_FromString("."));
    PyList_Append(sysPath, PyString_FromString(BABuild::buildLibDir().c_str()));

    PyObject* pmod = PyImport_ImportModule("bornagain");
    if (!pmod)
        throw std::runtime_error("Can't load module");

    PyObject* pfun = PyObject_GetAttrString(pmod, "GetVersionNumber");
    Py_DecRef(pmod);
    if (!pfun)
        throw std::runtime_error("Can't get a function");

    PyObject* pargs = Py_BuildValue("()");
    if (!pargs) {
        Py_DecRef(pfun);
        throw std::runtime_error("Can't build arguments list");
    }

    PyObject* result = PyEval_CallObject(pfun, pargs);
    Py_DecRef(pfun);
    Py_DecRef(pargs);
    if (!result)
        throw std::runtime_error("Error while calling function");

    auto str = PyEmbeddedUtils::toString(result);
    Py_DecRef(result);

    Py_Finalize();

    std::cout << "BornAgain version via Python: '" << str << "'\n";
    std::cout << "BornAgain version from Core:  '" << BornAgain::GetVersionNumber() << "'\n";
    if (str != BornAgain::GetVersionNumber()) {
        std::cout << "Version numbers disagree, test will fail.\n"
                  << "Possible reasons:\n"
                  << "- Python bindings not regenerated\n"
                  << "- Python module load from wrong location\n";
        EXPECT_TRUE(false);
    }
    EXPECT_TRUE(true);
}

//! Creating instance of FormFactorCylinder and calling its method in embedded Python.

TEST_F(PyEmbedded, MethodCall)
{
    const double radius(5.0), height(6.0);
    Py_Initialize();

    PyObject* sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath, PyString_FromString("."));
    PyList_Append(sysPath, PyString_FromString(BABuild::buildLibDir().c_str()));

    PyObject* pmod = PyImport_ImportModule("bornagain");
    if (!pmod)
        throw std::runtime_error("Can't load module");

    PyObject* pclass = PyObject_GetAttrString(pmod, "FormFactorCylinder");
    Py_DecRef(pmod);
    if (!pclass)
        throw std::runtime_error("Can't get a class");

    PyObject* pargs = Py_BuildValue("(dd)", radius, height);
    if (!pargs) {
        Py_DecRef(pclass);
        throw std::runtime_error("Can't build arguments list");
    }

    PyObject* pinst = PyEval_CallObject(pclass, pargs);
    Py_DecRef(pclass);
    Py_DecRef(pargs);

    if (!pinst)
        throw std::runtime_error("Error while creating object");

    // result of FormFactorCylinder
    PyObject* pmeth = PyObject_GetAttrString(pinst, "getHeight");
    Py_DecRef(pinst);
    if (!pmeth)
        throw std::runtime_error("Can't fetch FormFactorCylinder.getHeight");

    PyObject* pargs2 = Py_BuildValue("()");
    if (!pargs2) {
        Py_DECREF(pmeth);
        throw std::runtime_error("Can't build arguments list");
    }

    PyObject* pres = PyEval_CallObject(pmeth, pargs2);
    Py_DecRef(pmeth);
    Py_DecRef(pargs);

    if (!pres)
        throw std::runtime_error("Error calling FormFactorCylinder.getHeight()");

    double value(0);
    if (!PyArg_Parse(pres, "d", &value))
        throw std::runtime_error("Can't convert class method result");

    Py_DecRef(pres);

    Py_Finalize();

    EXPECT_TRUE(value == height);
}

//! From https://www.awasu.com/weblog/embedding-python/calling-python-code-from-your-program/

TEST_F(PyEmbedded, CompiledFunction)
{
    Py_Initialize();

    // compile our function
    std::stringstream buf;
    buf << "def add( n1 , n2 ) :" << std::endl << "    return n1+n2" << std::endl;

    PyObject* pCompiledFn = Py_CompileString(buf.str().c_str(), "", Py_file_input);
    if (!pCompiledFn)
        throw std::runtime_error("Can't compile a function");

    // create a module
    PyObject* pModule = PyImport_ExecCodeModule((char*)"test", pCompiledFn);
    if (!pModule)
        throw std::runtime_error("Can't exec module");

    // locate the "add" function (it's an attribute of the module)
    PyObject* pAddFn = PyObject_GetAttrString(pModule, "add");
    if (!pAddFn)
        throw std::runtime_error("Can't locate compiled functione");

    // clean up
    Py_DecRef(pAddFn);
    Py_DecRef(pModule);
    Py_DecRef(pCompiledFn);

    // ------------------------
    // using compiled function
    // ------------------------

    // create a new tuple with 2 elements
    PyObject* pPosArgs = PyTuple_New(2);

    PyObject* pVal1 = PyInt_FromLong(10);
    if (!pVal1)
        throw std::runtime_error("Can't create PyInt");
    int rc = PyTuple_SetItem(pPosArgs, 0, pVal1); // nb: tuple position 0
    if (rc != 0)
        throw std::runtime_error("Can't add to tuple");

    PyObject* pVal2 = PyInt_FromLong(20);
    if (!pVal2)
        throw std::runtime_error("Can't create PyInt");
    rc = PyTuple_SetItem(pPosArgs, 1, pVal2); // nb: tuple position 0
    if (rc != 0)
        throw std::runtime_error("Can't add to tuple");

    // create a new dictionary
    PyObject* pKywdArgs = PyDict_New();
    if (!pKywdArgs)
        throw std::runtime_error("Can't create dictionary");

    // call our function
    PyObject* pResult = PyObject_Call(pAddFn, pPosArgs, pKywdArgs);
    if (!pResult)
        throw std::runtime_error("Can't get result out of function");

    // convert the result to a string
    PyObject* pResultRepr = PyObject_Repr(pResult);
    std::string result = PyEmbeddedUtils::toString(pResultRepr);
    Py_DecRef(pResultRepr);

    Py_Finalize();

    EXPECT_TRUE(result == "30");
}

//! Creating MultiLayer in Python and extracting object to C++.
//! https://stackoverflow.com/questions/9040669/how-can-i-implement-a-c-class-in-python-to-be-called-by-c/

TEST_F(PyEmbedded, ObjectExtract)
{
    Py_Initialize();

    PyObject* sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath, PyString_FromString(BABuild::buildLibDir().c_str()));

    PyObject* pmod = PyImport_ImportModule("bornagain");
    if (!pmod)
        throw std::runtime_error("Can't load bornagain");

    PyObject* ml = PyObject_GetAttrString(pmod, "MultiLayer");
    Py_DecRef(pmod);
    if (!ml)
        throw std::runtime_error("Can't get MultiLayer attribute.");

    PyObject* instance = PyObject_CallFunctionObjArgs(ml, NULL);

    void* argp1 = 0;
    swig_type_info* pTypeInfo = SWIG_TypeQuery("MultiLayer *");

    const int res = SWIG_ConvertPtr(instance, &argp1, pTypeInfo, 0);
    if (!SWIG_IsOK(res))
        throw std::runtime_error("SWIG failed extract object");

    MultiLayer* multilayer = reinterpret_cast<MultiLayer*>(argp1);
    std::string name = multilayer->getName();

    Py_DecRef(instance);
    Py_DecRef(ml);

    Py_Finalize();

    EXPECT_TRUE(name == "MultiLayer");
}

//! Running Python snippet which creates a multilayer in embedded way.
//! Casting resulting PyObject to C++ MultiLayer.

TEST_F(PyEmbedded, EmbeddedMultiLayer)
{
    Py_Initialize();

    PyObject* sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath, PyString_FromString(BABuild::buildLibDir().c_str()));

    PyObject* pmod = PyImport_ImportModule("bornagain");
    if (!pmod)
        throw std::runtime_error("Can't load bornagain");

    // compile our function
    std::stringstream buf;
    buf << "import bornagain as ba                                        \n";
    buf << "                                                              \n";
    buf << "def get_simulation():                                         \n";
    buf << "    m_ambience = ba.HomogeneousMaterial(\"Air\", 0.0, 0.0)    \n";
    buf << "    air_layer = ba.Layer(m_ambience)                          \n";
    buf << "    multilayer = ba.MultiLayer()                              \n";
    buf << "    multilayer.addLayer(air_layer)                            \n";
    buf << "    return multilayer                                         \n";

    PyObject* pCompiledFn = Py_CompileString(buf.str().c_str(), "", Py_file_input);
    if (!pCompiledFn)
        throw std::runtime_error("Can't compile a function");

    // create a module
    PyObject* pModule = PyImport_ExecCodeModule((char*)"test", pCompiledFn);
    if (!pModule)
        throw std::runtime_error("Can't exec module");

    // locate the "get_simulation" function (it's an attribute of the module)
    PyObject* pAddFn = PyObject_GetAttrString(pModule, "get_simulation");
    if (!pAddFn)
        throw std::runtime_error("Can't locate compiled functione");

    PyObject* instance = PyObject_CallFunctionObjArgs(pAddFn, NULL);
    if (!instance)
        throw std::runtime_error("Can't call function");

    // clean up
    Py_DecRef(pAddFn);
    Py_DecRef(pModule);
    Py_DecRef(pCompiledFn);

    void* argp1 = 0;
    swig_type_info* pTypeInfo = SWIG_TypeQuery("MultiLayer *");

    const int res = SWIG_ConvertPtr(instance, &argp1, pTypeInfo, 0);
    if (!SWIG_IsOK(res))
        throw std::runtime_error("SWIG failed extract object");

    MultiLayer* multilayer = reinterpret_cast<MultiLayer*>(argp1);
    size_t n_layers = multilayer->numberOfLayers();

    Py_DecRef(instance);

    Py_Finalize();

    EXPECT_TRUE(n_layers == 1);
}

//! We use one of our standard sample builders to build a sample, then generate Python snippet
//! using our standard ExportToPython machinery.
//! Given snippet is compiled and executed in embedded interpretor. Resulting multi layer
//! is casted back to C++ object and used again, to generate code snippet.
//! Two code snippets must be identical.

TEST_F(PyEmbedded, ExportToPythonAndBack)
{
    SampleBuilderFactory factory;
    std::unique_ptr<MultiLayer> sample(factory.createSample("CylindersAndPrismsBuilder"));

    auto code = ExportToPython::generateSampleCode(*sample);

    std::stringstream snippet;
    snippet << pyfmt::scriptPreamble() << code;

    auto multilayer = PyImport::createFromPython(snippet.str(), pyfmt::getSampleFunctionName(),
                                                 BABuild::buildLibDir());
    auto new_code = ExportToPython::generateSampleCode(*multilayer);

    EXPECT_TRUE(code == new_code);
}

//! Retrieves list of functions from the imported script and checks, that there is
//! one function in a dictioonary with name "get_simulation".

TEST_F(PyEmbedded, ModuleFunctionsList)
{
    // compile our function
    std::stringstream buf;
    buf << "import bornagain as ba                                        \n";
    buf << "                                                              \n";
    buf << "def get_simulation():                                         \n";
    buf << "    m_ambience = ba.HomogeneousMaterial(\"Air\", 0.0, 0.0)    \n";
    buf << "    air_layer = ba.Layer(m_ambience)                          \n";
    buf << "    multilayer = ba.MultiLayer()                              \n";
    buf << "    multilayer.addLayer(air_layer)                            \n";
    buf << "    return multilayer                                         \n";

    auto listOfFunc = PyImport::listOfFunctions(buf.str(), BABuild::buildLibDir());
    for (auto s : listOfFunc)
        std::cout << "AAA" << s << std::endl;
    EXPECT_TRUE(listOfFunc.size() == 1 && listOfFunc.at(0) == "get_simulation");
}
