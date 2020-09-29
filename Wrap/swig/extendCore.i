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

%extend ISampleBuilder {
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

};

// needed to prevent ownership problems with passed ISampleBuilder
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

// --- MaterialProfile generation ----------------------------------------------------------------

// Function with optional default limits and/or number of points
%pythoncode %{
    def MaterialProfile(multilayer, n_points=400, z_min=None, z_max=None):
        """
        Creates a material profile from the given multilayer. If no limits are given,
        it will provide sensible default values, considering the included particles and
        interface roughnesses.
        :param multilayer: bornagain.MultiLayer object
        :param n_points: number of points to generate
        :param z_min: starting value for z
        :param z_max: ending value for z
        :return: numpy arrays containing z positions and the complex material values in those positions
        """
        def_z_min, def_z_max = DefaultMaterialProfileLimits(multilayer)
        z_min = def_z_min if z_min is None else z_min
        z_max = def_z_max if z_max is None else z_max
        z_points = GenerateZValues(n_points, z_min, z_max)
        material_values = MaterialProfile_cpp(multilayer, n_points, z_min, z_max)
        return (z_points, material_values)
%}
