%feature("autodoc");

%include "stdint.i"
%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
%include "std_shared_ptr.i"

%include "deprecation.i"
%include "warnings.i"

#define SWIG_FILE_WITH_INIT

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
%}

%include "numpy.i"
%init %{
    import_array();
%}

#define GCC_DIAG_OFF(x)
#define GCC_DIAG_ON(x)

#ifndef BORNAGAIN_PYTHON
#define BORNAGAIN_PYTHON
#endif

%template(vdouble1d_t) std::vector<double>;
%template(vdouble2d_t) std::vector<std::vector<double>>;
%template(vector_integer_t) std::vector<int>;
%template(vinteger2d_t) std::vector<std::vector<int>>;
%template(vector_longinteger_t) std::vector<unsigned long int>;
%template(vector_complex_t) std::vector< std::complex<double>>;
%template(vector_string_t) std::vector<std::string>;
%template(map_string_double_t) std::map<std::string, double>;
%template(pvacuum_double_t) std::pair<double, double>;
%template(vector_pvacuum_double_t) std::vector<std::pair<double, double>>;
