// renaming should be done in advance and has to be placed at the start of the interface file

%rename(setSampleBuilderCpp) Simulation::setSampleBuilder;
%rename(setSampleBuilderCpp) SpecularSimulation::setSampleBuilder;
%rename(addSimulationAndData_cpp) FitObjective::addSimulationAndData;

// force swig to use move ctor instead of copy ctor
%typemap(out) SlicedParticle %{
    $result = SWIG_NewPointerObj(new $1_ltype(std::move($1)), $&1_descriptor, SWIG_POINTER_OWN);
  %}
