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

%extend OutputData<double> {
    double __getitem__(unsigned int i) { return (*($self))[i]; }
    double __setitem__(unsigned int i, double value)
    {
        (*($self))[i] = value;
        return (*($self))[i];
    }
};

%extend SimulationResult {
    double __getitem__(unsigned int i) { return (*($self))[i]; }
    double __setitem__(unsigned int i, double value)
    {
        (*($self))[i] = value;
        return (*($self))[i];
    }
};

%extend FixedBinAxis {
    double __getitem__(unsigned int i) { return (*($self))[i]; }
};

%extend VariableBinAxis {
    double __getitem__(unsigned int i) { return (*($self))[i]; }
};

%extend IMultiLayerBuilder {
    virtual RealParameter* registerParameter(const std::string& name, int64_t parpointer) {
        return &(($self)->IParameterized::registerParameter(name, (double*)parpointer)); }

    virtual void setParameterValue(const std::string& name, double value) {
        ($self)->IParameterized::setParameterValue(name, value); }

    virtual std::string parametersToString() const {
        return ($self)->IParameterized::parametersToString();
        }

    virtual ParameterPool* createParameterTree() const {
        return ($self)->IParameterized::createParameterTree();
        }

    virtual ParameterPool* parameterPool() const {
        return ($self)->IParameterized::parameterPool();
    }

    virtual void onChange() {
        return ($self)->IParameterized::onChange();
    }

    static bool isPythonBuilder() {
        return true; }
};

// needed to prevent ownership problems with passed IMultiLayerBuilder
%extend Simulation {
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

// fancy names for ScanResolution static functions
%pythoncode %{
    def ScanRelativeResolution(distribution, rel_dev):
        """
        Creates a scan resolution from the given distribution and
        relative deviation values (that is, the ratios of standard
        deviations and means).
        :param distribution: bornagain.RangedDistribution object
        :param rel_dev: either single-valued or a numpy array.
                        In the latter case should coinside in
                        size with later used mean values array.
        :return: bornagain.ScanResolution object
        """
        return ScanResolution_scanRelativeResolution(distribution, rel_dev)

    def ScanAbsoluteResolution(distribution, std_dev):
        """
        Creates a scan resolution from the given distribution and
        standard deviation values.
        :param distribution: bornagain.RangedDistribution object
        :param std_dev: either single-valued or a numpy array.
                        In the latter case should coinside in
                        size with later used mean values array.
        :return: bornagain.ScanResolution object
        """
        return ScanResolution_scanAbsoluteResolution(distribution, std_dev)
%}

// --- ParameterPool accessors -------------------------------------------------------------------

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

        callback -- user-defined function returning fully-defined bornagain.Simulation object.
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
        return FitObjectiveInterface_cpp.addSimulationAndData(self, wrp, data, *args, **kwargs)

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
        return FitObjectiveInterface_cpp.initPlot(self, every_nth, self.wrp_plot_observer)

    def simulationResult(self, i=0):
        """
        Returns simulated values for i-th simulation-data pair
        """
        return FitObjectiveInterface_cpp.simulationResult(self, i)

    def experimentalData(self, i=0):
        """
        Returns experimental values for i-th simulation-data pair
        """
        return FitObjectiveInterface_cpp.experimentalData(self, i)

    def uncertaintyData(self, i=0):
        """
        Returns uncertainties for i-th simulation-data pair. If
        no uncertainties are assigned to the data pair, returns
        None
        """
        if FitObjectiveInterface_cpp.containsUncertainties(self, i):
            return FitObjectiveInterface_cpp.uncertaintyData(self, i)
        return None

    def relativeDifference(self, i=0):
        """
        Returns relative difference for i-th simulation-data pair
        """
        return FitObjectiveInterface_cpp.relativeDifference(self, i)

    def absoluteDifference(self, i=0):
        """
        Returns absolute difference for i-th simulation-data pair
        """
        return FitObjectiveInterface_cpp.absoluteDifference(self, i)

    def experimental_array(self):
        """
        Returns flattened array of experimental values
        """
        return FitObjectiveInterface_cpp.experimental_array(self)

    def simulation_array(self):
        """
        Returns flattened array of simulated values
        """
        return FitObjectiveInterface_cpp.simulation_array(self)

    def uncertainties(self):
        """
        Returns flattened array of data uncertainty values. If
        some of the data pairs lack uncertainties, returns None.
        """
        if FitObjectiveInterface_cpp.allPairsHaveUncertainties(self):
            return FitObjectiveInterface_cpp.uncertainties(self)
        return None

    def weights_array(self):
        """
        Returns flattened array of user weights
        """
        return FitObjectiveInterface_cpp.weights_array(self)

    def setObjectiveMetric(self, metric_name, norm_name=None):
        """
        Sets objective metric with the given name and norm to the fit objective instance.
        If norm is not specified, default one (L2) is used.
        """
        if norm_name is None:
            FitObjectiveInterface_cpp.setObjectiveMetric(self, metric_name)
        else:
            FitObjectiveInterface_cpp.setObjectiveMetric(self, metric_name, norm_name)
%}
};

