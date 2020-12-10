// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/swig/libBornAgainCore.i
//! @brief     SWIG interface file for libBornAgainCore
//!
//!            Configuration is done in Core/CMakeLists.txt
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1", moduleimport="import $module") "libBornAgainCore"

%include "commons.i"

%include "../../auto/Wrap/doxygenCore.i"

%include "ignoreBase.i"
%include "ignoreSample.i"

%ignore ISpecularScan;

%import(module="libBornAgainFit") ""

%rename(setSampleBuilderCpp) ISimulation::setSampleBuilder;
%rename(setSampleBuilderCpp) SpecularSimulation::setSampleBuilder;
%rename(addSimulationAndData_cpp) FitObjective::addSimulationAndData;
%rename(evaluate_residuals_cpp) FitObjective::evaluate_residuals;
%rename(evaluate_cpp) FitObjective::evaluate;
%rename(finalize_cpp) FitObjective::finalize;
%rename(initPlot_cpp) FitObjective::initPlot;
%rename(uncertainties_cpp) FitObjective::uncertainties;
%rename(uncertaintyData_cpp) FitObjective::uncertaintyData;
%rename(containsUncertainties_cpp) FitObjective::containsUncertainties;
%rename(allPairsHaveUncertainties_cpp) FitObjective::allPairsHaveUncertainties;

%feature("director") PyBuilderCallback;  // used in extendCore.i
%feature("director") PyObserverCallback; // used in extendCore.i

%feature("director") FitObjective;       // used in custom_objective_function.py

// Propagate python exceptions (from https://stackoverflow.com/questions/4811492)
%feature("director:except") {
    if( $error != NULL ) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch( &ptype, &pvalue, &ptraceback );
        PyErr_Restore( ptype, pvalue, ptraceback );
        PyErr_Print();
        Py_Exit(1);
    }
}

%{
#include "BAVersion.h"
#include "Core/Computation/ConstantBackground.h"
#include "Core/Computation/IBackground.h"
#include "Core/Computation/PoissonNoiseBackground.h"
#include "Core/Export/ExportToPython.h"
#include "Core/Fitting/FitObjective.h"
#include "Core/Fitting/IterationInfo.h"
#include "Core/Fitting/PyFittingCallbacks.h"
#include "Core/Residual/ChiSquaredModule.h"
#include "Core/Residual/IChiSquaredModule.h"
#include "Core/Residual/IIntensityFunction.h"
#include "Core/Residual/IIntensityFunction.h"
#include "Core/Residual/VarianceFunctions.h"
#include "Core/Scan/AngularSpecScan.h"
#include "Core/Scan/QSpecScan.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/ISimulation.h"
#include "Core/Simulation/ISimulation2D.h"
#include "Core/Simulation/OffSpecularSimulation.h"
#include "Core/Simulation/SimulationFactory.h"
#include "Core/Simulation/SpecularSimulation.h"
%}

// The following goes verbatim from libBornAgainCore.i to libBornAgainCore_wrap.cxx.
// Note that the order matters, as base classes must be included before derived classes.

%include "fromBase.i"

%include "fromParam.i"

%import(module="libBornAgainSample") "Sample/Scattering/ISampleNode.h"
%import(module="libBornAgainSample") "Sample/Scattering/IFormFactor.h"
%import(module="libBornAgainSample") "Sample/Scattering/IBornFF.h"

%template(swig_dummy_type_axisinfo_vector) std::vector<AxisInfo>;

%template(swig_dummy_type_inode_vector) std::vector<INode*>;
%template(swig_dummy_type_const_inode_vector) std::vector<const INode*>;

%include "Core/Fitting/FitObjective.h"
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<double>>;
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<std::vector<double>>>;

%include "BAVersion.h"

%include "Core/Fitting/IterationInfo.h"
%include "Core/Fitting/PyFittingCallbacks.h"

%include "Core/Scan/ISpecularScan.h"
%include "Core/Scan/AngularSpecScan.h"
%include "Core/Scan/QSpecScan.h"

%include "Core/Simulation/ISimulation.h"
%include "Core/Simulation/ISimulation2D.h"
%include "Core/Simulation/GISASSimulation.h"
%include "Core/Simulation/DepthProbeSimulation.h"
%include "Core/Simulation/SpecularSimulation.h"
%include "Core/Simulation/OffSpecularSimulation.h"

%include "Core/Computation/IBackground.h"
%include "Core/Computation/ConstantBackground.h"
%include "Core/Computation/PoissonNoiseBackground.h"

%include "Core/Export/ExportToPython.h"

