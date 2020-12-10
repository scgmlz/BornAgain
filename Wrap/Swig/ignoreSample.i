// fix SWIG warning 509, certain C++ overloads create ambiguities in Python
%ignore ParticleLayout::setInterferenceFunction(IInterferenceFunction*);
%ignore ParticleLayout::setInterferenceFunction(const IInterferenceFunction*);
%ignore MesoCrystal::MesoCrystal(IClusteredParticles*, IFormFactor*);
%ignore MesoCrystal::MesoCrystal(const IClusteredParticles*, const IFormFactor*);
%ignore Instrument::setDetectorResolutionFunction(IResolutionFunction2D*);
%ignore Instrument::setDetectorResolutionFunction(const IResolutionFunction2D*);

%ignore ISampleBuilder::addParametersToExternalPool(const std::string&, ParameterPool*, int) const;
%ignore ISampleBuilder::addParametersToExternalPool(const std::string&, ParameterPool*) const;

// ignored to avoid error (todo: check whether this is really necessary)
%ignore Crystal::getTransformedLattice(const IRotation*) const;

// extra ignores for types and methods that shouldn't be visible in Python
%ignore DWBAComputation;
%ignore DecoratedLayerComputation;
%ignore ComputeDWBA;
%ignore ComputeDWBAPol;
%ignore ISampleNodeVisitor::visit(const ComputeDWBA*);
%ignore ISampleNodeVisitor::visit(const ComputeDWBAPol*);
%ignore Lattice2D::ReciprocalBases;
%ignore Lattice2D::reciprocalBases();
%ignore RoughMultiLayerComputation;
%ignore SlicedFormFactorList;
%ignore SpecularComputation;
