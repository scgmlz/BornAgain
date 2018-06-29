%pythoncode %{
class ParametersIterator(object):

    def __init__(self, parameters):
        self.parameters = parameters
        self.index = -1

    def __iter__(self):
        return self

    def next(self):
        self.index += 1
        if self.index < self.parameters.size():
            return self.parameters[self.index]
        else:
            raise StopIteration

    def __next__(self):
        return self.next()
%}

// Parameters accessors
namespace Fit {

%extend Parameters {
    const Parameter& __getitem__(std::string name) const
    {
        return (*($self))[name];
    }
    const Parameter& __getitem__(size_t index) const
    {
        return (*($self))[index];
    }

%pythoncode %{
def __iter__(self):
    return ParametersIterator(self)
%}
};

}

// --- Parameter x.value attribute
namespace Fit {

%extend Parameter{
%pythoncode %{
__swig_getmethods__["value"] = value
__swig_setmethods__["value"] = setValue
if _newclass: value = property(value, setValue)
%}
};

}


// --- Setting up Minimizer callback ---

%pythoncode %{
class CallableWrapper(PyCallback):
    def __init__(self, f, callable_type):
        super(CallableWrapper, self).__init__(callable_type)
        self.f_ = f
    def call_scalar(self, obj):
        return self.f_(obj)
    def call_residuals(self, obj):
        return self.f_(obj)

%}

namespace Fit {

%extend Minimizer {
%pythoncode %{
    def minimize(self, callback, pars):
        if not callable(callback):
            raise Exception("Not a Python callable")

        # single call to callback to check return type
        result = callback(pars)

        if isinstance(result, float):
            wrp = CallableWrapper(callback, PyCallback.SCALAR)
            return self.minimize_cpp(wrp, pars)
        elif hasattr(result, '__len__'):
            wrp = CallableWrapper(callback, PyCallback.RESIDUAL)
            return self.minimize_cpp(wrp, pars)
        else:
            raise Exception("Wrong callable type")

%}

};

}

