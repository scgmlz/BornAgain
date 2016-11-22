
// fix SWIG warning 509, certain C++ overloads create ambiguities in Python
%ignore ParticleLayout::addInterferenceFunction(IInterferenceFunction*);
%ignore ParticleLayout::addInterferenceFunction(const IInterferenceFunction*);
%ignore MesoCrystal::MesoCrystal(IClusteredParticles*, IFormFactor*);
%ignore MesoCrystal::MesoCrystal(const IClusteredParticles*, const IFormFactor*);
%ignore Instrument::setDetectorResolutionFunction(IResolutionFunction2D*);
%ignore Instrument::setDetectorResolutionFunction(const IResolutionFunction2D*);

// problems with BasicVector3D.h
%ignore BasicVector3D<std::complex<double>>::complex() const;
%ignore BasicVector3D<std::complex<double>>::angle(const BasicVector3D<std::complex<double>>&) const;
%ignore BasicVector3D<std::complex<double>>::perp2(const BasicVector3D<std::complex<double>>&) const;
%ignore BasicVector3D<std::complex<double>>::sin2Theta() const;
%ignore BasicVector3D<std::complex<double>>::cosTheta() const;
%ignore BasicVector3D<std::complex<double>>::theta() const;
%ignore BasicVector3D<std::complex<double>>::phi() const;
%ignore BasicVector3D<std::complex<double>>::rotated(double, const BasicVector3D<std::complex<double>>&) const;
%ignore BasicVector3D<std::complex<double>>::rotatedX(double) const;
%ignore BasicVector3D<std::complex<double>>::rotatedY(double) const;
%ignore BasicVector3D<std::complex<double>>::rotatedZ(double) const;

%ignore BasicVector3D<std::complex<double>>::cross(const BasicVector3D<std::complex<double>>&) const;
%ignore BasicVector3D<std::complex<double>>::perp(const BasicVector3D<std::complex<double>>&) const;

%ignore BasicVector3D<double>::rotated(double, const BasicVector3D<double>&) const;
%ignore BasicVector3D<double>::rotatedX(double) const;
%ignore BasicVector3D<double>::rotatedY(double) const;
%ignore BasicVector3D<double>::rotatedZ(double) const;


// need this to play nicely with ctypes
%ignore IParameterized::addParametersToExternalPool(const std::string&, ParameterPool*, int) const;
%ignore IParameterized::addParametersToExternalPool(const std::string&, ParameterPool*) const;
%ignore IMultiLayerBuilder::addParametersToExternalPool(const std::string&, ParameterPool*, int) const;
%ignore IMultiLayerBuilder::addParametersToExternalPool(const std::string&, ParameterPool*) const;

// for determining if clone is neccesary after buildSample() call
%ignore IMultiLayerBuilder::isPythonBuilder();

// ignored to avoid error (todo: check whether this is really necessary)
%ignore Crystal::getTransformedLattice(const IRotation*) const;

// taken from dev-tools/python-bindings/settings_fit.py
%ignore FitSuite::setOptions(const FitOptions&);
%ignore FitSuite::getOptions();


// extra ignores for types and methods that shouldn't be visible in Python
%ignore FormFactorDWBAPol;
%ignore ISampleVisitor::visit(const FormFactorDWBAPol*);
%ignore FormFactorDWBA;
%ignore ISampleVisitor::visit(const FormFactorDWBA*);
%ignore MainComputation;
%ignore DecoratedLayerComputation;
%ignore RoughMultiLayerComputation;
%ignore SpecularComputation;
