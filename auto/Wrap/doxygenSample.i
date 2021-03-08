
// File: index.xml

// File: classAsymRippleBuilder.xml
%feature("docstring") AsymRippleBuilder "";

%feature("docstring")  AsymRippleBuilder::buildSample "MultiLayer * AsymRippleBuilder::buildSample() const
";


// File: classAveragedSlicedCylindersBuilder.xml
%feature("docstring") AveragedSlicedCylindersBuilder "

Provides exactly the same sample as  SLDSlicedCylindersBuilder, but with cylinders represented as homogeneous layers. SLD-based materials used. Assumed wavelength is 1.54 Angstrom.

C++ includes: SlicedCylindersBuilder.h
";

%feature("docstring")  AveragedSlicedCylindersBuilder::buildSample "MultiLayer * AveragedSlicedCylindersBuilder::buildSample() const
";


// File: classBaseMaterialImpl.xml
%feature("docstring") BaseMaterialImpl "

Interface for material implementation classes. Inherited by  MagneticMaterialImpl, which has further children.

C++ includes: BaseMaterialImpl.h
";

%feature("docstring")  BaseMaterialImpl::BaseMaterialImpl "BaseMaterialImpl::BaseMaterialImpl(const std::string &name)

Constructs basic material with name. 
";

%feature("docstring")  BaseMaterialImpl::~BaseMaterialImpl "virtual BaseMaterialImpl::~BaseMaterialImpl()=default
";

%feature("docstring")  BaseMaterialImpl::clone "virtual BaseMaterialImpl* BaseMaterialImpl::clone() const =0

Returns pointer to a copy of material. 
";

%feature("docstring")  BaseMaterialImpl::inverted "virtual BaseMaterialImpl* BaseMaterialImpl::inverted() const =0

Constructs a material with inverted magnetization. 
";

%feature("docstring")  BaseMaterialImpl::refractiveIndex "virtual complex_t BaseMaterialImpl::refractiveIndex(double wavelength) const =0

Returns refractive index. 
";

%feature("docstring")  BaseMaterialImpl::refractiveIndex2 "virtual complex_t BaseMaterialImpl::refractiveIndex2(double wavelength) const =0

Returns squared refractive index. 
";

%feature("docstring")  BaseMaterialImpl::isScalarMaterial "virtual bool BaseMaterialImpl::isScalarMaterial() const =0

Indicates whether the interaction with the material is scalar. This means that different polarization states will be diffracted equally 
";

%feature("docstring")  BaseMaterialImpl::isMagneticMaterial "virtual bool BaseMaterialImpl::isMagneticMaterial() const =0
";

%feature("docstring")  BaseMaterialImpl::magnetization "virtual kvector_t BaseMaterialImpl::magnetization() const =0

Returns the magnetization (in A/m) 
";

%feature("docstring")  BaseMaterialImpl::materialData "virtual complex_t BaseMaterialImpl::materialData() const =0

Returns underlying material data. 
";

%feature("docstring")  BaseMaterialImpl::typeID "virtual MATERIAL_TYPES BaseMaterialImpl::typeID() const =0

Returns type of material implementation. 
";

%feature("docstring")  BaseMaterialImpl::scalarSubtrSLD "virtual complex_t BaseMaterialImpl::scalarSubtrSLD(const WavevectorInfo &wavevectors) const =0

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld), sld being the scattering length density. 
";

%feature("docstring")  BaseMaterialImpl::polarizedSubtrSLD "virtual Eigen::Matrix2cd BaseMaterialImpl::polarizedSubtrSLD(const WavevectorInfo &wavevectors) const =0

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld) matrix with magnetization corrections. 
";

%feature("docstring")  BaseMaterialImpl::rotatedMaterial "virtual BaseMaterialImpl* BaseMaterialImpl::rotatedMaterial(const Transform3D &transform) const =0
";

%feature("docstring")  BaseMaterialImpl::print "virtual void BaseMaterialImpl::print(std::ostream &ostr) const =0

Prints object data. 
";

%feature("docstring")  BaseMaterialImpl::getName "const std::string& BaseMaterialImpl::getName() const

Returns name of the material. 
";


// File: classBasic2DLatticeBuilder.xml
%feature("docstring") Basic2DLatticeBuilder "

Builds sample: 2D lattice with arbitrary angle and different lattice length_1 and length_2.

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  Basic2DLatticeBuilder::Basic2DLatticeBuilder "Basic2DLatticeBuilder::Basic2DLatticeBuilder()
";

%feature("docstring")  Basic2DLatticeBuilder::buildSample "MultiLayer * Basic2DLatticeBuilder::buildSample() const
";


// File: classBasic2DParaCrystalBuilder.xml
%feature("docstring") Basic2DParaCrystalBuilder "

