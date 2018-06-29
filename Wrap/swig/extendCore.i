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


// FitParameterSet iterator

%pythoncode %{
class FitParameterSetIterator(object):

    def __init__(self, fitParameters):
        self.fitParameters = fitParameters
        self.index = -1

    def __iter__(self):
        return self

    def next(self):
        self.index += 1
        if self.index < self.fitParameters.size():
            return self.fitParameters[self.index]
        else:
            raise StopIteration

    def __next__(self):
        return self.next()
%}

// FitParameterSet accessors

%extend FitParameterSet {
    const IFitParameter* __getitem__(std::string name) const
    {
        return (*($self))[name];
    }
    const IFitParameter* __getitem__(size_t index) const
    {
        return (*($self))[index];
    }

%pythoncode {
    def __iter__(self):
        return FitParameterSetIterator(self)
}
};

%pythoncode %{
class SimulationBuilderWrapper(PyBuilderCallback):
    def __init__(self, f):
        super(SimulationBuilderWrapper, self).__init__()
        self.f_ = f
    def build_simulation(self, obj):
        return self.f_(obj)


%}

%extend FitObjective {
%pythoncode %{
    def addSimulationAndData(self, callback, data, weight):
        self.wrp = SimulationBuilderWrapper(callback)
        return self.addSimulationAndData_cpp(self.wrp, data, weight)
%}
};

