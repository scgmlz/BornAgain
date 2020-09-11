 // manually declare which classes can be derived in Python and passed back to C++
 // this can be used to reduce the bloat in the swig-generated code

%feature("director") IParameterized;
%feature("director") IMultiLayerBuilder;
%feature("director") INode;
%feature("director") ISample;
%feature("director") IFormFactor;
%feature("director") IFormFactorBorn;
%feature("director") IInterferenceFunction;
%feature("director") PyCallback;
%feature("director") PyBuilderCallback;
%feature("director") PyObserverCallback;
%feature("director") FitObjective;

// Propagate python exceptions
// taken from
// https://stackoverflow.com/questions/4811492/swig-reporting-python-exceptions-from-c-code
%feature("director:except") {
    if( $error != NULL ) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch( &ptype, &pvalue, &ptraceback );
        PyErr_Restore( ptype, pvalue, ptraceback );
        PyErr_Print();
        Py_Exit(1);
    }
}