Builds sample: basic two dimensional paracrystal with various probability distribution functions (PDF's). They are initialized via component service.

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  Basic2DParaCrystalBuilder::Basic2DParaCrystalBuilder "Basic2DParaCrystalBuilder::Basic2DParaCrystalBuilder()
";

%feature("docstring")  Basic2DParaCrystalBuilder::~Basic2DParaCrystalBuilder "Basic2DParaCrystalBuilder::~Basic2DParaCrystalBuilder()
";

%feature("docstring")  Basic2DParaCrystalBuilder::buildSample "MultiLayer * Basic2DParaCrystalBuilder::buildSample() const
";

%feature("docstring")  Basic2DParaCrystalBuilder::createSampleByIndex "MultiLayer * Basic2DParaCrystalBuilder::createSampleByIndex(size_t index)
";


// File: classBasicLattice2D.xml
%feature("docstring") BasicLattice2D "

A two-dimensional Bravais lattice with no special symmetry.

C++ includes: Lattice2D.h
";

%feature("docstring")  BasicLattice2D::BasicLattice2D "BasicLattice2D::BasicLattice2D(double length1, double length2, double angle, double xi)
";

%feature("docstring")  BasicLattice2D::clone "BasicLattice2D * BasicLattice2D::clone() const
";

%feature("docstring")  BasicLattice2D::accept "void BasicLattice2D::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  BasicLattice2D::length1 "virtual double BasicLattice2D::length1() const
";

%feature("docstring")  BasicLattice2D::length2 "virtual double BasicLattice2D::length2() const
";

%feature("docstring")  BasicLattice2D::latticeAngle "virtual double BasicLattice2D::latticeAngle() const
";

%feature("docstring")  BasicLattice2D::unitCellArea "double BasicLattice2D::unitCellArea() const
";


// File: classBox.xml
%feature("docstring") Box "";

%feature("docstring")  Box::Box "Box::Box(double length, double width, double height)
";

%feature("docstring")  Box::~Box "Box::~Box()
";


// File: classBoxCompositionRotateXBuilder.xml
%feature("docstring") BoxCompositionRotateXBuilder "

Two boxes in particle composition rotated in X by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateXBuilder::buildSample "MultiLayer * BoxCompositionRotateXBuilder::buildSample() const
";


// File: classBoxCompositionRotateYBuilder.xml
%feature("docstring") BoxCompositionRotateYBuilder "

Two boxes in particle composition rotated in Y by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateYBuilder::buildSample "MultiLayer * BoxCompositionRotateYBuilder::buildSample() const
";


// File: classBoxCompositionRotateZandYBuilder.xml
%feature("docstring") BoxCompositionRotateZandYBuilder "

Two boxes in particle composition rotated in Z and Y by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateZandYBuilder::buildSample "MultiLayer * BoxCompositionRotateZandYBuilder::buildSample() const
";


// File: classBoxCompositionRotateZBuilder.xml
%feature("docstring") BoxCompositionRotateZBuilder "

Two boxes in particle composition rotated in Z by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateZBuilder::buildSample "MultiLayer * BoxCompositionRotateZBuilder::buildSample() const
";


// File: classBoxesSquareLattice2DBuilder.xml
%feature("docstring") BoxesSquareLattice2DBuilder "

Builds sample: square boxes in a square lattice

C++ includes: BoxesSquareLatticeBuilder.h
";

%feature("docstring")  BoxesSquareLattice2DBuilder::buildSample "MultiLayer * BoxesSquareLattice2DBuilder::buildSample() const
";


// File: classBoxStackCompositionBuilder.xml
%feature("docstring") BoxStackCompositionBuilder "

Two different boxes are first rotated and then composed, composition is then rotated.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxStackCompositionBuilder::buildSample "MultiLayer * BoxStackCompositionBuilder::buildSample() const
";


// File: classCenteredSquareLattice2DBuilder.xml
%feature("docstring") CenteredSquareLattice2DBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  CenteredSquareLattice2DBuilder::buildSample "MultiLayer * CenteredSquareLattice2DBuilder::buildSample() const
";


// File: classComputeBA.xml
%feature("docstring") ComputeBA "

Provides scalar form factor evaluation in Born Approximation for given  IFormFactor.

C++ includes: ComputeBA.h
";

%feature("docstring")  ComputeBA::ComputeBA "ComputeBA::ComputeBA(const IFormFactor &ff)
";

%feature("docstring")  ComputeBA::~ComputeBA "ComputeBA::~ComputeBA() override
";

%feature("docstring")  ComputeBA::clone "ComputeBA * ComputeBA::clone() const override
";

%feature("docstring")  ComputeBA::evaluate "complex_t ComputeBA::evaluate(const WavevectorInfo &wavevectors) const override

Calculates and returns a form factor calculation in BA. 
";


// File: classComputeBAPol.xml
%feature("docstring") ComputeBAPol "

Provides polarized form factor evaluation in Born Approximation for given  IFormFactor.

C++ includes: ComputeBAPol.h
";

%feature("docstring")  ComputeBAPol::ComputeBAPol "ComputeBAPol::ComputeBAPol(const IFormFactor &ff)
";

%feature("docstring")  ComputeBAPol::~ComputeBAPol "ComputeBAPol::~ComputeBAPol() override
";

%feature("docstring")  ComputeBAPol::clone "ComputeBAPol * ComputeBAPol::clone() const override
";

%feature("docstring")  ComputeBAPol::evaluate "complex_t ComputeBAPol::evaluate(const WavevectorInfo &wavevectors) const override

Throws not-implemented exception. 
";

%feature("docstring")  ComputeBAPol::evaluatePol "Eigen::Matrix2cd ComputeBAPol::evaluatePol(const WavevectorInfo &wavevectors) const override

Calculates and returns a polarized form factor calculation in BA. 
";


// File: classComputeDWBA.xml
%feature("docstring") ComputeDWBA "

Provides scalar DWBA computation for given  IFormFactor.

C++ includes: ComputeDWBA.h
";

%feature("docstring")  ComputeDWBA::ComputeDWBA "ComputeDWBA::ComputeDWBA(const IFormFactor &ff)
";

%feature("docstring")  ComputeDWBA::~ComputeDWBA "ComputeDWBA::~ComputeDWBA() override
";

%feature("docstring")  ComputeDWBA::clone "ComputeDWBA * ComputeDWBA::clone() const override
";

%feature("docstring")  ComputeDWBA::evaluate "complex_t ComputeDWBA::evaluate(const WavevectorInfo &wavevectors) const override

Returns the coherent sum of the four DWBA terms for scalar scattering. 
";

%feature("docstring")  ComputeDWBA::setSpecularInfo "void ComputeDWBA::setSpecularInfo(std::unique_ptr< const ILayerRTCoefficients > p_in_coeffs, std::unique_ptr< const ILayerRTCoefficients > p_out_coeffs) override

Sets reflection/transmission info. 
";


// File: classComputeDWBAPol.xml
%feature("docstring") ComputeDWBAPol "

Provides polarized DWBA computation for given  IFormFactor.

C++ includes: ComputeDWBAPol.h
";

%feature("docstring")  ComputeDWBAPol::ComputeDWBAPol "ComputeDWBAPol::ComputeDWBAPol(const IFormFactor &ff)
";

%feature("docstring")  ComputeDWBAPol::~ComputeDWBAPol "ComputeDWBAPol::~ComputeDWBAPol() override
";

%feature("docstring")  ComputeDWBAPol::clone "ComputeDWBAPol * ComputeDWBAPol::clone() const override
";

%feature("docstring")  ComputeDWBAPol::evaluate "complex_t ComputeDWBAPol::evaluate(const WavevectorInfo &wavevectors) const override

Throws not-implemented exception. 
";

%feature("docstring")  ComputeDWBAPol::evaluatePol "Eigen::Matrix2cd ComputeDWBAPol::evaluatePol(const WavevectorInfo &wavevectors) const override

Returns the coherent sum of the four DWBA terms for polarized scattering. 
";

%feature("docstring")  ComputeDWBAPol::setSpecularInfo "void ComputeDWBAPol::setSpecularInfo(std::unique_ptr< const ILayerRTCoefficients > p_in_coeffs, std::unique_ptr< const ILayerRTCoefficients > p_out_coeffs) override

Sets reflection/transmission info. 
";


// File: classConesWithLimitsDistributionBuilder.xml
%feature("docstring") ConesWithLimitsDistributionBuilder "

Cones with the distribution applied to the angle and RealLimits defined.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  ConesWithLimitsDistributionBuilder::ConesWithLimitsDistributionBuilder "ConesWithLimitsDistributionBuilder::ConesWithLimitsDistributionBuilder()
";

%feature("docstring")  ConesWithLimitsDistributionBuilder::buildSample "MultiLayer * ConesWithLimitsDistributionBuilder::buildSample() const
";


// File: classCoreShellBoxRotateZandYBuilder.xml
%feature("docstring") CoreShellBoxRotateZandYBuilder "

Rotation and translation of core shell box particle in 3 layers system.

C++ includes: CoreShellParticleBuilder.h
";

%feature("docstring")  CoreShellBoxRotateZandYBuilder::buildSample "MultiLayer * CoreShellBoxRotateZandYBuilder::buildSample() const
";


// File: classCoreShellParticleBuilder.xml
%feature("docstring") CoreShellParticleBuilder "

Builds sample: Core Shell Nanoparticles (IsGISAXS example #11).

C++ includes: CoreShellParticleBuilder.h
";

%feature("docstring")  CoreShellParticleBuilder::buildSample "MultiLayer * CoreShellParticleBuilder::buildSample() const
";


// File: classCosineRippleBuilder.xml
%feature("docstring") CosineRippleBuilder "

Builds sample: cosine ripple within the 1D-paracrystal model.

C++ includes: RipplesBuilder.h
";

%feature("docstring")  CosineRippleBuilder::buildSample "MultiLayer * CosineRippleBuilder::buildSample() const
";


// File: classCrystal.xml
%feature("docstring") Crystal "

A crystal structure, defined by a Bravais lattice, a basis, and a position variance.

The basis is either a  Particle or a  ParticleComposition.

Computations are delegated to class  FormFactorCrystal.

Used in  MesoCrystal, where it is given an outer shape.

C++ includes: Crystal.h
";

%feature("docstring")  Crystal::Crystal "Crystal::Crystal(const IParticle &basis, const Lattice3D &lattice, double position_variance=0)
";

%feature("docstring")  Crystal::~Crystal "Crystal::~Crystal()
";

%feature("docstring")  Crystal::clone "Crystal * Crystal::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  Crystal::accept "void Crystal::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  Crystal::createTotalFormFactor "IFormFactor * Crystal::createTotalFormFactor(const IFormFactor &meso_crystal_form_factor, const IRotation *p_rotation, const kvector_t &translation) const
";

%feature("docstring")  Crystal::homogeneousRegions "std::vector< HomogeneousRegion > Crystal::homogeneousRegions() const
";

%feature("docstring")  Crystal::transformedLattice "Lattice3D Crystal::transformedLattice(const IRotation *p_rotation=nullptr) const
";

%feature("docstring")  Crystal::getChildren "std::vector< const INode * > Crystal::getChildren() const final
";


// File: classCustomMorphologyBuilder.xml
%feature("docstring") CustomMorphologyBuilder "

Builds sample: mixture of different particles (IsGISAXS example #7).

C++ includes: CustomMorphologyBuilder.h
";

%feature("docstring")  CustomMorphologyBuilder::buildSample "MultiLayer * CustomMorphologyBuilder::buildSample() const
";


// File: classCylindersAndPrismsBuilder.xml
%feature("docstring") CylindersAndPrismsBuilder "

Builds sample: mixture of cylinders and prisms without interference (IsGISAXS example #1).

C++ includes: CylindersAndPrismsBuilder.h
";

%feature("docstring")  CylindersAndPrismsBuilder::buildSample "MultiLayer * CylindersAndPrismsBuilder::buildSample() const
";


// File: classCylindersInBABuilder.xml
%feature("docstring") CylindersInBABuilder "

Builds sample: cylinder form factor in BA (IsGISAXS example #3, part II).

C++ includes: CylindersBuilder.h
";

%feature("docstring")  CylindersInBABuilder::CylindersInBABuilder "CylindersInBABuilder::CylindersInBABuilder()
";

%feature("docstring")  CylindersInBABuilder::buildSample "MultiLayer * CylindersInBABuilder::buildSample() const
";


// File: classCylindersInDWBABuilder.xml
%feature("docstring") CylindersInDWBABuilder "

Builds sample: cylinder form factor in DWBA (IsGISAXS example #3, part I).

C++ includes: CylindersBuilder.h
";

%feature("docstring")  CylindersInDWBABuilder::CylindersInDWBABuilder "CylindersInDWBABuilder::CylindersInDWBABuilder()
";

%feature("docstring")  CylindersInDWBABuilder::buildSample "MultiLayer * CylindersInDWBABuilder::buildSample() const
";


// File: classCylindersInSSCABuilder.xml
%feature("docstring") CylindersInSSCABuilder "

Builds sample: size spacing correlation approximation (IsGISAXS example #15).

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  CylindersInSSCABuilder::buildSample "MultiLayer * CylindersInSSCABuilder::buildSample() const
";


// File: classCylindersWithSizeDistributionBuilder.xml
%feature("docstring") CylindersWithSizeDistributionBuilder "

Cylinders in BA with size distributions (IsGISAXS example #3, part II).

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  CylindersWithSizeDistributionBuilder::buildSample "MultiLayer * CylindersWithSizeDistributionBuilder::buildSample() const
";


// File: classDecouplingApproximationStrategy.xml
%feature("docstring") DecouplingApproximationStrategy "

Strategy class to compute the total scattering from a particle layout in the decoupling approximation.

C++ includes: DecouplingApproximationStrategy.h
";

%feature("docstring")  DecouplingApproximationStrategy::DecouplingApproximationStrategy "DecouplingApproximationStrategy::DecouplingApproximationStrategy(const std::vector< FormFactorCoherentSum > &weighted_formfactors, const IInterferenceFunction *iff, SimulationOptions sim_params, bool polarized)
";


// File: classDistribution1DCauchySampler.xml
%feature("docstring") Distribution1DCauchySampler "";

%feature("docstring")  Distribution1DCauchySampler::Distribution1DCauchySampler "Distribution1DCauchySampler::Distribution1DCauchySampler(double lambda)
";

%feature("docstring")  Distribution1DCauchySampler::randomSample "double Distribution1DCauchySampler::randomSample() const final
";


// File: classDistribution1DCosineSampler.xml
%feature("docstring") Distribution1DCosineSampler "";

%feature("docstring")  Distribution1DCosineSampler::Distribution1DCosineSampler "Distribution1DCosineSampler::Distribution1DCosineSampler(double omega)
";

%feature("docstring")  Distribution1DCosineSampler::randomSample "double Distribution1DCosineSampler::randomSample() const final
";


// File: classDistribution1DGateSampler.xml
%feature("docstring") Distribution1DGateSampler "";

%feature("docstring")  Distribution1DGateSampler::Distribution1DGateSampler "Distribution1DGateSampler::Distribution1DGateSampler(double a, double b)
";

%feature("docstring")  Distribution1DGateSampler::randomSample "double Distribution1DGateSampler::randomSample() const final
";


// File: classDistribution1DGaussSampler.xml
%feature("docstring") Distribution1DGaussSampler "";

%feature("docstring")  Distribution1DGaussSampler::Distribution1DGaussSampler "Distribution1DGaussSampler::Distribution1DGaussSampler(double mean, double stddev)
";

%feature("docstring")  Distribution1DGaussSampler::randomSample "double Distribution1DGaussSampler::randomSample() const final
";


// File: classDistribution1DTriangleSampler.xml
%feature("docstring") Distribution1DTriangleSampler "";

%feature("docstring")  Distribution1DTriangleSampler::Distribution1DTriangleSampler "Distribution1DTriangleSampler::Distribution1DTriangleSampler(double omega)
";

%feature("docstring")  Distribution1DTriangleSampler::randomSample "double Distribution1DTriangleSampler::randomSample() const final
";


// File: classDistribution2DCauchySampler.xml
%feature("docstring") Distribution2DCauchySampler "";

%feature("docstring")  Distribution2DCauchySampler::Distribution2DCauchySampler "Distribution2DCauchySampler::Distribution2DCauchySampler(double omega_x, double omega_y)
";

%feature("docstring")  Distribution2DCauchySampler::randomSample "std::pair< double, double > Distribution2DCauchySampler::randomSample() const final
";


// File: classDistribution2DConeSampler.xml
%feature("docstring") Distribution2DConeSampler "";

%feature("docstring")  Distribution2DConeSampler::Distribution2DConeSampler "Distribution2DConeSampler::Distribution2DConeSampler(double omega_x, double omega_y)
";

%feature("docstring")  Distribution2DConeSampler::randomSample "std::pair< double, double > Distribution2DConeSampler::randomSample() const final
";


// File: classDistribution2DGateSampler.xml
%feature("docstring") Distribution2DGateSampler "";

%feature("docstring")  Distribution2DGateSampler::Distribution2DGateSampler "Distribution2DGateSampler::Distribution2DGateSampler(double omega_x, double omega_y)
";

%feature("docstring")  Distribution2DGateSampler::randomSample "std::pair< double, double > Distribution2DGateSampler::randomSample() const final
";


// File: classDistribution2DGaussSampler.xml
%feature("docstring") Distribution2DGaussSampler "";

%feature("docstring")  Distribution2DGaussSampler::Distribution2DGaussSampler "Distribution2DGaussSampler::Distribution2DGaussSampler(double omega_x, double omega_y)
";

%feature("docstring")  Distribution2DGaussSampler::randomSample "std::pair< double, double > Distribution2DGaussSampler::randomSample() const final
";


// File: classDoubleEllipse.xml
%feature("docstring") DoubleEllipse "";

%feature("docstring")  DoubleEllipse::DoubleEllipse "DoubleEllipse::DoubleEllipse(double r0_x, double r0_y, double z, double rz_x, double rz_y)
";

%feature("docstring")  DoubleEllipse::~DoubleEllipse "DoubleEllipse::~DoubleEllipse()
";


// File: classFeNiBilayerBuilder.xml
%feature("docstring") FeNiBilayerBuilder "";

%feature("docstring")  FeNiBilayerBuilder::buildSample "MultiLayer * FeNiBilayerBuilder::buildSample() const
";


// File: classFeNiBilayerNCBuilder.xml
%feature("docstring") FeNiBilayerNCBuilder "";

%feature("docstring")  FeNiBilayerNCBuilder::buildSample "MultiLayer * FeNiBilayerNCBuilder::buildSample() const
";


// File: classFeNiBilayerSpinFlipBuilder.xml
%feature("docstring") FeNiBilayerSpinFlipBuilder "";

%feature("docstring")  FeNiBilayerSpinFlipBuilder::buildSample "MultiLayer * FeNiBilayerSpinFlipBuilder::buildSample() const
";


// File: classFeNiBilayerSpinFlipNCBuilder.xml
%feature("docstring") FeNiBilayerSpinFlipNCBuilder "";

%feature("docstring")  FeNiBilayerSpinFlipNCBuilder::buildSample "MultiLayer * FeNiBilayerSpinFlipNCBuilder::buildSample() const
";


// File: classFeNiBilayerSpinFlipTanhBuilder.xml
%feature("docstring") FeNiBilayerSpinFlipTanhBuilder "";

%feature("docstring")  FeNiBilayerSpinFlipTanhBuilder::buildSample "MultiLayer * FeNiBilayerSpinFlipTanhBuilder::buildSample() const
";


// File: classFeNiBilayerTanhBuilder.xml
%feature("docstring") FeNiBilayerTanhBuilder "";

%feature("docstring")  FeNiBilayerTanhBuilder::buildSample "MultiLayer * FeNiBilayerTanhBuilder::buildSample() const
";


// File: classFiniteSquareLattice2DBuilder.xml
%feature("docstring") FiniteSquareLattice2DBuilder "

Builds sample: 2D finite lattice with thermal disorder.

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  FiniteSquareLattice2DBuilder::buildSample "MultiLayer * FiniteSquareLattice2DBuilder::buildSample() const
";


// File: classFixedBuilder.xml
%feature("docstring") FixedBuilder "

A trivial sample builder class that builds a fixed sample.

C++ includes: FixedBuilder.h
";

%feature("docstring")  FixedBuilder::FixedBuilder "FixedBuilder::FixedBuilder()=delete
";

%feature("docstring")  FixedBuilder::FixedBuilder "FixedBuilder::FixedBuilder(const MultiLayer &)
";

%feature("docstring")  FixedBuilder::buildSample "MultiLayer * FixedBuilder::buildSample() const
";


// File: classFormFactorAnisoPyramid.xml
%feature("docstring") FormFactorAnisoPyramid "

A frustum (truncated pyramid) with rectangular base.

C++ includes: FormFactorAnisoPyramid.h
";

%feature("docstring")  FormFactorAnisoPyramid::FormFactorAnisoPyramid "FormFactorAnisoPyramid::FormFactorAnisoPyramid(const std::vector< double > P)
";

%feature("docstring")  FormFactorAnisoPyramid::FormFactorAnisoPyramid "FormFactorAnisoPyramid::FormFactorAnisoPyramid(double length, double width, double height, double alpha)
";

%feature("docstring")  FormFactorAnisoPyramid::clone "FormFactorAnisoPyramid* FormFactorAnisoPyramid::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorAnisoPyramid::accept "void FormFactorAnisoPyramid::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorAnisoPyramid::getLength "double FormFactorAnisoPyramid::getLength() const
";

%feature("docstring")  FormFactorAnisoPyramid::getWidth "double FormFactorAnisoPyramid::getWidth() const
";

%feature("docstring")  FormFactorAnisoPyramid::getHeight "double FormFactorAnisoPyramid::getHeight() const
";

%feature("docstring")  FormFactorAnisoPyramid::getAlpha "double FormFactorAnisoPyramid::getAlpha() const
";


// File: classFormFactorBarGauss.xml
%feature("docstring") FormFactorBarGauss "

The form factor of an elongated bar, with Gaussian profile in elongation direction.

C++ includes: FormFactorBar.h
";

%feature("docstring")  FormFactorBarGauss::FormFactorBarGauss "FormFactorBarGauss::FormFactorBarGauss(const std::vector< double > P)
";

%feature("docstring")  FormFactorBarGauss::FormFactorBarGauss "FormFactorBarGauss::FormFactorBarGauss(double length, double width, double height)
";

%feature("docstring")  FormFactorBarGauss::clone "FormFactorBarGauss * FormFactorBarGauss::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorBarGauss::accept "void FormFactorBarGauss::accept(INodeVisitor *visitor) const final
";


// File: classFormFactorBarLorentz.xml
%feature("docstring") FormFactorBarLorentz "

The form factor of an elongated, with Lorentz form factor in elongation direction.

C++ includes: FormFactorBar.h
";

%feature("docstring")  FormFactorBarLorentz::FormFactorBarLorentz "FormFactorBarLorentz::FormFactorBarLorentz(const std::vector< double > P)
";

%feature("docstring")  FormFactorBarLorentz::FormFactorBarLorentz "FormFactorBarLorentz::FormFactorBarLorentz(double length, double width, double height)
";

%feature("docstring")  FormFactorBarLorentz::clone "FormFactorBarLorentz * FormFactorBarLorentz::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorBarLorentz::accept "void FormFactorBarLorentz::accept(INodeVisitor *visitor) const final
";


// File: classFormFactorBox.xml
%feature("docstring") FormFactorBox "

A rectangular prism (parallelepiped).

C++ includes: FormFactorBox.h
";

%feature("docstring")  FormFactorBox::FormFactorBox "FormFactorBox::FormFactorBox(const std::vector< double > P)
";

%feature("docstring")  FormFactorBox::FormFactorBox "FormFactorBox::FormFactorBox(double length, double width, double height)
";

%feature("docstring")  FormFactorBox::clone "FormFactorBox* FormFactorBox::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorBox::accept "void FormFactorBox::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorBox::getLength "double FormFactorBox::getLength() const
";

%feature("docstring")  FormFactorBox::getWidth "double FormFactorBox::getWidth() const
";

%feature("docstring")  FormFactorBox::volume "double FormFactorBox::volume() const final

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorBox::radialExtension "double FormFactorBox::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorBox::evaluate_for_q "complex_t FormFactorBox::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorCantellatedCube.xml
%feature("docstring") FormFactorCantellatedCube "

A cube, with truncation of all edges and corners, as in Croset (2017) Fig 7

C++ includes: FormFactorCantellatedCube.h
";

%feature("docstring")  FormFactorCantellatedCube::FormFactorCantellatedCube "FormFactorCantellatedCube::FormFactorCantellatedCube(const std::vector< double > P)
";

%feature("docstring")  FormFactorCantellatedCube::FormFactorCantellatedCube "FormFactorCantellatedCube::FormFactorCantellatedCube(double length, double removed_length)
";

%feature("docstring")  FormFactorCantellatedCube::clone "FormFactorCantellatedCube* FormFactorCantellatedCube::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorCantellatedCube::accept "void FormFactorCantellatedCube::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorCantellatedCube::getLength "double FormFactorCantellatedCube::getLength() const
";

%feature("docstring")  FormFactorCantellatedCube::getRemovedLength "double FormFactorCantellatedCube::getRemovedLength() const
";


// File: classFormFactorCoherentPart.xml
%feature("docstring") FormFactorCoherentPart "

Information about single particle form factor and specular info of the embedding layer.

C++ includes: FormFactorCoherentPart.h
";

%feature("docstring")  FormFactorCoherentPart::FormFactorCoherentPart "FormFactorCoherentPart::FormFactorCoherentPart(IComputeFF *ff)
";

%feature("docstring")  FormFactorCoherentPart::FormFactorCoherentPart "FormFactorCoherentPart::FormFactorCoherentPart(const FormFactorCoherentPart &other)
";

%feature("docstring")  FormFactorCoherentPart::FormFactorCoherentPart "FormFactorCoherentPart::FormFactorCoherentPart(FormFactorCoherentPart &&other)
";

%feature("docstring")  FormFactorCoherentPart::~FormFactorCoherentPart "FormFactorCoherentPart::~FormFactorCoherentPart()
";

%feature("docstring")  FormFactorCoherentPart::evaluate "complex_t FormFactorCoherentPart::evaluate(const SimulationElement &sim_element) const
";

%feature("docstring")  FormFactorCoherentPart::evaluatePol "Eigen::Matrix2cd FormFactorCoherentPart::evaluatePol(const SimulationElement &sim_element) const
";

%feature("docstring")  FormFactorCoherentPart::setSpecularInfo "void FormFactorCoherentPart::setSpecularInfo(const IFresnelMap *fresnel_map, size_t layer_index)
";

%feature("docstring")  FormFactorCoherentPart::radialExtension "double FormFactorCoherentPart::radialExtension() const
";


// File: classFormFactorCoherentSum.xml
%feature("docstring") FormFactorCoherentSum "

Information about particle form factor and abundance.

C++ includes: FormFactorCoherentSum.h
";

%feature("docstring")  FormFactorCoherentSum::FormFactorCoherentSum "FormFactorCoherentSum::FormFactorCoherentSum(double abundance)
";

%feature("docstring")  FormFactorCoherentSum::addCoherentPart "void FormFactorCoherentSum::addCoherentPart(const FormFactorCoherentPart &part)
";

%feature("docstring")  FormFactorCoherentSum::evaluate "complex_t FormFactorCoherentSum::evaluate(const SimulationElement &sim_element) const
";

%feature("docstring")  FormFactorCoherentSum::evaluatePol "Eigen::Matrix2cd FormFactorCoherentSum::evaluatePol(const SimulationElement &sim_element) const
";

%feature("docstring")  FormFactorCoherentSum::relativeAbundance "double FormFactorCoherentSum::relativeAbundance() const
";

%feature("docstring")  FormFactorCoherentSum::scaleRelativeAbundance "void FormFactorCoherentSum::scaleRelativeAbundance(double total_abundance)
";

%feature("docstring")  FormFactorCoherentSum::radialExtension "double FormFactorCoherentSum::radialExtension() const
";


// File: classFormFactorComponents.xml
%feature("docstring") FormFactorComponents "

Predefined form factors for functional tests.

C++ includes: FormFactorComponents.h
";

%feature("docstring")  FormFactorComponents::FormFactorComponents "FormFactorComponents::FormFactorComponents()
";


// File: classFormFactorCone.xml
%feature("docstring") FormFactorCone "

A conical frustum (cone truncated parallel to the base) with circular base.

C++ includes: FormFactorCone.h
";

%feature("docstring")  FormFactorCone::FormFactorCone "FormFactorCone::FormFactorCone(const std::vector< double > P)
";

%feature("docstring")  FormFactorCone::FormFactorCone "FormFactorCone::FormFactorCone(double radius, double height, double alpha)
";

%feature("docstring")  FormFactorCone::clone "FormFactorCone* FormFactorCone::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorCone::accept "void FormFactorCone::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorCone::getHeight "double FormFactorCone::getHeight() const
";

%feature("docstring")  FormFactorCone::getAlpha "double FormFactorCone::getAlpha() const
";

%feature("docstring")  FormFactorCone::getRadius "double FormFactorCone::getRadius() const
";

%feature("docstring")  FormFactorCone::radialExtension "double FormFactorCone::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCone::evaluate_for_q "complex_t FormFactorCone::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorCone6.xml
%feature("docstring") FormFactorCone6 "

A frustum (truncated pyramid) with regular hexagonal base.

C++ includes: FormFactorCone6.h
";

%feature("docstring")  FormFactorCone6::FormFactorCone6 "FormFactorCone6::FormFactorCone6(const std::vector< double > P)
";

%feature("docstring")  FormFactorCone6::FormFactorCone6 "FormFactorCone6::FormFactorCone6(double base_edge, double height, double alpha)
";

%feature("docstring")  FormFactorCone6::clone "FormFactorCone6* FormFactorCone6::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorCone6::accept "void FormFactorCone6::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorCone6::getBaseEdge "double FormFactorCone6::getBaseEdge() const
";

%feature("docstring")  FormFactorCone6::getHeight "double FormFactorCone6::getHeight() const
";

%feature("docstring")  FormFactorCone6::getAlpha "double FormFactorCone6::getAlpha() const
";


// File: classFormFactorCoreShell.xml
%feature("docstring") FormFactorCoreShell "

Form Factor for a core shell particle.

Used by  ParticleCoreShell.

C++ includes: FormFactorCoreShell.h
";

%feature("docstring")  FormFactorCoreShell::FormFactorCoreShell "FormFactorCoreShell::FormFactorCoreShell(IFormFactor *core, IFormFactor *shell)
";

%feature("docstring")  FormFactorCoreShell::~FormFactorCoreShell "FormFactorCoreShell::~FormFactorCoreShell() override
";

%feature("docstring")  FormFactorCoreShell::clone "FormFactorCoreShell * FormFactorCoreShell::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorCoreShell::accept "void FormFactorCoreShell::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  FormFactorCoreShell::radialExtension "double FormFactorCoreShell::radialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCoreShell::bottomZ "double FormFactorCoreShell::bottomZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorCoreShell::topZ "double FormFactorCoreShell::topZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorCoreShell::setAmbientMaterial "void FormFactorCoreShell::setAmbientMaterial(const Material &material) override

Passes the material in which this particle is embedded. 
";

%feature("docstring")  FormFactorCoreShell::evaluate "complex_t FormFactorCoreShell::evaluate(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorCoreShell::evaluatePol "Eigen::Matrix2cd FormFactorCoreShell::evaluatePol(const WavevectorInfo &wavevectors) const override

Calculates and returns a polarized form factor calculation in DWBA. 
";


// File: classFormFactorCosineRippleBox.xml
%feature("docstring") FormFactorCosineRippleBox "

The form factor for a cosine ripple, with box profile in elongation direction.

C++ includes: FormFactorCosineRipple.h
";

%feature("docstring")  FormFactorCosineRippleBox::FormFactorCosineRippleBox "FormFactorCosineRippleBox::FormFactorCosineRippleBox(const std::vector< double > P)
";

%feature("docstring")  FormFactorCosineRippleBox::FormFactorCosineRippleBox "FormFactorCosineRippleBox::FormFactorCosineRippleBox(double length, double width, double height)
";

%feature("docstring")  FormFactorCosineRippleBox::clone "FormFactorCosineRippleBox * FormFactorCosineRippleBox::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorCosineRippleBox::accept "void FormFactorCosineRippleBox::accept(INodeVisitor *visitor) const final
";


// File: classFormFactorCosineRippleGauss.xml
%feature("docstring") FormFactorCosineRippleGauss "

The form factor for a cosine ripple, with Gaussian profile in elongation direction.

C++ includes: FormFactorCosineRipple.h
";

%feature("docstring")  FormFactorCosineRippleGauss::FormFactorCosineRippleGauss "FormFactorCosineRippleGauss::FormFactorCosineRippleGauss(const std::vector< double > P)
";

%feature("docstring")  FormFactorCosineRippleGauss::FormFactorCosineRippleGauss "FormFactorCosineRippleGauss::FormFactorCosineRippleGauss(double length, double width, double height)
";

%feature("docstring")  FormFactorCosineRippleGauss::clone "FormFactorCosineRippleGauss * FormFactorCosineRippleGauss::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorCosineRippleGauss::accept "void FormFactorCosineRippleGauss::accept(INodeVisitor *visitor) const final
";


// File: classFormFactorCosineRippleLorentz.xml
%feature("docstring") FormFactorCosineRippleLorentz "

The form factor for a cosine ripple, with Lorentz form factor in elongation direction.

C++ includes: FormFactorCosineRipple.h
";

%feature("docstring")  FormFactorCosineRippleLorentz::FormFactorCosineRippleLorentz "FormFactorCosineRippleLorentz::FormFactorCosineRippleLorentz(const std::vector< double > P)
";

%feature("docstring")  FormFactorCosineRippleLorentz::FormFactorCosineRippleLorentz "FormFactorCosineRippleLorentz::FormFactorCosineRippleLorentz(double length, double width, double height)
";

%feature("docstring")  FormFactorCosineRippleLorentz::clone "FormFactorCosineRippleLorentz * FormFactorCosineRippleLorentz::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorCosineRippleLorentz::accept "void FormFactorCosineRippleLorentz::accept(INodeVisitor *visitor) const final
";


// File: classFormFactorCrystal.xml
%feature("docstring") FormFactorCrystal "

The form factor of a  MesoCrystal.

C++ includes: FormFactorCrystal.h
";

%feature("docstring")  FormFactorCrystal::FormFactorCrystal "FormFactorCrystal::FormFactorCrystal(const Lattice3D &lattice, const IFormFactor &basis_form_factor, const IFormFactor &meso_form_factor, double position_variance=0.0)
";

%feature("docstring")  FormFactorCrystal::~FormFactorCrystal "FormFactorCrystal::~FormFactorCrystal() override
";

%feature("docstring")  FormFactorCrystal::clone "FormFactorCrystal* FormFactorCrystal::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorCrystal::accept "void FormFactorCrystal::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  FormFactorCrystal::setAmbientMaterial "void FormFactorCrystal::setAmbientMaterial(const Material &material) override

Passes the material in which this particle is embedded. 
";

%feature("docstring")  FormFactorCrystal::volume "double FormFactorCrystal::volume() const override

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorCrystal::radialExtension "double FormFactorCrystal::radialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCrystal::bottomZ "double FormFactorCrystal::bottomZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorCrystal::topZ "double FormFactorCrystal::topZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorCrystal::evaluate "complex_t FormFactorCrystal::evaluate(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorCrystal::evaluatePol "Eigen::Matrix2cd FormFactorCrystal::evaluatePol(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorCuboctahedron.xml
%feature("docstring") FormFactorCuboctahedron "

A truncated bifrustum with quadratic base.

C++ includes: FormFactorCuboctahedron.h
";

%feature("docstring")  FormFactorCuboctahedron::FormFactorCuboctahedron "FormFactorCuboctahedron::FormFactorCuboctahedron(const std::vector< double > P)
";

%feature("docstring")  FormFactorCuboctahedron::FormFactorCuboctahedron "FormFactorCuboctahedron::FormFactorCuboctahedron(double length, double height, double height_ratio, double alpha)
";

%feature("docstring")  FormFactorCuboctahedron::clone "FormFactorCuboctahedron* FormFactorCuboctahedron::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorCuboctahedron::accept "void FormFactorCuboctahedron::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorCuboctahedron::getLength "double FormFactorCuboctahedron::getLength() const
";

%feature("docstring")  FormFactorCuboctahedron::getHeight "double FormFactorCuboctahedron::getHeight() const
";

%feature("docstring")  FormFactorCuboctahedron::getHeightRatio "double FormFactorCuboctahedron::getHeightRatio() const
";

%feature("docstring")  FormFactorCuboctahedron::getAlpha "double FormFactorCuboctahedron::getAlpha() const
";


// File: classFormFactorCylinder.xml
%feature("docstring") FormFactorCylinder "

A circular cylinder.

C++ includes: FormFactorCylinder.h
";

%feature("docstring")  FormFactorCylinder::FormFactorCylinder "FormFactorCylinder::FormFactorCylinder(const std::vector< double > P)
";

%feature("docstring")  FormFactorCylinder::FormFactorCylinder "FormFactorCylinder::FormFactorCylinder(double radius, double height)
";

%feature("docstring")  FormFactorCylinder::clone "FormFactorCylinder* FormFactorCylinder::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorCylinder::accept "void FormFactorCylinder::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorCylinder::getHeight "double FormFactorCylinder::getHeight() const
";

%feature("docstring")  FormFactorCylinder::getRadius "double FormFactorCylinder::getRadius() const
";

%feature("docstring")  FormFactorCylinder::radialExtension "double FormFactorCylinder::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCylinder::evaluate_for_q "complex_t FormFactorCylinder::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorDecoratorMaterial.xml
%feature("docstring") FormFactorDecoratorMaterial "

Decorates a scalar formfactor with the correct factor for the material's refractive index and that of its surrounding material.

C++ includes: FormFactorDecoratorMaterial.h
";

%feature("docstring")  FormFactorDecoratorMaterial::FormFactorDecoratorMaterial "FormFactorDecoratorMaterial::FormFactorDecoratorMaterial(const IFormFactor &ff)
";

%feature("docstring")  FormFactorDecoratorMaterial::~FormFactorDecoratorMaterial "FormFactorDecoratorMaterial::~FormFactorDecoratorMaterial() override
";

%feature("docstring")  FormFactorDecoratorMaterial::clone "FormFactorDecoratorMaterial * FormFactorDecoratorMaterial::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorDecoratorMaterial::accept "void FormFactorDecoratorMaterial::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  FormFactorDecoratorMaterial::setMaterial "void FormFactorDecoratorMaterial::setMaterial(const Material &material)

Sets the material of the scatterer. 
";

%feature("docstring")  FormFactorDecoratorMaterial::setAmbientMaterial "void FormFactorDecoratorMaterial::setAmbientMaterial(const Material &material) override

Sets the ambient material. 
";

%feature("docstring")  FormFactorDecoratorMaterial::evaluate "complex_t FormFactorDecoratorMaterial::evaluate(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorDecoratorMaterial::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorMaterial::evaluatePol(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorDecoratorPositionFactor.xml
%feature("docstring") FormFactorDecoratorPositionFactor "

Decorates a form factor with a position dependent phase factor.

C++ includes: FormFactorDecoratorPositionFactor.h
";

%feature("docstring")  FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor "FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor(const IFormFactor &ff, const kvector_t &position)
";

%feature("docstring")  FormFactorDecoratorPositionFactor::clone "FormFactorDecoratorPositionFactor* FormFactorDecoratorPositionFactor::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::accept "void FormFactorDecoratorPositionFactor::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorDecoratorPositionFactor::bottomZ "double FormFactorDecoratorPositionFactor::bottomZ(const IRotation &rotation) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::topZ "double FormFactorDecoratorPositionFactor::topZ(const IRotation &rotation) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::evaluate "complex_t FormFactorDecoratorPositionFactor::evaluate(const WavevectorInfo &wavevectors) const final

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorPositionFactor::evaluatePol(const WavevectorInfo &wavevectors) const final

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorDecoratorRotation.xml
%feature("docstring") FormFactorDecoratorRotation "

Equips a form factor with a rotation.

C++ includes: FormFactorDecoratorRotation.h
";

%feature("docstring")  FormFactorDecoratorRotation::FormFactorDecoratorRotation "FormFactorDecoratorRotation::FormFactorDecoratorRotation(const IFormFactor &ff, const IRotation &rotation)

Constructor, setting form factor and rotation. 
";

%feature("docstring")  FormFactorDecoratorRotation::clone "FormFactorDecoratorRotation * FormFactorDecoratorRotation::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorDecoratorRotation::accept "void FormFactorDecoratorRotation::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorDecoratorRotation::bottomZ "double FormFactorDecoratorRotation::bottomZ(const IRotation &rotation) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDecoratorRotation::topZ "double FormFactorDecoratorRotation::topZ(const IRotation &rotation) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDecoratorRotation::evaluate "complex_t FormFactorDecoratorRotation::evaluate(const WavevectorInfo &wavevectors) const final

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorDecoratorRotation::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorRotation::evaluatePol(const WavevectorInfo &wavevectors) const final

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorDodecahedron.xml
%feature("docstring") FormFactorDodecahedron "

A regular dodecahedron.

C++ includes: FormFactorDodecahedron.h
";

%feature("docstring")  FormFactorDodecahedron::FormFactorDodecahedron "FormFactorDodecahedron::FormFactorDodecahedron(const std::vector< double > P)
";

%feature("docstring")  FormFactorDodecahedron::FormFactorDodecahedron "FormFactorDodecahedron::FormFactorDodecahedron(double edge)
";

%feature("docstring")  FormFactorDodecahedron::clone "FormFactorDodecahedron* FormFactorDodecahedron::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorDodecahedron::accept "void FormFactorDodecahedron::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorDodecahedron::getEdge "double FormFactorDodecahedron::getEdge() const
";


// File: classFormFactorDot.xml
%feature("docstring") FormFactorDot "

A dot, with scattering power as a sphere of radius rscat, but with F(q)=const.

C++ includes: FormFactorDot.h
";

%feature("docstring")  FormFactorDot::FormFactorDot "FormFactorDot::FormFactorDot(const std::vector< double > P)
";

%feature("docstring")  FormFactorDot::FormFactorDot "FormFactorDot::FormFactorDot(double radius)
";

%feature("docstring")  FormFactorDot::clone "FormFactorDot* FormFactorDot::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorDot::accept "void FormFactorDot::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorDot::getRadius "double FormFactorDot::getRadius() const
";

%feature("docstring")  FormFactorDot::radialExtension "double FormFactorDot::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorDot::bottomZ "double FormFactorDot::bottomZ(const IRotation &) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDot::topZ "double FormFactorDot::topZ(const IRotation &) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDot::evaluate_for_q "complex_t FormFactorDot::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorEllipsoidalCylinder.xml
%feature("docstring") FormFactorEllipsoidalCylinder "

A cylinder with elliptical base.

C++ includes: FormFactorEllipsoidalCylinder.h
";

%feature("docstring")  FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder "FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(const std::vector< double > P)
";

%feature("docstring")  FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder "FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(double radius_x, double radius_y, double height)
";

%feature("docstring")  FormFactorEllipsoidalCylinder::clone "FormFactorEllipsoidalCylinder* FormFactorEllipsoidalCylinder::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::accept "void FormFactorEllipsoidalCylinder::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getRadiusX "double FormFactorEllipsoidalCylinder::getRadiusX() const
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getRadiusY "double FormFactorEllipsoidalCylinder::getRadiusY() const
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getHeight "double FormFactorEllipsoidalCylinder::getHeight() const
";

%feature("docstring")  FormFactorEllipsoidalCylinder::radialExtension "double FormFactorEllipsoidalCylinder::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::evaluate_for_q "complex_t FormFactorEllipsoidalCylinder::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorFullSphere.xml
%feature("docstring") FormFactorFullSphere "

A full sphere.

C++ includes: FormFactorFullSphere.h
";

%feature("docstring")  FormFactorFullSphere::FormFactorFullSphere "FormFactorFullSphere::FormFactorFullSphere(const std::vector< double > P, bool position_at_center=false)
";

%feature("docstring")  FormFactorFullSphere::FormFactorFullSphere "FormFactorFullSphere::FormFactorFullSphere(double radius, bool position_at_center=false)
";

%feature("docstring")  FormFactorFullSphere::clone "FormFactorFullSphere* FormFactorFullSphere::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorFullSphere::accept "void FormFactorFullSphere::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorFullSphere::getRadius "double FormFactorFullSphere::getRadius() const
";

%feature("docstring")  FormFactorFullSphere::radialExtension "double FormFactorFullSphere::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorFullSphere::bottomZ "double FormFactorFullSphere::bottomZ(const IRotation &rotation) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorFullSphere::topZ "double FormFactorFullSphere::topZ(const IRotation &rotation) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorFullSphere::evaluate_for_q "complex_t FormFactorFullSphere::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorFullSpheroid.xml
%feature("docstring") FormFactorFullSpheroid "

A full spheroid (an ellipsoid with two equal axes, hence with circular cross section)

C++ includes: FormFactorFullSpheroid.h
";

%feature("docstring")  FormFactorFullSpheroid::FormFactorFullSpheroid "FormFactorFullSpheroid::FormFactorFullSpheroid(const std::vector< double > P)
";

%feature("docstring")  FormFactorFullSpheroid::FormFactorFullSpheroid "FormFactorFullSpheroid::FormFactorFullSpheroid(double radius, double height)
";

%feature("docstring")  FormFactorFullSpheroid::clone "FormFactorFullSpheroid* FormFactorFullSpheroid::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorFullSpheroid::accept "void FormFactorFullSpheroid::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorFullSpheroid::getHeight "double FormFactorFullSpheroid::getHeight() const
";

%feature("docstring")  FormFactorFullSpheroid::getRadius "double FormFactorFullSpheroid::getRadius() const
";

%feature("docstring")  FormFactorFullSpheroid::radialExtension "double FormFactorFullSpheroid::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorFullSpheroid::evaluate_for_q "complex_t FormFactorFullSpheroid::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorGaussSphere.xml
%feature("docstring") FormFactorGaussSphere "

The form factor of a Gaussian sphere.

C++ includes: FormFactorGauss.h
";

%feature("docstring")  FormFactorGaussSphere::FormFactorGaussSphere "FormFactorGaussSphere::FormFactorGaussSphere(const std::vector< double > P)
";

%feature("docstring")  FormFactorGaussSphere::FormFactorGaussSphere "FormFactorGaussSphere::FormFactorGaussSphere(double mean_radius)
";

%feature("docstring")  FormFactorGaussSphere::clone "FormFactorGaussSphere* FormFactorGaussSphere::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorGaussSphere::accept "void FormFactorGaussSphere::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorGaussSphere::getMeanRadius "double FormFactorGaussSphere::getMeanRadius() const
";

%feature("docstring")  FormFactorGaussSphere::radialExtension "double FormFactorGaussSphere::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorGaussSphere::evaluate_for_q "complex_t FormFactorGaussSphere::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorHemiEllipsoid.xml
%feature("docstring") FormFactorHemiEllipsoid "

An hemi ellipsoid, obtained by truncating a full ellipsoid in the middle plane spanned by two principal axes.

C++ includes: FormFactorHemiEllipsoid.h
";

%feature("docstring")  FormFactorHemiEllipsoid::FormFactorHemiEllipsoid "FormFactorHemiEllipsoid::FormFactorHemiEllipsoid(const std::vector< double > P)
";

%feature("docstring")  FormFactorHemiEllipsoid::FormFactorHemiEllipsoid "FormFactorHemiEllipsoid::FormFactorHemiEllipsoid(double radius_x, double radius_y, double height)
";

%feature("docstring")  FormFactorHemiEllipsoid::~FormFactorHemiEllipsoid "virtual FormFactorHemiEllipsoid::~FormFactorHemiEllipsoid()
";

%feature("docstring")  FormFactorHemiEllipsoid::clone "FormFactorHemiEllipsoid* FormFactorHemiEllipsoid::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorHemiEllipsoid::accept "void FormFactorHemiEllipsoid::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorHemiEllipsoid::getHeight "double FormFactorHemiEllipsoid::getHeight() const
";

%feature("docstring")  FormFactorHemiEllipsoid::getRadiusX "double FormFactorHemiEllipsoid::getRadiusX() const
";

%feature("docstring")  FormFactorHemiEllipsoid::getRadiusY "double FormFactorHemiEllipsoid::getRadiusY() const
";

%feature("docstring")  FormFactorHemiEllipsoid::radialExtension "double FormFactorHemiEllipsoid::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorHemiEllipsoid::evaluate_for_q "complex_t FormFactorHemiEllipsoid::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorHollowSphere.xml
%feature("docstring") FormFactorHollowSphere "

Integrated full sphere form factor over a uniform distribution of radii.

C++ includes: FormFactorHollowSphere.h
";

%feature("docstring")  FormFactorHollowSphere::FormFactorHollowSphere "FormFactorHollowSphere::FormFactorHollowSphere(const std::vector< double > P)
";

%feature("docstring")  FormFactorHollowSphere::FormFactorHollowSphere "FormFactorHollowSphere::FormFactorHollowSphere(double mean, double full_width)
";

%feature("docstring")  FormFactorHollowSphere::clone "FormFactorHollowSphere* FormFactorHollowSphere::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorHollowSphere::accept "void FormFactorHollowSphere::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorHollowSphere::radialExtension "double FormFactorHollowSphere::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorHollowSphere::evaluate_for_q "complex_t FormFactorHollowSphere::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorIcosahedron.xml
%feature("docstring") FormFactorIcosahedron "

A regular icosahedron.

C++ includes: FormFactorIcosahedron.h
";

%feature("docstring")  FormFactorIcosahedron::FormFactorIcosahedron "FormFactorIcosahedron::FormFactorIcosahedron(const std::vector< double > P)
";

%feature("docstring")  FormFactorIcosahedron::FormFactorIcosahedron "FormFactorIcosahedron::FormFactorIcosahedron(double edge)
";

%feature("docstring")  FormFactorIcosahedron::clone "FormFactorIcosahedron* FormFactorIcosahedron::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorIcosahedron::accept "void FormFactorIcosahedron::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorIcosahedron::getEdge "double FormFactorIcosahedron::getEdge() const
";


// File: classFormFactorLongBoxGauss.xml
%feature("docstring") FormFactorLongBoxGauss "

The form factor for a long rectangular box.

C++ includes: FormFactorLongBoxGauss.h
";

%feature("docstring")  FormFactorLongBoxGauss::FormFactorLongBoxGauss "FormFactorLongBoxGauss::FormFactorLongBoxGauss(const std::vector< double > P)
";

%feature("docstring")  FormFactorLongBoxGauss::FormFactorLongBoxGauss "FormFactorLongBoxGauss::FormFactorLongBoxGauss(double length, double width, double height)
";

%feature("docstring")  FormFactorLongBoxGauss::clone "FormFactorLongBoxGauss* FormFactorLongBoxGauss::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorLongBoxGauss::accept "void FormFactorLongBoxGauss::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorLongBoxGauss::getLength "double FormFactorLongBoxGauss::getLength() const
";

%feature("docstring")  FormFactorLongBoxGauss::getHeight "double FormFactorLongBoxGauss::getHeight() const
";

%feature("docstring")  FormFactorLongBoxGauss::getWidth "double FormFactorLongBoxGauss::getWidth() const
";

%feature("docstring")  FormFactorLongBoxGauss::radialExtension "double FormFactorLongBoxGauss::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongBoxGauss::evaluate_for_q "complex_t FormFactorLongBoxGauss::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorLongBoxLorentz.xml
%feature("docstring") FormFactorLongBoxLorentz "

The form factor for a long rectangular box.

C++ includes: FormFactorLongBoxLorentz.h
";

%feature("docstring")  FormFactorLongBoxLorentz::FormFactorLongBoxLorentz "FormFactorLongBoxLorentz::FormFactorLongBoxLorentz(const std::vector< double > P)
";

%feature("docstring")  FormFactorLongBoxLorentz::FormFactorLongBoxLorentz "FormFactorLongBoxLorentz::FormFactorLongBoxLorentz(double length, double width, double height)
";

%feature("docstring")  FormFactorLongBoxLorentz::clone "FormFactorLongBoxLorentz* FormFactorLongBoxLorentz::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorLongBoxLorentz::accept "void FormFactorLongBoxLorentz::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorLongBoxLorentz::getLength "double FormFactorLongBoxLorentz::getLength() const
";

%feature("docstring")  FormFactorLongBoxLorentz::getHeight "double FormFactorLongBoxLorentz::getHeight() const
";

%feature("docstring")  FormFactorLongBoxLorentz::getWidth "double FormFactorLongBoxLorentz::getWidth() const
";

%feature("docstring")  FormFactorLongBoxLorentz::radialExtension "double FormFactorLongBoxLorentz::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongBoxLorentz::evaluate_for_q "complex_t FormFactorLongBoxLorentz::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorPrism3.xml
%feature("docstring") FormFactorPrism3 "

A prism based on an equilateral triangle.

C++ includes: FormFactorPrism3.h
";

%feature("docstring")  FormFactorPrism3::FormFactorPrism3 "FormFactorPrism3::FormFactorPrism3(const std::vector< double > P)
";

%feature("docstring")  FormFactorPrism3::FormFactorPrism3 "FormFactorPrism3::FormFactorPrism3(double base_edge, double height)
";

%feature("docstring")  FormFactorPrism3::clone "FormFactorPrism3* FormFactorPrism3::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorPrism3::accept "void FormFactorPrism3::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorPrism3::getBaseEdge "double FormFactorPrism3::getBaseEdge() const
";


// File: classFormFactorPrism6.xml
%feature("docstring") FormFactorPrism6 "

A prism based on a regular hexagonal.

C++ includes: FormFactorPrism6.h
";

%feature("docstring")  FormFactorPrism6::FormFactorPrism6 "FormFactorPrism6::FormFactorPrism6(const std::vector< double > P)
";

%feature("docstring")  FormFactorPrism6::FormFactorPrism6 "FormFactorPrism6::FormFactorPrism6(double base_edge, double height)
";

%feature("docstring")  FormFactorPrism6::clone "FormFactorPrism6* FormFactorPrism6::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorPrism6::accept "void FormFactorPrism6::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorPrism6::getBaseEdge "double FormFactorPrism6::getBaseEdge() const
";


// File: classFormFactorPyramid.xml
%feature("docstring") FormFactorPyramid "

A frustum with a quadratic base.

C++ includes: FormFactorPyramid.h
";

%feature("docstring")  FormFactorPyramid::FormFactorPyramid "FormFactorPyramid::FormFactorPyramid(const std::vector< double > P)
";

%feature("docstring")  FormFactorPyramid::FormFactorPyramid "FormFactorPyramid::FormFactorPyramid(double base_edge, double height, double alpha)
";

%feature("docstring")  FormFactorPyramid::clone "FormFactorPyramid* FormFactorPyramid::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorPyramid::accept "void FormFactorPyramid::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorPyramid::getHeight "double FormFactorPyramid::getHeight() const
";

%feature("docstring")  FormFactorPyramid::getBaseEdge "double FormFactorPyramid::getBaseEdge() const
";

%feature("docstring")  FormFactorPyramid::getAlpha "double FormFactorPyramid::getAlpha() const
";


// File: classFormFactorSawtoothRippleBox.xml
%feature("docstring") FormFactorSawtoothRippleBox "

The form factor for a cosine ripple, with box profile in elongation direction.

C++ includes: FormFactorSawtoothRipple.h
";

%feature("docstring")  FormFactorSawtoothRippleBox::FormFactorSawtoothRippleBox "FormFactorSawtoothRippleBox::FormFactorSawtoothRippleBox(const std::vector< double > P)
";

%feature("docstring")  FormFactorSawtoothRippleBox::FormFactorSawtoothRippleBox "FormFactorSawtoothRippleBox::FormFactorSawtoothRippleBox(double length, double width, double height, double asymmetry)
";

%feature("docstring")  FormFactorSawtoothRippleBox::clone "FormFactorSawtoothRippleBox * FormFactorSawtoothRippleBox::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorSawtoothRippleBox::accept "void FormFactorSawtoothRippleBox::accept(INodeVisitor *visitor) const final
";


// File: classFormFactorSawtoothRippleGauss.xml
%feature("docstring") FormFactorSawtoothRippleGauss "

The form factor for a cosine ripple, with Gaussian profile in elongation direction.

C++ includes: FormFactorSawtoothRipple.h
";

%feature("docstring")  FormFactorSawtoothRippleGauss::FormFactorSawtoothRippleGauss "FormFactorSawtoothRippleGauss::FormFactorSawtoothRippleGauss(const std::vector< double > P)
";

%feature("docstring")  FormFactorSawtoothRippleGauss::FormFactorSawtoothRippleGauss "FormFactorSawtoothRippleGauss::FormFactorSawtoothRippleGauss(double length, double width, double height, double asymmetry)
";

%feature("docstring")  FormFactorSawtoothRippleGauss::clone "FormFactorSawtoothRippleGauss * FormFactorSawtoothRippleGauss::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorSawtoothRippleGauss::accept "void FormFactorSawtoothRippleGauss::accept(INodeVisitor *visitor) const final
";


// File: classFormFactorSawtoothRippleLorentz.xml
%feature("docstring") FormFactorSawtoothRippleLorentz "

The form factor for a cosine ripple, with Lorentz form factor in elongation direction.

C++ includes: FormFactorSawtoothRipple.h
";

%feature("docstring")  FormFactorSawtoothRippleLorentz::FormFactorSawtoothRippleLorentz "FormFactorSawtoothRippleLorentz::FormFactorSawtoothRippleLorentz(const std::vector< double > P)
";

%feature("docstring")  FormFactorSawtoothRippleLorentz::FormFactorSawtoothRippleLorentz "FormFactorSawtoothRippleLorentz::FormFactorSawtoothRippleLorentz(double length, double width, double height, double asymmetry)
";

%feature("docstring")  FormFactorSawtoothRippleLorentz::clone "FormFactorSawtoothRippleLorentz * FormFactorSawtoothRippleLorentz::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorSawtoothRippleLorentz::accept "void FormFactorSawtoothRippleLorentz::accept(INodeVisitor *visitor) const final
";


// File: classFormFactorSphereGaussianRadius.xml
%feature("docstring") FormFactorSphereGaussianRadius "

A sphere with gaussian radius distribution.

C++ includes: FormFactorSphereGaussianRadius.h
";

%feature("docstring")  FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius "FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius(const std::vector< double > P)
";

%feature("docstring")  FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius "FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius(double mean, double sigma)
";

%feature("docstring")  FormFactorSphereGaussianRadius::clone "FormFactorSphereGaussianRadius* FormFactorSphereGaussianRadius::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorSphereGaussianRadius::accept "void FormFactorSphereGaussianRadius::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorSphereGaussianRadius::radialExtension "double FormFactorSphereGaussianRadius::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorSphereGaussianRadius::evaluate_for_q "complex_t FormFactorSphereGaussianRadius::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorSphereLogNormalRadius.xml
%feature("docstring") FormFactorSphereLogNormalRadius "

A sphere with log normal radius distribution.

C++ includes: FormFactorSphereLogNormalRadius.h
";

%feature("docstring")  FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius "FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius(const std::vector< double > P, size_t n_samples=0)
";

%feature("docstring")  FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius "FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius(double mean, double scale_param, size_t n_samples)
";

%feature("docstring")  FormFactorSphereLogNormalRadius::clone "FormFactorSphereLogNormalRadius * FormFactorSphereLogNormalRadius::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorSphereLogNormalRadius::accept "void FormFactorSphereLogNormalRadius::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorSphereLogNormalRadius::radialExtension "double FormFactorSphereLogNormalRadius::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorSphereLogNormalRadius::evaluate_for_q "complex_t FormFactorSphereLogNormalRadius::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorTetrahedron.xml
%feature("docstring") FormFactorTetrahedron "

A frustum with equilateral trigonal base.

C++ includes: FormFactorTetrahedron.h
";

%feature("docstring")  FormFactorTetrahedron::FormFactorTetrahedron "FormFactorTetrahedron::FormFactorTetrahedron(const std::vector< double > P)
";

%feature("docstring")  FormFactorTetrahedron::FormFactorTetrahedron "FormFactorTetrahedron::FormFactorTetrahedron(double base_edge, double height, double alpha)
";

%feature("docstring")  FormFactorTetrahedron::clone "FormFactorTetrahedron* FormFactorTetrahedron::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorTetrahedron::accept "void FormFactorTetrahedron::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorTetrahedron::getBaseEdge "double FormFactorTetrahedron::getBaseEdge() const
";

%feature("docstring")  FormFactorTetrahedron::getHeight "double FormFactorTetrahedron::getHeight() const
";

%feature("docstring")  FormFactorTetrahedron::getAlpha "double FormFactorTetrahedron::getAlpha() const
";


// File: classFormFactorTruncatedCube.xml
%feature("docstring") FormFactorTruncatedCube "

A cube, with tetrahedral truncation of all corners

C++ includes: FormFactorTruncatedCube.h
";

%feature("docstring")  FormFactorTruncatedCube::FormFactorTruncatedCube "FormFactorTruncatedCube::FormFactorTruncatedCube(const std::vector< double > P)
";

%feature("docstring")  FormFactorTruncatedCube::FormFactorTruncatedCube "FormFactorTruncatedCube::FormFactorTruncatedCube(double length, double removed_length)
";

%feature("docstring")  FormFactorTruncatedCube::clone "FormFactorTruncatedCube* FormFactorTruncatedCube::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorTruncatedCube::accept "void FormFactorTruncatedCube::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorTruncatedCube::getLength "double FormFactorTruncatedCube::getLength() const
";

%feature("docstring")  FormFactorTruncatedCube::getRemovedLength "double FormFactorTruncatedCube::getRemovedLength() const
";


// File: classFormFactorTruncatedSphere.xml
%feature("docstring") FormFactorTruncatedSphere "

A truncated Sphere.

C++ includes: FormFactorTruncatedSphere.h
";

%feature("docstring")  FormFactorTruncatedSphere::FormFactorTruncatedSphere "FormFactorTruncatedSphere::FormFactorTruncatedSphere(const std::vector< double > P)
";

%feature("docstring")  FormFactorTruncatedSphere::FormFactorTruncatedSphere "FormFactorTruncatedSphere::FormFactorTruncatedSphere(double radius, double height, double dh)
";

%feature("docstring")  FormFactorTruncatedSphere::clone "FormFactorTruncatedSphere* FormFactorTruncatedSphere::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorTruncatedSphere::accept "void FormFactorTruncatedSphere::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorTruncatedSphere::getHeight "double FormFactorTruncatedSphere::getHeight() const
";

%feature("docstring")  FormFactorTruncatedSphere::getRadius "double FormFactorTruncatedSphere::getRadius() const
";

%feature("docstring")  FormFactorTruncatedSphere::getRemovedTop "double FormFactorTruncatedSphere::getRemovedTop() const
";

%feature("docstring")  FormFactorTruncatedSphere::radialExtension "double FormFactorTruncatedSphere::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTruncatedSphere::evaluate_for_q "complex_t FormFactorTruncatedSphere::evaluate_for_q(cvector_t q) const final

Complex form factor. 
";


// File: classFormFactorTruncatedSpheroid.xml
%feature("docstring") FormFactorTruncatedSpheroid "

A truncated spheroid. An ellipsoid with two equal axis, truncated by a plane perpendicular to the third axis.

C++ includes: FormFactorTruncatedSpheroid.h
";

%feature("docstring")  FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid "FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid(const std::vector< double > P)
";

%feature("docstring")  FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid "FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid(double radius, double height, double height_flattening, double dh)
";

%feature("docstring")  FormFactorTruncatedSpheroid::clone "FormFactorTruncatedSpheroid* FormFactorTruncatedSpheroid::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorTruncatedSpheroid::accept "void FormFactorTruncatedSpheroid::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FormFactorTruncatedSpheroid::getRadius "double FormFactorTruncatedSpheroid::getRadius() const
";

%feature("docstring")  FormFactorTruncatedSpheroid::getHeight "double FormFactorTruncatedSpheroid::getHeight() const
";

%feature("docstring")  FormFactorTruncatedSpheroid::getHeightFlattening "double FormFactorTruncatedSpheroid::getHeightFlattening() const
";

%feature("docstring")  FormFactorTruncatedSpheroid::getRemovedTop "double FormFactorTruncatedSpheroid::getRemovedTop() const
";

%feature("docstring")  FormFactorTruncatedSpheroid::radialExtension "double FormFactorTruncatedSpheroid::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTruncatedSpheroid::evaluate_for_q "complex_t FormFactorTruncatedSpheroid::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorWeighted.xml
%feature("docstring") FormFactorWeighted "

Coherent sum of different scalar  IFormFactors with different weights.

Used by  ParticleComposition. If same particles are at different positions, then consider FormFactorDecoratorMultiPositionFactor (restore from commit 0500a26de76).

C++ includes: FormFactorWeighted.h
";

%feature("docstring")  FormFactorWeighted::FormFactorWeighted "FormFactorWeighted::FormFactorWeighted()
";

%feature("docstring")  FormFactorWeighted::~FormFactorWeighted "FormFactorWeighted::~FormFactorWeighted() override
";

%feature("docstring")  FormFactorWeighted::clone "FormFactorWeighted * FormFactorWeighted::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  FormFactorWeighted::accept "void FormFactorWeighted::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  FormFactorWeighted::radialExtension "double FormFactorWeighted::radialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorWeighted::bottomZ "double FormFactorWeighted::bottomZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorWeighted::topZ "double FormFactorWeighted::topZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorWeighted::addFormFactor "void FormFactorWeighted::addFormFactor(const IFormFactor &form_factor, double weight=1.0)
";

%feature("docstring")  FormFactorWeighted::setAmbientMaterial "void FormFactorWeighted::setAmbientMaterial(const Material &material) override

Passes the material in which this particle is embedded. 
";

%feature("docstring")  FormFactorWeighted::evaluate "complex_t FormFactorWeighted::evaluate(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorWeighted::evaluatePol "Eigen::Matrix2cd FormFactorWeighted::evaluatePol(const WavevectorInfo &wavevectors) const override

Calculates and returns a polarized form factor calculation in DWBA. 
";


// File: classFTDecayFunction1DCauchy.xml
%feature("docstring") FTDecayFunction1DCauchy "

One-dimensional Cauchy decay function in reciprocal space; corresponds to exp(-|x|/decay_length) in real space.

C++ includes: FTDecay1D.h
";

%feature("docstring")  FTDecayFunction1DCauchy::FTDecayFunction1DCauchy "FTDecayFunction1DCauchy::FTDecayFunction1DCauchy(const std::vector< double > P)
";

%feature("docstring")  FTDecayFunction1DCauchy::FTDecayFunction1DCauchy "FTDecayFunction1DCauchy::FTDecayFunction1DCauchy(double decay_length)
";

%feature("docstring")  FTDecayFunction1DCauchy::clone "FTDecayFunction1DCauchy * FTDecayFunction1DCauchy::clone() const
";

%feature("docstring")  FTDecayFunction1DCauchy::accept "void FTDecayFunction1DCauchy::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDecayFunction1DCauchy::evaluate "double FTDecayFunction1DCauchy::evaluate(double q) const final
";


// File: classFTDecayFunction1DGauss.xml
%feature("docstring") FTDecayFunction1DGauss "

One-dimensional Gauss decay function in reciprocal space; corresponds to exp[-x^2/(2*decay_length^2)] in real space.

C++ includes: FTDecay1D.h
";

%feature("docstring")  FTDecayFunction1DGauss::FTDecayFunction1DGauss "FTDecayFunction1DGauss::FTDecayFunction1DGauss(const std::vector< double > P)
";

%feature("docstring")  FTDecayFunction1DGauss::FTDecayFunction1DGauss "FTDecayFunction1DGauss::FTDecayFunction1DGauss(double decay_length)
";

%feature("docstring")  FTDecayFunction1DGauss::clone "FTDecayFunction1DGauss * FTDecayFunction1DGauss::clone() const
";

%feature("docstring")  FTDecayFunction1DGauss::accept "void FTDecayFunction1DGauss::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDecayFunction1DGauss::evaluate "double FTDecayFunction1DGauss::evaluate(double q) const final
";


// File: classFTDecayFunction1DTriangle.xml
%feature("docstring") FTDecayFunction1DTriangle "

One-dimensional triangle decay function in reciprocal space; corresponds to 1-|x|/decay_length if |x|<decay_length (and 0 otherwise) in real space.

C++ includes: FTDecay1D.h
";

%feature("docstring")  FTDecayFunction1DTriangle::FTDecayFunction1DTriangle "FTDecayFunction1DTriangle::FTDecayFunction1DTriangle(const std::vector< double > P)
";

%feature("docstring")  FTDecayFunction1DTriangle::FTDecayFunction1DTriangle "FTDecayFunction1DTriangle::FTDecayFunction1DTriangle(double decay_length)
";

%feature("docstring")  FTDecayFunction1DTriangle::clone "FTDecayFunction1DTriangle * FTDecayFunction1DTriangle::clone() const
";

%feature("docstring")  FTDecayFunction1DTriangle::accept "void FTDecayFunction1DTriangle::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDecayFunction1DTriangle::evaluate "double FTDecayFunction1DTriangle::evaluate(double q) const final
";


// File: classFTDecayFunction1DVoigt.xml
%feature("docstring") FTDecayFunction1DVoigt "

One-dimensional pseudo-Voigt decay function in reciprocal space; corresponds to eta*Gauss + (1-eta)*Cauchy.

C++ includes: FTDecay1D.h
";

%feature("docstring")  FTDecayFunction1DVoigt::FTDecayFunction1DVoigt "FTDecayFunction1DVoigt::FTDecayFunction1DVoigt(const std::vector< double > P)
";

%feature("docstring")  FTDecayFunction1DVoigt::FTDecayFunction1DVoigt "FTDecayFunction1DVoigt::FTDecayFunction1DVoigt(double decay_length, double eta)
";

%feature("docstring")  FTDecayFunction1DVoigt::clone "FTDecayFunction1DVoigt * FTDecayFunction1DVoigt::clone() const
";

%feature("docstring")  FTDecayFunction1DVoigt::accept "void FTDecayFunction1DVoigt::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDecayFunction1DVoigt::evaluate "double FTDecayFunction1DVoigt::evaluate(double q) const final
";

%feature("docstring")  FTDecayFunction1DVoigt::eEta "double FTDecayFunction1DVoigt::eEta() const
";


// File: classFTDecayFunction2DCauchy.xml
%feature("docstring") FTDecayFunction2DCauchy "

Two-dimensional Cauchy decay function in reciprocal space; corresponds to exp(-r) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDecay2D.h
";

%feature("docstring")  FTDecayFunction2DCauchy::FTDecayFunction2DCauchy "FTDecayFunction2DCauchy::FTDecayFunction2DCauchy(const std::vector< double > P)
";

%feature("docstring")  FTDecayFunction2DCauchy::FTDecayFunction2DCauchy "FTDecayFunction2DCauchy::FTDecayFunction2DCauchy(double decay_length_x, double decay_length_y, double gamma)
";

%feature("docstring")  FTDecayFunction2DCauchy::clone "FTDecayFunction2DCauchy * FTDecayFunction2DCauchy::clone() const
";

%feature("docstring")  FTDecayFunction2DCauchy::accept "void FTDecayFunction2DCauchy::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDecayFunction2DCauchy::evaluate "double FTDecayFunction2DCauchy::evaluate(double qx, double qy) const final

evaluate Fourier transformed decay function for q in X,Y coordinates 
";


// File: classFTDecayFunction2DGauss.xml
%feature("docstring") FTDecayFunction2DGauss "

Two-dimensional Gauss decay function in reciprocal space; corresponds to exp(-r^2/2) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDecay2D.h
";

%feature("docstring")  FTDecayFunction2DGauss::FTDecayFunction2DGauss "FTDecayFunction2DGauss::FTDecayFunction2DGauss(const std::vector< double > P)
";

%feature("docstring")  FTDecayFunction2DGauss::FTDecayFunction2DGauss "FTDecayFunction2DGauss::FTDecayFunction2DGauss(double decay_length_x, double decay_length_y, double gamma)
";

%feature("docstring")  FTDecayFunction2DGauss::clone "FTDecayFunction2DGauss * FTDecayFunction2DGauss::clone() const
";

%feature("docstring")  FTDecayFunction2DGauss::accept "void FTDecayFunction2DGauss::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDecayFunction2DGauss::evaluate "double FTDecayFunction2DGauss::evaluate(double qx, double qy) const final

evaluate Fourier transformed decay function for q in X,Y coordinates 
";


// File: classFTDecayFunction2DVoigt.xml
%feature("docstring") FTDecayFunction2DVoigt "

Two-dimensional pseudo-Voigt decay function in reciprocal space; corresponds to eta*Gauss + (1-eta)*Cauchy.

C++ includes: FTDecay2D.h
";

%feature("docstring")  FTDecayFunction2DVoigt::FTDecayFunction2DVoigt "FTDecayFunction2DVoigt::FTDecayFunction2DVoigt(const std::vector< double > P)
";

%feature("docstring")  FTDecayFunction2DVoigt::FTDecayFunction2DVoigt "FTDecayFunction2DVoigt::FTDecayFunction2DVoigt(double decay_length_x, double decay_length_y, double gamma, double eta)
";

%feature("docstring")  FTDecayFunction2DVoigt::clone "FTDecayFunction2DVoigt * FTDecayFunction2DVoigt::clone() const
";

%feature("docstring")  FTDecayFunction2DVoigt::accept "void FTDecayFunction2DVoigt::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDecayFunction2DVoigt::evaluate "double FTDecayFunction2DVoigt::evaluate(double qx, double qy) const final

evaluate Fourier transformed decay function for q in X,Y coordinates 
";

%feature("docstring")  FTDecayFunction2DVoigt::eta "double FTDecayFunction2DVoigt::eta() const
";


// File: classFTDistribution1DCauchy.xml
%feature("docstring") FTDistribution1DCauchy "

Exponential  IFTDistribution1D exp(-|omega*x|); its Fourier transform evaluate(q) is a Cauchy-Lorentzian starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DCauchy::FTDistribution1DCauchy "FTDistribution1DCauchy::FTDistribution1DCauchy(const std::vector< double > P)
";

%feature("docstring")  FTDistribution1DCauchy::FTDistribution1DCauchy "FTDistribution1DCauchy::FTDistribution1DCauchy(double omega)
";

%feature("docstring")  FTDistribution1DCauchy::clone "FTDistribution1DCauchy * FTDistribution1DCauchy::clone() const final
";

%feature("docstring")  FTDistribution1DCauchy::accept "void FTDistribution1DCauchy::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDistribution1DCauchy::evaluate "double FTDistribution1DCauchy::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DCauchy::qSecondDerivative "double FTDistribution1DCauchy::qSecondDerivative() const final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DCauchy::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DCauchy::createSampler() const final
";


// File: classFTDistribution1DCosine.xml
%feature("docstring") FTDistribution1DCosine "

IFTDistribution1D consisting of one cosine wave [1+cos(pi*x/omega) if |x|<omega, and 0 otherwise]; its Fourier transform evaluate(q) starts at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DCosine::FTDistribution1DCosine "FTDistribution1DCosine::FTDistribution1DCosine(const std::vector< double > P)
";

%feature("docstring")  FTDistribution1DCosine::FTDistribution1DCosine "FTDistribution1DCosine::FTDistribution1DCosine(double omega)
";

%feature("docstring")  FTDistribution1DCosine::clone "FTDistribution1DCosine * FTDistribution1DCosine::clone() const final
";

%feature("docstring")  FTDistribution1DCosine::accept "void FTDistribution1DCosine::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDistribution1DCosine::evaluate "double FTDistribution1DCosine::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DCosine::qSecondDerivative "double FTDistribution1DCosine::qSecondDerivative() const final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DCosine::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DCosine::createSampler() const final
";


// File: classFTDistribution1DGate.xml
%feature("docstring") FTDistribution1DGate "

Square gate  IFTDistribution1D; its Fourier transform evaluate(q) is a sinc function starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DGate::FTDistribution1DGate "FTDistribution1DGate::FTDistribution1DGate(const std::vector< double > P)
";

%feature("docstring")  FTDistribution1DGate::FTDistribution1DGate "FTDistribution1DGate::FTDistribution1DGate(double omega)
";

%feature("docstring")  FTDistribution1DGate::clone "FTDistribution1DGate * FTDistribution1DGate::clone() const final
";

%feature("docstring")  FTDistribution1DGate::accept "void FTDistribution1DGate::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDistribution1DGate::evaluate "double FTDistribution1DGate::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DGate::qSecondDerivative "double FTDistribution1DGate::qSecondDerivative() const final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DGate::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DGate::createSampler() const final
";


// File: classFTDistribution1DGauss.xml
%feature("docstring") FTDistribution1DGauss "

Gaussian  IFTDistribution1D; its Fourier transform evaluate(q) is a Gaussian starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DGauss::FTDistribution1DGauss "FTDistribution1DGauss::FTDistribution1DGauss(const std::vector< double > P)
";

%feature("docstring")  FTDistribution1DGauss::FTDistribution1DGauss "FTDistribution1DGauss::FTDistribution1DGauss(double omega)
";

%feature("docstring")  FTDistribution1DGauss::clone "FTDistribution1DGauss * FTDistribution1DGauss::clone() const final
";

%feature("docstring")  FTDistribution1DGauss::accept "void FTDistribution1DGauss::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDistribution1DGauss::evaluate "double FTDistribution1DGauss::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DGauss::qSecondDerivative "double FTDistribution1DGauss::qSecondDerivative() const final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DGauss::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DGauss::createSampler() const final
";


// File: classFTDistribution1DTriangle.xml
%feature("docstring") FTDistribution1DTriangle "

Triangle  IFTDistribution1D [1-|x|/omega if |x|<omega, and 0 otherwise]; its Fourier transform evaluate(q) is a squared sinc function starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DTriangle::FTDistribution1DTriangle "FTDistribution1DTriangle::FTDistribution1DTriangle(const std::vector< double > P)
";

%feature("docstring")  FTDistribution1DTriangle::FTDistribution1DTriangle "FTDistribution1DTriangle::FTDistribution1DTriangle(double omega)
";

%feature("docstring")  FTDistribution1DTriangle::clone "FTDistribution1DTriangle * FTDistribution1DTriangle::clone() const final
";

%feature("docstring")  FTDistribution1DTriangle::accept "void FTDistribution1DTriangle::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDistribution1DTriangle::evaluate "double FTDistribution1DTriangle::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DTriangle::qSecondDerivative "double FTDistribution1DTriangle::qSecondDerivative() const final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DTriangle::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DTriangle::createSampler() const final
";


// File: classFTDistribution1DVoigt.xml
%feature("docstring") FTDistribution1DVoigt "

IFTDistribution1D that provides a Fourier transform evaluate(q) in form of a pseudo-Voigt decay function eta*Gauss + (1-eta)*Cauchy, with both components starting at 1 for q=0.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DVoigt::FTDistribution1DVoigt "FTDistribution1DVoigt::FTDistribution1DVoigt(const std::vector< double > P)
";

%feature("docstring")  FTDistribution1DVoigt::FTDistribution1DVoigt "FTDistribution1DVoigt::FTDistribution1DVoigt(double omega, double eta)
";

%feature("docstring")  FTDistribution1DVoigt::clone "FTDistribution1DVoigt * FTDistribution1DVoigt::clone() const final
";

%feature("docstring")  FTDistribution1DVoigt::accept "void FTDistribution1DVoigt::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDistribution1DVoigt::evaluate "double FTDistribution1DVoigt::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DVoigt::eta "double FTDistribution1DVoigt::eta() const
";

%feature("docstring")  FTDistribution1DVoigt::qSecondDerivative "double FTDistribution1DVoigt::qSecondDerivative() const final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DVoigt::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DVoigt::createSampler() const final
";


// File: classFTDistribution2DCauchy.xml
%feature("docstring") FTDistribution2DCauchy "

Two-dimensional Cauchy distribution in Fourier space; corresponds to a normalized exp(-r) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DCauchy::FTDistribution2DCauchy "FTDistribution2DCauchy::FTDistribution2DCauchy(const std::vector< double > P)
";

%feature("docstring")  FTDistribution2DCauchy::FTDistribution2DCauchy "FTDistribution2DCauchy::FTDistribution2DCauchy(double omega_x, double omega_y, double gamma)
";

%feature("docstring")  FTDistribution2DCauchy::clone "FTDistribution2DCauchy * FTDistribution2DCauchy::clone() const final
";

%feature("docstring")  FTDistribution2DCauchy::accept "void FTDistribution2DCauchy::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDistribution2DCauchy::evaluate "double FTDistribution2DCauchy::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DCauchy::createSampler "std::unique_ptr< IDistribution2DSampler > FTDistribution2DCauchy::createSampler() const final
";


// File: classFTDistribution2DComponents.xml
%feature("docstring") FTDistribution2DComponents "

Predefined Fourier transformed distributions for functional tests.

C++ includes: FTDistribution2DComponents.h
";

%feature("docstring")  FTDistribution2DComponents::FTDistribution2DComponents "FTDistribution2DComponents::FTDistribution2DComponents()
";


// File: classFTDistribution2DCone.xml
%feature("docstring") FTDistribution2DCone "

Two-dimensional cone distribution in Fourier space; corresponds to 1-r if r<1 (and 0 otherwise) in real space with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DCone::FTDistribution2DCone "FTDistribution2DCone::FTDistribution2DCone(const std::vector< double > P)
";

%feature("docstring")  FTDistribution2DCone::FTDistribution2DCone "FTDistribution2DCone::FTDistribution2DCone(double omega_x, double omega_y, double gamma)
";

%feature("docstring")  FTDistribution2DCone::clone "FTDistribution2DCone * FTDistribution2DCone::clone() const final
";

%feature("docstring")  FTDistribution2DCone::accept "void FTDistribution2DCone::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDistribution2DCone::evaluate "double FTDistribution2DCone::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DCone::createSampler "std::unique_ptr< IDistribution2DSampler > FTDistribution2DCone::createSampler() const final
";


// File: classFTDistribution2DGate.xml
%feature("docstring") FTDistribution2DGate "

Two-dimensional gate distribution in Fourier space; corresponds to normalized constant if r<1 (and 0 otherwise) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DGate::FTDistribution2DGate "FTDistribution2DGate::FTDistribution2DGate(const std::vector< double > P)
";

%feature("docstring")  FTDistribution2DGate::FTDistribution2DGate "FTDistribution2DGate::FTDistribution2DGate(double omega_x, double omega_y, double gamma)
";

%feature("docstring")  FTDistribution2DGate::clone "FTDistribution2DGate * FTDistribution2DGate::clone() const final
";

%feature("docstring")  FTDistribution2DGate::accept "void FTDistribution2DGate::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDistribution2DGate::evaluate "double FTDistribution2DGate::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DGate::createSampler "std::unique_ptr< IDistribution2DSampler > FTDistribution2DGate::createSampler() const final
";


// File: classFTDistribution2DGauss.xml
%feature("docstring") FTDistribution2DGauss "

Two-dimensional Gauss distribution in Fourier space; corresponds to normalized exp(-r^2/2) in real space with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DGauss::FTDistribution2DGauss "FTDistribution2DGauss::FTDistribution2DGauss(const std::vector< double > P)
";

%feature("docstring")  FTDistribution2DGauss::FTDistribution2DGauss "FTDistribution2DGauss::FTDistribution2DGauss(double omega_x, double omega_y, double gamma)
";

%feature("docstring")  FTDistribution2DGauss::clone "FTDistribution2DGauss * FTDistribution2DGauss::clone() const final
";

%feature("docstring")  FTDistribution2DGauss::accept "void FTDistribution2DGauss::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDistribution2DGauss::evaluate "double FTDistribution2DGauss::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DGauss::createSampler "std::unique_ptr< IDistribution2DSampler > FTDistribution2DGauss::createSampler() const final
";


// File: classFTDistribution2DVoigt.xml
%feature("docstring") FTDistribution2DVoigt "

Two-dimensional Voigt distribution in Fourier space; corresponds to eta*Gauss + (1-eta)*Cauchy

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DVoigt::FTDistribution2DVoigt "FTDistribution2DVoigt::FTDistribution2DVoigt(const std::vector< double > P)
";

%feature("docstring")  FTDistribution2DVoigt::FTDistribution2DVoigt "FTDistribution2DVoigt::FTDistribution2DVoigt(double omega_x, double omega_y, double gamma, double eta)
";

%feature("docstring")  FTDistribution2DVoigt::clone "FTDistribution2DVoigt * FTDistribution2DVoigt::clone() const final
";

%feature("docstring")  FTDistribution2DVoigt::accept "void FTDistribution2DVoigt::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  FTDistribution2DVoigt::evaluate "double FTDistribution2DVoigt::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DVoigt::eta "double FTDistribution2DVoigt::eta() const
";

%feature("docstring")  FTDistribution2DVoigt::createSampler "std::unique_ptr< IDistribution2DSampler > FTDistribution2DVoigt::createSampler() const final
";


// File: classGaussFisherPeakShape.xml
%feature("docstring") GaussFisherPeakShape "

A peak shape that is Gaussian in the radial direction and uses the Mises-Fisher distribution in the angular direction.

C++ includes: IPeakShape.h
";

%feature("docstring")  GaussFisherPeakShape::GaussFisherPeakShape "GaussFisherPeakShape::GaussFisherPeakShape(double max_intensity, double radial_size, double kappa)
";

%feature("docstring")  GaussFisherPeakShape::~GaussFisherPeakShape "GaussFisherPeakShape::~GaussFisherPeakShape() override
";

%feature("docstring")  GaussFisherPeakShape::clone "GaussFisherPeakShape * GaussFisherPeakShape::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  GaussFisherPeakShape::accept "void GaussFisherPeakShape::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  GaussFisherPeakShape::evaluate "double GaussFisherPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";

%feature("docstring")  GaussFisherPeakShape::angularDisorder "bool GaussFisherPeakShape::angularDisorder() const override

Indicates if the peak shape encodes angular disorder, in which case all peaks in a spherical shell are needed 
";


// File: classHardDiskBuilder.xml
%feature("docstring") HardDiskBuilder "

Builds sample: cylinders with hard disk Percus-Yevick interference.

C++ includes: PercusYevickBuilder.h
";

%feature("docstring")  HardDiskBuilder::buildSample "MultiLayer * HardDiskBuilder::buildSample() const
";


// File: classScalarFresnelMap_1_1Hash2Doubles.xml


// File: classMatrixFresnelMap_1_1HashKVector.xml


// File: classHexagonalLattice2D.xml
%feature("docstring") HexagonalLattice2D "

A two-dimensional Bravais lattice with hexagonal symmetry.

C++ includes: Lattice2D.h
";

%feature("docstring")  HexagonalLattice2D::HexagonalLattice2D "HexagonalLattice2D::HexagonalLattice2D(double length, double xi)
";

%feature("docstring")  HexagonalLattice2D::clone "HexagonalLattice2D * HexagonalLattice2D::clone() const
";

%feature("docstring")  HexagonalLattice2D::accept "void HexagonalLattice2D::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  HexagonalLattice2D::length1 "virtual double HexagonalLattice2D::length1() const
";

%feature("docstring")  HexagonalLattice2D::length2 "virtual double HexagonalLattice2D::length2() const
";

%feature("docstring")  HexagonalLattice2D::latticeAngle "double HexagonalLattice2D::latticeAngle() const
";

%feature("docstring")  HexagonalLattice2D::unitCellArea "double HexagonalLattice2D::unitCellArea() const
";


// File: classHexParaCrystalBuilder.xml
%feature("docstring") HexParaCrystalBuilder "

Builds sample: cylinders with 2DDL structure factor (IsGISAXS example #4).

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  HexParaCrystalBuilder::buildSample "MultiLayer * HexParaCrystalBuilder::buildSample() const
";


// File: classHomogeneousMultilayerBuilder.xml
%feature("docstring") HomogeneousMultilayerBuilder "

Builds a sample with 10 interchanging homogeneous layers of Ti and Ni on silicone substrate. Ti is 70 angstroms thick, Ni is 30 angstroms thick. No absorption, no roughness, target wavelength is 1.54 angstroms.

C++ includes: HomogeneousMultilayerBuilder.h
";

%feature("docstring")  HomogeneousMultilayerBuilder::buildSample "MultiLayer * HomogeneousMultilayerBuilder::buildSample() const
";


// File: structHomogeneousRegion.xml
%feature("docstring") HomogeneousRegion "

Struct that contains information on a single homogeneous region of a particle inside a single layer. This information is needed for calculating the average of a material, used in the Fresnel calculations.

C++ includes: HomogeneousRegion.h
";


// File: classIAbstractParticle.xml
%feature("docstring") IAbstractParticle "

Interface for a generic particle.

Inherited by  IParticle and  ParticleDistribution.

C++ includes: IAbstractParticle.h
";

%feature("docstring")  IAbstractParticle::IAbstractParticle "IAbstractParticle::IAbstractParticle()=default
";

%feature("docstring")  IAbstractParticle::IAbstractParticle "IAbstractParticle::IAbstractParticle(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IAbstractParticle::~IAbstractParticle "virtual IAbstractParticle::~IAbstractParticle()=default
";

%feature("docstring")  IAbstractParticle::clone "virtual IAbstractParticle* IAbstractParticle::clone() const =0

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  IAbstractParticle::accept "void IAbstractParticle::accept(INodeVisitor *visitor) const
";

%feature("docstring")  IAbstractParticle::abundance "double IAbstractParticle::abundance() const
";

%feature("docstring")  IAbstractParticle::setAbundance "void IAbstractParticle::setAbundance(double abundance)

Sets particle abundance.

Parameters:
-----------

abundance: 
proportion of this type of particles normalized to the total number of particles in the layout. 
";

%feature("docstring")  IAbstractParticle::translate "virtual void IAbstractParticle::translate(kvector_t translation)=0

Translates the particle with the given vector. 
";

%feature("docstring")  IAbstractParticle::rotate "virtual void IAbstractParticle::rotate(const IRotation &rotation)=0

Applies the given rotation to the particle. 
";


// File: classIBornFF.xml
%feature("docstring") IBornFF "

Abstract base class for Born form factors.

In contrast to the generic  IFormFactor, a Born form factor does not depend on the incoming and outgoing wave vectors ki and kf, except through their difference, the scattering vector q=ki-kf.

C++ includes: IBornFF.h
";

%feature("docstring")  IBornFF::IBornFF "IBornFF::IBornFF()
";

%feature("docstring")  IBornFF::IBornFF "IBornFF::IBornFF(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IBornFF::~IBornFF "IBornFF::~IBornFF()
";

%feature("docstring")  IBornFF::clone "IBornFF* IBornFF::clone() const override=0

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  IBornFF::setAmbientMaterial "void IBornFF::setAmbientMaterial(const Material &) override

Passes the material in which this particle is embedded. 
";

%feature("docstring")  IBornFF::evaluate "complex_t IBornFF::evaluate(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  IBornFF::evaluatePol "Eigen::Matrix2cd IBornFF::evaluatePol(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for matrix interactions. 
";

%feature("docstring")  IBornFF::bottomZ "double IBornFF::bottomZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IBornFF::topZ "double IBornFF::topZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IBornFF::evaluate_for_q "virtual complex_t IBornFF::evaluate_for_q(cvector_t q) const =0

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classIComputeFF.xml
%feature("docstring") IComputeFF "

Abstract base class for form factor evaluations.

Wraps an  IFormFactor, and provides functions evaluate or evaluatePol.

C++ includes: IComputeFF.h
";

%feature("docstring")  IComputeFF::IComputeFF "IComputeFF::IComputeFF()=delete
";

%feature("docstring")  IComputeFF::~IComputeFF "IComputeFF::~IComputeFF()
";

%feature("docstring")  IComputeFF::clone "virtual IComputeFF* IComputeFF::clone() const =0
";

%feature("docstring")  IComputeFF::setAmbientMaterial "void IComputeFF::setAmbientMaterial(const Material &material)
";

%feature("docstring")  IComputeFF::volume "double IComputeFF::volume() const
";

%feature("docstring")  IComputeFF::radialExtension "double IComputeFF::radialExtension() const
";

%feature("docstring")  IComputeFF::bottomZ "double IComputeFF::bottomZ(const IRotation &rotation) const
";

%feature("docstring")  IComputeFF::topZ "double IComputeFF::topZ(const IRotation &rotation) const
";

%feature("docstring")  IComputeFF::evaluate "virtual complex_t IComputeFF::evaluate(const WavevectorInfo &wavevectors) const =0
";

%feature("docstring")  IComputeFF::evaluatePol "Eigen::Matrix2cd IComputeFF::evaluatePol(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for matrix interactions. 
";

%feature("docstring")  IComputeFF::setSpecularInfo "void IComputeFF::setSpecularInfo(std::unique_ptr< const ILayerRTCoefficients >, std::unique_ptr< const ILayerRTCoefficients >)

Sets reflection/transmission info. 
";


// File: classICosineRipple.xml
%feature("docstring") ICosineRipple "

Base class for form factors with a cosine ripple profile in the yz plane.

C++ includes: IProfileRipple.h
";

%feature("docstring")  ICosineRipple::ICosineRipple "ICosineRipple::ICosineRipple(const NodeMeta &meta, const std::vector< double > &PValues)
";


// File: classIdentityRotation.xml
%feature("docstring") IdentityRotation "

The identity rotation, which leaves everything in place.

C++ includes: Rotations.h
";

%feature("docstring")  IdentityRotation::IdentityRotation "IdentityRotation::IdentityRotation()
";

%feature("docstring")  IdentityRotation::clone "IdentityRotation* IdentityRotation::clone() const
";

%feature("docstring")  IdentityRotation::createInverse "IdentityRotation* IdentityRotation::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  IdentityRotation::accept "void IdentityRotation::accept(INodeVisitor *visitor) const
";

%feature("docstring")  IdentityRotation::getTransform3D "Transform3D IdentityRotation::getTransform3D() const

Returns transformation. 
";

%feature("docstring")  IdentityRotation::isIdentity "bool IdentityRotation::isIdentity() const

Returns true if rotation matrix is identity matrix (no rotations) 
";


// File: classIDistribution1DSampler.xml
%feature("docstring") IDistribution1DSampler "";

%feature("docstring")  IDistribution1DSampler::IDistribution1DSampler "IDistribution1DSampler::IDistribution1DSampler()
";

%feature("docstring")  IDistribution1DSampler::~IDistribution1DSampler "IDistribution1DSampler::~IDistribution1DSampler()
";

%feature("docstring")  IDistribution1DSampler::randomSample "virtual double IDistribution1DSampler::randomSample() const =0
";


// File: classIDistribution2DSampler.xml
%feature("docstring") IDistribution2DSampler "";

%feature("docstring")  IDistribution2DSampler::IDistribution2DSampler "IDistribution2DSampler::IDistribution2DSampler()
";

%feature("docstring")  IDistribution2DSampler::~IDistribution2DSampler "IDistribution2DSampler::~IDistribution2DSampler()
";

%feature("docstring")  IDistribution2DSampler::randomSample "virtual std::pair<double, double> IDistribution2DSampler::randomSample() const =0
";


// File: classIFormFactor.xml
%feature("docstring") IFormFactor "

Abstract base class for all form factors.

The actual form factor is returned by the complex valued function  IFormFactor::evaluate, which depends on the incoming and outgoing wave vectors ki and kf. If it only depends on the scattering vector q=ki-kf, then it is a  IBornFF.

C++ includes: IFormFactor.h
";

%feature("docstring")  IFormFactor::IFormFactor "IFormFactor::IFormFactor()=default
";

%feature("docstring")  IFormFactor::IFormFactor "IFormFactor::IFormFactor(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IFormFactor::~IFormFactor "IFormFactor::~IFormFactor()=default
";

%feature("docstring")  IFormFactor::clone "IFormFactor* IFormFactor::clone() const override=0

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  IFormFactor::createSlicedFormFactor "IFormFactor * IFormFactor::createSlicedFormFactor(ZLimits limits, const IRotation &rot, kvector_t translation) const

Creates a (possibly sliced) form factor with the given rotation and translation. 
";

%feature("docstring")  IFormFactor::setAmbientMaterial "virtual void IFormFactor::setAmbientMaterial(const Material &)=0

Passes the material in which this particle is embedded. 
";

%feature("docstring")  IFormFactor::evaluate "virtual complex_t IFormFactor::evaluate(const WavevectorInfo &wavevectors) const =0

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  IFormFactor::evaluatePol "Eigen::Matrix2cd IFormFactor::evaluatePol(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for matrix interactions. 
";

%feature("docstring")  IFormFactor::volume "double IFormFactor::volume() const

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  IFormFactor::radialExtension "virtual double IFormFactor::radialExtension() const =0

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  IFormFactor::bottomZ "virtual double IFormFactor::bottomZ(const IRotation &rotation) const =0

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactor::topZ "virtual double IFormFactor::topZ(const IRotation &rotation) const =0

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactor::setSpecularInfo "void IFormFactor::setSpecularInfo(std::unique_ptr< const ILayerRTCoefficients >, std::unique_ptr< const ILayerRTCoefficients >)

Sets reflection/transmission info. 
";


// File: classIFormFactorDecorator.xml
%feature("docstring") IFormFactorDecorator "

Encapsulates another formfactor and adds extra functionality (a scalar factor, a position-dependent phase factor, ...).

This class is designed according to the Decorator Pattern. It inherits from  IFormFactor and has a member of type IFormFactor*.

C++ includes: IFormFactorDecorator.h
";

%feature("docstring")  IFormFactorDecorator::IFormFactorDecorator "IFormFactorDecorator::IFormFactorDecorator(const IFormFactor &ff)
";

%feature("docstring")  IFormFactorDecorator::~IFormFactorDecorator "IFormFactorDecorator::~IFormFactorDecorator() override
";

%feature("docstring")  IFormFactorDecorator::clone "IFormFactorDecorator* IFormFactorDecorator::clone() const override=0

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  IFormFactorDecorator::setAmbientMaterial "void IFormFactorDecorator::setAmbientMaterial(const Material &material) override

Passes the material in which this particle is embedded. 
";

%feature("docstring")  IFormFactorDecorator::volume "double IFormFactorDecorator::volume() const override

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  IFormFactorDecorator::radialExtension "double IFormFactorDecorator::radialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  IFormFactorDecorator::bottomZ "double IFormFactorDecorator::bottomZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactorDecorator::topZ "double IFormFactorDecorator::topZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactorDecorator::getFormFactor "const IFormFactor* IFormFactorDecorator::getFormFactor() const
";


// File: classIFormFactorPolyhedron.xml
%feature("docstring") IFormFactorPolyhedron "

A polyhedron, for form factor computation.

C++ includes: IFormFactorPolyhedron.h
";

%feature("docstring")  IFormFactorPolyhedron::IFormFactorPolyhedron "IFormFactorPolyhedron::IFormFactorPolyhedron()=delete
";

%feature("docstring")  IFormFactorPolyhedron::IFormFactorPolyhedron "IFormFactorPolyhedron::IFormFactorPolyhedron(const NodeMeta &meta, const std::vector< double > &PValues)

The mathematics implemented here is described in full detail in a paper by Joachim Wuttke, entitled \"Form factor (Fourier shape transform) of polygon and polyhedron.\" 
";

%feature("docstring")  IFormFactorPolyhedron::~IFormFactorPolyhedron "IFormFactorPolyhedron::~IFormFactorPolyhedron()
";

%feature("docstring")  IFormFactorPolyhedron::bottomZ "double IFormFactorPolyhedron::bottomZ(const IRotation &rotation) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactorPolyhedron::topZ "double IFormFactorPolyhedron::topZ(const IRotation &rotation) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactorPolyhedron::evaluate_for_q "complex_t IFormFactorPolyhedron::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";

%feature("docstring")  IFormFactorPolyhedron::evaluate_centered "complex_t IFormFactorPolyhedron::evaluate_centered(cvector_t q) const
";

%feature("docstring")  IFormFactorPolyhedron::volume "double IFormFactorPolyhedron::volume() const final

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  IFormFactorPolyhedron::radialExtension "double IFormFactorPolyhedron::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  IFormFactorPolyhedron::assert_platonic "void IFormFactorPolyhedron::assert_platonic() const

Assertions for Platonic solid. 
";


// File: classIFormFactorPrism.xml
%feature("docstring") IFormFactorPrism "

A prism with a polygonal base, for form factor computation.

C++ includes: IFormFactorPrism.h
";

%feature("docstring")  IFormFactorPrism::IFormFactorPrism "IFormFactorPrism::IFormFactorPrism(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IFormFactorPrism::~IFormFactorPrism "IFormFactorPrism::~IFormFactorPrism()
";

%feature("docstring")  IFormFactorPrism::bottomZ "double IFormFactorPrism::bottomZ(const IRotation &rotation) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactorPrism::topZ "double IFormFactorPrism::topZ(const IRotation &rotation) const final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactorPrism::evaluate_for_q "complex_t IFormFactorPrism::evaluate_for_q(cvector_t q) const override

Returns the form factor F(q) of this polyhedron, respecting the offset height/2. 
";

%feature("docstring")  IFormFactorPrism::volume "double IFormFactorPrism::volume() const override

Returns the volume of this prism. 
";

%feature("docstring")  IFormFactorPrism::radialExtension "double IFormFactorPrism::radialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  IFormFactorPrism::getHeight "double IFormFactorPrism::getHeight() const
";


// File: classIFresnelMap.xml
%feature("docstring") IFresnelMap "

Holds the necessary information to calculate the radiation wavefunction in every layer for different incoming (outgoing) angles of the beam in the top layer (these amplitudes correspond to the specular part of the wavefunction).

C++ includes: IFresnelMap.h
";

%feature("docstring")  IFresnelMap::IFresnelMap "IFresnelMap::IFresnelMap(std::unique_ptr< ISpecularStrategy > strategy)
";

%feature("docstring")  IFresnelMap::~IFresnelMap "IFresnelMap::~IFresnelMap()
";

%feature("docstring")  IFresnelMap::getOutCoefficients "virtual std::unique_ptr<const ILayerRTCoefficients> IFresnelMap::getOutCoefficients(const SimulationElement &sim_element, size_t layer_index) const =0

Retrieves the amplitude coefficients for a (time-reversed) outgoing wavevector. 
";

%feature("docstring")  IFresnelMap::getInCoefficients "std::unique_ptr<const ILayerRTCoefficients> IFresnelMap::getInCoefficients(const T &sim_element, size_t layer_index) const

Retrieves the amplitude coefficients for an incoming wavevector. 
";

%feature("docstring")  IFresnelMap::setSlices "void IFresnelMap::setSlices(const std::vector< Slice > &slices)
";

%feature("docstring")  IFresnelMap::slices "const std::vector< Slice > & IFresnelMap::slices() const
";

%feature("docstring")  IFresnelMap::disableCaching "void IFresnelMap::disableCaching()

Disables caching of previously computed Fresnel coefficients. 
";


// File: classIFTDecayFunction1D.xml
%feature("docstring") IFTDecayFunction1D "

Interface for a one-dimensional decay function, with evaluate(q) returning the Fourier transform, normalized to  $\\\\int dq\\\\; {\\\\rm evaluate}(q) = 1$.

C++ includes: FTDecay1D.h
";

%feature("docstring")  IFTDecayFunction1D::IFTDecayFunction1D "IFTDecayFunction1D::IFTDecayFunction1D(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IFTDecayFunction1D::clone "virtual IFTDecayFunction1D* IFTDecayFunction1D::clone() const =0
";

%feature("docstring")  IFTDecayFunction1D::evaluate "virtual double IFTDecayFunction1D::evaluate(double q) const =0
";

%feature("docstring")  IFTDecayFunction1D::decayLength "double IFTDecayFunction1D::decayLength() const
";


// File: classIFTDecayFunction2D.xml
%feature("docstring") IFTDecayFunction2D "

Interface for two-dimensional decay function in reciprocal space.

C++ includes: FTDecay2D.h
";

%feature("docstring")  IFTDecayFunction2D::IFTDecayFunction2D "IFTDecayFunction2D::IFTDecayFunction2D(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IFTDecayFunction2D::clone "virtual IFTDecayFunction2D* IFTDecayFunction2D::clone() const =0
";

%feature("docstring")  IFTDecayFunction2D::decayLengthX "double IFTDecayFunction2D::decayLengthX() const

get decay length in distribution's X-direction 
";

%feature("docstring")  IFTDecayFunction2D::decayLengthY "double IFTDecayFunction2D::decayLengthY() const

get decay length in distribution's Y-direction 
";

%feature("docstring")  IFTDecayFunction2D::gamma "double IFTDecayFunction2D::gamma() const

get angle between first lattice vector and X-axis of distribution (both in direct space) 
";

%feature("docstring")  IFTDecayFunction2D::evaluate "virtual double IFTDecayFunction2D::evaluate(double qx, double qy) const =0

evaluate Fourier transformed decay function for q in X,Y coordinates 
";

%feature("docstring")  IFTDecayFunction2D::boundingReciprocalLatticeCoordinates "std::pair< double, double > IFTDecayFunction2D::boundingReciprocalLatticeCoordinates(double qX, double qY, double a, double b, double alpha) const

transform back to a*, b* basis:

Calculates bounding values of reciprocal lattice coordinates that contain the centered rectangle with a corner defined by qX and qY 
";


// File: classIFTDistribution1D.xml
%feature("docstring") IFTDistribution1D "

Interface for a one-dimensional distribution, with normalization adjusted so that the Fourier transform evaluate(q) is a decay function that starts at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  IFTDistribution1D::IFTDistribution1D "IFTDistribution1D::IFTDistribution1D(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IFTDistribution1D::clone "virtual IFTDistribution1D* IFTDistribution1D::clone() const =0
";

%feature("docstring")  IFTDistribution1D::evaluate "virtual double IFTDistribution1D::evaluate(double q) const =0

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  IFTDistribution1D::omega "double IFTDistribution1D::omega() const
";

%feature("docstring")  IFTDistribution1D::qSecondDerivative "virtual double IFTDistribution1D::qSecondDerivative() const =0

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  IFTDistribution1D::createSampler "virtual std::unique_ptr<IDistribution1DSampler> IFTDistribution1D::createSampler() const =0
";


// File: classIFTDistribution2D.xml
%feature("docstring") IFTDistribution2D "

Interface for two-dimensional distributions in Fourier space.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  IFTDistribution2D::IFTDistribution2D "IFTDistribution2D::IFTDistribution2D(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IFTDistribution2D::clone "IFTDistribution2D* IFTDistribution2D::clone() const =0
";

%feature("docstring")  IFTDistribution2D::omegaX "double IFTDistribution2D::omegaX() const
";

%feature("docstring")  IFTDistribution2D::omegaY "double IFTDistribution2D::omegaY() const
";

%feature("docstring")  IFTDistribution2D::gamma "double IFTDistribution2D::gamma() const
";

%feature("docstring")  IFTDistribution2D::delta "double IFTDistribution2D::delta() const

Angle in direct space between X- and Y-axis of distribution. 
";

%feature("docstring")  IFTDistribution2D::evaluate "virtual double IFTDistribution2D::evaluate(double qx, double qy) const =0

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  IFTDistribution2D::createSampler "virtual std::unique_ptr<IDistribution2DSampler> IFTDistribution2D::createSampler() const =0
";


// File: classIInterferenceFunction.xml
%feature("docstring") IInterferenceFunction "

Abstract base class of interference functions.

C++ includes: IInterferenceFunction.h
";

%feature("docstring")  IInterferenceFunction::IInterferenceFunction "IInterferenceFunction::IInterferenceFunction(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IInterferenceFunction::IInterferenceFunction "IInterferenceFunction::IInterferenceFunction(double position_var)
";

%feature("docstring")  IInterferenceFunction::clone "virtual IInterferenceFunction* IInterferenceFunction::clone() const =0

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  IInterferenceFunction::evaluate "double IInterferenceFunction::evaluate(const kvector_t q, double outer_iff=1.0) const

Evaluates the interference function for a given wavevector transfer. 
";

%feature("docstring")  IInterferenceFunction::setPositionVariance "void IInterferenceFunction::setPositionVariance(double var)

Sets the variance of the position for the calculation of the DW factor It is defined as the variance in each relevant dimension 
";

%feature("docstring")  IInterferenceFunction::positionVariance "double IInterferenceFunction::positionVariance() const

Returns the position variance. 
";

%feature("docstring")  IInterferenceFunction::getParticleDensity "virtual double IInterferenceFunction::getParticleDensity() const

If defined by this interference function's parameters, returns the particle density (per area). Otherwise, returns zero or a user-defined value 
";

%feature("docstring")  IInterferenceFunction::supportsMultilayer "virtual bool IInterferenceFunction::supportsMultilayer() const

Indicates if this interference function can be used with a multilayer (DWBA mode) 
";

%feature("docstring")  IInterferenceFunction::DWfactor "double IInterferenceFunction::DWfactor(kvector_t q) const

Evaluates the Debye-Waller factor for a given wavevector transfer. 
";


// File: classIInterferenceFunctionStrategy.xml
%feature("docstring") IInterferenceFunctionStrategy "

Base class of all interference function strategy classes. Provides an 'evaluate' function that computes the total scattering intensity from a decorated layer, taking into account a specific inter-particle interference function. This function uses the low-level functions scalarCalculation and polarizedCalculation that are to be overriden in the derived classes. Inheritance is used to support different approximation schemes ( DecouplingApproximationStrategy,  SSCApproximationStrategy).

Instantiation of child classes takes place in LayoutStrategyBuilder::createStrategy, which is called from ParticleLayoutComputation::eval.

C++ includes: IInterferenceFunctionStrategy.h
";

%feature("docstring")  IInterferenceFunctionStrategy::IInterferenceFunctionStrategy "IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(const std::vector< FormFactorCoherentSum > &weighted_formfactors, const SimulationOptions &sim_params, bool polarized)
";

%feature("docstring")  IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy "IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy()
";

%feature("docstring")  IInterferenceFunctionStrategy::evaluate "double IInterferenceFunctionStrategy::evaluate(const SimulationElement &sim_element) const

Calculates the intensity for scalar particles/interactions. 
";


// File: classILayerRTCoefficients.xml
%feature("docstring") ILayerRTCoefficients "

Interface to access reflection/transmission coefficients.

C++ includes: ILayerRTCoefficients.h
";

%feature("docstring")  ILayerRTCoefficients::~ILayerRTCoefficients "virtual ILayerRTCoefficients::~ILayerRTCoefficients()
";

%feature("docstring")  ILayerRTCoefficients::clone "virtual ILayerRTCoefficients* ILayerRTCoefficients::clone() const =0
";

%feature("docstring")  ILayerRTCoefficients::T1plus "virtual Eigen::Vector2cd ILayerRTCoefficients::T1plus() const =0

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  ILayerRTCoefficients::R1plus "virtual Eigen::Vector2cd ILayerRTCoefficients::R1plus() const =0
";

%feature("docstring")  ILayerRTCoefficients::T2plus "virtual Eigen::Vector2cd ILayerRTCoefficients::T2plus() const =0
";

%feature("docstring")  ILayerRTCoefficients::R2plus "virtual Eigen::Vector2cd ILayerRTCoefficients::R2plus() const =0
";

%feature("docstring")  ILayerRTCoefficients::T1min "virtual Eigen::Vector2cd ILayerRTCoefficients::T1min() const =0
";

%feature("docstring")  ILayerRTCoefficients::R1min "virtual Eigen::Vector2cd ILayerRTCoefficients::R1min() const =0
";

%feature("docstring")  ILayerRTCoefficients::T2min "virtual Eigen::Vector2cd ILayerRTCoefficients::T2min() const =0
";

%feature("docstring")  ILayerRTCoefficients::R2min "virtual Eigen::Vector2cd ILayerRTCoefficients::R2min() const =0
";

%feature("docstring")  ILayerRTCoefficients::getKz "virtual Eigen::Vector2cd ILayerRTCoefficients::getKz() const =0

Returns z-part of the two wavevector eigenmodes. 
";

%feature("docstring")  ILayerRTCoefficients::getScalarT "virtual complex_t ILayerRTCoefficients::getScalarT() const

Scalar value getters; these throw errors by default as they should only be used when the derived object is really scalar 
";

%feature("docstring")  ILayerRTCoefficients::getScalarR "virtual complex_t ILayerRTCoefficients::getScalarR() const
";

%feature("docstring")  ILayerRTCoefficients::getScalarKz "virtual complex_t ILayerRTCoefficients::getScalarKz() const
";

%feature("docstring")  ILayerRTCoefficients::getReflectionMatrix "virtual Eigen::Matrix2cd ILayerRTCoefficients::getReflectionMatrix() const
";


// File: classIntegratorMCMiser.xml
%feature("docstring") IntegratorMCMiser "";


// File: classInterferenceFunction1DLattice.xml
%feature("docstring") InterferenceFunction1DLattice "

Interference function of a 1D lattice.

C++ includes: InterferenceFunction1DLattice.h
";

%feature("docstring")  InterferenceFunction1DLattice::InterferenceFunction1DLattice "InterferenceFunction1DLattice::InterferenceFunction1DLattice(double length, double xi)

Constructor of interference function of one-dimensional lattice.

Parameters:
-----------

length: 
lattice constant in nanometers

xi: 
rotation of lattice with respect to x-axis in radians 
";

%feature("docstring")  InterferenceFunction1DLattice::~InterferenceFunction1DLattice "InterferenceFunction1DLattice::~InterferenceFunction1DLattice() override
";

%feature("docstring")  InterferenceFunction1DLattice::clone "InterferenceFunction1DLattice * InterferenceFunction1DLattice::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  InterferenceFunction1DLattice::accept "void InterferenceFunction1DLattice::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  InterferenceFunction1DLattice::setDecayFunction "void InterferenceFunction1DLattice::setDecayFunction(const IFTDecayFunction1D &decay)

Sets one-dimensional decay function.

Parameters:
-----------

decay: 
one-dimensional decay function in reciprocal space 
";

%feature("docstring")  InterferenceFunction1DLattice::getLength "double InterferenceFunction1DLattice::getLength() const
";

%feature("docstring")  InterferenceFunction1DLattice::getXi "double InterferenceFunction1DLattice::getXi() const
";

%feature("docstring")  InterferenceFunction1DLattice::getChildren "std::vector< const INode * > InterferenceFunction1DLattice::getChildren() const override
";


// File: classInterferenceFunction2DLattice.xml
%feature("docstring") InterferenceFunction2DLattice "

Interference function of a 2D lattice.

C++ includes: InterferenceFunction2DLattice.h
";

%feature("docstring")  InterferenceFunction2DLattice::InterferenceFunction2DLattice "InterferenceFunction2DLattice::InterferenceFunction2DLattice(const Lattice2D &lattice)
";

%feature("docstring")  InterferenceFunction2DLattice::~InterferenceFunction2DLattice "InterferenceFunction2DLattice::~InterferenceFunction2DLattice() override
";

%feature("docstring")  InterferenceFunction2DLattice::clone "InterferenceFunction2DLattice * InterferenceFunction2DLattice::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  InterferenceFunction2DLattice::accept "void InterferenceFunction2DLattice::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  InterferenceFunction2DLattice::setDecayFunction "void InterferenceFunction2DLattice::setDecayFunction(const IFTDecayFunction2D &decay)

Sets two-dimensional decay function.

Parameters:
-----------

decay: 
two-dimensional decay function in reciprocal space 
";

%feature("docstring")  InterferenceFunction2DLattice::setIntegrationOverXi "void InterferenceFunction2DLattice::setIntegrationOverXi(bool integrate_xi)
";

%feature("docstring")  InterferenceFunction2DLattice::integrationOverXi "bool InterferenceFunction2DLattice::integrationOverXi() const
";

%feature("docstring")  InterferenceFunction2DLattice::lattice "const Lattice2D & InterferenceFunction2DLattice::lattice() const
";

%feature("docstring")  InterferenceFunction2DLattice::getParticleDensity "double InterferenceFunction2DLattice::getParticleDensity() const override

Returns the particle density associated with this 2d lattice. 
";

%feature("docstring")  InterferenceFunction2DLattice::getChildren "std::vector< const INode * > InterferenceFunction2DLattice::getChildren() const override
";

%feature("docstring")  InterferenceFunction2DLattice::onChange "void InterferenceFunction2DLattice::onChange() override
";


// File: classInterferenceFunction2DParaCrystal.xml
%feature("docstring") InterferenceFunction2DParaCrystal "

Interference function of a 2D paracrystal.

C++ includes: InterferenceFunction2DParaCrystal.h
";

%feature("docstring")  InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal "InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal(const Lattice2D &lattice, double damping_length, double domain_size_1, double domain_size_2)
";

%feature("docstring")  InterferenceFunction2DParaCrystal::~InterferenceFunction2DParaCrystal "InterferenceFunction2DParaCrystal::~InterferenceFunction2DParaCrystal() override
";

%feature("docstring")  InterferenceFunction2DParaCrystal::clone "InterferenceFunction2DParaCrystal * InterferenceFunction2DParaCrystal::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::accept "void InterferenceFunction2DParaCrystal::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setDomainSizes "void InterferenceFunction2DParaCrystal::setDomainSizes(double size_1, double size_2)

Sets the sizes of coherence domains.

Parameters:
-----------

size_1: 
coherence domain size along the first basis vector in nanometers

size_2: 
coherence domain size along the second basis vector in nanometers 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setProbabilityDistributions "void InterferenceFunction2DParaCrystal::setProbabilityDistributions(const IFTDistribution2D &pdf_1, const IFTDistribution2D &pdf_2)

Sets the probability distributions (Fourier transformed) for the two lattice directions.

Parameters:
-----------

pdf_1: 
probability distribution in first lattice direction

pdf_2: 
probability distribution in second lattice direction 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setDampingLength "void InterferenceFunction2DParaCrystal::setDampingLength(double damping_length)

Sets the damping length.

Parameters:
-----------

damping_length: 
the damping (coherence) length of the paracrystal in nanometers 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::domainSizes "std::vector< double > InterferenceFunction2DParaCrystal::domainSizes() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setIntegrationOverXi "void InterferenceFunction2DParaCrystal::setIntegrationOverXi(bool integrate_xi)

Enables/disables averaging over the lattice rotation angle.

Parameters:
-----------

integrate_xi: 
integration flag 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::integrationOverXi "bool InterferenceFunction2DParaCrystal::integrationOverXi() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::dampingLength "double InterferenceFunction2DParaCrystal::dampingLength() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::lattice "const Lattice2D & InterferenceFunction2DParaCrystal::lattice() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getParticleDensity "double InterferenceFunction2DParaCrystal::getParticleDensity() const override

If defined by this interference function's parameters, returns the particle density (per area). Otherwise, returns zero or a user-defined value 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getChildren "std::vector< const INode * > InterferenceFunction2DParaCrystal::getChildren() const override
";

%feature("docstring")  InterferenceFunction2DParaCrystal::pdf1 "const IFTDistribution2D* InterferenceFunction2DParaCrystal::pdf1() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::pdf2 "const IFTDistribution2D* InterferenceFunction2DParaCrystal::pdf2() const
";


// File: classInterferenceFunction2DSuperLattice.xml
%feature("docstring") InterferenceFunction2DSuperLattice "

Interference function of a 2D superlattice with a configurable interference function for each lattice site.

C++ includes: InterferenceFunction2DSuperLattice.h
";

%feature("docstring")  InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice "InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(const Lattice2D &lattice, unsigned size_1, unsigned size_2)
";

%feature("docstring")  InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice "InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(double length_1, double length_2, double alpha, double xi, unsigned size_1, unsigned size_2)

Constructor of two-dimensional interference function.

Parameters:
-----------

length_1: 
length of first lattice vector in nanometers

length_2: 
length of second lattice vector in nanometers

alpha: 
angle between lattice vectors in radians

xi: 
rotation of lattice with respect to x-axis (beam direction) in radians

size_1: 
correlation length in direction 1

size_2: 
correlation length in direction 2 
";

%feature("docstring")  InterferenceFunction2DSuperLattice::~InterferenceFunction2DSuperLattice "InterferenceFunction2DSuperLattice::~InterferenceFunction2DSuperLattice() override
";

%feature("docstring")  InterferenceFunction2DSuperLattice::clone "InterferenceFunction2DSuperLattice * InterferenceFunction2DSuperLattice::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  InterferenceFunction2DSuperLattice::accept "void InterferenceFunction2DSuperLattice::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  InterferenceFunction2DSuperLattice::setSubstructureIFF "void InterferenceFunction2DSuperLattice::setSubstructureIFF(const IInterferenceFunction &sub_iff)
";

%feature("docstring")  InterferenceFunction2DSuperLattice::substructureIFF "const IInterferenceFunction & InterferenceFunction2DSuperLattice::substructureIFF() const
";

%feature("docstring")  InterferenceFunction2DSuperLattice::evaluate "double InterferenceFunction2DSuperLattice::evaluate(const kvector_t q, double outer_iff=1.0) const override

Evaluates the interference function for a given wavevector transfer. 
";

%feature("docstring")  InterferenceFunction2DSuperLattice::domainSize1 "unsigned InterferenceFunction2DSuperLattice::domainSize1() const
";

%feature("docstring")  InterferenceFunction2DSuperLattice::domainSize2 "unsigned InterferenceFunction2DSuperLattice::domainSize2() const
";

%feature("docstring")  InterferenceFunction2DSuperLattice::setIntegrationOverXi "void InterferenceFunction2DSuperLattice::setIntegrationOverXi(bool integrate_xi)
";

%feature("docstring")  InterferenceFunction2DSuperLattice::integrationOverXi "bool InterferenceFunction2DSuperLattice::integrationOverXi() const
";

%feature("docstring")  InterferenceFunction2DSuperLattice::lattice "const Lattice2D & InterferenceFunction2DSuperLattice::lattice() const
";

%feature("docstring")  InterferenceFunction2DSuperLattice::getChildren "std::vector< const INode * > InterferenceFunction2DSuperLattice::getChildren() const override
";


// File: classInterferenceFunction3DLattice.xml
%feature("docstring") InterferenceFunction3DLattice "

Interference function of a 3D lattice.

C++ includes: InterferenceFunction3DLattice.h
";

%feature("docstring")  InterferenceFunction3DLattice::InterferenceFunction3DLattice "InterferenceFunction3DLattice::InterferenceFunction3DLattice(const Lattice3D &lattice)
";

%feature("docstring")  InterferenceFunction3DLattice::~InterferenceFunction3DLattice "InterferenceFunction3DLattice::~InterferenceFunction3DLattice() override
";

%feature("docstring")  InterferenceFunction3DLattice::clone "InterferenceFunction3DLattice * InterferenceFunction3DLattice::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  InterferenceFunction3DLattice::accept "void InterferenceFunction3DLattice::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  InterferenceFunction3DLattice::setPeakShape "void InterferenceFunction3DLattice::setPeakShape(const IPeakShape &peak_shape)
";

%feature("docstring")  InterferenceFunction3DLattice::lattice "const Lattice3D & InterferenceFunction3DLattice::lattice() const
";

%feature("docstring")  InterferenceFunction3DLattice::supportsMultilayer "bool InterferenceFunction3DLattice::supportsMultilayer() const override

Indicates if this interference function can be used with a multilayer (DWBA mode) 
";

%feature("docstring")  InterferenceFunction3DLattice::getChildren "std::vector< const INode * > InterferenceFunction3DLattice::getChildren() const override
";

%feature("docstring")  InterferenceFunction3DLattice::onChange "void InterferenceFunction3DLattice::onChange() override
";


// File: classInterferenceFunctionFinite2DLattice.xml
%feature("docstring") InterferenceFunctionFinite2DLattice "

Interference function of a finite 2D lattice.

C++ includes: InterferenceFunctionFinite2DLattice.h
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::InterferenceFunctionFinite2DLattice "InterferenceFunctionFinite2DLattice::InterferenceFunctionFinite2DLattice(const Lattice2D &lattice, unsigned N_1, unsigned N_2)

Constructor of two-dimensional finite lattice interference function.

Parameters:
-----------

lattice: 
object specifying a 2d lattice structure

N_1: 
number of lattice cells in the first lattice direction

N_2: 
number of lattice cells in the second lattice direction 
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::~InterferenceFunctionFinite2DLattice "InterferenceFunctionFinite2DLattice::~InterferenceFunctionFinite2DLattice() override
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::clone "InterferenceFunctionFinite2DLattice * InterferenceFunctionFinite2DLattice::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::accept "void InterferenceFunctionFinite2DLattice::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::numberUnitCells1 "unsigned InterferenceFunctionFinite2DLattice::numberUnitCells1() const
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::numberUnitCells2 "unsigned InterferenceFunctionFinite2DLattice::numberUnitCells2() const
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::setIntegrationOverXi "void InterferenceFunctionFinite2DLattice::setIntegrationOverXi(bool integrate_xi)
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::integrationOverXi "bool InterferenceFunctionFinite2DLattice::integrationOverXi() const
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::lattice "const Lattice2D & InterferenceFunctionFinite2DLattice::lattice() const
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::getParticleDensity "double InterferenceFunctionFinite2DLattice::getParticleDensity() const override

Returns the particle density associated with this 2d lattice. 
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::getChildren "std::vector< const INode * > InterferenceFunctionFinite2DLattice::getChildren() const override
";


// File: classInterferenceFunctionFinite3DLattice.xml
%feature("docstring") InterferenceFunctionFinite3DLattice "

Interference function of a finite 3D lattice.

C++ includes: InterferenceFunctionFinite3DLattice.h
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::InterferenceFunctionFinite3DLattice "InterferenceFunctionFinite3DLattice::InterferenceFunctionFinite3DLattice(const Lattice3D &lattice, unsigned N_1, unsigned N_2, unsigned N_3)
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::~InterferenceFunctionFinite3DLattice "InterferenceFunctionFinite3DLattice::~InterferenceFunctionFinite3DLattice() override
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::clone "InterferenceFunctionFinite3DLattice * InterferenceFunctionFinite3DLattice::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::accept "void InterferenceFunctionFinite3DLattice::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::numberUnitCells1 "unsigned InterferenceFunctionFinite3DLattice::numberUnitCells1() const
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::numberUnitCells2 "unsigned InterferenceFunctionFinite3DLattice::numberUnitCells2() const
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::numberUnitCells3 "unsigned InterferenceFunctionFinite3DLattice::numberUnitCells3() const
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::lattice "const Lattice3D & InterferenceFunctionFinite3DLattice::lattice() const
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::supportsMultilayer "bool InterferenceFunctionFinite3DLattice::supportsMultilayer() const override

Indicates if this interference function can be used with a multilayer (DWBA mode) 
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::getChildren "std::vector< const INode * > InterferenceFunctionFinite3DLattice::getChildren() const override
";


// File: classInterferenceFunctionHardDisk.xml
%feature("docstring") InterferenceFunctionHardDisk "

Percus-Yevick hard disk interference function.

M.S. Ripoll & C.F. Tejero (1995) Approximate analytical expression for the direct correlation function of hard discs within the Percus-Yevick equation, Molecular Physics, 85:2, 423-428, DOI: 10.1080/00268979500101211

C++ includes: InterferenceFunctionHardDisk.h
";

%feature("docstring")  InterferenceFunctionHardDisk::InterferenceFunctionHardDisk "InterferenceFunctionHardDisk::InterferenceFunctionHardDisk(double radius, double density, double position_var=0)
";

%feature("docstring")  InterferenceFunctionHardDisk::~InterferenceFunctionHardDisk "InterferenceFunctionHardDisk::~InterferenceFunctionHardDisk() override=default
";

%feature("docstring")  InterferenceFunctionHardDisk::clone "InterferenceFunctionHardDisk * InterferenceFunctionHardDisk::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  InterferenceFunctionHardDisk::accept "void InterferenceFunctionHardDisk::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  InterferenceFunctionHardDisk::getParticleDensity "double InterferenceFunctionHardDisk::getParticleDensity() const override

If defined by this interference function's parameters, returns the particle density (per area). Otherwise, returns zero or a user-defined value 
";

%feature("docstring")  InterferenceFunctionHardDisk::radius "double InterferenceFunctionHardDisk::radius() const
";

%feature("docstring")  InterferenceFunctionHardDisk::density "double InterferenceFunctionHardDisk::density() const
";


// File: classInterferenceFunctionNone.xml
%feature("docstring") InterferenceFunctionNone "

Default interference function (i.e. absence of any interference).

C++ includes: InterferenceFunctionNone.h
";

%feature("docstring")  InterferenceFunctionNone::InterferenceFunctionNone "InterferenceFunctionNone::InterferenceFunctionNone()
";

%feature("docstring")  InterferenceFunctionNone::clone "InterferenceFunctionNone * InterferenceFunctionNone::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  InterferenceFunctionNone::accept "void InterferenceFunctionNone::accept(INodeVisitor *visitor) const final
";


// File: classInterferenceFunctionRadialParaCrystal.xml
%feature("docstring") InterferenceFunctionRadialParaCrystal "

Interference function of radial paracrystal.

C++ includes: InterferenceFunctionRadialParaCrystal.h
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::InterferenceFunctionRadialParaCrystal "InterferenceFunctionRadialParaCrystal::InterferenceFunctionRadialParaCrystal(double peak_distance, double damping_length)

Constructor of interference function of radial paracrystal.

Parameters:
-----------

peak_distance: 
average distance to the next neighbor in nanometers

damping_length: 
the damping (coherence) length of the paracrystal in nanometers 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::clone "InterferenceFunctionRadialParaCrystal * InterferenceFunctionRadialParaCrystal::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::accept "void InterferenceFunctionRadialParaCrystal::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setKappa "void InterferenceFunctionRadialParaCrystal::setKappa(double kappa)

Sets size spacing coupling parameter of the Size Spacing Correlation Approximation. 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::kappa "double InterferenceFunctionRadialParaCrystal::kappa() const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setDomainSize "void InterferenceFunctionRadialParaCrystal::setDomainSize(double size)

Sets domain size (finite size corrections).

Parameters:
-----------

size: 
size of coherence domain along the lattice main axis in nanometers 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::domainSize "double InterferenceFunctionRadialParaCrystal::domainSize() const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::FTPDF "complex_t InterferenceFunctionRadialParaCrystal::FTPDF(double qpar) const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setProbabilityDistribution "void InterferenceFunctionRadialParaCrystal::setProbabilityDistribution(const IFTDistribution1D &pdf)

Sets one-dimensional probability distribution.

Parameters:
-----------

pdf: 
probability distribution (Fourier transform of probability density) 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::peakDistance "double InterferenceFunctionRadialParaCrystal::peakDistance() const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::dampingLength "double InterferenceFunctionRadialParaCrystal::dampingLength() const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getChildren "std::vector< const INode * > InterferenceFunctionRadialParaCrystal::getChildren() const final
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::randomSample "double InterferenceFunctionRadialParaCrystal::randomSample() const
";


// File: classInterferenceFunctionTwin.xml
%feature("docstring") InterferenceFunctionTwin "

Interference function for two particles at a mean distance and given standard deviation from each other in a given direction.

C++ includes: InterferenceFunctionTwin.h
";

%feature("docstring")  InterferenceFunctionTwin::InterferenceFunctionTwin "InterferenceFunctionTwin::InterferenceFunctionTwin(const kvector_t &direction, double mean_distance, double std_dev)
";

%feature("docstring")  InterferenceFunctionTwin::clone "InterferenceFunctionTwin * InterferenceFunctionTwin::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  InterferenceFunctionTwin::accept "void InterferenceFunctionTwin::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  InterferenceFunctionTwin::direction "kvector_t InterferenceFunctionTwin::direction() const
";

%feature("docstring")  InterferenceFunctionTwin::meanDistance "double InterferenceFunctionTwin::meanDistance() const
";

%feature("docstring")  InterferenceFunctionTwin::stdDev "double InterferenceFunctionTwin::stdDev() const
";


// File: classIParticle.xml
%feature("docstring") IParticle "

Abstract base class for  Particle,  ParticleComposition,  ParticleCoreShell,  MesoCrystal. Provides position/rotation and form factor. Abundance is inherited from  IAbstractParticle.

C++ includes: IParticle.h
";

%feature("docstring")  IParticle::~IParticle "IParticle::~IParticle()
";

%feature("docstring")  IParticle::clone "IParticle* IParticle::clone() const override=0

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  IParticle::createFormFactor "IFormFactor * IParticle::createFormFactor() const

Creates a form factor for this particle. 
";

%feature("docstring")  IParticle::createSlicedParticle "SlicedParticle IParticle::createSlicedParticle(ZLimits limits) const

Creates a sliced form factor for this particle. 
";

%feature("docstring")  IParticle::position "kvector_t IParticle::position() const

Returns particle position. 
";

%feature("docstring")  IParticle::setPosition "void IParticle::setPosition(kvector_t position)

Sets relative position of the particle's reference point in the coordinate system of parent.

Parameters:
-----------

position: 
relative position vector (components are in nanometers) 
";

%feature("docstring")  IParticle::setPosition "void IParticle::setPosition(double x, double y, double z)

Sets relative position of the particle's reference point in the coordinate system of parent.

Parameters:
-----------

x: 
x-coordinate in nanometers

y: 
y-coordinate in nanometers

z: 
z-coordinate in nanometers 
";

%feature("docstring")  IParticle::translate "void IParticle::translate(kvector_t translation) final

Translates the particle. 
";

%feature("docstring")  IParticle::rotation "const IRotation * IParticle::rotation() const

Returns rotation object. 
";

%feature("docstring")  IParticle::setRotation "void IParticle::setRotation(const IRotation &rotation)

Sets transformation. 
";

%feature("docstring")  IParticle::rotate "void IParticle::rotate(const IRotation &rotation) final

Rotates the particle. 
";

%feature("docstring")  IParticle::getChildren "std::vector< const INode * > IParticle::getChildren() const override
";

%feature("docstring")  IParticle::registerAbundance "void IParticle::registerAbundance(bool make_registered=true)
";

%feature("docstring")  IParticle::registerPosition "void IParticle::registerPosition(bool make_registered=true)

Registers the three components of its position. 
";

%feature("docstring")  IParticle::decompose "SafePointerVector< IParticle > IParticle::decompose() const

Decompose in constituent  IParticle objects. 
";

%feature("docstring")  IParticle::bottomTopZ "ParticleLimits IParticle::bottomTopZ() const

Top and bottom z-coordinate. 
";


// File: classIPeakShape.xml
%feature("docstring") IPeakShape "

Abstract base class class that defines the peak shape of a Bragg peak.

C++ includes: IPeakShape.h
";

%feature("docstring")  IPeakShape::IPeakShape "IPeakShape::IPeakShape()=default
";

%feature("docstring")  IPeakShape::IPeakShape "IPeakShape::IPeakShape(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IPeakShape::~IPeakShape "IPeakShape::~IPeakShape()
";

%feature("docstring")  IPeakShape::clone "virtual IPeakShape* IPeakShape::clone() const =0

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  IPeakShape::evaluate "virtual double IPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const =0

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";

%feature("docstring")  IPeakShape::angularDisorder "virtual bool IPeakShape::angularDisorder() const

Indicates if the peak shape encodes angular disorder, in which case all peaks in a spherical shell are needed 
";


// File: classIProfileRectangularRipple.xml
%feature("docstring") IProfileRectangularRipple "

Base class for form factors with a rectangular ripple (bar) profile in the yz plane.

C++ includes: IProfileRipple.h
";

%feature("docstring")  IProfileRectangularRipple::IProfileRectangularRipple "IProfileRectangularRipple::IProfileRectangularRipple(const NodeMeta &meta, const std::vector< double > &PValues)
";


// File: classIProfileRipple.xml
%feature("docstring") IProfileRipple "

Base class for form factors with a cosine ripple profile in the yz plane.

C++ includes: IProfileRipple.h
";

%feature("docstring")  IProfileRipple::IProfileRipple "IProfileRipple::IProfileRipple(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IProfileRipple::getLength "double IProfileRipple::getLength() const
";

%feature("docstring")  IProfileRipple::getHeight "double IProfileRipple::getHeight() const
";

%feature("docstring")  IProfileRipple::getWidth "double IProfileRipple::getWidth() const
";

%feature("docstring")  IProfileRipple::radialExtension "double IProfileRipple::radialExtension() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  IProfileRipple::evaluate_for_q "complex_t IProfileRipple::evaluate_for_q(cvector_t q) const final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classIRegistry.xml
%feature("docstring") IRegistry "

Templated object registry.

C++ includes: IRegistry.h
";

%feature("docstring")  IRegistry::getItem "const ValueType* IRegistry< ValueType >::getItem(const std::string &key) const
";

%feature("docstring")  IRegistry::keys "std::vector<std::string> IRegistry< ValueType >::keys() const
";

%feature("docstring")  IRegistry::size "size_t IRegistry< ValueType >::size() const
";


// File: classIRotation.xml
%feature("docstring") IRotation "

Abstract base class for rotations.

C++ includes: Rotations.h
";

%feature("docstring")  IRotation::IRotation "IRotation::IRotation(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IRotation::clone "virtual IRotation* IRotation::clone() const =0
";

%feature("docstring")  IRotation::createInverse "virtual IRotation* IRotation::createInverse() const =0

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  IRotation::getTransform3D "virtual Transform3D IRotation::getTransform3D() const =0

Returns transformation. 
";

%feature("docstring")  IRotation::transformed "kvector_t IRotation::transformed(const kvector_t &v) const
";

%feature("docstring")  IRotation::isIdentity "bool IRotation::isIdentity() const

Returns true if rotation matrix is identity matrix (no rotations) 
";

%feature("docstring")  IRotation::zInvariant "bool IRotation::zInvariant() const
";


// File: classISampleBuilder.xml
%feature("docstring") ISampleBuilder "

Interface to the class capable to build samples to simulate.

C++ includes: ISampleBuilder.h
";

%feature("docstring")  ISampleBuilder::ISampleBuilder "ISampleBuilder::ISampleBuilder()
";

%feature("docstring")  ISampleBuilder::~ISampleBuilder "ISampleBuilder::~ISampleBuilder()
";

%feature("docstring")  ISampleBuilder::buildSample "virtual MultiLayer* ISampleBuilder::buildSample() const =0
";

%feature("docstring")  ISampleBuilder::createSampleByIndex "virtual MultiLayer* ISampleBuilder::createSampleByIndex(size_t)
";

%feature("docstring")  ISampleBuilder::size "virtual size_t ISampleBuilder::size()
";


// File: classISampleNode.xml
%feature("docstring") ISampleNode "

Abstract base class for sample components and properties related to scattering.

C++ includes: ISampleNode.h
";

%feature("docstring")  ISampleNode::ISampleNode "ISampleNode::ISampleNode()=default
";

%feature("docstring")  ISampleNode::ISampleNode "ISampleNode::ISampleNode(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  ISampleNode::clone "ISampleNode* ISampleNode::clone() const override=0

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  ISampleNode::material "virtual const Material* ISampleNode::material() const

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  ISampleNode::containedMaterials "std::vector< const Material * > ISampleNode::containedMaterials() const

Returns set of unique materials contained in this  ISampleNode. 
";

%feature("docstring")  ISampleNode::isMagnetic "bool ISampleNode::isMagnetic() const

Returns true if there is any magnetic material in this  ISampleNode. 
";


// File: classISawtoothRipple.xml
%feature("docstring") ISawtoothRipple "

Base class for form factors with a triangular ripple profile in the yz plane.

C++ includes: IProfileRipple.h
";

%feature("docstring")  ISawtoothRipple::ISawtoothRipple "ISawtoothRipple::ISawtoothRipple(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  ISawtoothRipple::getAsymmetry "double ISawtoothRipple::getAsymmetry() const
";


// File: classISelectionRule.xml
%feature("docstring") ISelectionRule "

Abstract base class for selection rules.

C++ includes: ISelectionRule.h
";

%feature("docstring")  ISelectionRule::~ISelectionRule "virtual ISelectionRule::~ISelectionRule()
";

%feature("docstring")  ISelectionRule::clone "virtual ISelectionRule* ISelectionRule::clone() const =0
";

%feature("docstring")  ISelectionRule::coordinateSelected "virtual bool ISelectionRule::coordinateSelected(const ivector_t &coordinate) const =0
";


// File: classIShape3D.xml
%feature("docstring") IShape3D "

Abstract base class for different shapes.

In contrast to the form factors, these shapes only provide an interface for returning a set of vertices.

C++ includes: IShape3D.h
";

%feature("docstring")  IShape3D::IShape3D "IShape3D::IShape3D()
";

%feature("docstring")  IShape3D::~IShape3D "virtual IShape3D::~IShape3D()
";

%feature("docstring")  IShape3D::vertices "std::vector< kvector_t > IShape3D::vertices() const

Retrieves a list of the vertices constituting this concrete shape. 
";


// File: classIsotropicGaussPeakShape.xml
%feature("docstring") IsotropicGaussPeakShape "

Class that implements an isotropic Gaussian peak shape of a Bragg peak.

C++ includes: IPeakShape.h
";

%feature("docstring")  IsotropicGaussPeakShape::IsotropicGaussPeakShape "IsotropicGaussPeakShape::IsotropicGaussPeakShape(double max_intensity, double domainsize)
";

%feature("docstring")  IsotropicGaussPeakShape::~IsotropicGaussPeakShape "IsotropicGaussPeakShape::~IsotropicGaussPeakShape() override
";

%feature("docstring")  IsotropicGaussPeakShape::clone "IsotropicGaussPeakShape * IsotropicGaussPeakShape::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  IsotropicGaussPeakShape::accept "void IsotropicGaussPeakShape::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  IsotropicGaussPeakShape::evaluate "double IsotropicGaussPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";


// File: classIsotropicLorentzPeakShape.xml
%feature("docstring") IsotropicLorentzPeakShape "

An isotropic Lorentzian peak shape of a Bragg peak.

C++ includes: IPeakShape.h
";

%feature("docstring")  IsotropicLorentzPeakShape::IsotropicLorentzPeakShape "IsotropicLorentzPeakShape::IsotropicLorentzPeakShape(double max_intensity, double domainsize)
";

%feature("docstring")  IsotropicLorentzPeakShape::~IsotropicLorentzPeakShape "IsotropicLorentzPeakShape::~IsotropicLorentzPeakShape() override
";

%feature("docstring")  IsotropicLorentzPeakShape::clone "IsotropicLorentzPeakShape * IsotropicLorentzPeakShape::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  IsotropicLorentzPeakShape::accept "void IsotropicLorentzPeakShape::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  IsotropicLorentzPeakShape::evaluate "double IsotropicLorentzPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";


// File: classISpecularStrategy.xml
%feature("docstring") ISpecularStrategy "

Interface for the Fresnel computations, both in the scalar and magnetic case

Inherited by  SpecularScalarStrategy, SpecularMagneticOldStrategy,  SpecularMagneticStrategy, SpecularMagneticNewStrategy

C++ includes: ISpecularStrategy.h
";

%feature("docstring")  ISpecularStrategy::ISpecularStrategy "ISpecularStrategy::ISpecularStrategy()=default
";

%feature("docstring")  ISpecularStrategy::~ISpecularStrategy "virtual ISpecularStrategy::~ISpecularStrategy()=default
";

%feature("docstring")  ISpecularStrategy::ISpecularStrategy "ISpecularStrategy::ISpecularStrategy(const ISpecularStrategy &other)=delete
";

%feature("docstring")  ISpecularStrategy::Execute "virtual coeffs_t ISpecularStrategy::Execute(const std::vector< Slice > &slices, const kvector_t &k) const =0
";

%feature("docstring")  ISpecularStrategy::Execute "virtual coeffs_t ISpecularStrategy::Execute(const std::vector< Slice > &slices, const std::vector< complex_t > &kz) const =0
";


// File: classLargeCylindersInDWBABuilder.xml
%feature("docstring") LargeCylindersInDWBABuilder "

Builds sample with large cylinders for MC integration tests.

C++ includes: CylindersBuilder.h
";

%feature("docstring")  LargeCylindersInDWBABuilder::LargeCylindersInDWBABuilder "LargeCylindersInDWBABuilder::LargeCylindersInDWBABuilder()
";

%feature("docstring")  LargeCylindersInDWBABuilder::buildSample "MultiLayer * LargeCylindersInDWBABuilder::buildSample() const
";


// File: classLattice1DBuilder.xml
%feature("docstring") Lattice1DBuilder "

Builds sample: cylinders with 1DDL structure factor.

C++ includes: LatticeBuilder.h
";

%feature("docstring")  Lattice1DBuilder::buildSample "MultiLayer * Lattice1DBuilder::buildSample() const
";


// File: classLattice2D.xml
%feature("docstring") Lattice2D "

A two-dimensional Bravais lattice.

C++ includes: Lattice2D.h
";

%feature("docstring")  Lattice2D::Lattice2D "Lattice2D::Lattice2D(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  Lattice2D::Lattice2D "Lattice2D::Lattice2D(double xi)
";

%feature("docstring")  Lattice2D::clone "virtual Lattice2D* Lattice2D::clone() const =0
";

%feature("docstring")  Lattice2D::length1 "virtual double Lattice2D::length1() const =0
";

%feature("docstring")  Lattice2D::length2 "virtual double Lattice2D::length2() const =0
";

%feature("docstring")  Lattice2D::latticeAngle "virtual double Lattice2D::latticeAngle() const =0
";

%feature("docstring")  Lattice2D::unitCellArea "virtual double Lattice2D::unitCellArea() const =0
";

%feature("docstring")  Lattice2D::rotationAngle "double Lattice2D::rotationAngle() const
";

%feature("docstring")  Lattice2D::reciprocalBases "Lattice2D::ReciprocalBases Lattice2D::reciprocalBases() const
";

%feature("docstring")  Lattice2D::setRotationEnabled "void Lattice2D::setRotationEnabled(bool enabled)
";


// File: classLattice3D.xml
%feature("docstring") Lattice3D "

A Bravais lattice, characterized by three basis vectors, and optionally an  ISelectionRule.

C++ includes: Lattice3D.h
";

%feature("docstring")  Lattice3D::Lattice3D "Lattice3D::Lattice3D()=delete
";

%feature("docstring")  Lattice3D::Lattice3D "Lattice3D::Lattice3D(const kvector_t a, const kvector_t b, const kvector_t c)
";

%feature("docstring")  Lattice3D::Lattice3D "Lattice3D::Lattice3D(const Lattice3D &lattice)
";

%feature("docstring")  Lattice3D::~Lattice3D "Lattice3D::~Lattice3D() override
";

%feature("docstring")  Lattice3D::accept "void Lattice3D::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  Lattice3D::transformed "Lattice3D Lattice3D::transformed(const Transform3D &transform) const

Creates transformed lattice. 
";

%feature("docstring")  Lattice3D::initialize "void Lattice3D::initialize()

Initializes cached data. 
";

%feature("docstring")  Lattice3D::getBasisVectorA "kvector_t Lattice3D::getBasisVectorA() const

Returns basis vector a. 
";

%feature("docstring")  Lattice3D::getBasisVectorB "kvector_t Lattice3D::getBasisVectorB() const

Returns basis vector b. 
";

%feature("docstring")  Lattice3D::getBasisVectorC "kvector_t Lattice3D::getBasisVectorC() const

Returns basis vector c. 
";

%feature("docstring")  Lattice3D::getMillerDirection "kvector_t Lattice3D::getMillerDirection(double h, double k, double l) const

Returns normalized direction corresponding to the given Miller indices.

Currently unused but may be useful for checks. 
";

%feature("docstring")  Lattice3D::unitCellVolume "double Lattice3D::unitCellVolume() const

Returns the volume of the unit cell. 
";

%feature("docstring")  Lattice3D::getReciprocalLatticeBasis "void Lattice3D::getReciprocalLatticeBasis(kvector_t &ra, kvector_t &rb, kvector_t &rc) const

Returns the reciprocal basis vectors.

Currently only used in tests. 
";

%feature("docstring")  Lattice3D::getNearestReciprocalLatticeVectorCoordinates "ivector_t Lattice3D::getNearestReciprocalLatticeVectorCoordinates(const kvector_t q) const

Returns the nearest reciprocal lattice point from a given vector. 
";

%feature("docstring")  Lattice3D::reciprocalLatticeVectorsWithinRadius "std::vector< kvector_t > Lattice3D::reciprocalLatticeVectorsWithinRadius(const kvector_t q, double dq) const

Returns a list of reciprocal lattice vectors within distance dq of a vector q. 
";

%feature("docstring")  Lattice3D::setSelectionRule "void Lattice3D::setSelectionRule(const ISelectionRule &selection_rule)

Sets a selection rule for the reciprocal vectors. 
";


// File: classLayer.xml
%feature("docstring") Layer "

A layer in a  MultiLayer sample.

C++ includes: Layer.h
";

%feature("docstring")  Layer::Layer "Layer::Layer(Material material, double thickness=0)

Constructor of a layer with thickness and material

Parameters:
-----------

material: 
material the layer is made of

thickness: 
thickness of a layer in nanometers 
";

%feature("docstring")  Layer::~Layer "Layer::~Layer() override
";

%feature("docstring")  Layer::clone "Layer * Layer::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  Layer::accept "void Layer::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  Layer::setThickness "void Layer::setThickness(double thickness)

Sets layer thickness in nanometers. 
";

%feature("docstring")  Layer::thickness "double Layer::thickness() const
";

%feature("docstring")  Layer::material "const Material* Layer::material() const final

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  Layer::setMaterial "void Layer::setMaterial(Material material)
";

%feature("docstring")  Layer::addLayout "void Layer::addLayout(const ParticleLayout &decoration)
";

%feature("docstring")  Layer::numberOfLayouts "size_t Layer::numberOfLayouts() const
";

%feature("docstring")  Layer::layouts "std::vector< const ParticleLayout * > Layer::layouts() const
";

%feature("docstring")  Layer::getChildren "std::vector< const INode * > Layer::getChildren() const final
";

%feature("docstring")  Layer::registerThickness "void Layer::registerThickness(bool make_registered=true)
";

%feature("docstring")  Layer::setNumberOfSlices "void Layer::setNumberOfSlices(unsigned int n_slices)
";

%feature("docstring")  Layer::numberOfSlices "unsigned int Layer::numberOfSlices() const
";


// File: classLayerFillLimits.xml
%feature("docstring") LayerFillLimits "

Helper class for the graded layer approximation. Generates limits for each layer, indicating the region of the layer (along z) that contains particle(s)

The constructor takes the bottom layer z-coordinates as parameter. This means that for N layers, only N-1 coordinates need to be passed (the last layer is assumed to be semi-infinite).

C++ includes: LayerFillLimits.h
";

%feature("docstring")  LayerFillLimits::LayerFillLimits "LayerFillLimits::LayerFillLimits(std::vector< double > layers_bottomz)
";

%feature("docstring")  LayerFillLimits::update "void LayerFillLimits::update(ParticleLimits particle_limits, double offset=0.0)

Particle limits are given in global coordinates. 
";

%feature("docstring")  LayerFillLimits::layerZLimits "std::vector< ZLimits > LayerFillLimits::layerZLimits() const

Returns the filled region limits for each layer (in local layer coordinates) 
";


// File: classLayerInterface.xml
%feature("docstring") LayerInterface "

Interface between two layers, possibly with roughness.

C++ includes: LayerInterface.h
";

%feature("docstring")  LayerInterface::~LayerInterface "LayerInterface::~LayerInterface()
";

%feature("docstring")  LayerInterface::clone "LayerInterface * LayerInterface::clone() const

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  LayerInterface::accept "virtual void LayerInterface::accept(INodeVisitor *visitor) const
";

%feature("docstring")  LayerInterface::setRoughness "void LayerInterface::setRoughness(const LayerRoughness &roughness)

Sets roughness of the interface. 
";

%feature("docstring")  LayerInterface::getRoughness "const LayerRoughness * LayerInterface::getRoughness() const

Returns roughness of the interface. 
";

%feature("docstring")  LayerInterface::topLayer "const Layer * LayerInterface::topLayer() const
";

%feature("docstring")  LayerInterface::bottomLayer "const Layer * LayerInterface::bottomLayer() const
";

%feature("docstring")  LayerInterface::getChildren "std::vector< const INode * > LayerInterface::getChildren() const
";


// File: classLayerRoughness.xml
%feature("docstring") LayerRoughness "

A roughness of interface between two layers.

Based on the article D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995 \"X-ray reflection and transmission by rough surfaces\"

C++ includes: LayerRoughness.h
";

%feature("docstring")  LayerRoughness::LayerRoughness "LayerRoughness::LayerRoughness(double sigma, double hurstParameter, double lateralCorrLength)

Constructor of layer roughness.

Parameters:
-----------

sigma: 
rms of the roughness in nanometers

hurstParameter: 
hurst parameter which describes how jagged the interface, dimensionless [0.0, 1.0], where 0.0 gives more spikes, 1.0 more smoothness

lateralCorrLength: 
lateral correlation length of the roughness in nanometers 
";

%feature("docstring")  LayerRoughness::LayerRoughness "LayerRoughness::LayerRoughness()
";

%feature("docstring")  LayerRoughness::clone "LayerRoughness* LayerRoughness::clone() const

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  LayerRoughness::accept "virtual void LayerRoughness::accept(INodeVisitor *visitor) const
";

%feature("docstring")  LayerRoughness::getSpectralFun "double LayerRoughness::getSpectralFun(const kvector_t kvec) const

Returns power spectral density of the surface roughness.

Power spectral density of the surface roughness is a result of two-dimensional Fourier transform of the correlation function of the roughness profile.

Based on the article D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995 \"X-ray reflection and transmission by rough surfaces\" 
";

%feature("docstring")  LayerRoughness::getCorrFun "double LayerRoughness::getCorrFun(const kvector_t k) const

Correlation function of the roughness profile. 
";

%feature("docstring")  LayerRoughness::setSigma "void LayerRoughness::setSigma(double sigma)

Sets rms of roughness. 
";

%feature("docstring")  LayerRoughness::getSigma "double LayerRoughness::getSigma() const

Returns rms of roughness. 
";

%feature("docstring")  LayerRoughness::setHurstParameter "void LayerRoughness::setHurstParameter(double hurstParameter)

Sets hurst parameter. It describes how jagged the surface is. 
";

%feature("docstring")  LayerRoughness::getHurstParameter "double LayerRoughness::getHurstParameter() const

Returns hurst parameter. 
";

%feature("docstring")  LayerRoughness::setLatteralCorrLength "void LayerRoughness::setLatteralCorrLength(double lateralCorrLength)

Sets lateral correlation length. 
";

%feature("docstring")  LayerRoughness::getLatteralCorrLength "double LayerRoughness::getLatteralCorrLength() const

Returns lateral correlation length. 
";


// File: classLayersWithAbsorptionBuilder.xml
%feature("docstring") LayersWithAbsorptionBuilder "

The  LayersWithAbsorptionBuilder class generates a multilayer with 3 layers with absorption (refractive index has imaginary part).

The middle layer is populated with particles.

C++ includes: LayersWithAbsorptionBuilder.h
";

%feature("docstring")  LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder "LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder()
";

%feature("docstring")  LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder "LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder()
";

%feature("docstring")  LayersWithAbsorptionBuilder::buildSample "MultiLayer * LayersWithAbsorptionBuilder::buildSample() const
";

%feature("docstring")  LayersWithAbsorptionBuilder::createSampleByIndex "MultiLayer * LayersWithAbsorptionBuilder::createSampleByIndex(size_t index)
";

%feature("docstring")  LayersWithAbsorptionBuilder::size "size_t LayersWithAbsorptionBuilder::size()
";


// File: classLayersWithAbsorptionBySLDBuilder.xml
%feature("docstring") LayersWithAbsorptionBySLDBuilder "

The  LayersWithAbsorptionBySLDBuilder class generates a multilayer with 3 layers with absorption (refractive index has imaginary part). //! The middle layer is populated with particles. MaterialBySLD is used to generate maaterials

C++ includes: LayersWithAbsorptionBySLDBuilder.h
";

%feature("docstring")  LayersWithAbsorptionBySLDBuilder::buildSample "MultiLayer * LayersWithAbsorptionBySLDBuilder::buildSample() const
";


// File: classLinkedBoxDistributionBuilder.xml
%feature("docstring") LinkedBoxDistributionBuilder "

Distribution of boxes with main parameter and two linked parameters.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  LinkedBoxDistributionBuilder::LinkedBoxDistributionBuilder "LinkedBoxDistributionBuilder::LinkedBoxDistributionBuilder()=default
";

%feature("docstring")  LinkedBoxDistributionBuilder::buildSample "MultiLayer * LinkedBoxDistributionBuilder::buildSample() const
";


// File: classLorentzFisherPeakShape.xml
%feature("docstring") LorentzFisherPeakShape "

A peak shape that is Lorentzian in the radial direction and uses the Mises-Fisher distribution in the angular direction.

C++ includes: IPeakShape.h
";

%feature("docstring")  LorentzFisherPeakShape::LorentzFisherPeakShape "LorentzFisherPeakShape::LorentzFisherPeakShape(double max_intensity, double radial_size, double kappa)
";

%feature("docstring")  LorentzFisherPeakShape::~LorentzFisherPeakShape "LorentzFisherPeakShape::~LorentzFisherPeakShape() override
";

%feature("docstring")  LorentzFisherPeakShape::clone "LorentzFisherPeakShape * LorentzFisherPeakShape::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  LorentzFisherPeakShape::accept "void LorentzFisherPeakShape::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  LorentzFisherPeakShape::evaluate "double LorentzFisherPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";

%feature("docstring")  LorentzFisherPeakShape::angularDisorder "bool LorentzFisherPeakShape::angularDisorder() const override

Indicates if the peak shape encodes angular disorder, in which case all peaks in a spherical shell are needed 
";


// File: classMagneticCylindersBuilder.xml
%feature("docstring") MagneticCylindersBuilder "

Builds sample: cylinders with magnetic material and non-zero magnetic field.

C++ includes: MagneticParticlesBuilder.h
";

%feature("docstring")  MagneticCylindersBuilder::buildSample "MultiLayer * MagneticCylindersBuilder::buildSample() const
";


// File: classMagneticLayerBuilder.xml
%feature("docstring") MagneticLayerBuilder "

Builds sample: magnetic spheres in a magnetized layer on a non-magnetized substrate.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  MagneticLayerBuilder::buildSample "MultiLayer * MagneticLayerBuilder::buildSample() const
";


// File: classMagneticMaterialImpl.xml
%feature("docstring") MagneticMaterialImpl "

Basic implementation for magnetized material. Inherited by  RefractiveMaterialImpl and  MaterialBySLDImpl. Incorporates data and methods required to handle material magnetization.

C++ includes: MagneticMaterialImpl.h
";

%feature("docstring")  MagneticMaterialImpl::MagneticMaterialImpl "MagneticMaterialImpl::MagneticMaterialImpl(const std::string &name, kvector_t magnetization)

Constructs basic material with name and magnetization. 
";

%feature("docstring")  MagneticMaterialImpl::~MagneticMaterialImpl "virtual MagneticMaterialImpl::~MagneticMaterialImpl()=default
";

%feature("docstring")  MagneticMaterialImpl::clone "MagneticMaterialImpl* MagneticMaterialImpl::clone() const override=0

Returns pointer to a copy of material. 
";

%feature("docstring")  MagneticMaterialImpl::inverted "MagneticMaterialImpl * MagneticMaterialImpl::inverted() const final

Constructs a material with inverted magnetization. 
";

%feature("docstring")  MagneticMaterialImpl::isScalarMaterial "bool MagneticMaterialImpl::isScalarMaterial() const final

Indicates whether the interaction with the material is scalar. This means that different polarization states will be diffracted equally 
";

%feature("docstring")  MagneticMaterialImpl::isMagneticMaterial "bool MagneticMaterialImpl::isMagneticMaterial() const final
";

%feature("docstring")  MagneticMaterialImpl::magnetization "kvector_t MagneticMaterialImpl::magnetization() const final

Returns the magnetization (in A/m) 
";

%feature("docstring")  MagneticMaterialImpl::polarizedSubtrSLD "Eigen::Matrix2cd MagneticMaterialImpl::polarizedSubtrSLD(const WavevectorInfo &wavevectors) const final

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld) matrix with magnetization corrections. 
";

%feature("docstring")  MagneticMaterialImpl::rotatedMaterial "MagneticMaterialImpl * MagneticMaterialImpl::rotatedMaterial(const Transform3D &transform) const final
";


// File: classMagneticParticleZeroFieldBuilder.xml
%feature("docstring") MagneticParticleZeroFieldBuilder "

Builds sample: cylinders with magnetic material and zero magnetic field.

C++ includes: MagneticParticlesBuilder.h
";

%feature("docstring")  MagneticParticleZeroFieldBuilder::buildSample "MultiLayer * MagneticParticleZeroFieldBuilder::buildSample() const
";


// File: classMagneticRotationBuilder.xml
%feature("docstring") MagneticRotationBuilder "

Builds sample: rotated magnetic spheres in substrate layer with a unit magnetic field.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  MagneticRotationBuilder::buildSample "MultiLayer * MagneticRotationBuilder::buildSample() const
";


// File: classMagneticSpheresBuilder.xml
%feature("docstring") MagneticSpheresBuilder "

Builds sample: spheres with magnetization inside substrate.

C++ includes: MagneticParticlesBuilder.h
";

%feature("docstring")  MagneticSpheresBuilder::buildSample "MultiLayer * MagneticSpheresBuilder::buildSample() const
";


// File: classMagneticSubstrateZeroFieldBuilder.xml
%feature("docstring") MagneticSubstrateZeroFieldBuilder "

Builds sample: spheres in substrate layer with a zero magnetic field.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  MagneticSubstrateZeroFieldBuilder::buildSample "MultiLayer * MagneticSubstrateZeroFieldBuilder::buildSample() const
";


// File: classMaterial.xml
%feature("docstring") Material "

A wrapper for underlying material implementation

C++ includes: Material.h
";

%feature("docstring")  Material::Material "Material::Material(std::unique_ptr< BaseMaterialImpl > material_impl)

Creates material with particular material implementation. 
";

%feature("docstring")  Material::Material "Material::Material(const Material &material)
";

%feature("docstring")  Material::Material "Material::Material(Material &&material)=default
";

%feature("docstring")  Material::inverted "Material Material::inverted() const

Constructs a material with inverted magnetization. 
";

%feature("docstring")  Material::refractiveIndex "complex_t Material::refractiveIndex(double wavelength) const

Returns refractive index. 
";

%feature("docstring")  Material::refractiveIndex2 "complex_t Material::refractiveIndex2(double wavelength) const

Returns squared refractive index. 
";

%feature("docstring")  Material::isScalarMaterial "bool Material::isScalarMaterial() const

Indicates whether the interaction with the material is scalar. This means that different polarization states will be diffracted equally 
";

%feature("docstring")  Material::isMagneticMaterial "bool Material::isMagneticMaterial() const
";

%feature("docstring")  Material::getName "std::string Material::getName() const

Returns the name of material. 
";

%feature("docstring")  Material::typeID "MATERIAL_TYPES Material::typeID() const

Returns the type of underlying material implementation. 
";

%feature("docstring")  Material::magnetization "kvector_t Material::magnetization() const

Get the magnetization (in A/m) 
";

%feature("docstring")  Material::materialData "complex_t Material::materialData() const

Returns underlying material data. The units of returned values are the same as the ones passed to material factory functions 
";

%feature("docstring")  Material::isEmpty "bool Material::isEmpty() const

Returns true if material underlying data is nullptr. 
";

%feature("docstring")  Material::isDefaultMaterial "bool Material::isDefaultMaterial() const

Returns true if material has refractive index of (1.0, 0.0) and zero magnetization. 
";

%feature("docstring")  Material::scalarSubtrSLD "complex_t Material::scalarSubtrSLD(const WavevectorInfo &wavevectors) const

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld), sld (in  $nm^{-2}$) being the scattering length density 
";

%feature("docstring")  Material::polarizedSubtrSLD "Eigen::Matrix2cd Material::polarizedSubtrSLD(const WavevectorInfo &wavevectors) const

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld) matrix with magnetization corrections. 
";

%feature("docstring")  Material::rotatedMaterial "Material Material::rotatedMaterial(const Transform3D &transform) const
";


// File: classMaterialBySLDImpl.xml
%feature("docstring") MaterialBySLDImpl "

Material implementation based on wavelength-independent data (valid for a range of wavelengths)

C++ includes: MaterialBySLDImpl.h
";

%feature("docstring")  MaterialBySLDImpl::~MaterialBySLDImpl "virtual MaterialBySLDImpl::~MaterialBySLDImpl()=default
";

%feature("docstring")  MaterialBySLDImpl::clone "MaterialBySLDImpl * MaterialBySLDImpl::clone() const override

Returns pointer to a copy of material. 
";

%feature("docstring")  MaterialBySLDImpl::refractiveIndex "complex_t MaterialBySLDImpl::refractiveIndex(double wavelength) const override

Returns refractive index. 
";

%feature("docstring")  MaterialBySLDImpl::refractiveIndex2 "complex_t MaterialBySLDImpl::refractiveIndex2(double wavelength) const override

Returns squared refractive index. 
";

%feature("docstring")  MaterialBySLDImpl::materialData "complex_t MaterialBySLDImpl::materialData() const override

Returns underlying material data. 
";

%feature("docstring")  MaterialBySLDImpl::typeID "MATERIAL_TYPES MaterialBySLDImpl::typeID() const override

Returns type of material implementation. 
";

%feature("docstring")  MaterialBySLDImpl::scalarSubtrSLD "complex_t MaterialBySLDImpl::scalarSubtrSLD(const WavevectorInfo &wavevectors) const override

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld), sld (in  $nm^{-2}$) being the scattering length density 
";

%feature("docstring")  MaterialBySLDImpl::print "void MaterialBySLDImpl::print(std::ostream &ostr) const override

Prints object data. 
";


// File: structPlainMultiLayerBySLDBuilder_1_1MaterialData.xml


// File: classMatrixFresnelMap.xml
%feature("docstring") MatrixFresnelMap "

Implementation of  IFresnelMap for matrix valued reflection/transmission coefficients.

C++ includes: MatrixFresnelMap.h
";

%feature("docstring")  MatrixFresnelMap::MatrixFresnelMap "MatrixFresnelMap::MatrixFresnelMap(std::unique_ptr< ISpecularStrategy > strategy)
";

%feature("docstring")  MatrixFresnelMap::~MatrixFresnelMap "MatrixFresnelMap::~MatrixFresnelMap() override
";

%feature("docstring")  MatrixFresnelMap::MatrixFresnelMap "MatrixFresnelMap::MatrixFresnelMap(const MatrixFresnelMap &other)=delete
";

%feature("docstring")  MatrixFresnelMap::getOutCoefficients "std::unique_ptr< const ILayerRTCoefficients > MatrixFresnelMap::getOutCoefficients(const SimulationElement &sim_element, size_t layer_index) const final

Retrieves the amplitude coefficients for a (time-reversed) outgoing wavevector. 
";

%feature("docstring")  MatrixFresnelMap::setSlices "void MatrixFresnelMap::setSlices(const std::vector< Slice > &slices) final
";


// File: classMatrixRTCoefficients.xml
%feature("docstring") MatrixRTCoefficients "

Specular reflection and transmission coefficients in a layer in case of magnetic interactions between the scattered particle and the layer.

C++ includes: MatrixRTCoefficients.h
";

%feature("docstring")  MatrixRTCoefficients::MatrixRTCoefficients "MatrixRTCoefficients::MatrixRTCoefficients(double kz_sign, Eigen::Vector2cd eigenvalues, kvector_t b, double magnetic_SLD)
";

%feature("docstring")  MatrixRTCoefficients::MatrixRTCoefficients "MatrixRTCoefficients::MatrixRTCoefficients(const MatrixRTCoefficients &other)
";

%feature("docstring")  MatrixRTCoefficients::~MatrixRTCoefficients "MatrixRTCoefficients::~MatrixRTCoefficients() override
";

%feature("docstring")  MatrixRTCoefficients::clone "MatrixRTCoefficients * MatrixRTCoefficients::clone() const override
";

%feature("docstring")  MatrixRTCoefficients::T1plus "Eigen::Vector2cd MatrixRTCoefficients::T1plus() const override

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  MatrixRTCoefficients::R1plus "Eigen::Vector2cd MatrixRTCoefficients::R1plus() const override
";

%feature("docstring")  MatrixRTCoefficients::T2plus "Eigen::Vector2cd MatrixRTCoefficients::T2plus() const override
";

%feature("docstring")  MatrixRTCoefficients::R2plus "Eigen::Vector2cd MatrixRTCoefficients::R2plus() const override
";

%feature("docstring")  MatrixRTCoefficients::T1min "Eigen::Vector2cd MatrixRTCoefficients::T1min() const override
";

%feature("docstring")  MatrixRTCoefficients::R1min "Eigen::Vector2cd MatrixRTCoefficients::R1min() const override
";

%feature("docstring")  MatrixRTCoefficients::T2min "Eigen::Vector2cd MatrixRTCoefficients::T2min() const override
";

%feature("docstring")  MatrixRTCoefficients::R2min "Eigen::Vector2cd MatrixRTCoefficients::R2min() const override
";

%feature("docstring")  MatrixRTCoefficients::getKz "Eigen::Vector2cd MatrixRTCoefficients::getKz() const override

Returns z-part of the two wavevector eigenmodes. 
";

%feature("docstring")  MatrixRTCoefficients::magneticSLD "double MatrixRTCoefficients::magneticSLD() const
";

%feature("docstring")  MatrixRTCoefficients::computeP "Eigen::Matrix2cd MatrixRTCoefficients::computeP() const
";

%feature("docstring")  MatrixRTCoefficients::computeInverseP "Eigen::Matrix2cd MatrixRTCoefficients::computeInverseP() const
";

%feature("docstring")  MatrixRTCoefficients::computeDeltaMatrix "Eigen::Matrix2cd MatrixRTCoefficients::computeDeltaMatrix(double thickness)
";

%feature("docstring")  MatrixRTCoefficients::getReflectionMatrix "Eigen::Matrix2cd MatrixRTCoefficients::getReflectionMatrix() const override
";


// File: classMatrixRTCoefficients__v1.xml
%feature("docstring") MatrixRTCoefficients_v1 "

Specular reflection and transmission coefficients in a layer in case of 2x2 matrix interactions between the layers and the scattered particle.

C++ includes: MatrixRTCoefficients_v1.h
";

%feature("docstring")  MatrixRTCoefficients_v1::MatrixRTCoefficients_v1 "MatrixRTCoefficients_v1::MatrixRTCoefficients_v1()
";

%feature("docstring")  MatrixRTCoefficients_v1::~MatrixRTCoefficients_v1 "virtual MatrixRTCoefficients_v1::~MatrixRTCoefficients_v1()
";

%feature("docstring")  MatrixRTCoefficients_v1::clone "MatrixRTCoefficients_v1 * MatrixRTCoefficients_v1::clone() const
";

%feature("docstring")  MatrixRTCoefficients_v1::T1plus "Eigen::Vector2cd MatrixRTCoefficients_v1::T1plus() const

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  MatrixRTCoefficients_v1::R1plus "Eigen::Vector2cd MatrixRTCoefficients_v1::R1plus() const
";

%feature("docstring")  MatrixRTCoefficients_v1::T2plus "Eigen::Vector2cd MatrixRTCoefficients_v1::T2plus() const
";

%feature("docstring")  MatrixRTCoefficients_v1::R2plus "Eigen::Vector2cd MatrixRTCoefficients_v1::R2plus() const
";

%feature("docstring")  MatrixRTCoefficients_v1::T1min "Eigen::Vector2cd MatrixRTCoefficients_v1::T1min() const
";

%feature("docstring")  MatrixRTCoefficients_v1::R1min "Eigen::Vector2cd MatrixRTCoefficients_v1::R1min() const
";

%feature("docstring")  MatrixRTCoefficients_v1::T2min "Eigen::Vector2cd MatrixRTCoefficients_v1::T2min() const
";

%feature("docstring")  MatrixRTCoefficients_v1::R2min "Eigen::Vector2cd MatrixRTCoefficients_v1::R2min() const
";

%feature("docstring")  MatrixRTCoefficients_v1::getKz "virtual Eigen::Vector2cd MatrixRTCoefficients_v1::getKz() const

Returns z-part of the two wavevector eigenmodes. 
";

%feature("docstring")  MatrixRTCoefficients_v1::calculateTRMatrices "void MatrixRTCoefficients_v1::calculateTRMatrices()
";

%feature("docstring")  MatrixRTCoefficients_v1::calculateTRWithoutMagnetization "void MatrixRTCoefficients_v1::calculateTRWithoutMagnetization()
";

%feature("docstring")  MatrixRTCoefficients_v1::initializeBottomLayerPhiPsi "void MatrixRTCoefficients_v1::initializeBottomLayerPhiPsi()
";


// File: classMatrixRTCoefficients__v2.xml
%feature("docstring") MatrixRTCoefficients_v2 "

Specular reflection and transmission coefficients in a layer in case of magnetic interactions between the scattered particle and the layer.

C++ includes: MatrixRTCoefficients_v2.h
";

%feature("docstring")  MatrixRTCoefficients_v2::MatrixRTCoefficients_v2 "MatrixRTCoefficients_v2::MatrixRTCoefficients_v2(double kz_sign, Eigen::Vector2cd eigenvalues, kvector_t b)
";

%feature("docstring")  MatrixRTCoefficients_v2::MatrixRTCoefficients_v2 "MatrixRTCoefficients_v2::MatrixRTCoefficients_v2(const MatrixRTCoefficients_v2 &other)
";

%feature("docstring")  MatrixRTCoefficients_v2::~MatrixRTCoefficients_v2 "MatrixRTCoefficients_v2::~MatrixRTCoefficients_v2() override
";

%feature("docstring")  MatrixRTCoefficients_v2::clone "MatrixRTCoefficients_v2 * MatrixRTCoefficients_v2::clone() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::T1plus "Eigen::Vector2cd MatrixRTCoefficients_v2::T1plus() const override

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  MatrixRTCoefficients_v2::R1plus "Eigen::Vector2cd MatrixRTCoefficients_v2::R1plus() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::T2plus "Eigen::Vector2cd MatrixRTCoefficients_v2::T2plus() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::R2plus "Eigen::Vector2cd MatrixRTCoefficients_v2::R2plus() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::T1min "Eigen::Vector2cd MatrixRTCoefficients_v2::T1min() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::R1min "Eigen::Vector2cd MatrixRTCoefficients_v2::R1min() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::T2min "Eigen::Vector2cd MatrixRTCoefficients_v2::T2min() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::R2min "Eigen::Vector2cd MatrixRTCoefficients_v2::R2min() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::getKz "Eigen::Vector2cd MatrixRTCoefficients_v2::getKz() const override

Returns z-part of the two wavevector eigenmodes. 
";

%feature("docstring")  MatrixRTCoefficients_v2::getReflectionMatrix "Eigen::Matrix2cd MatrixRTCoefficients_v2::getReflectionMatrix() const override
";


// File: classMesoCrystal.xml
%feature("docstring") MesoCrystal "

A particle with an internal structure of smaller particles.

C++ includes: MesoCrystal.h
";

%feature("docstring")  MesoCrystal::MesoCrystal "MesoCrystal::MesoCrystal(const Crystal &particle_structure, const IFormFactor &form_factor)
";

%feature("docstring")  MesoCrystal::~MesoCrystal "MesoCrystal::~MesoCrystal()
";

%feature("docstring")  MesoCrystal::clone "MesoCrystal * MesoCrystal::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  MesoCrystal::accept "void MesoCrystal::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  MesoCrystal::createSlicedParticle "SlicedParticle MesoCrystal::createSlicedParticle(ZLimits limits) const final

Creates a sliced form factor for this particle. 
";

%feature("docstring")  MesoCrystal::getChildren "std::vector< const INode * > MesoCrystal::getChildren() const final
";


// File: classMesoCrystalBuilder.xml
%feature("docstring") MesoCrystalBuilder "

Builds sample: cylindrical mesocrystal composed of spheres in a cubic lattice.

C++ includes: MesoCrystalBuilder.h
";

%feature("docstring")  MesoCrystalBuilder::buildSample "MultiLayer * MesoCrystalBuilder::buildSample() const
";


// File: classMisesFisherGaussPeakShape.xml
%feature("docstring") MisesFisherGaussPeakShape "

A peak shape that is Gaussian in the radial direction and a convolution of a Mises-Fisher distribution with a Mises distribution on the two-sphere.

C++ includes: IPeakShape.h
";

%feature("docstring")  MisesFisherGaussPeakShape::MisesFisherGaussPeakShape "MisesFisherGaussPeakShape::MisesFisherGaussPeakShape(double max_intensity, double radial_size, kvector_t zenith, double kappa_1, double kappa_2)
";

%feature("docstring")  MisesFisherGaussPeakShape::~MisesFisherGaussPeakShape "MisesFisherGaussPeakShape::~MisesFisherGaussPeakShape() override
";

%feature("docstring")  MisesFisherGaussPeakShape::clone "MisesFisherGaussPeakShape * MisesFisherGaussPeakShape::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  MisesFisherGaussPeakShape::accept "void MisesFisherGaussPeakShape::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  MisesFisherGaussPeakShape::evaluate "double MisesFisherGaussPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";

%feature("docstring")  MisesFisherGaussPeakShape::angularDisorder "bool MisesFisherGaussPeakShape::angularDisorder() const override

Indicates if the peak shape encodes angular disorder, in which case all peaks in a spherical shell are needed 
";


// File: classMisesGaussPeakShape.xml
%feature("docstring") MisesGaussPeakShape "

A peak shape that is a convolution of a Mises-Fisher distribution with a 3d Gaussian.

C++ includes: IPeakShape.h
";

%feature("docstring")  MisesGaussPeakShape::MisesGaussPeakShape "MisesGaussPeakShape::MisesGaussPeakShape(double max_intensity, double radial_size, kvector_t zenith, double kappa)
";

%feature("docstring")  MisesGaussPeakShape::~MisesGaussPeakShape "MisesGaussPeakShape::~MisesGaussPeakShape() override
";

%feature("docstring")  MisesGaussPeakShape::clone "MisesGaussPeakShape * MisesGaussPeakShape::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  MisesGaussPeakShape::accept "void MisesGaussPeakShape::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  MisesGaussPeakShape::evaluate "double MisesGaussPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";

%feature("docstring")  MisesGaussPeakShape::angularDisorder "bool MisesGaussPeakShape::angularDisorder() const override

Indicates if the peak shape encodes angular disorder, in which case all peaks in a spherical shell are needed 
";


// File: classMultiLayer.xml
%feature("docstring") MultiLayer "

Our sample model: a stack of layers one below the other. Example of system of 4 layers (3 interfaces):

ambience layer #0 ------ interface #0 z=0.0 Fe, 20A layer #1 ------ interface #1 z=-20.0 Cr, 40A layer #2 ------ interface #2 z=-60.0 substrate layer #3

C++ includes: MultiLayer.h
";

%feature("docstring")  MultiLayer::MultiLayer "MultiLayer::MultiLayer()
";

%feature("docstring")  MultiLayer::~MultiLayer "MultiLayer::~MultiLayer() override
";

%feature("docstring")  MultiLayer::clone "MultiLayer * MultiLayer::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  MultiLayer::accept "void MultiLayer::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  MultiLayer::numberOfLayers "size_t MultiLayer::numberOfLayers() const
";

%feature("docstring")  MultiLayer::addLayer "void MultiLayer::addLayer(const Layer &layer)

Adds layer with default (zero) roughness. 
";

%feature("docstring")  MultiLayer::addLayerWithTopRoughness "void MultiLayer::addLayerWithTopRoughness(const Layer &layer, const LayerRoughness &roughness)

Adds layer with top roughness. 
";

%feature("docstring")  MultiLayer::setRoughnessModel "void MultiLayer::setRoughnessModel(RoughnessModel roughnessModel)
";

%feature("docstring")  MultiLayer::setCrossCorrLength "void MultiLayer::setCrossCorrLength(double crossCorrLength)

Sets cross correlation length of roughnesses between interfaces. 
";

%feature("docstring")  MultiLayer::setExternalField "void MultiLayer::setExternalField(kvector_t ext_field)

Sets the external field applied to the multilayer (units: A/m) 
";

%feature("docstring")  MultiLayer::layer "const Layer * MultiLayer::layer(size_t i_layer) const

Returns layer with given index. 
";

%feature("docstring")  MultiLayer::layerInterface "const LayerInterface * MultiLayer::layerInterface(size_t i_interface) const

Returns interface with given index. 
";

%feature("docstring")  MultiLayer::roughnessModel "RoughnessModel MultiLayer::roughnessModel() const
";

%feature("docstring")  MultiLayer::crossCorrLength "double MultiLayer::crossCorrLength() const

Returns cross correlation length of roughnesses between interfaces. 
";

%feature("docstring")  MultiLayer::externalField "kvector_t MultiLayer::externalField() const

Returns the external field applied to the multilayer (units: A/m) 
";

%feature("docstring")  MultiLayer::getChildren "std::vector< const INode * > MultiLayer::getChildren() const final
";


// File: classMultiLayerWithNCRoughnessBuilder.xml
%feature("docstring") MultiLayerWithNCRoughnessBuilder "

Builds sample: layers with correlated roughness.

C++ includes: MultiLayerWithNCRoughnessBuilder.h
";

%feature("docstring")  MultiLayerWithNCRoughnessBuilder::buildSample "MultiLayer * MultiLayerWithNCRoughnessBuilder::buildSample() const override
";


// File: classMultiLayerWithRoughnessBuilder.xml
%feature("docstring") MultiLayerWithRoughnessBuilder "

Builds sample: layers with correlated roughness.

C++ includes: MultiLayerWithRoughnessBuilder.h
";

%feature("docstring")  MultiLayerWithRoughnessBuilder::buildSample "MultiLayer * MultiLayerWithRoughnessBuilder::buildSample() const
";


// File: classMultipleLayoutBuilder.xml
%feature("docstring") MultipleLayoutBuilder "

Builds sample: mixture of cylinders and prisms without interference, using multiple particle layouts

C++ includes: MultipleLayoutBuilder.h
";

%feature("docstring")  MultipleLayoutBuilder::buildSample "MultiLayer * MultipleLayoutBuilder::buildSample() const
";


// File: structOneSidedLimit.xml
%feature("docstring") OneSidedLimit "

Helper class that represents a onesided limit

C++ includes: ZLimits.h
";


// File: classParticle.xml
%feature("docstring") Particle "

A particle with a form factor and refractive index.

C++ includes: Particle.h
";

%feature("docstring")  Particle::Particle "Particle::Particle()=delete
";

%feature("docstring")  Particle::~Particle "Particle::~Particle()
";

%feature("docstring")  Particle::Particle "Particle::Particle(Material material)
";

%feature("docstring")  Particle::Particle "Particle::Particle(Material material, const IFormFactor &form_factor)
";

%feature("docstring")  Particle::Particle "Particle::Particle(Material material, const IFormFactor &form_factor, const IRotation &rotation)
";

%feature("docstring")  Particle::clone "Particle * Particle::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  Particle::accept "void Particle::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  Particle::createSlicedParticle "SlicedParticle Particle::createSlicedParticle(ZLimits limits) const final

Creates a sliced form factor for this particle. 
";

%feature("docstring")  Particle::setMaterial "void Particle::setMaterial(Material material)
";

%feature("docstring")  Particle::material "const Material* Particle::material() const final

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  Particle::getChildren "std::vector< const INode * > Particle::getChildren() const final
";


// File: classParticleComposition.xml
%feature("docstring") ParticleComposition "

A composition of particles at fixed positions

C++ includes: ParticleComposition.h
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition()
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition(const IParticle &particle, std::vector< kvector_t > positions)
";

%feature("docstring")  ParticleComposition::~ParticleComposition "ParticleComposition::~ParticleComposition()
";

%feature("docstring")  ParticleComposition::clone "ParticleComposition * ParticleComposition::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  ParticleComposition::accept "void ParticleComposition::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  ParticleComposition::createFormFactor "IFormFactor * ParticleComposition::createFormFactor() const final

Creates a form factor for this particle. 
";

%feature("docstring")  ParticleComposition::addParticle "void ParticleComposition::addParticle(const IParticle &particle)
";

%feature("docstring")  ParticleComposition::addParticle "void ParticleComposition::addParticle(const IParticle &particle, kvector_t position)
";

%feature("docstring")  ParticleComposition::addParticles "void ParticleComposition::addParticles(const IParticle &particle, std::vector< kvector_t > positions)
";

%feature("docstring")  ParticleComposition::nbrParticles "size_t ParticleComposition::nbrParticles() const

Returns number of different particles. 
";

%feature("docstring")  ParticleComposition::getChildren "std::vector< const INode * > ParticleComposition::getChildren() const final
";

%feature("docstring")  ParticleComposition::decompose "SafePointerVector< IParticle > ParticleComposition::decompose() const final

Decompose in constituent  IParticle objects. 
";

%feature("docstring")  ParticleComposition::bottomTopZ "ParticleLimits ParticleComposition::bottomTopZ() const final

Top and bottom z-coordinate. 
";


// File: classParticleCompositionBuilder.xml
%feature("docstring") ParticleCompositionBuilder "

Builds sample: two layers of spheres at hex lattice.

C++ includes: ParticleCompositionBuilder.h
";

%feature("docstring")  ParticleCompositionBuilder::buildSample "MultiLayer * ParticleCompositionBuilder::buildSample() const
";


// File: classParticleCoreShell.xml
%feature("docstring") ParticleCoreShell "

A particle with a core/shell geometry.

C++ includes: ParticleCoreShell.h
";

%feature("docstring")  ParticleCoreShell::ParticleCoreShell "ParticleCoreShell::ParticleCoreShell(const Particle &shell, const Particle &core, kvector_t relative_core_position=kvector_t(0.0, 0.0, 0.0))
";

%feature("docstring")  ParticleCoreShell::~ParticleCoreShell "ParticleCoreShell::~ParticleCoreShell()
";

%feature("docstring")  ParticleCoreShell::clone "ParticleCoreShell * ParticleCoreShell::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  ParticleCoreShell::accept "void ParticleCoreShell::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  ParticleCoreShell::createSlicedParticle "SlicedParticle ParticleCoreShell::createSlicedParticle(ZLimits limits) const final

Creates a sliced form factor for this particle. 
";

%feature("docstring")  ParticleCoreShell::coreParticle "const Particle * ParticleCoreShell::coreParticle() const
";

%feature("docstring")  ParticleCoreShell::shellParticle "const Particle * ParticleCoreShell::shellParticle() const
";

%feature("docstring")  ParticleCoreShell::getChildren "std::vector< const INode * > ParticleCoreShell::getChildren() const final
";


// File: classParticleDistribution.xml
%feature("docstring") ParticleDistribution "

A particle type that is a parametric distribution of  IParticle's.

C++ includes: ParticleDistribution.h
";

%feature("docstring")  ParticleDistribution::ParticleDistribution "ParticleDistribution::ParticleDistribution(const IParticle &prototype, const ParameterDistribution &par_distr)
";

%feature("docstring")  ParticleDistribution::clone "ParticleDistribution * ParticleDistribution::clone() const final

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  ParticleDistribution::accept "void ParticleDistribution::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  ParticleDistribution::translate "void ParticleDistribution::translate(kvector_t translation) final

Translates the particle with the given vector. 
";

%feature("docstring")  ParticleDistribution::rotate "void ParticleDistribution::rotate(const IRotation &rotation) final

Applies the given rotation to the particle. 
";

%feature("docstring")  ParticleDistribution::generateParticles "SafePointerVector< IParticle > ParticleDistribution::generateParticles() const

Returns list of new particles generated according to a distribution.

Returns particle clones with parameter values drawn from distribution. 
";

%feature("docstring")  ParticleDistribution::prototype "const IParticle& ParticleDistribution::prototype() const

Returns the prototype particle, used for generating multiple ones. 
";

%feature("docstring")  ParticleDistribution::parameterDistribution "ParameterDistribution ParticleDistribution::parameterDistribution() const

Returns the distributed parameter data. 
";

%feature("docstring")  ParticleDistribution::getChildren "std::vector< const INode * > ParticleDistribution::getChildren() const final
";

%feature("docstring")  ParticleDistribution::mainUnits "std::string ParticleDistribution::mainUnits() const
";


// File: classParticleInVacuumBuilder.xml
%feature("docstring") ParticleInVacuumBuilder "

The  ParticleInVacuumBuilder class generates a multilayer with single vacuum layer populated with particles of certain types.

C++ includes: ParticleInVacuumBuilder.h
";

%feature("docstring")  ParticleInVacuumBuilder::ParticleInVacuumBuilder "ParticleInVacuumBuilder::ParticleInVacuumBuilder()
";

%feature("docstring")  ParticleInVacuumBuilder::buildSample "MultiLayer * ParticleInVacuumBuilder::buildSample() const
";

%feature("docstring")  ParticleInVacuumBuilder::createSampleByIndex "MultiLayer * ParticleInVacuumBuilder::createSampleByIndex(size_t index)
";

%feature("docstring")  ParticleInVacuumBuilder::size "size_t ParticleInVacuumBuilder::size()
";


// File: classParticleLayout.xml
%feature("docstring") ParticleLayout "

Decorator class that adds particles to  ISampleNode objects.

C++ includes: ParticleLayout.h
";

%feature("docstring")  ParticleLayout::ParticleLayout "ParticleLayout::ParticleLayout()
";

%feature("docstring")  ParticleLayout::ParticleLayout "ParticleLayout::ParticleLayout(const IAbstractParticle &particle, double abundance=-1.0)
";

%feature("docstring")  ParticleLayout::~ParticleLayout "ParticleLayout::~ParticleLayout() override
";

%feature("docstring")  ParticleLayout::clone "ParticleLayout * ParticleLayout::clone() const override

Returns a clone of this  ISampleNode object. 
";

%feature("docstring")  ParticleLayout::accept "void ParticleLayout::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  ParticleLayout::addParticle "void ParticleLayout::addParticle(const IAbstractParticle &particle, double abundance=-1.0, const kvector_t position={}, const IRotation &rotation=IdentityRotation())

Adds particle to the layout with abundance, position and the rotation defined.

Parameters:
-----------

particle: 
to be added

abundance: 
 Particle abundance

position: 
 Particle position

rotation: 
 Particle rotation 
";

%feature("docstring")  ParticleLayout::particles "SafePointerVector< IParticle > ParticleLayout::particles() const

Returns information on all particles (type and abundance) and generates new particles if an  IAbstractParticle denotes a collection 
";

%feature("docstring")  ParticleLayout::interferenceFunction "const IInterferenceFunction * ParticleLayout::interferenceFunction() const
";

%feature("docstring")  ParticleLayout::getTotalAbundance "double ParticleLayout::getTotalAbundance() const
";

%feature("docstring")  ParticleLayout::setInterferenceFunction "void ParticleLayout::setInterferenceFunction(const IInterferenceFunction &interference_function)

Adds interference functions. 
";

%feature("docstring")  ParticleLayout::totalParticleSurfaceDensity "double ParticleLayout::totalParticleSurfaceDensity() const
";

%feature("docstring")  ParticleLayout::setTotalParticleSurfaceDensity "void ParticleLayout::setTotalParticleSurfaceDensity(double particle_density)

Sets total particle surface density.

Parameters:
-----------

particle_density: 
number of particles per square nanometer 
";

%feature("docstring")  ParticleLayout::getChildren "std::vector< const INode * > ParticleLayout::getChildren() const override
";

%feature("docstring")  ParticleLayout::weight "double ParticleLayout::weight() const

Returns the relative weight of this layout. 
";

%feature("docstring")  ParticleLayout::setWeight "void ParticleLayout::setWeight(double weight)

Sets the relative weight of this layout. 
";


// File: structParticleLimits.xml
%feature("docstring") ParticleLimits "

Vertical extension of a particle, specified by bottom and top z coordinate.

C++ includes: ZLimits.h
";


// File: classPlainMultiLayerBySLDBuilder.xml
%feature("docstring") PlainMultiLayerBySLDBuilder "

Builds a sample with 10 interchanging homogeneous layers of Ti and Ni on silicone substrate. Ti is 70 angstroms thick, Ni is 30 angstroms thick.

C++ includes: PlainMultiLayerBySLDBuilder.h
";

%feature("docstring")  PlainMultiLayerBySLDBuilder::PlainMultiLayerBySLDBuilder "PlainMultiLayerBySLDBuilder::PlainMultiLayerBySLDBuilder(int n_layers=10)
";

%feature("docstring")  PlainMultiLayerBySLDBuilder::buildSample "MultiLayer * PlainMultiLayerBySLDBuilder::buildSample() const override
";


// File: classPolygonalTopology.xml
%feature("docstring") PolygonalTopology "

For internal use in  PolyhedralFace.

C++ includes: PolyhedralTopology.h
";


// File: classPolyhedralEdge.xml
%feature("docstring") PolyhedralEdge "

One edge of a polygon, for form factor computation.

C++ includes: PolyhedralComponents.h
";

%feature("docstring")  PolyhedralEdge::PolyhedralEdge "PolyhedralEdge::PolyhedralEdge(const kvector_t _Vlow, const kvector_t _Vhig)
";

%feature("docstring")  PolyhedralEdge::E "kvector_t PolyhedralEdge::E() const
";

%feature("docstring")  PolyhedralEdge::R "kvector_t PolyhedralEdge::R() const
";

%feature("docstring")  PolyhedralEdge::qE "complex_t PolyhedralEdge::qE(cvector_t q) const
";

%feature("docstring")  PolyhedralEdge::qR "complex_t PolyhedralEdge::qR(cvector_t q) const
";

%feature("docstring")  PolyhedralEdge::contrib "complex_t PolyhedralEdge::contrib(int m, cvector_t qpa, complex_t qrperp) const

Returns sum_l=0^M/2 u^2l v^(M-2l) / (2l+1)!(M-2l)! - vperp^M/M! 
";


// File: classPolyhedralFace.xml
%feature("docstring") PolyhedralFace "

A polygon, for form factor computation.

C++ includes: PolyhedralComponents.h
";

%feature("docstring")  PolyhedralFace::PolyhedralFace "PolyhedralFace::PolyhedralFace(const std::vector< kvector_t > &_V=std::vector< kvector_t >(), bool _sym_S2=false)

Sets internal variables for given vertex chain.

Parameters:
-----------

V: 
oriented vertex list

_sym_S2: 
true if face has a perpedicular two-fold symmetry axis 
";

%feature("docstring")  PolyhedralFace::area "double PolyhedralFace::area() const
";

%feature("docstring")  PolyhedralFace::pyramidalVolume "double PolyhedralFace::pyramidalVolume() const
";

%feature("docstring")  PolyhedralFace::radius3d "double PolyhedralFace::radius3d() const
";

%feature("docstring")  PolyhedralFace::normalProjectionConj "complex_t PolyhedralFace::normalProjectionConj(cvector_t q) const

Returns conj(q)*normal [BasicVector3D::dot is antilinear in 'this' argument]. 
";

%feature("docstring")  PolyhedralFace::ff_n "complex_t PolyhedralFace::ff_n(int m, cvector_t q) const

Returns contribution qn*f_n [of order q^(n+1)] from this face to the polyhedral form factor. 
";

%feature("docstring")  PolyhedralFace::ff "complex_t PolyhedralFace::ff(cvector_t q, bool sym_Ci) const

Returns the contribution ff(q) of this face to the polyhedral form factor. 
";

%feature("docstring")  PolyhedralFace::ff_2D "complex_t PolyhedralFace::ff_2D(cvector_t qpa) const

Returns the two-dimensional form factor of this face, for use in a prism. 
";

%feature("docstring")  PolyhedralFace::ff_2D_direct "complex_t PolyhedralFace::ff_2D_direct(cvector_t qpa) const

Two-dimensional form factor, for use in prism, from sum over edge form factors. 
";

%feature("docstring")  PolyhedralFace::ff_2D_expanded "complex_t PolyhedralFace::ff_2D_expanded(cvector_t qpa) const

Two-dimensional form factor, for use in prism, from power series. 
";

%feature("docstring")  PolyhedralFace::assert_Ci "void PolyhedralFace::assert_Ci(const PolyhedralFace &other) const

Throws if deviation from inversion symmetry is detected. Does not check vertices. 
";


// File: classPolyhedralTopology.xml
%feature("docstring") PolyhedralTopology "

For internal use in  IFormFactorPolyhedron.

C++ includes: PolyhedralTopology.h
";


// File: classPolyhedron.xml
%feature("docstring") Polyhedron "

A polyhedron, implementation class for use in  IFormFactorPolyhedron.

C++ includes: Polyhedron.h
";

%feature("docstring")  Polyhedron::Polyhedron "Polyhedron::Polyhedron()=delete
";

%feature("docstring")  Polyhedron::Polyhedron "Polyhedron::Polyhedron(const Polyhedron &)=delete
";

%feature("docstring")  Polyhedron::Polyhedron "Polyhedron::Polyhedron(const PolyhedralTopology &topology, double z_bottom, const std::vector< kvector_t > &vertices)
";

%feature("docstring")  Polyhedron::~Polyhedron "Polyhedron::~Polyhedron()
";

%feature("docstring")  Polyhedron::assert_platonic "void Polyhedron::assert_platonic() const
";

%feature("docstring")  Polyhedron::volume "double Polyhedron::volume() const
";

%feature("docstring")  Polyhedron::radius "double Polyhedron::radius() const
";

%feature("docstring")  Polyhedron::vertices "const std::vector< kvector_t > & Polyhedron::vertices()
";

%feature("docstring")  Polyhedron::evaluate_for_q "complex_t Polyhedron::evaluate_for_q(const cvector_t &q) const

needed for topZ, bottomZ computation

Returns the form factor F(q) of this polyhedron, respecting the offset z_bottom. 
";

%feature("docstring")  Polyhedron::evaluate_centered "complex_t Polyhedron::evaluate_centered(const cvector_t &q) const

Returns the form factor F(q) of this polyhedron, with origin at z=0. 
";


// File: classPrism.xml
%feature("docstring") Prism "";

%feature("docstring")  Prism::Prism "Prism::Prism()=delete
";

%feature("docstring")  Prism::Prism "Prism::Prism(const Prism &)=delete
";

%feature("docstring")  Prism::Prism "Prism::Prism(bool symmetry_Ci, double height, const std::vector< kvector_t > &vertices)

The mathematics implemented here is described in full detail in a paper by Joachim Wuttke, entitled \"Form factor (Fourier shape transform) of polygon and polyhedron.\" 
";

%feature("docstring")  Prism::area "double Prism::area() const
";

%feature("docstring")  Prism::vertices "const std::vector< kvector_t > & Prism::vertices()
";

%feature("docstring")  Prism::evaluate_for_q "complex_t Prism::evaluate_for_q(const cvector_t &q) const

needed for topZ, bottomZ computation 
";


// File: classProcessedLayout.xml
%feature("docstring") ProcessedLayout "

Data structure that contains preprocessed data for a single layout.

If particles in the layout crossed the limits of the layer slices, these particles will be sliced themselves.

C++ includes: ProcessedLayout.h
";

%feature("docstring")  ProcessedLayout::ProcessedLayout "ProcessedLayout::ProcessedLayout(const ParticleLayout &layout, const std::vector< Slice > &slices, double z_ref, const IFresnelMap *p_fresnel_map, bool polarized)
";

%feature("docstring")  ProcessedLayout::ProcessedLayout "ProcessedLayout::ProcessedLayout(ProcessedLayout &&other)
";

%feature("docstring")  ProcessedLayout::~ProcessedLayout "ProcessedLayout::~ProcessedLayout()
";

%feature("docstring")  ProcessedLayout::numberOfSlices "size_t ProcessedLayout::numberOfSlices() const
";

%feature("docstring")  ProcessedLayout::surfaceDensity "double ProcessedLayout::surfaceDensity() const
";

%feature("docstring")  ProcessedLayout::formFactorList "const std::vector< FormFactorCoherentSum > & ProcessedLayout::formFactorList() const
";

%feature("docstring")  ProcessedLayout::interferenceFunction "const IInterferenceFunction * ProcessedLayout::interferenceFunction() const
";

%feature("docstring")  ProcessedLayout::regionMap "std::map< size_t, std::vector< HomogeneousRegion > > ProcessedLayout::regionMap() const
";


// File: classProcessedSample.xml
%feature("docstring") ProcessedSample "

Data structure that contains all the necessary data for scattering calculations.

If the usage of average materials is requested, layers and particles are sliced into multiple slices and the average material is calculated for each slice.

C++ includes: ProcessedSample.h
";

%feature("docstring")  ProcessedSample::ProcessedSample "ProcessedSample::ProcessedSample(const MultiLayer &sample, const SimulationOptions &options)
";

%feature("docstring")  ProcessedSample::~ProcessedSample "ProcessedSample::~ProcessedSample()
";

%feature("docstring")  ProcessedSample::numberOfSlices "size_t ProcessedSample::numberOfSlices() const
";

%feature("docstring")  ProcessedSample::slices "const std::vector< Slice > & ProcessedSample::slices() const
";

%feature("docstring")  ProcessedSample::averageSlices "const std::vector< Slice > & ProcessedSample::averageSlices() const
";

%feature("docstring")  ProcessedSample::layouts "const std::vector< ProcessedLayout > & ProcessedSample::layouts() const
";

%feature("docstring")  ProcessedSample::fresnelMap "const IFresnelMap * ProcessedSample::fresnelMap() const
";

%feature("docstring")  ProcessedSample::crossCorrelationLength "double ProcessedSample::crossCorrelationLength() const
";

%feature("docstring")  ProcessedSample::externalField "kvector_t ProcessedSample::externalField() const
";

%feature("docstring")  ProcessedSample::bottomRoughness "const LayerRoughness * ProcessedSample::bottomRoughness(size_t i) const
";

%feature("docstring")  ProcessedSample::sliceTopZ "double ProcessedSample::sliceTopZ(size_t i) const
";

%feature("docstring")  ProcessedSample::sliceBottomZ "double ProcessedSample::sliceBottomZ(size_t i) const
";

%feature("docstring")  ProcessedSample::containsMagneticMaterial "bool ProcessedSample::containsMagneticMaterial() const
";

%feature("docstring")  ProcessedSample::hasRoughness "bool ProcessedSample::hasRoughness() const
";

%feature("docstring")  ProcessedSample::crossCorrSpectralFun "double ProcessedSample::crossCorrSpectralFun(const kvector_t kvec, size_t j, size_t k) const

Fourier transform of the correlation function of roughnesses between the interfaces 
";


// File: classProfileHelper.xml
%feature("docstring") ProfileHelper "

Object that can generate the material profile of a sample as a function of depth.

The generated profile contains the complex SLD for SLD materials and the parameters delta and beta for refractive index materials

C++ includes: ProfileHelper.h
";

%feature("docstring")  ProfileHelper::ProfileHelper "ProfileHelper::ProfileHelper(const ProcessedSample &sample)
";

%feature("docstring")  ProfileHelper::~ProfileHelper "ProfileHelper::~ProfileHelper()
";

%feature("docstring")  ProfileHelper::calculateProfile "std::vector< complex_t > ProfileHelper::calculateProfile(const std::vector< double > &z_values) const
";

%feature("docstring")  ProfileHelper::defaultLimits "std::pair< double, double > ProfileHelper::defaultLimits() const
";


// File: classRadialParaCrystalBuilder.xml
%feature("docstring") RadialParaCrystalBuilder "

Builds sample: cylinders with 1DDL structure factor (IsGISAXS example #4).

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RadialParaCrystalBuilder::buildSample "MultiLayer * RadialParaCrystalBuilder::buildSample() const
";


// File: structLattice2D_1_1ReciprocalBases.xml
%feature("docstring") Lattice2D::ReciprocalBases "";


// File: classRectParaCrystalBuilder.xml
%feature("docstring") RectParaCrystalBuilder "

Builds sample: 2D paracrystal lattice (IsGISAXS example #8).

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RectParaCrystalBuilder::buildSample "MultiLayer * RectParaCrystalBuilder::buildSample() const
";


// File: classRefractiveMaterialImpl.xml
%feature("docstring") RefractiveMaterialImpl "

Material implementation based on refractive coefficiencts (valid for one wavelength value only)

C++ includes: RefractiveMaterialImpl.h
";

%feature("docstring")  RefractiveMaterialImpl::~RefractiveMaterialImpl "virtual RefractiveMaterialImpl::~RefractiveMaterialImpl()=default
";

%feature("docstring")  RefractiveMaterialImpl::clone "RefractiveMaterialImpl * RefractiveMaterialImpl::clone() const override

Returns pointer to a copy of material. 
";

%feature("docstring")  RefractiveMaterialImpl::refractiveIndex "complex_t RefractiveMaterialImpl::refractiveIndex(double wavelength) const override

Returns refractive index For this particular implementation returned value does not depend on passed wavelength 
";

%feature("docstring")  RefractiveMaterialImpl::refractiveIndex2 "complex_t RefractiveMaterialImpl::refractiveIndex2(double wavelength) const override

Returns squared refractive index. For this particular implementation returned value does not depend on passed wavelength. 
";

%feature("docstring")  RefractiveMaterialImpl::materialData "complex_t RefractiveMaterialImpl::materialData() const override

Returns underlying material data. 
";

%feature("docstring")  RefractiveMaterialImpl::typeID "MATERIAL_TYPES RefractiveMaterialImpl::typeID() const override

Returns type of material implementation. 
";

%feature("docstring")  RefractiveMaterialImpl::scalarSubtrSLD "complex_t RefractiveMaterialImpl::scalarSubtrSLD(const WavevectorInfo &wavevectors) const override

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld), sld (in  $nm^{-2}$) being the scattering length density. If the wavelength associated with passed wavevector is different from the one associated with refractive coefficients used during the object construction, provided result is inconsistent. 
";

%feature("docstring")  RefractiveMaterialImpl::print "void RefractiveMaterialImpl::print(std::ostream &ostr) const override

Prints object data. 
";


// File: classResonatorBuilder.xml
%feature("docstring") ResonatorBuilder "

Builds sample: multilayer with Ti/Pt layers sequence.

C++ includes: ResonatorBuilder.h
";

%feature("docstring")  ResonatorBuilder::ResonatorBuilder "ResonatorBuilder::ResonatorBuilder()
";

%feature("docstring")  ResonatorBuilder::buildSample "MultiLayer * ResonatorBuilder::buildSample() const
";


// File: classRippleCosine.xml
%feature("docstring") RippleCosine "";

%feature("docstring")  RippleCosine::RippleCosine "RippleCosine::RippleCosine(double length, double width, double height)
";

%feature("docstring")  RippleCosine::~RippleCosine "RippleCosine::~RippleCosine()
";


// File: classRippleSawtooth.xml
%feature("docstring") RippleSawtooth "";

%feature("docstring")  RippleSawtooth::RippleSawtooth "RippleSawtooth::RippleSawtooth(double length, double width, double height, double asymmetry)
";

%feature("docstring")  RippleSawtooth::~RippleSawtooth "RippleSawtooth::~RippleSawtooth()
";


// File: classRotatedCylindersBuilder.xml
%feature("docstring") RotatedCylindersBuilder "

Builds sample: cylinder form factor in DWBA (IsGISAXS example #3, part I).

C++ includes: CylindersBuilder.h
";

%feature("docstring")  RotatedCylindersBuilder::RotatedCylindersBuilder "RotatedCylindersBuilder::RotatedCylindersBuilder()
";

%feature("docstring")  RotatedCylindersBuilder::buildSample "MultiLayer * RotatedCylindersBuilder::buildSample() const
";


// File: classRotatedPyramidsBuilder.xml
%feature("docstring") RotatedPyramidsBuilder "

Builds sample: Pyramids, rotated pyramids on top of substrate (IsGISAXS example #9)

C++ includes: RotatedPyramidsBuilder.h
";

%feature("docstring")  RotatedPyramidsBuilder::buildSample "MultiLayer * RotatedPyramidsBuilder::buildSample() const
";


// File: classRotatedPyramidsDistributionBuilder.xml
%feature("docstring") RotatedPyramidsDistributionBuilder "

Rotated Pyramids with the distribution applied to the rotation angle.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  RotatedPyramidsDistributionBuilder::RotatedPyramidsDistributionBuilder "RotatedPyramidsDistributionBuilder::RotatedPyramidsDistributionBuilder()
";

%feature("docstring")  RotatedPyramidsDistributionBuilder::buildSample "MultiLayer * RotatedPyramidsDistributionBuilder::buildSample() const
";


// File: classRotatedSquareLattice2DBuilder.xml
%feature("docstring") RotatedSquareLattice2DBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  RotatedSquareLattice2DBuilder::buildSample "MultiLayer * RotatedSquareLattice2DBuilder::buildSample() const
";


// File: classRotationEuler.xml
%feature("docstring") RotationEuler "

A sequence of rotations about the z-x'-z'' axes.

C++ includes: Rotations.h
";

%feature("docstring")  RotationEuler::RotationEuler "RotationEuler::RotationEuler(const std::vector< double > P)
";

%feature("docstring")  RotationEuler::RotationEuler "RotationEuler::RotationEuler(double alpha, double beta, double gamma)
";

%feature("docstring")  RotationEuler::clone "RotationEuler* RotationEuler::clone() const
";

%feature("docstring")  RotationEuler::createInverse "IRotation * RotationEuler::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationEuler::accept "void RotationEuler::accept(INodeVisitor *visitor) const
";

%feature("docstring")  RotationEuler::getAlpha "double RotationEuler::getAlpha() const
";

%feature("docstring")  RotationEuler::getBeta "double RotationEuler::getBeta() const
";

%feature("docstring")  RotationEuler::getGamma "double RotationEuler::getGamma() const
";

%feature("docstring")  RotationEuler::getTransform3D "Transform3D RotationEuler::getTransform3D() const

Returns transformation. 
";


// File: classRotationX.xml
%feature("docstring") RotationX "

A rotation about the x axis.

C++ includes: Rotations.h
";

%feature("docstring")  RotationX::RotationX "RotationX::RotationX(const std::vector< double > P)

Constructor of rotation around x-axis. 
";

%feature("docstring")  RotationX::RotationX "RotationX::RotationX(double angle)
";

%feature("docstring")  RotationX::clone "RotationX* RotationX::clone() const
";

%feature("docstring")  RotationX::createInverse "RotationX* RotationX::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationX::accept "void RotationX::accept(INodeVisitor *visitor) const
";

%feature("docstring")  RotationX::getAngle "double RotationX::getAngle() const
";

%feature("docstring")  RotationX::getTransform3D "Transform3D RotationX::getTransform3D() const

Returns transformation. 
";


// File: classRotationY.xml
%feature("docstring") RotationY "

A rotation about the y axis.

C++ includes: Rotations.h
";

%feature("docstring")  RotationY::RotationY "RotationY::RotationY(const std::vector< double > P)

Constructor of rotation around y-axis. 
";

%feature("docstring")  RotationY::RotationY "RotationY::RotationY(double angle)
";

%feature("docstring")  RotationY::clone "RotationY* RotationY::clone() const
";

%feature("docstring")  RotationY::createInverse "RotationY* RotationY::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationY::accept "void RotationY::accept(INodeVisitor *visitor) const
";

%feature("docstring")  RotationY::getAngle "double RotationY::getAngle() const
";

%feature("docstring")  RotationY::getTransform3D "Transform3D RotationY::getTransform3D() const

Returns transformation. 
";


// File: classRotationZ.xml
%feature("docstring") RotationZ "

A rotation about the z axis.

C++ includes: Rotations.h
";

%feature("docstring")  RotationZ::RotationZ "RotationZ::RotationZ(const std::vector< double > P)

Constructor of rotation around z-axis. 
";

%feature("docstring")  RotationZ::RotationZ "RotationZ::RotationZ(double angle)
";

%feature("docstring")  RotationZ::clone "RotationZ* RotationZ::clone() const
";

%feature("docstring")  RotationZ::createInverse "RotationZ* RotationZ::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationZ::accept "void RotationZ::accept(INodeVisitor *visitor) const
";

%feature("docstring")  RotationZ::getAngle "double RotationZ::getAngle() const
";

%feature("docstring")  RotationZ::getTransform3D "Transform3D RotationZ::getTransform3D() const

Returns transformation. 
";


// File: structRoughnessModelWrap.xml
%feature("docstring") RoughnessModelWrap "";


// File: classSampleBuilderFactory.xml
%feature("docstring") SampleBuilderFactory "

Factory to create standard pre-defined samples

C++ includes: SampleBuilderFactory.h
";

%feature("docstring")  SampleBuilderFactory::SampleBuilderFactory "SampleBuilderFactory::SampleBuilderFactory()
";

%feature("docstring")  SampleBuilderFactory::createSampleByName "MultiLayer * SampleBuilderFactory::createSampleByName(const std::string &name)

Retrieves a SampleBuilder from the registry, does the build, and returns the result. 
";


// File: classSampleBuilderNode.xml
%feature("docstring") SampleBuilderNode "

Wraps an  ISampleBuilder, and puts it in an INode tree. Used by  SampleProvider.

C++ includes: SampleBuilderNode.h
";

%feature("docstring")  SampleBuilderNode::SampleBuilderNode "SampleBuilderNode::SampleBuilderNode()
";

%feature("docstring")  SampleBuilderNode::SampleBuilderNode "SampleBuilderNode::SampleBuilderNode(const SampleBuilderNode &other)
";

%feature("docstring")  SampleBuilderNode::setSBN "void SampleBuilderNode::setSBN(const std::shared_ptr< ISampleBuilder > &sample_builder)

Sets sample builder and borrows its parameters. 
";

%feature("docstring")  SampleBuilderNode::reset "void SampleBuilderNode::reset()

Resets to initial state by removing builder and its borrowed parameters. 
";

%feature("docstring")  SampleBuilderNode::accept "void SampleBuilderNode::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  SampleBuilderNode::createMultiLayer "std::unique_ptr< MultiLayer > SampleBuilderNode::createMultiLayer()

Creates a multilayer using sample builder. 
";

%feature("docstring")  SampleBuilderNode::builder "std::shared_ptr< ISampleBuilder > SampleBuilderNode::builder() const

Returns current sample builder. 
";


// File: classSampleProvider.xml
%feature("docstring") SampleProvider "

Holds either a Sample, or a  SampleBuilderNode (which holds an  ISampleBuilder). Used in ISimulation, which holds a  SampleProvider member.

C++ includes: SampleProvider.h
";

%feature("docstring")  SampleProvider::SampleProvider "SampleProvider::SampleProvider()
";

%feature("docstring")  SampleProvider::SampleProvider "SampleProvider::SampleProvider(const SampleProvider &other)
";

%feature("docstring")  SampleProvider::~SampleProvider "SampleProvider::~SampleProvider()
";

%feature("docstring")  SampleProvider::setSample "void SampleProvider::setSample(const MultiLayer &multilayer)
";

%feature("docstring")  SampleProvider::setBuilder "void SampleProvider::setBuilder(const std::shared_ptr< ISampleBuilder > &sample_builder)
";

%feature("docstring")  SampleProvider::sample "const MultiLayer * SampleProvider::sample() const

Returns current sample. 
";

%feature("docstring")  SampleProvider::updateSample "void SampleProvider::updateSample()

Generates new sample if sample builder defined. 
";

%feature("docstring")  SampleProvider::getChildren "std::vector< const INode * > SampleProvider::getChildren() const override
";

%feature("docstring")  SampleProvider::accept "void SampleProvider::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  SampleProvider::setParent "void SampleProvider::setParent(const INode *newParent) override
";


// File: classScalarFresnelMap.xml
%feature("docstring") ScalarFresnelMap "

Implementation of  IFresnelMap for scalar valued reflection/transmission coefficients.

C++ includes: ScalarFresnelMap.h
";

%feature("docstring")  ScalarFresnelMap::ScalarFresnelMap "ScalarFresnelMap::ScalarFresnelMap(std::unique_ptr< ISpecularStrategy > strategy)
";

%feature("docstring")  ScalarFresnelMap::~ScalarFresnelMap "ScalarFresnelMap::~ScalarFresnelMap() override
";

%feature("docstring")  ScalarFresnelMap::ScalarFresnelMap "ScalarFresnelMap::ScalarFresnelMap(const ScalarFresnelMap &other)=delete
";

%feature("docstring")  ScalarFresnelMap::getOutCoefficients "std::unique_ptr< const ILayerRTCoefficients > ScalarFresnelMap::getOutCoefficients(const SimulationElement &sim_element, size_t layer_index) const override

Retrieves the amplitude coefficients for a (time-reversed) outgoing wavevector. 
";


// File: classScalarRTCoefficients.xml
%feature("docstring") ScalarRTCoefficients "

Specular reflection and transmission coefficients in a layer in case of scalar interactions between the layers and the scattered particle.

C++ includes: ScalarRTCoefficients.h
";

%feature("docstring")  ScalarRTCoefficients::ScalarRTCoefficients "ScalarRTCoefficients::ScalarRTCoefficients()
";

%feature("docstring")  ScalarRTCoefficients::~ScalarRTCoefficients "virtual ScalarRTCoefficients::~ScalarRTCoefficients()
";

%feature("docstring")  ScalarRTCoefficients::clone "ScalarRTCoefficients * ScalarRTCoefficients::clone() const
";

%feature("docstring")  ScalarRTCoefficients::T1plus "Eigen::Vector2cd ScalarRTCoefficients::T1plus() const

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  ScalarRTCoefficients::R1plus "Eigen::Vector2cd ScalarRTCoefficients::R1plus() const
";

%feature("docstring")  ScalarRTCoefficients::T2plus "Eigen::Vector2cd ScalarRTCoefficients::T2plus() const
";

%feature("docstring")  ScalarRTCoefficients::R2plus "Eigen::Vector2cd ScalarRTCoefficients::R2plus() const
";

%feature("docstring")  ScalarRTCoefficients::T1min "Eigen::Vector2cd ScalarRTCoefficients::T1min() const
";

%feature("docstring")  ScalarRTCoefficients::R1min "Eigen::Vector2cd ScalarRTCoefficients::R1min() const
";

%feature("docstring")  ScalarRTCoefficients::T2min "Eigen::Vector2cd ScalarRTCoefficients::T2min() const
";

%feature("docstring")  ScalarRTCoefficients::R2min "Eigen::Vector2cd ScalarRTCoefficients::R2min() const
";

%feature("docstring")  ScalarRTCoefficients::getKz "Eigen::Vector2cd ScalarRTCoefficients::getKz() const

Returns z-part of the two wavevector eigenmodes. 
";

%feature("docstring")  ScalarRTCoefficients::getScalarT "complex_t ScalarRTCoefficients::getScalarT() const

Scalar value getters; these throw errors by default as they should only be used when the derived object is really scalar 
";

%feature("docstring")  ScalarRTCoefficients::getScalarR "complex_t ScalarRTCoefficients::getScalarR() const
";

%feature("docstring")  ScalarRTCoefficients::getScalarKz "virtual complex_t ScalarRTCoefficients::getScalarKz() const
";


// File: classSimpleMagneticLayerBuilder.xml
%feature("docstring") SimpleMagneticLayerBuilder "

Builds sample: ambient and one magnetized layer on a non-magnetized substrate.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  SimpleMagneticLayerBuilder::buildSample "MultiLayer * SimpleMagneticLayerBuilder::buildSample() const
";


// File: classSimpleMagneticRotationBuilder.xml
%feature("docstring") SimpleMagneticRotationBuilder "

Builds sample: magnetic layer on a magnetic substrate with the fields rotated by 90°

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  SimpleMagneticRotationBuilder::buildSample "MultiLayer * SimpleMagneticRotationBuilder::buildSample() const override
";

%feature("docstring")  SimpleMagneticRotationBuilder::createSampleByIndex "MultiLayer * SimpleMagneticRotationBuilder::createSampleByIndex(size_t index) override
";

%feature("docstring")  SimpleMagneticRotationBuilder::size "size_t SimpleMagneticRotationBuilder::size() override
";


// File: classSimpleSelectionRule.xml
%feature("docstring") SimpleSelectionRule "

Selection rule (v*q)modulus!=0, defined by vector v(a,b,c) and modulus.

C++ includes: ISelectionRule.h
";

%feature("docstring")  SimpleSelectionRule::SimpleSelectionRule "SimpleSelectionRule::SimpleSelectionRule(int a, int b, int c, int modulus)
";

%feature("docstring")  SimpleSelectionRule::~SimpleSelectionRule "virtual SimpleSelectionRule::~SimpleSelectionRule()
";

%feature("docstring")  SimpleSelectionRule::clone "SimpleSelectionRule * SimpleSelectionRule::clone() const
";

%feature("docstring")  SimpleSelectionRule::coordinateSelected "bool SimpleSelectionRule::coordinateSelected(const ivector_t &coordinate) const
";


// File: classSimulationOptions.xml
%feature("docstring") SimulationOptions "

Collect the different options for simulation.

SimulationOptions

C++ includes: SimulationOptions.h
";

%feature("docstring")  SimulationOptions::SimulationOptions "SimulationOptions::SimulationOptions()
";

%feature("docstring")  SimulationOptions::isIntegrate "bool SimulationOptions::isIntegrate() const
";

%feature("docstring")  SimulationOptions::getMcPoints "size_t SimulationOptions::getMcPoints() const
";

%feature("docstring")  SimulationOptions::setMonteCarloIntegration "void SimulationOptions::setMonteCarloIntegration(bool flag=true, size_t mc_points=50)

Enables/disables MonetCarlo integration.

Parameters:
-----------

flag: 
If true, MonteCarlo integration will be used, otherwise analytical calculations

mc_points: 
Number of points for MonteCarlo integrator 
";

%feature("docstring")  SimulationOptions::setNumberOfThreads "void SimulationOptions::setNumberOfThreads(int nthreads)

Sets number of threads to use during the simulation (0 - take the default value from the hardware) 
";

%feature("docstring")  SimulationOptions::getNumberOfThreads "unsigned SimulationOptions::getNumberOfThreads() const
";

%feature("docstring")  SimulationOptions::setNumberOfBatches "void SimulationOptions::setNumberOfBatches(int nbatches)

Sets number of batches to split. 
";

%feature("docstring")  SimulationOptions::getNumberOfBatches "unsigned SimulationOptions::getNumberOfBatches() const
";

%feature("docstring")  SimulationOptions::getCurrentBatch "unsigned SimulationOptions::getCurrentBatch() const
";

%feature("docstring")  SimulationOptions::setThreadInfo "void SimulationOptions::setThreadInfo(const ThreadInfo &thread_info)

Sets the batch and thread information to be used. 
";

%feature("docstring")  SimulationOptions::getHardwareConcurrency "unsigned SimulationOptions::getHardwareConcurrency() const
";

%feature("docstring")  SimulationOptions::setIncludeSpecular "void SimulationOptions::setIncludeSpecular(bool include_specular)
";

%feature("docstring")  SimulationOptions::includeSpecular "bool SimulationOptions::includeSpecular() const
";

%feature("docstring")  SimulationOptions::setUseAvgMaterials "void SimulationOptions::setUseAvgMaterials(bool use_avg_materials)
";

%feature("docstring")  SimulationOptions::useAvgMaterials "bool SimulationOptions::useAvgMaterials() const
";


// File: classSizeDistributionDAModelBuilder.xml
%feature("docstring") SizeDistributionDAModelBuilder "

Creates the sample demonstrating size distribution model in decoupling approximation. Equivalent of Examples/Python/simulation/ex03_InterferenceFunctions/ApproximationDA.py

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionDAModelBuilder::buildSample "MultiLayer * SizeDistributionDAModelBuilder::buildSample() const
";


// File: classSizeDistributionLMAModelBuilder.xml
%feature("docstring") SizeDistributionLMAModelBuilder "

Creates the sample demonstrating size distribution model in local monodisperse approximation. Equivalent of Examples/Python/simulation/ex03_InterferenceFunctions/ApproximationLMA.py

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionLMAModelBuilder::buildSample "MultiLayer * SizeDistributionLMAModelBuilder::buildSample() const
";


// File: classSizeDistributionSSCAModelBuilder.xml
%feature("docstring") SizeDistributionSSCAModelBuilder "

Creates the sample demonstrating size distribution model in size space coupling approximation. Equivalent of Examples/Python/simulation/ex03_InterferenceFunctions/ApproximationSSCA.py

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionSSCAModelBuilder::buildSample "MultiLayer * SizeDistributionSSCAModelBuilder::buildSample() const
";


// File: classSLDSlicedCylindersBuilder.xml
%feature("docstring") SLDSlicedCylindersBuilder "

Provides exactly the same sample as  SlicedCylindersBuilder, but with sld-based materials. Assumed wavelength is 1.54 Angstrom.

C++ includes: SlicedCylindersBuilder.h
";

%feature("docstring")  SLDSlicedCylindersBuilder::buildSample "MultiLayer * SLDSlicedCylindersBuilder::buildSample() const
";


// File: classSlice.xml
%feature("docstring") Slice "

Data structure containing the data of a single slice, for calculating the Fresnel coefficients.

C++ includes: Slice.h
";

%feature("docstring")  Slice::Slice "Slice::Slice(double thickness, const Material &material)
";

%feature("docstring")  Slice::Slice "Slice::Slice(double thickness, const Material &material, const LayerRoughness &top_roughness)
";

%feature("docstring")  Slice::Slice "Slice::Slice(const Slice &other)
";

%feature("docstring")  Slice::Slice "Slice::Slice(Slice &&other)
";

%feature("docstring")  Slice::~Slice "Slice::~Slice()
";

%feature("docstring")  Slice::setMaterial "void Slice::setMaterial(const Material &material)
";

%feature("docstring")  Slice::material "Material Slice::material() const
";

%feature("docstring")  Slice::thickness "double Slice::thickness() const
";

%feature("docstring")  Slice::topRoughness "const LayerRoughness * Slice::topRoughness() const
";

%feature("docstring")  Slice::scalarReducedPotential "complex_t Slice::scalarReducedPotential(kvector_t k, double n_ref) const

Return the potential term that is used in the one-dimensional Fresnel calculations. 
";

%feature("docstring")  Slice::polarizedReducedPotential "Eigen::Matrix2cd Slice::polarizedReducedPotential(kvector_t k, double n_ref) const

Return the potential term that is used in the one-dimensional Fresnel calculations in the presence of magnetization 
";

%feature("docstring")  Slice::initBField "void Slice::initBField(kvector_t h_field, double b_z)

Initializes the magnetic B field from a given ambient field strength H. 
";

%feature("docstring")  Slice::bField "kvector_t Slice::bField() const
";

%feature("docstring")  Slice::invertBField "void Slice::invertBField()
";


// File: classSlicedCompositionBuilder.xml
%feature("docstring") SlicedCompositionBuilder "

Builds sample: spherical composition made of top+bottom spherical cups

C++ includes: SlicedCompositionBuilder.h
";

%feature("docstring")  SlicedCompositionBuilder::buildSample "MultiLayer * SlicedCompositionBuilder::buildSample() const
";


// File: classSlicedCylindersBuilder.xml
%feature("docstring") SlicedCylindersBuilder "

Builds sample: cylinders on a silicon substrate

C++ includes: SlicedCylindersBuilder.h
";

%feature("docstring")  SlicedCylindersBuilder::buildSample "MultiLayer * SlicedCylindersBuilder::buildSample() const
";


// File: classSlicedFormFactorList.xml
%feature("docstring") SlicedFormFactorList "

Class that contains and owns a list of form factors and the index of their containing layer. This class also handles the slicing of form factors if they cross layer interfaces.

C++ includes: SlicedFormFactorList.h
";

%feature("docstring")  SlicedFormFactorList::SlicedFormFactorList "SlicedFormFactorList::SlicedFormFactorList()=default
";

%feature("docstring")  SlicedFormFactorList::SlicedFormFactorList "SlicedFormFactorList::SlicedFormFactorList(SlicedFormFactorList &&other)=default
";

%feature("docstring")  SlicedFormFactorList::~SlicedFormFactorList "SlicedFormFactorList::~SlicedFormFactorList()=default
";

%feature("docstring")  SlicedFormFactorList::size "size_t SlicedFormFactorList::size() const
";

%feature("docstring")  SlicedFormFactorList::regionMap "std::map< size_t, std::vector< HomogeneousRegion > > SlicedFormFactorList::regionMap() const
";


// File: structSlicedParticle.xml
%feature("docstring") SlicedParticle "

Struct that contains information on a sliced particle. This information is needed for evaluating the sliced form factor and the average of a material, used in the Fresnel calculations.

C++ includes: SlicedParticle.h
";


// File: structSlicingEffects.xml
%feature("docstring") SlicingEffects "

Nested structure that holds slicing effects on position and removed parts.

C++ includes: IBornFF.h
";


// File: classSpecularMagneticNCStrategy.xml
%feature("docstring") SpecularMagneticNCStrategy "

Implements the magnetic Fresnel computation with Nevot-Croce roughness

Implements the transfer matrix formalism for the calculation of wave amplitudes of the coherent wave solution in a multilayer with magnetization. For a description, see internal document \"Polarized Implementation of the Transfer Matrix Method\"

C++ includes: SpecularMagneticNCStrategy.h
";


// File: classSpecularMagneticStrategy.xml
%feature("docstring") SpecularMagneticStrategy "

Implements the magnetic Fresnel computation with Nevot-Croce roughness

Implements the transfer matrix formalism for the calculation of wave amplitudes of the coherent wave solution in a multilayer with magnetization. For a description, see internal document \"Polarized Implementation of the Transfer Matrix Method\"

C++ includes: SpecularMagneticStrategy.h
";

%feature("docstring")  SpecularMagneticStrategy::Execute "ISpecularStrategy::coeffs_t SpecularMagneticStrategy::Execute(const std::vector< Slice > &slices, const kvector_t &k) const

Computes refraction angle reflection/transmission coefficients for given sliced multilayer and wavevector k 
";

%feature("docstring")  SpecularMagneticStrategy::Execute "ISpecularStrategy::coeffs_t SpecularMagneticStrategy::Execute(const std::vector< Slice > &slices, const std::vector< complex_t > &kz) const

Computes refraction angle reflection/transmission coefficients for given sliced multilayer and a set of kz projections corresponding to each slice 
";


// File: classSpecularMagneticStrategy__v1.xml
%feature("docstring") SpecularMagneticStrategy_v1 "

Implements the matrix formalism for the calculation of wave amplitudes of the coherent wave solution in a multilayer with magnetization.

C++ includes: SpecularMagneticStrategy_v1.h
";

%feature("docstring")  SpecularMagneticStrategy_v1::Execute "ISpecularStrategy::coeffs_t SpecularMagneticStrategy_v1::Execute(const std::vector< Slice > &slices, const kvector_t &k) const

Computes refraction angle reflection/transmission coefficients for given sliced multilayer and wavevector k 
";

%feature("docstring")  SpecularMagneticStrategy_v1::Execute "ISpecularStrategy::coeffs_t SpecularMagneticStrategy_v1::Execute(const std::vector< Slice > &slices, const std::vector< complex_t > &kz) const
";


// File: classSpecularMagneticStrategy__v2.xml
%feature("docstring") SpecularMagneticStrategy_v2 "

Implements the magnetic Fresnel computation without roughness

Implements the matrix formalism for the calculation of wave amplitudes of the coherent wave solution in a multilayer with magnetization. For a detailed description see internal document \"Polarized Specular Reflectometry\"

C++ includes: SpecularMagneticStrategy_v2.h
";

%feature("docstring")  SpecularMagneticStrategy_v2::Execute "ISpecularStrategy::coeffs_t SpecularMagneticStrategy_v2::Execute(const std::vector< Slice > &slices, const kvector_t &k) const

Computes refraction angle reflection/transmission coefficients for given sliced multilayer and wavevector k 
";

%feature("docstring")  SpecularMagneticStrategy_v2::Execute "ISpecularStrategy::coeffs_t SpecularMagneticStrategy_v2::Execute(const std::vector< Slice > &slices, const std::vector< complex_t > &kz) const

Computes refraction angle reflection/transmission coefficients for given sliced multilayer and a set of kz projections corresponding to each slice 
";


// File: classSpecularMagneticTanhStrategy.xml
%feature("docstring") SpecularMagneticTanhStrategy "

Implements the magnetic Fresnel computation with the analytical Tanh roughness

Implements the transfer matrix formalism for the calculation of wave amplitudes of the coherent wave solution in a multilayer with magnetization. For a description, see internal document \"Polarized Implementation of the Transfer Matrix Method\"

C++ includes: SpecularMagneticTanhStrategy.h
";


// File: classSpecularScalarNCStrategy.xml
%feature("docstring") SpecularScalarNCStrategy "

Implements Nevot-Croce roughness for a scaler computation.

Implements the transition function that includes Nevot-Croce roughness in the computation of the coefficients for coherent wave propagation in a multilayer by applying modified Fresnel coefficients.

C++ includes: SpecularScalarNCStrategy.h
";


// File: classSpecularScalarStrategy.xml
%feature("docstring") SpecularScalarStrategy "

Implements the scalar Fresnel computation

Implements method 'execute' to compute refraction angles and transmission/reflection coefficients for coherent wave propagation in a multilayer.

Inherited by  SpecularScalarNCStrategy,  SpecularScalarTanhStrategy

C++ includes: SpecularScalarStrategy.h
";

%feature("docstring")  SpecularScalarStrategy::Execute "ISpecularStrategy::coeffs_t SpecularScalarStrategy::Execute(const std::vector< Slice > &slices, const kvector_t &k) const override

Computes refraction angles and transmission/reflection coefficients for given coherent wave propagation in a multilayer. 
";

%feature("docstring")  SpecularScalarStrategy::Execute "ISpecularStrategy::coeffs_t SpecularScalarStrategy::Execute(const std::vector< Slice > &slices, const std::vector< complex_t > &kz) const override
";


// File: classSpecularScalarTanhStrategy.xml
%feature("docstring") SpecularScalarTanhStrategy "

Implements an tanh transition function to model roughness in a scaler computation.

Implements the transition function that includes the analytical roughness model of an tanh interface transition in the computation of the coefficients for coherent wave propagation in a multilayer by applying modified Fresnel coefficients.

C++ includes: SpecularScalarTanhStrategy.h
";


// File: classSpecularStrategyBuilder.xml
%feature("docstring") SpecularStrategyBuilder "";


// File: classSpheresWithLimitsDistributionBuilder.xml
%feature("docstring") SpheresWithLimitsDistributionBuilder "

Spherical particles with the distribution applied to the radius and RealLimits defined.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  SpheresWithLimitsDistributionBuilder::SpheresWithLimitsDistributionBuilder "SpheresWithLimitsDistributionBuilder::SpheresWithLimitsDistributionBuilder()
";

%feature("docstring")  SpheresWithLimitsDistributionBuilder::buildSample "MultiLayer * SpheresWithLimitsDistributionBuilder::buildSample() const
";


// File: classSquareLattice2D.xml
%feature("docstring") SquareLattice2D "

A two-dimensional Bravais lattice with square unit cell.

C++ includes: Lattice2D.h
";

%feature("docstring")  SquareLattice2D::SquareLattice2D "SquareLattice2D::SquareLattice2D(double length, double xi=0.0)
";

%feature("docstring")  SquareLattice2D::clone "SquareLattice2D * SquareLattice2D::clone() const
";

%feature("docstring")  SquareLattice2D::accept "void SquareLattice2D::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  SquareLattice2D::length1 "virtual double SquareLattice2D::length1() const
";

%feature("docstring")  SquareLattice2D::length2 "virtual double SquareLattice2D::length2() const
";

%feature("docstring")  SquareLattice2D::latticeAngle "double SquareLattice2D::latticeAngle() const
";

%feature("docstring")  SquareLattice2D::unitCellArea "double SquareLattice2D::unitCellArea() const
";


// File: classSquareLattice2DBuilder.xml
%feature("docstring") SquareLattice2DBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  SquareLattice2DBuilder::SquareLattice2DBuilder "SquareLattice2DBuilder::SquareLattice2DBuilder()
";

%feature("docstring")  SquareLattice2DBuilder::buildSample "MultiLayer * SquareLattice2DBuilder::buildSample() const
";


// File: classSSCApproximationStrategy.xml
%feature("docstring") SSCApproximationStrategy "

Strategy class to compute the total scattering from a particle layout in the size-spacing correlation approximation.

C++ includes: SSCApproximationStrategy.h
";

%feature("docstring")  SSCApproximationStrategy::SSCApproximationStrategy "SSCApproximationStrategy::SSCApproximationStrategy(const std::vector< FormFactorCoherentSum > &weighted_formfactors, const InterferenceFunctionRadialParaCrystal *iff, SimulationOptions sim_params, bool polarized, double kappa)
";


// File: classSuperLatticeBuilder.xml
%feature("docstring") SuperLatticeBuilder "

Builds sample: 2D finite lattice of 2D finite lattices (superlattice).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  SuperLatticeBuilder::buildSample "MultiLayer * SuperLatticeBuilder::buildSample() const
";


// File: classThickAbsorptiveSampleBuilder.xml
%feature("docstring") ThickAbsorptiveSampleBuilder "";

%feature("docstring")  ThickAbsorptiveSampleBuilder::buildSample "MultiLayer * ThickAbsorptiveSampleBuilder::buildSample() const override
";


// File: classTransformBoxBuilder.xml
%feature("docstring") TransformBoxBuilder "

Rotated box in 3 layers system.

C++ includes: TransformationsBuilder.h
";

%feature("docstring")  TransformBoxBuilder::buildSample "MultiLayer * TransformBoxBuilder::buildSample() const
";


// File: classTriangularRippleBuilder.xml
%feature("docstring") TriangularRippleBuilder "

Builds sample: triangular ripple within the 1D-paracrystal model (from PRB 85, 235415, 2012).

C++ includes: RipplesBuilder.h
";

%feature("docstring")  TriangularRippleBuilder::TriangularRippleBuilder "TriangularRippleBuilder::TriangularRippleBuilder()
";

%feature("docstring")  TriangularRippleBuilder::buildSample "MultiLayer * TriangularRippleBuilder::buildSample() const
";


// File: classTruncatedEllipsoid.xml
%feature("docstring") TruncatedEllipsoid "";

%feature("docstring")  TruncatedEllipsoid::TruncatedEllipsoid "TruncatedEllipsoid::TruncatedEllipsoid(double r_x, double r_y, double r_z, double height, double dh)
";

%feature("docstring")  TruncatedEllipsoid::~TruncatedEllipsoid "TruncatedEllipsoid::~TruncatedEllipsoid()
";


// File: classTwoLayerRoughnessBuilder.xml
%feature("docstring") TwoLayerRoughnessBuilder "

Builds sample: two layers with rough interface.

C++ includes: TwoLayerRoughnessBuilder.h
";

%feature("docstring")  TwoLayerRoughnessBuilder::buildSample "MultiLayer * TwoLayerRoughnessBuilder::buildSample() const
";


// File: classTwoTypesCylindersDistributionBuilder.xml
%feature("docstring") TwoTypesCylindersDistributionBuilder "

Builds mixture of cylinder particles with different size distribution (IsGISAXS example #2)

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  TwoTypesCylindersDistributionBuilder::TwoTypesCylindersDistributionBuilder "TwoTypesCylindersDistributionBuilder::TwoTypesCylindersDistributionBuilder()
";

%feature("docstring")  TwoTypesCylindersDistributionBuilder::buildSample "MultiLayer * TwoTypesCylindersDistributionBuilder::buildSample() const
";


// File: classWavevectorInfo.xml
%feature("docstring") WavevectorInfo "

Holds all wavevector information relevant for calculating form factors.

C++ includes: WavevectorInfo.h
";

%feature("docstring")  WavevectorInfo::WavevectorInfo "WavevectorInfo::WavevectorInfo(cvector_t ki, cvector_t kf, double wavelength)
";

%feature("docstring")  WavevectorInfo::WavevectorInfo "WavevectorInfo::WavevectorInfo(kvector_t ki, kvector_t kf, double wavelength)
";

%feature("docstring")  WavevectorInfo::transformed "WavevectorInfo WavevectorInfo::transformed(const Transform3D &transform) const
";

%feature("docstring")  WavevectorInfo::getKi "cvector_t WavevectorInfo::getKi() const
";

%feature("docstring")  WavevectorInfo::getKf "cvector_t WavevectorInfo::getKf() const
";

%feature("docstring")  WavevectorInfo::getQ "cvector_t WavevectorInfo::getQ() const
";

%feature("docstring")  WavevectorInfo::wavelength "double WavevectorInfo::wavelength() const
";


// File: classZLimits.xml
%feature("docstring") ZLimits "

Class that contains upper and lower limits of the z-coordinate for the slicing of form factors.

C++ includes: ZLimits.h
";

%feature("docstring")  ZLimits::ZLimits "ZLimits::ZLimits()
";

%feature("docstring")  ZLimits::ZLimits "ZLimits::ZLimits(double min, double max)
";

%feature("docstring")  ZLimits::ZLimits "ZLimits::ZLimits(OneSidedLimit lower_limit, OneSidedLimit upper_limit)
";

%feature("docstring")  ZLimits::isFinite "bool ZLimits::isFinite() const
";

%feature("docstring")  ZLimits::lowerLimit "OneSidedLimit ZLimits::lowerLimit() const
";

%feature("docstring")  ZLimits::upperLimit "OneSidedLimit ZLimits::upperLimit() const
";


// File: namespace_0d122.xml


// File: namespace_0d125.xml


// File: namespace_0d148.xml


// File: namespace_0d150.xml


// File: namespace_0d152.xml


// File: namespace_0d157.xml


// File: namespace_0d16.xml


// File: namespace_0d161.xml


// File: namespace_0d165.xml


// File: namespace_0d177.xml


// File: namespace_0d179.xml


// File: namespace_0d189.xml


// File: namespace_0d2.xml


// File: namespace_0d208.xml


// File: namespace_0d210.xml


// File: namespace_0d212.xml


// File: namespace_0d215.xml


// File: namespace_0d229.xml


// File: namespace_0d241.xml


// File: namespace_0d246.xml


// File: namespace_0d25.xml


// File: namespace_0d264.xml


// File: namespace_0d272.xml


// File: namespace_0d282.xml


// File: namespace_0d284.xml


// File: namespace_0d286.xml


// File: namespace_0d290.xml


// File: namespace_0d292.xml


// File: namespace_0d296.xml


// File: namespace_0d308.xml


// File: namespace_0d31.xml


// File: namespace_0d314.xml


// File: namespace_0d318.xml


// File: namespace_0d336.xml


// File: namespace_0d355.xml


// File: namespace_0d37.xml


// File: namespace_0d39.xml


// File: namespace_0d4.xml


// File: namespace_0d47.xml


// File: namespacebake.xml
%feature("docstring")  bake::CubicLattice "Lattice3D bake::CubicLattice(double a)

Returns a primitive cubic (cP) lattice with edge length a. 
";

%feature("docstring")  bake::FCCLattice "Lattice3D bake::FCCLattice(double a)

Returns a face-centered cubic (cF) lattice with edge length a. 
";

%feature("docstring")  bake::HexagonalLattice "Lattice3D bake::HexagonalLattice(double a, double c)

Returns a primitive hexagonal (hP) lattice with hexagonal edge a and height c. 
";

%feature("docstring")  bake::HCPLattice "Lattice3D bake::HCPLattice(double a, double c)

TODO: Clarify how this is meant: HCP is not a Bravais lattice. 
";

%feature("docstring")  bake::TetragonalLattice "Lattice3D bake::TetragonalLattice(double a, double c)

Returns a primitive tetragonal (tP) lattice with square base edge a and height c. 
";

%feature("docstring")  bake::BCTLattice "Lattice3D bake::BCTLattice(double a, double c)

Returns a body-centered cubic (cI) lattice with edge length a. TODO: Clarify meaning of c 
";


// File: namespaceFormFactorPrecompute.xml
%feature("docstring")  FormFactorPrecompute::scalar "std::vector< complex_t > FormFactorPrecompute::scalar(const SimulationElement &sim_element, const std::vector< FormFactorCoherentSum > &ff_wrappers)
";

%feature("docstring")  FormFactorPrecompute::polarized "FormFactorPrecompute::matrixFFVector_t FormFactorPrecompute::polarized(const SimulationElement &sim_element, const std::vector< FormFactorCoherentSum > &ff_wrappers)
";


// File: namespaceKzComputation.xml
%feature("docstring")  KzComputation::computeReducedKz "std::vector< complex_t > KzComputation::computeReducedKz(const std::vector< Slice > &slices, kvector_t k)
";

%feature("docstring")  KzComputation::computeKzFromSLDs "std::vector< complex_t > KzComputation::computeKzFromSLDs(const std::vector< Slice > &slices, double kz)
";

%feature("docstring")  KzComputation::computeKzFromRefIndices "std::vector< complex_t > KzComputation::computeKzFromRefIndices(const std::vector< Slice > &slices, kvector_t k)
";


// File: namespaceMaterialUtils.xml
%feature("docstring")  MaterialUtils::ScalarReducedPotential "complex_t MaterialUtils::ScalarReducedPotential(complex_t n, kvector_t k, double n_ref)

Function for calculating the reduced potential, used for obtaining the Fresnel coefficients (non-polarized material case) 
";

%feature("docstring")  MaterialUtils::PolarizedReducedPotential "Eigen::Matrix2cd MaterialUtils::PolarizedReducedPotential(complex_t n, kvector_t b_field, kvector_t k, double n_ref)

Function for calculating the reduced potential, used for obtaining the Fresnel coefficients (polarized material case) 
";

%feature("docstring")  MaterialUtils::MagnetizationCorrection "Eigen::Matrix2cd MaterialUtils::MagnetizationCorrection(complex_t unit_factor, double magnetic_factor, BasicVector3D< T > polarization)
";

%feature("docstring")  MaterialUtils::checkMaterialTypes "MATERIAL_TYPES MaterialUtils::checkMaterialTypes(const std::vector< const Material * > &materials)

Checks if all non-default materials in  materials are of the same type and returns this type. If several types of materials are involved, InvalidMaterialType identifier is returned. 
";


// File: namespaceMultiLayerUtils.xml
%feature("docstring")  MultiLayerUtils::LayerTopRoughness "const LayerRoughness * MultiLayerUtils::LayerTopRoughness(const MultiLayer &multilayer, size_t i)

Returns top roughness of layer. 
";

%feature("docstring")  MultiLayerUtils::IndexOfLayer "size_t MultiLayerUtils::IndexOfLayer(const MultiLayer &multilayer, const Layer *p_layer)

Returns the index of the given layer. 
";

%feature("docstring")  MultiLayerUtils::ContainsCompatibleMaterials "bool MultiLayerUtils::ContainsCompatibleMaterials(const MultiLayer &multilayer)

Returns true if the multilayer contains non-default materials of one type only. 
";

%feature("docstring")  MultiLayerUtils::hasRoughness "bool MultiLayerUtils::hasRoughness(const MultiLayer &sample)
";


// File: namespacePyImport.xml
%feature("docstring")  PyImport::createFromPython "std::unique_ptr< MultiLayer > PyImport::createFromPython(const std::string &script, const std::string &functionName, const std::string &path=\"\")

Creates a multi layer by running python code in embedded interpreter.

Parameters:
-----------

script: 
Python script

functionName: 
A function name in this script which produces a  MultiLayer

path: 
A path to import BornAgain library. If empty, relies on PYTHONPATH 
";

%feature("docstring")  PyImport::listOfFunctions "std::vector< std::string > PyImport::listOfFunctions(const std::string &script, const std::string &path=\"\")

Returns list of functions defined in the script.

Parameters:
-----------

script: 
Python script

path: 
A path to import BornAgain library. If empty, relies on PYTHONPATH 
";


// File: namespacerefMat.xml


// File: namespaceripples.xml
%feature("docstring")  ripples::factor_x_box "complex_t ripples::factor_x_box(complex_t q, double l)
";

%feature("docstring")  ripples::factor_x_Gauss "complex_t ripples::factor_x_Gauss(complex_t q, double l)
";

%feature("docstring")  ripples::factor_x_Lorentz "complex_t ripples::factor_x_Lorentz(complex_t q, double l)
";

%feature("docstring")  ripples::profile_yz_bar "complex_t ripples::profile_yz_bar(complex_t qy, complex_t qz, double width, double height)

Complex form factor of rectangular ripple (bar). 
";

%feature("docstring")  ripples::profile_yz_cosine "complex_t ripples::profile_yz_cosine(complex_t qy, complex_t qz, double width, double height)

Complex form factor of cosine ripple. 
";

%feature("docstring")  ripples::profile_yz_triangular "complex_t ripples::profile_yz_triangular(complex_t qy, complex_t qz, double width, double height, double asymmetry)

Complex form factor of triangular ripple. 
";


// File: namespacesomeff.xml
%feature("docstring")  someff::ffSphere "complex_t someff::ffSphere(cvector_t q, double R)

Returns the form factor of a sphere of radius R.

Used by the hard sphere and by several soft sphere classes. 
";


// File: namespaceswigAPI.xml
%feature("docstring")  swigAPI::generateZValues "std::vector< double > swigAPI::generateZValues(int n_points, double z_min, double z_max)
";

%feature("docstring")  swigAPI::materialProfileSLD "std::vector< complex_t > swigAPI::materialProfileSLD(const MultiLayer &multilayer, int n_points, double z_min, double z_max)

Calculate average material profile for given multilayer. 
";

%feature("docstring")  swigAPI::defaultMaterialProfileLimits "std::pair< double, double > swigAPI::defaultMaterialProfileLimits(const MultiLayer &multilayer)

Get default z limits for generating a material profile. 
";


// File: IInterferenceFunction_8cpp.xml


// File: IInterferenceFunction_8h.xml


// File: InterferenceFunction1DLattice_8cpp.xml


// File: InterferenceFunction1DLattice_8h.xml


// File: InterferenceFunction2DLattice_8cpp.xml


// File: InterferenceFunction2DLattice_8h.xml


// File: InterferenceFunction2DParaCrystal_8cpp.xml


// File: InterferenceFunction2DParaCrystal_8h.xml


// File: InterferenceFunction2DSuperLattice_8cpp.xml


// File: InterferenceFunction2DSuperLattice_8h.xml


// File: InterferenceFunction3DLattice_8cpp.xml


// File: InterferenceFunction3DLattice_8h.xml


// File: InterferenceFunctionFinite2DLattice_8cpp.xml


// File: InterferenceFunctionFinite2DLattice_8h.xml


// File: InterferenceFunctionFinite3DLattice_8cpp.xml


// File: InterferenceFunctionFinite3DLattice_8h.xml


// File: InterferenceFunctionHardDisk_8cpp.xml


// File: InterferenceFunctionHardDisk_8h.xml


// File: InterferenceFunctionNone_8cpp.xml


// File: InterferenceFunctionNone_8h.xml


// File: InterferenceFunctionRadialParaCrystal_8cpp.xml


// File: InterferenceFunctionRadialParaCrystal_8h.xml


// File: InterferenceFunctions_8h.xml


// File: InterferenceFunctionTwin_8cpp.xml


// File: InterferenceFunctionTwin_8h.xml


// File: ParticleLayout_8cpp.xml


// File: ParticleLayout_8h.xml


// File: FTDecay1D_8cpp.xml


// File: FTDecay1D_8h.xml


// File: FTDecay2D_8cpp.xml


// File: FTDecay2D_8h.xml


// File: FTDistributions1D_8cpp.xml


// File: FTDistributions1D_8h.xml


// File: FTDistributions2D_8cpp.xml


// File: FTDistributions2D_8h.xml


// File: IDistribution1DSampler_8cpp.xml


// File: IDistribution1DSampler_8h.xml


// File: IDistribution2DSampler_8cpp.xml


// File: IDistribution2DSampler_8h.xml


// File: IPeakShape_8cpp.xml


// File: IPeakShape_8h.xml


// File: ComputeBA_8cpp.xml


// File: ComputeBA_8h.xml


// File: ComputeBAPol_8cpp.xml


// File: ComputeBAPol_8h.xml


// File: ComputeDWBA_8cpp.xml


// File: ComputeDWBA_8h.xml


// File: ComputeDWBAPol_8cpp.xml


// File: ComputeDWBAPol_8h.xml


// File: IComputeFF_8cpp.xml


// File: IComputeFF_8h.xml


// File: FormFactorCoherentPart_8cpp.xml


// File: FormFactorCoherentPart_8h.xml


// File: FormFactorCoherentSum_8cpp.xml


// File: FormFactorCoherentSum_8h.xml


// File: IFresnelMap_8cpp.xml


// File: IFresnelMap_8h.xml


// File: MatrixFresnelMap_8cpp.xml


// File: MatrixFresnelMap_8h.xml


// File: ScalarFresnelMap_8cpp.xml


// File: ScalarFresnelMap_8h.xml


// File: FormFactorAnisoPyramid_8cpp.xml


// File: FormFactorAnisoPyramid_8h.xml


// File: FormFactorBar_8cpp.xml


// File: FormFactorBar_8h.xml


// File: FormFactorBox_8cpp.xml


// File: FormFactorBox_8h.xml


// File: FormFactorCantellatedCube_8cpp.xml


// File: FormFactorCantellatedCube_8h.xml


// File: FormFactorCone_8cpp.xml


// File: FormFactorCone_8h.xml


// File: FormFactorCone6_8cpp.xml


// File: FormFactorCone6_8h.xml


// File: FormFactorCosineRipple_8cpp.xml


// File: FormFactorCosineRipple_8h.xml


// File: FormFactorCuboctahedron_8cpp.xml


// File: FormFactorCuboctahedron_8h.xml


// File: FormFactorCylinder_8cpp.xml


// File: FormFactorCylinder_8h.xml


// File: FormFactorDodecahedron_8cpp.xml


// File: FormFactorDodecahedron_8h.xml


// File: FormFactorDot_8cpp.xml


// File: FormFactorDot_8h.xml


// File: FormFactorEllipsoidalCylinder_8cpp.xml


// File: FormFactorEllipsoidalCylinder_8h.xml


// File: FormFactorFullSphere_8cpp.xml


// File: FormFactorFullSphere_8h.xml


// File: FormFactorFullSpheroid_8cpp.xml


// File: FormFactorFullSpheroid_8h.xml


// File: FormFactorHemiEllipsoid_8cpp.xml


// File: FormFactorHemiEllipsoid_8h.xml


// File: FormFactorHollowSphere_8cpp.xml


// File: FormFactorHollowSphere_8h.xml


// File: FormFactorIcosahedron_8cpp.xml


// File: FormFactorIcosahedron_8h.xml


// File: FormFactorLongBoxGauss_8cpp.xml


// File: FormFactorLongBoxGauss_8h.xml


// File: FormFactorLongBoxLorentz_8cpp.xml


// File: FormFactorLongBoxLorentz_8h.xml


// File: FormFactorPrism3_8cpp.xml


// File: FormFactorPrism3_8h.xml


// File: FormFactorPrism6_8cpp.xml


// File: FormFactorPrism6_8h.xml


// File: FormFactorPyramid_8cpp.xml


// File: FormFactorPyramid_8h.xml


// File: FormFactorSawtoothRipple_8cpp.xml


// File: FormFactorSawtoothRipple_8h.xml


// File: FormFactorTetrahedron_8cpp.xml


// File: FormFactorTetrahedron_8h.xml


// File: FormFactorTruncatedCube_8cpp.xml


// File: FormFactorTruncatedCube_8h.xml


// File: FormFactorTruncatedSphere_8cpp.xml


// File: FormFactorTruncatedSphere_8h.xml


// File: FormFactorTruncatedSpheroid_8cpp.xml


// File: FormFactorTruncatedSpheroid_8h.xml


// File: HardParticles_8h.xml


// File: IFormFactorPolyhedron_8cpp.xml


// File: IFormFactorPolyhedron_8h.xml


// File: IFormFactorPrism_8cpp.xml


// File: IFormFactorPrism_8h.xml


// File: IProfileRipple_8cpp.xml


// File: IProfileRipple_8h.xml


// File: PolyhedralComponents_8cpp.xml


// File: PolyhedralComponents_8h.xml


// File: PolyhedralTopology_8h.xml


// File: Polyhedron_8cpp.xml


// File: Polyhedron_8h.xml


// File: Prism_8cpp.xml


// File: Prism_8h.xml


// File: Ripples_8cpp.xml


// File: Ripples_8h.xml


// File: DecouplingApproximationStrategy_8cpp.xml


// File: DecouplingApproximationStrategy_8h.xml


// File: FormFactorPrecompute_8cpp.xml


// File: FormFactorPrecompute_8h.xml


// File: IInterferenceFunctionStrategy_8cpp.xml


// File: IInterferenceFunctionStrategy_8h.xml


// File: SSCApproximationStrategy_8cpp.xml


// File: SSCApproximationStrategy_8h.xml


// File: BakeLattice_8cpp.xml


// File: BakeLattice_8h.xml


// File: ISelectionRule_8h.xml


// File: Lattice2D_8cpp.xml


// File: Lattice2D_8h.xml


// File: Lattice3D_8cpp.xml


// File: Lattice3D_8h.xml


// File: MatrixRTCoefficients__v1_8cpp.xml


// File: MatrixRTCoefficients__v1_8h.xml


// File: MatrixRTCoefficients__v2_8cpp.xml


// File: MatrixRTCoefficients__v2_8h.xml


// File: SpecularMagneticStrategy__v1_8cpp.xml


// File: SpecularMagneticStrategy__v1_8h.xml


// File: SpecularMagneticStrategy__v2_8cpp.xml


// File: SpecularMagneticStrategy__v2_8h.xml


// File: SomeFormFactors_8cpp.xml


// File: SomeFormFactors_8h.xml


// File: BaseMaterialImpl_8h.xml


// File: MagneticMaterialImpl_8cpp.xml


// File: MagneticMaterialImpl_8h.xml


// File: Material_8cpp.xml


// File: Material_8h.xml


// File: MaterialBySLDImpl_8cpp.xml


// File: MaterialBySLDImpl_8h.xml


// File: MaterialFactoryFuncs_8cpp.xml
%feature("docstring")  HomogeneousMaterial "Material HomogeneousMaterial(const std::string &name, complex_t refractive_index, kvector_t magnetization)

Constructs a material with  name,  refractive_index and  magnetization (in A/m). Alternatively,  $\\\\delta$ and  $\\\\beta$ for refractive index  $n = 1 - \\\\delta + i \\\\beta$ can be passed directly. With no parameters given, constructs default (vacuum) material with  $n = 1$ and zero magnetization. 
";

%feature("docstring")  HomogeneousMaterial "Material HomogeneousMaterial(const std::string &name, double delta, double beta, kvector_t magnetization)
";

%feature("docstring")  HomogeneousMaterial "Material HomogeneousMaterial()
";

%feature("docstring")  MaterialBySLD "Material MaterialBySLD()
";

%feature("docstring")  MaterialBySLD "Material MaterialBySLD(const std::string &name, double sld_real, double sld_imag, kvector_t magnetization)

Constructs a wavelength-independent material with a given complex-valued scattering length density (SLD). SLD values for a wide variety of materials can be found on https://sld-calculator.appspot.com/ and https://www.ncnr.nist.gov/resources/activation/ By convention, SLD imaginary part is treated as negative by default, which corresponds to attenuation of the signal. With no parameters given, MaterialBySLD constructs default (vacuum) material with zero sld and zero magnetization.

Parameters:
-----------

name: 
material name

sld_real: 
real part of the scattering length density, inverse square angstroms

sld_imag: 
imaginary part of the scattering length density, inverse square angstroms

magnetization: 
magnetization (in A/m) 
";


// File: MaterialFactoryFuncs_8h.xml
%feature("docstring")  HomogeneousMaterial "Material HomogeneousMaterial()
";

%feature("docstring")  HomogeneousMaterial "Material HomogeneousMaterial(const std::string &name, double delta, double beta, kvector_t magnetization={})
";

%feature("docstring")  HomogeneousMaterial "Material HomogeneousMaterial(const std::string &name, complex_t refractive_index, kvector_t magnetization={})

Constructs a material with  name,  refractive_index and  magnetization (in A/m). Alternatively,  $\\\\delta$ and  $\\\\beta$ for refractive index  $n = 1 - \\\\delta + i \\\\beta$ can be passed directly. With no parameters given, constructs default (vacuum) material with  $n = 1$ and zero magnetization. 
";

%feature("docstring")  MaterialBySLD "Material MaterialBySLD()
";

%feature("docstring")  MaterialBySLD "Material MaterialBySLD(const std::string &name, double sld_real, double sld_imag, kvector_t magnetization={})

Constructs a wavelength-independent material with a given complex-valued scattering length density (SLD). SLD values for a wide variety of materials can be found on https://sld-calculator.appspot.com/ and https://www.ncnr.nist.gov/resources/activation/ By convention, SLD imaginary part is treated as negative by default, which corresponds to attenuation of the signal. With no parameters given, MaterialBySLD constructs default (vacuum) material with zero sld and zero magnetization.

Parameters:
-----------

name: 
material name

sld_real: 
real part of the scattering length density, inverse square angstroms

sld_imag: 
imaginary part of the scattering length density, inverse square angstroms

magnetization: 
magnetization (in A/m) 
";


// File: MaterialUtils_8cpp.xml
%feature("docstring")  Unit_Matrix "const Eigen::Matrix2cd Unit_Matrix(Eigen::Matrix2cd::Identity())
";


// File: MaterialUtils_8h.xml


// File: RefractiveMaterialImpl_8cpp.xml


// File: RefractiveMaterialImpl_8h.xml


// File: WavevectorInfo_8cpp.xml


// File: WavevectorInfo_8h.xml


// File: Layer_8cpp.xml


// File: Layer_8h.xml


// File: MultiLayer_8cpp.xml


// File: MultiLayer_8h.xml


// File: MultiLayerUtils_8cpp.xml


// File: MultiLayerUtils_8h.xml


// File: PyImport_8cpp.xml


// File: PyImport_8h.xml


// File: RoughnessModels_8cpp.xml


// File: RoughnessModels_8h.xml


// File: Crystal_8cpp.xml


// File: Crystal_8h.xml


// File: FormFactorCoreShell_8cpp.xml


// File: FormFactorCoreShell_8h.xml


// File: FormFactorCrystal_8cpp.xml


// File: FormFactorCrystal_8h.xml


// File: FormFactorWeighted_8cpp.xml


// File: FormFactorWeighted_8h.xml


// File: HomogeneousRegion_8cpp.xml
%feature("docstring")  createAveragedMaterial "Material createAveragedMaterial(const Material &layer_mat, const std::vector< HomogeneousRegion > &regions)

Creates averaged material. Square refractive index of returned material is arithmetic mean over  regions and  layer_mat. Magnetization (if present) is averaged linearly. 
";


// File: HomogeneousRegion_8h.xml
%feature("docstring")  createAveragedMaterial "Material createAveragedMaterial(const Material &layer_mat, const std::vector< HomogeneousRegion > &regions)

Creates averaged material. Square refractive index of returned material is arithmetic mean over  regions and  layer_mat. Magnetization (if present) is averaged linearly. 
";


// File: IAbstractParticle_8cpp.xml


// File: IAbstractParticle_8h.xml


// File: IParticle_8cpp.xml


// File: IParticle_8h.xml


// File: MesoCrystal_8cpp.xml


// File: MesoCrystal_8h.xml


// File: Particle_8cpp.xml


// File: Particle_8h.xml


// File: ParticleComposition_8cpp.xml


// File: ParticleComposition_8h.xml


// File: ParticleCoreShell_8cpp.xml


// File: ParticleCoreShell_8h.xml


// File: ParticleDistribution_8cpp.xml


// File: ParticleDistribution_8h.xml


// File: SlicedParticle_8h.xml


// File: MultiLayerFuncs_8cpp.xml


// File: MultiLayerFuncs_8h.xml


// File: ProcessedLayout_8cpp.xml


// File: ProcessedLayout_8h.xml


// File: ProcessedSample_8cpp.xml


// File: ProcessedSample_8h.xml


// File: ProfileHelper_8cpp.xml


// File: ProfileHelper_8h.xml


// File: ILayerRTCoefficients_8h.xml


// File: MatrixRTCoefficients_8cpp.xml


// File: MatrixRTCoefficients_8h.xml


// File: ScalarRTCoefficients_8h.xml


// File: SimulationOptions_8cpp.xml


// File: SimulationOptions_8h.xml


// File: FixedBuilder_8cpp.xml


// File: FixedBuilder_8h.xml


// File: FormFactorComponents_8cpp.xml


// File: FormFactorComponents_8h.xml


// File: FTDistribution2DComponents_8cpp.xml


// File: FTDistribution2DComponents_8h.xml


// File: IRegistry_8h.xml


// File: ISampleBuilder_8cpp.xml


// File: ISampleBuilder_8h.xml


// File: SampleBuilderNode_8cpp.xml


// File: SampleBuilderNode_8h.xml


// File: SampleProvider_8cpp.xml


// File: SampleProvider_8h.xml


// File: FormFactorDecoratorMaterial_8cpp.xml


// File: FormFactorDecoratorMaterial_8h.xml


// File: FormFactorDecoratorPositionFactor_8cpp.xml


// File: FormFactorDecoratorPositionFactor_8h.xml


// File: FormFactorDecoratorRotation_8cpp.xml


// File: FormFactorDecoratorRotation_8h.xml


// File: IBornFF_8cpp.xml


// File: IBornFF_8h.xml


// File: IFormFactor_8cpp.xml


// File: IFormFactor_8h.xml


// File: IFormFactorDecorator_8h.xml


// File: ISampleNode_8cpp.xml


// File: ISampleNode_8h.xml


// File: LayerFillLimits_8cpp.xml


// File: LayerFillLimits_8h.xml


// File: Rotations_8cpp.xml
%feature("docstring")  createProduct "IRotation* createProduct(const IRotation &left, const IRotation &right)

Returns concatenated rotation (first right, then left). 
";


// File: Rotations_8h.xml
%feature("docstring")  createProduct "IRotation* createProduct(const IRotation &left, const IRotation &right)

Returns concatenated rotation (first right, then left). 
";


// File: ZLimits_8cpp.xml
%feature("docstring")  MinLimit "OneSidedLimit MinLimit(const OneSidedLimit &left, const OneSidedLimit &right)
";

%feature("docstring")  MaxLimit "OneSidedLimit MaxLimit(const OneSidedLimit &left, const OneSidedLimit &right)
";

%feature("docstring")  ConvexHull "ZLimits ConvexHull(const ZLimits &left, const ZLimits &right)
";


// File: ZLimits_8h.xml
%feature("docstring")  MinLimit "OneSidedLimit MinLimit(const OneSidedLimit &left, const OneSidedLimit &right)
";

%feature("docstring")  MaxLimit "OneSidedLimit MaxLimit(const OneSidedLimit &left, const OneSidedLimit &right)
";

%feature("docstring")  ConvexHull "ZLimits ConvexHull(const ZLimits &left, const ZLimits &right)
";


// File: Box_8cpp.xml


// File: Box_8h.xml


// File: DoubleEllipse_8cpp.xml


// File: DoubleEllipse_8h.xml


// File: IShape3D_8cpp.xml
%feature("docstring")  RectangleVertices "std::vector<kvector_t> RectangleVertices(double length, double width, double z)

Helper functions to construct lists of vertices

Generate vertices of centered rectangle at height z 
";

%feature("docstring")  EllipseVertices "std::vector<kvector_t> EllipseVertices(double r_x, double r_y, double z)

Generate vertices of centered ellipse with given semi-axes at height z. 
";


// File: IShape3D_8h.xml
%feature("docstring")  RectangleVertices "std::vector<kvector_t> RectangleVertices(double length, double width, double z)

Helper functions to construct lists of vertices

Generate vertices of centered rectangle at height z 
";

%feature("docstring")  EllipseVertices "std::vector<kvector_t> EllipseVertices(double r_x, double r_y, double z)

Generate vertices of centered ellipse with given semi-axes at height z. 
";


// File: RippleCosine_8cpp.xml


// File: RippleCosine_8h.xml


// File: RippleSawtooth_8cpp.xml


// File: RippleSawtooth_8h.xml


// File: TruncatedEllipsoid_8cpp.xml


// File: TruncatedEllipsoid_8h.xml


// File: KzComputation_8cpp.xml


// File: KzComputation_8h.xml


// File: LayerInterface_8cpp.xml


// File: LayerInterface_8h.xml


// File: LayerRoughness_8cpp.xml


// File: LayerRoughness_8h.xml


// File: Slice_8cpp.xml


// File: Slice_8h.xml


// File: SlicedFormFactorList_8cpp.xml


// File: SlicedFormFactorList_8h.xml


// File: FormFactorGauss_8cpp.xml


// File: FormFactorGauss_8h.xml


// File: FormFactorSphereGaussianRadius_8cpp.xml


// File: FormFactorSphereGaussianRadius_8h.xml


// File: FormFactorSphereLogNormalRadius_8cpp.xml


// File: FormFactorSphereLogNormalRadius_8h.xml


// File: SoftParticles_8h.xml


// File: ISpecularStrategy_8h.xml


// File: SpecularMagneticNCStrategy_8cpp.xml


// File: SpecularMagneticNCStrategy_8h.xml


// File: SpecularMagneticStrategy_8cpp.xml


// File: SpecularMagneticStrategy_8h.xml


// File: SpecularMagneticTanhStrategy_8cpp.xml


// File: SpecularMagneticTanhStrategy_8h.xml


// File: SpecularScalarNCStrategy_8cpp.xml


// File: SpecularScalarNCStrategy_8h.xml


// File: SpecularScalarStrategy_8cpp.xml


// File: SpecularScalarStrategy_8h.xml


// File: SpecularScalarTanhStrategy_8cpp.xml


// File: SpecularScalarTanhStrategy_8h.xml


// File: SpecularStrategyBuilder_8cpp.xml


// File: SpecularStrategyBuilder_8h.xml


// File: BoxCompositionBuilder_8cpp.xml


// File: BoxCompositionBuilder_8h.xml


// File: BoxesSquareLatticeBuilder_8cpp.xml


// File: BoxesSquareLatticeBuilder_8h.xml


// File: CoreShellParticleBuilder_8cpp.xml


// File: CoreShellParticleBuilder_8h.xml


// File: CustomMorphologyBuilder_8cpp.xml


// File: CustomMorphologyBuilder_8h.xml


// File: CylindersAndPrismsBuilder_8cpp.xml


// File: CylindersAndPrismsBuilder_8h.xml


// File: CylindersBuilder_8cpp.xml


// File: CylindersBuilder_8h.xml


// File: FeNiBilayerBuilder_8cpp.xml


// File: FeNiBilayerBuilder_8h.xml


// File: HomogeneousMultilayerBuilder_8cpp.xml


// File: HomogeneousMultilayerBuilder_8h.xml


// File: LatticeBuilder_8cpp.xml


// File: LatticeBuilder_8h.xml


// File: LayersWithAbsorptionBuilder_8cpp.xml


// File: LayersWithAbsorptionBuilder_8h.xml


// File: LayersWithAbsorptionBySLDBuilder_8cpp.xml
%feature("docstring")  middle_layer_thickness "const double middle_layer_thickness(60.0 *Units::nm)
";


// File: LayersWithAbsorptionBySLDBuilder_8h.xml


// File: MagneticLayersBuilder_8cpp.xml


// File: MagneticLayersBuilder_8h.xml


// File: MagneticParticlesBuilder_8cpp.xml


// File: MagneticParticlesBuilder_8h.xml


// File: MesoCrystalBuilder_8cpp.xml


// File: MesoCrystalBuilder_8h.xml


// File: MultiLayerWithNCRoughnessBuilder_8cpp.xml


// File: MultiLayerWithNCRoughnessBuilder_8h.xml


// File: MultiLayerWithRoughnessBuilder_8cpp.xml


// File: MultiLayerWithRoughnessBuilder_8h.xml


// File: MultipleLayoutBuilder_8cpp.xml


// File: MultipleLayoutBuilder_8h.xml


// File: ParaCrystalBuilder_8cpp.xml


// File: ParaCrystalBuilder_8h.xml


// File: ParticleCompositionBuilder_8cpp.xml


// File: ParticleCompositionBuilder_8h.xml


// File: ParticleDistributionsBuilder_8cpp.xml


// File: ParticleDistributionsBuilder_8h.xml


// File: ParticleInVacuumBuilder_8cpp.xml


// File: ParticleInVacuumBuilder_8h.xml


// File: PercusYevickBuilder_8cpp.xml


// File: PercusYevickBuilder_8h.xml


// File: PlainMultiLayerBySLDBuilder_8cpp.xml


// File: PlainMultiLayerBySLDBuilder_8h.xml


// File: ReferenceMaterials_8h.xml


// File: ResonatorBuilder_8cpp.xml


// File: ResonatorBuilder_8h.xml


// File: RipplesBuilder_8cpp.xml


// File: RipplesBuilder_8h.xml


// File: RotatedPyramidsBuilder_8cpp.xml


// File: RotatedPyramidsBuilder_8h.xml


// File: SampleBuilderFactory_8cpp.xml


// File: SampleBuilderFactory_8h.xml


// File: SizeDistributionModelsBuilder_8cpp.xml


// File: SizeDistributionModelsBuilder_8h.xml


// File: SlicedCompositionBuilder_8cpp.xml


// File: SlicedCompositionBuilder_8h.xml


// File: SlicedCylindersBuilder_8cpp.xml


// File: SlicedCylindersBuilder_8h.xml


// File: ThickAbsorptiveSampleBuilder_8cpp.xml


// File: ThickAbsorptiveSampleBuilder_8h.xml


// File: TransformationsBuilder_8cpp.xml


// File: TransformationsBuilder_8h.xml


// File: TwoDimLatticeBuilder_8cpp.xml


// File: TwoDimLatticeBuilder_8h.xml


// File: TwoLayerRoughnessBuilder_8cpp.xml


// File: TwoLayerRoughnessBuilder_8h.xml


// File: dir_220e7f16e10b4e45e27e10ed0346ff0c.xml


// File: dir_7b210e8d28f50f0c519681ee1b473363.xml


// File: dir_c4c8c79bb34eb89326ea47d04b453458.xml


// File: dir_e6ff3e2fec27a07ceb0da6f4d6911ef2.xml


// File: dir_844f24c588eea1b259def164cc466f1a.xml


// File: dir_4517c083a90cc85a9a1560bcd67541e1.xml


// File: dir_da063889c15f3636a66540651967c41d.xml


// File: dir_9a5e0b0e0913dd118bde6961ef93e44c.xml


// File: dir_ed097210e0926370940660d36aeab42a.xml


// File: dir_fba8602a8c23825d875c7205aab8e979.xml


// File: dir_9b633c8be420b8d6b83f5ed5376ef19b.xml


// File: dir_61bfb933e72dfe3586b97d80db501038.xml


// File: dir_ccb77c5fc9fada2051f2fad6bbe3a645.xml


// File: dir_52f00155c6a6846eb7173e2ee1c8b0ff.xml


// File: dir_8f7f72226bf217e57890a767dfa82dfa.xml


// File: dir_d3d78e1a889fb126c8391722741399f0.xml


// File: dir_c4bcd3a441ff6332187b5528d22c5933.xml


// File: dir_7002b98d93049c66d9f454102abc535d.xml


// File: dir_853a8df00e778b87ff55618a6b919e4c.xml


// File: dir_ccd033f493018670b3204f8d6a838d21.xml


// File: dir_4bb6681b49b81f2bef6bc1e3a5b08661.xml


// File: dir_d9d42b37b662547974602e66402128ce.xml