%include "Core/Residual/IIntensityFunction.h"
%include "Core/Residual/IChiSquaredModule.h"
%include "Core/Residual/ChiSquaredModule.h"
%include "Core/Residual/VarianceFunctions.h"

%extend BasicVector3D<double> {
    BasicVector3D<double> __add__(const BasicVector3D<double>& rhs) const {
        return *($self) + rhs; }
    BasicVector3D<double> __mul__(double c) const {
        return c * *($self); }
    BasicVector3D<double> __rmul__(double c) const {
        return *($self) * c; }
    BasicVector3D<double> __neg__() const {
        return - *($self); }
};

// needed to prevent ownership problems with passed ISampleBuilder
%extend ISimulation {
    %pythoncode %{
         def setSampleBuilder(self, ptr):
             self.samplebuilder = ptr
             self.setSampleBuilderCpp(ptr)
    %}
 };

%extend SpecularSimulation {
    %pythoncode %{
         def setSampleBuilder(self, ptr):
             self.samplebuilder = ptr
             self.setSampleBuilderCpp(ptr)
    %}
 };

%pythoncode %{
class SimulationBuilderWrapper(PyBuilderCallback):
    def __init__(self, f):
        super(SimulationBuilderWrapper, self).__init__()
        self.f_ = f

    def create_par_dict(self, pars):
        """
        Convertion of ba.Parameters to Python dictionary
        """
        pars_dict = dict()
        for index, p in enumerate(pars):
            pars_dict[p.name()] = p.value
        return pars_dict

    def build_simulation(self, obj):
        simulation = self.f_(self.create_par_dict(obj))
        simulation.__disown__()
        return simulation


%}

%pythoncode %{
class ObserverCallbackWrapper(PyObserverCallback):
    def __init__(self, callback):
        super(ObserverCallbackWrapper, self).__init__()
        self.callback_ = callback

    def update(self, fit_objective):
        return self.callback_(fit_objective)

%}

%extend FitObjective {
%pythoncode %{
    def addSimulationAndData(self, callback, data, *args, **kwargs):
        """
        Sets simulation and experimental data to the fit objective.
        Optionally accepts experimental data uncertainties and
        user-defined dataset weight.

        Arguments:

        callback -- user-defined function returning fully-defined bornagain.ISimulation object.
        The function must use fit parameter dictionary as its input.

        data -- numpy array with experimental data.

        uncertainties -- numpy array with experimental data uncertainties.
        Array shape must correspond to the shape of data. Optional argument.

        weight -- user-defined weight of the dataset. If not specified, defaults to 1.0.
        """
        if not hasattr(self, 'callback_container'):
            self.callback_container = []
        wrp = SimulationBuilderWrapper(callback)
        self.callback_container.append(wrp)
        return self.addSimulationAndData_cpp(wrp, data, *args, **kwargs)

    def convert_params(self, params):
        """
        Converts parameters to what FitObjective::evaluate expects
        """

        if str(params.__module__) == "lmfit.parameter":
            bapars = libBornAgainFit.Parameters()
            for p in params:
                bapars.add(p, params[p].value)
            return bapars
        else:
            return params

    def evaluate_residuals(self, params):
        return self.evaluate_residuals_cpp(self.convert_params(params))

    def evaluate(self, params):
        return self.evaluate_cpp(self.convert_params(params))

    def convert_result(self, minim_result):
        """
        Converts result reported by arbitrary minimizer to ba.MinimizerResult
        """

        if str(minim_result.__module__) == "lmfit.minimizer":
            return libBornAgainFit.MinimizerResult()
        else:
            return minim_result

    def finalize(self, minimizer_result):
        return self.finalize_cpp(self.convert_result(minimizer_result))

    def create_default_plotter(self):
        import plot_utils
        self.m_plotter = plot_utils.PlotterGISAS()
        return self.m_plotter.plot

    def initPlot(self, every_nth, callback = None):
        if not callback:
            callback = self.create_default_plotter()

        self.wrp_plot_observer = ObserverCallbackWrapper(callback)
        return self.initPlot_cpp(every_nth, self.wrp_plot_observer)

    def uncertainties(self):
        """
        Returns one-dimensional array representing merged data uncertainties.
        If any of the associated data pairs lack uncertainties, returns None.
        """
        if self.allPairsHaveUncertainties_cpp():
            return self.uncertainties_cpp()
        return None

    def uncertaintyData(self, i=0):
        """
        Returns uncertainties for i-th simulation-data pair. If
        no uncertainties are assigned to the data pair, returns
        None.
        """
        if self.containsUncertainties_cpp(i):
            return self.uncertaintyData_cpp(i)
        return None
%}
};
