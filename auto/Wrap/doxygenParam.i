
// File: index.xml

// File: classDistributionCosine.xml
%feature("docstring") DistributionCosine "

Cosine distribution.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionCosine::DistributionCosine "DistributionCosine::DistributionCosine(const std::vector< double > P)
";

%feature("docstring")  DistributionCosine::DistributionCosine "DistributionCosine::DistributionCosine(double mean, double sigma)
";

%feature("docstring")  DistributionCosine::DistributionCosine "DistributionCosine::DistributionCosine()
";

%feature("docstring")  DistributionCosine::clone "DistributionCosine* DistributionCosine::clone() const final
";

%feature("docstring")  DistributionCosine::probabilityDensity "double DistributionCosine::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionCosine::getMean "double DistributionCosine::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionCosine::getSigma "double DistributionCosine::getSigma() const
";

%feature("docstring")  DistributionCosine::equidistantPoints "std::vector< double > DistributionCosine::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionCosine::isDelta "bool DistributionCosine::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionCosine::accept "void DistributionCosine::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";


// File: classDistributionGate.xml
%feature("docstring") DistributionGate "

Uniform distribution function with half width hwhm.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionGate::DistributionGate "DistributionGate::DistributionGate(const std::vector< double > P)
";

%feature("docstring")  DistributionGate::DistributionGate "DistributionGate::DistributionGate(double min, double max)
";

%feature("docstring")  DistributionGate::DistributionGate "DistributionGate::DistributionGate()
";

%feature("docstring")  DistributionGate::clone "DistributionGate* DistributionGate::clone() const final
";

%feature("docstring")  DistributionGate::probabilityDensity "double DistributionGate::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionGate::getMean "double DistributionGate::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionGate::getMin "double DistributionGate::getMin() const
";

%feature("docstring")  DistributionGate::getMax "double DistributionGate::getMax() const
";

%feature("docstring")  DistributionGate::equidistantPoints "std::vector< double > DistributionGate::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

Returns list of sample values. 
";

%feature("docstring")  DistributionGate::isDelta "bool DistributionGate::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionGate::accept "void DistributionGate::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";


// File: classDistributionGaussian.xml
%feature("docstring") DistributionGaussian "

Gaussian distribution with standard deviation std_dev.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionGaussian::DistributionGaussian "DistributionGaussian::DistributionGaussian(const std::vector< double > P)
";

%feature("docstring")  DistributionGaussian::DistributionGaussian "DistributionGaussian::DistributionGaussian(double mean, double std_dev)
";

%feature("docstring")  DistributionGaussian::DistributionGaussian "DistributionGaussian::DistributionGaussian()
";

%feature("docstring")  DistributionGaussian::clone "DistributionGaussian* DistributionGaussian::clone() const final
";

%feature("docstring")  DistributionGaussian::probabilityDensity "double DistributionGaussian::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionGaussian::getMean "double DistributionGaussian::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionGaussian::getStdDev "double DistributionGaussian::getStdDev() const
";

%feature("docstring")  DistributionGaussian::equidistantPoints "std::vector< double > DistributionGaussian::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionGaussian::isDelta "bool DistributionGaussian::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionGaussian::accept "void DistributionGaussian::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";


// File: classDistributionHandler.xml
%feature("docstring") DistributionHandler "

Provides the functionality to average over parameter distributions with weights.

C++ includes: DistributionHandler.h
";

%feature("docstring")  DistributionHandler::DistributionHandler "DistributionHandler::DistributionHandler()
";

%feature("docstring")  DistributionHandler::~DistributionHandler "DistributionHandler::~DistributionHandler()
";

%feature("docstring")  DistributionHandler::addParameterDistribution "void DistributionHandler::addParameterDistribution(const std::string &param_name, const IDistribution1D &distribution, size_t nbr_samples, double sigma_factor=0.0, const RealLimits &limits=RealLimits())

add a sampled parameter distribution 
";

%feature("docstring")  DistributionHandler::addParameterDistribution "void DistributionHandler::addParameterDistribution(const ParameterDistribution &par_distr)
";

%feature("docstring")  DistributionHandler::getTotalNumberOfSamples "size_t DistributionHandler::getTotalNumberOfSamples() const

get the total number of parameter value combinations (product of the individual sizes of each parameter distribution 
";

%feature("docstring")  DistributionHandler::setParameterValues "double DistributionHandler::setParameterValues(ParameterPool *p_parameter_pool, size_t index)

set the parameter values of the simulation object to a specific combination of values, determined by the index (which must be smaller than the total number of combinations) and returns the weight associated with this combination of parameter values 
";

%feature("docstring")  DistributionHandler::setParameterToMeans "void DistributionHandler::setParameterToMeans(ParameterPool *p_parameter_pool) const

Sets mean distribution values to the parameter pool. 
";

%feature("docstring")  DistributionHandler::getDistributions "const DistributionHandler::Distributions_t & DistributionHandler::getDistributions() const
";


// File: classDistributionLogNormal.xml
%feature("docstring") DistributionLogNormal "

Log-normal distribution.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionLogNormal::DistributionLogNormal "DistributionLogNormal::DistributionLogNormal(const std::vector< double > P)
";

%feature("docstring")  DistributionLogNormal::DistributionLogNormal "DistributionLogNormal::DistributionLogNormal(double median, double scale_param)
";

%feature("docstring")  DistributionLogNormal::DistributionLogNormal "DistributionLogNormal::DistributionLogNormal()=delete
";

%feature("docstring")  DistributionLogNormal::clone "DistributionLogNormal* DistributionLogNormal::clone() const final
";

%feature("docstring")  DistributionLogNormal::probabilityDensity "double DistributionLogNormal::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionLogNormal::getMean "double DistributionLogNormal::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionLogNormal::getMedian "double DistributionLogNormal::getMedian() const
";

%feature("docstring")  DistributionLogNormal::getScalePar "double DistributionLogNormal::getScalePar() const
";

%feature("docstring")  DistributionLogNormal::equidistantPoints "std::vector< double > DistributionLogNormal::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionLogNormal::isDelta "bool DistributionLogNormal::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionLogNormal::accept "void DistributionLogNormal::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  DistributionLogNormal::setUnits "void DistributionLogNormal::setUnits(const std::string &units)

Sets distribution units. 
";


// File: classDistributionLorentz.xml
%feature("docstring") DistributionLorentz "

Lorentz distribution with half width hwhm.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionLorentz::DistributionLorentz "DistributionLorentz::DistributionLorentz(const std::vector< double > P)
";

%feature("docstring")  DistributionLorentz::DistributionLorentz "DistributionLorentz::DistributionLorentz(double mean, double hwhm)
";

%feature("docstring")  DistributionLorentz::DistributionLorentz "DistributionLorentz::DistributionLorentz()
";

%feature("docstring")  DistributionLorentz::clone "DistributionLorentz* DistributionLorentz::clone() const final
";

%feature("docstring")  DistributionLorentz::probabilityDensity "double DistributionLorentz::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionLorentz::getMean "double DistributionLorentz::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionLorentz::getHWHM "double DistributionLorentz::getHWHM() const
";

%feature("docstring")  DistributionLorentz::equidistantPoints "std::vector< double > DistributionLorentz::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionLorentz::isDelta "bool DistributionLorentz::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionLorentz::accept "void DistributionLorentz::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";


// File: classDistributionTrapezoid.xml
%feature("docstring") DistributionTrapezoid "

Trapezoidal distribution.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionTrapezoid::DistributionTrapezoid "DistributionTrapezoid::DistributionTrapezoid(const std::vector< double > P)
";

%feature("docstring")  DistributionTrapezoid::DistributionTrapezoid "DistributionTrapezoid::DistributionTrapezoid(double center, double left, double middle, double right)
";

%feature("docstring")  DistributionTrapezoid::DistributionTrapezoid "DistributionTrapezoid::DistributionTrapezoid()
";

%feature("docstring")  DistributionTrapezoid::clone "DistributionTrapezoid* DistributionTrapezoid::clone() const final
";

%feature("docstring")  DistributionTrapezoid::probabilityDensity "double DistributionTrapezoid::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionTrapezoid::getMean "double DistributionTrapezoid::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionTrapezoid::getLeftWidth "double DistributionTrapezoid::getLeftWidth() const
";

%feature("docstring")  DistributionTrapezoid::getMiddleWidth "double DistributionTrapezoid::getMiddleWidth() const
";

%feature("docstring")  DistributionTrapezoid::getRightWidth "double DistributionTrapezoid::getRightWidth() const
";

%feature("docstring")  DistributionTrapezoid::equidistantPoints "std::vector< double > DistributionTrapezoid::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionTrapezoid::isDelta "bool DistributionTrapezoid::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionTrapezoid::accept "void DistributionTrapezoid::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";


// File: classIDistribution1D.xml
%feature("docstring") IDistribution1D "

Interface for one-dimensional distributions.

C++ includes: Distributions.h
";

%feature("docstring")  IDistribution1D::IDistribution1D "IDistribution1D::IDistribution1D(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IDistribution1D::clone "virtual IDistribution1D* IDistribution1D::clone() const =0
";

%feature("docstring")  IDistribution1D::probabilityDensity "virtual double IDistribution1D::probabilityDensity(double x) const =0

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  IDistribution1D::getMean "virtual double IDistribution1D::getMean() const =0

Returns the distribution-specific mean. 
";

%feature("docstring")  IDistribution1D::equidistantSamples "std::vector< ParameterSample > IDistribution1D::equidistantSamples(size_t nbr_samples, double sigma_factor=0., const RealLimits &limits=RealLimits()) const

Returns equidistant samples, using intrinsic parameters, weighted with  probabilityDensity(). 
";

%feature("docstring")  IDistribution1D::equidistantSamplesInRange "std::vector< ParameterSample > IDistribution1D::equidistantSamplesInRange(size_t nbr_samples, double xmin, double xmax) const

Returns equidistant samples from xmin to xmax, weighted with  probabilityDensity(). 
";

%feature("docstring")  IDistribution1D::equidistantPoints "virtual std::vector<double> IDistribution1D::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const =0

Returns equidistant interpolation points, with range computed in distribution-specific way from mean and width parameter, taking into account limits and sigma_factor. 
";

%feature("docstring")  IDistribution1D::equidistantPointsInRange "std::vector< double > IDistribution1D::equidistantPointsInRange(size_t nbr_samples, double xmin, double xmax) const

Returns equidistant interpolation points from xmin to xmax. 
";

%feature("docstring")  IDistribution1D::isDelta "virtual bool IDistribution1D::isDelta() const =0

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  IDistribution1D::setUnits "void IDistribution1D::setUnits(const std::string &units)

Sets distribution units. 
";


// File: classINode.xml
%feature("docstring") INode "

Base class for tree-like structures containing parameterized objects.

C++ includes: INode.h
";

%feature("docstring")  INode::INode "INode::INode()
";

%feature("docstring")  INode::INode "INode::INode(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  INode::~INode "virtual INode::~INode()
";

%feature("docstring")  INode::accept "virtual void INode::accept(INodeVisitor *visitor) const =0

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  INode::treeToString "std::string INode::treeToString() const

Returns multiline string representing tree structure below the node. 
";

%feature("docstring")  INode::registerChild "void INode::registerChild(INode *node)
";

%feature("docstring")  INode::getChildren "std::vector< const INode * > INode::getChildren() const

Returns a vector of children (const). 
";

%feature("docstring")  INode::setParent "void INode::setParent(const INode *newParent)
";

%feature("docstring")  INode::parent "const INode * INode::parent() const
";

%feature("docstring")  INode::parent "INode * INode::parent()
";

%feature("docstring")  INode::copyNumber "int INode::copyNumber(const INode *node) const

Returns copyNumber of child, which takes into account existence of children with same name. 
";

%feature("docstring")  INode::displayName "std::string INode::displayName() const

Returns display name, composed from the name of node and it's copy number. 
";

%feature("docstring")  INode::createParameterTree "ParameterPool * INode::createParameterTree() const

Creates new parameter pool, with all local parameters and those of its children. 
";


// File: classINodeVisitor.xml
%feature("docstring") INodeVisitor "

From visitor pattern to achieve double dispatch.

Visitor interface to visit ISample objects.

C++ includes: INodeVisitor.h
";

%feature("docstring")  INodeVisitor::INodeVisitor "INodeVisitor::INodeVisitor()
";

%feature("docstring")  INodeVisitor::~INodeVisitor "virtual INodeVisitor::~INodeVisitor()
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const BasicLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Beam *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ConstantBackground *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ConvolutionDetectorResolution *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Crystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionCosine *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionGate *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionGaussian *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionLogNormal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionTrapezoid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FootprintGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FootprintSquare *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorAnisoPyramid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorBarGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorBarLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorBox *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCantellatedCube *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCone *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCone6 *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCoreShell *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCuboctahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCylinder *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDWBA *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDWBAPol *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDecoratorMaterial *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDecoratorPositionFactor *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDecoratorRotation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDodecahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDot *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorEllipsoidalCylinder *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorFullSphere *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorFullSpheroid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorGaussSphere *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorHemiEllipsoid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorHollowSphere *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorIcosahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorLongBoxGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorLongBoxLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorPrism3 *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorPrism6 *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorPyramid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCosineRippleBox *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCosineRippleGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCosineRippleLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSawtoothRippleBox *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSawtoothRippleGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSawtoothRippleLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSphereGaussianRadius *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSphereLogNormalRadius *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTetrahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTruncatedCube *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTruncatedSphere *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTruncatedSpheroid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorWeighted *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DTriangle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction2DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction2DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction2DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DCosine *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DGate *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DTriangle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DCone *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DGate *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const GISASSimulation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const HexagonalLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IAbstractParticle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IClusteredParticles *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IdentityRotation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IFormFactor *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IFormFactorBorn *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IFormFactorDecorator *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IInterferenceFunction *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ILayout *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const INode *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Instrument *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction1DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction2DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction2DParaCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction2DSuperLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction3DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionFinite2DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionFinite3DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionHardDisk *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionRadialParaCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionTwin *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionNone *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IParticle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IPeakShape *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IRotation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ISample *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IsGISAXSDetector *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Layer *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const LayerInterface *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const LayerRoughness *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const MesoCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const MultiLayer *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const OffSpecSimulation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Particle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleComposition *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleCoreShell *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleDistribution *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleLayout *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const PoissonNoiseBackground *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RectangularDetector *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ResolutionFunction2DGaussian *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationEuler *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationX *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationY *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationZ *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SpecularDetector1D *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SpecularSimulation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SphericalDetector *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SquareLattice *)
";

%feature("docstring")  INodeVisitor::depth "int INodeVisitor::depth() const

Returns depth of the visitor in the composite hierarchy. 
";

%feature("docstring")  INodeVisitor::setDepth "void INodeVisitor::setDepth(int depth)

Sets depth of the visitor in the composite hierarchy. 
";


// File: classIParameter.xml
%feature("docstring") IParameter "

Pure virtual base class for parameter wrapper classes  RealParameter, ComponentParameter. Holds a pointer to the wrapped parameter, a name, and a callback function to be called when the parameter is changed. This class is templated on the data type of the wrapped parameter.

C++ includes: IParameter.h
";

%feature("docstring")  IParameter::IParameter "IParameter< T >::IParameter()=delete
";

%feature("docstring")  IParameter::IParameter "IParameter< T >::IParameter(const std::string &name, T *data, const std::string &parent_name, const std::function< void()> &onChange)
";

%feature("docstring")  IParameter::~IParameter "virtual IParameter< T >::~IParameter()=default
";

%feature("docstring")  IParameter::clone "virtual IParameter* IParameter< T >::clone(const std::string &new_name=\"\") const =0
";

%feature("docstring")  IParameter::isNull "virtual bool IParameter< T >::isNull() const

Returns true if wrapped parameter was not initialized with proper real value. 
";

%feature("docstring")  IParameter::getData "T& IParameter< T >::getData() const
";

%feature("docstring")  IParameter::setData "void IParameter< T >::setData(T &data)
";

%feature("docstring")  IParameter::hasSameData "bool IParameter< T >::hasSameData(const IParameter &other)

Returns true if two parameters are pointing to the same raw data. 
";

%feature("docstring")  IParameter::getName "const std::string& IParameter< T >::getName() const
";


// File: classIParameterized.xml
%feature("docstring") IParameterized "

Manages a local parameter pool, and a tree of child pools.

C++ includes: IParameterized.h
";

%feature("docstring")  IParameterized::IParameterized "IParameterized::IParameterized(const std::string &name=\"\")
";

%feature("docstring")  IParameterized::IParameterized "IParameterized::IParameterized(const IParameterized &other)
";

%feature("docstring")  IParameterized::~IParameterized "IParameterized::~IParameterized()
";

%feature("docstring")  IParameterized::parameterPool "ParameterPool* IParameterized::parameterPool() const

Returns pointer to the parameter pool. 
";

%feature("docstring")  IParameterized::createParameterTree "ParameterPool * IParameterized::createParameterTree() const

Creates new parameter pool, with all local parameters and those of its children. 
";

%feature("docstring")  IParameterized::parametersToString "std::string IParameterized::parametersToString() const

Returns multiline string representing available parameters. 
";

%feature("docstring")  IParameterized::registerParameter "RealParameter & IParameterized::registerParameter(const std::string &name, double *parpointer)
";

%feature("docstring")  IParameterized::registerVector "void IParameterized::registerVector(const std::string &base_name, kvector_t *p_vec, const std::string &units=\"nm\")
";

%feature("docstring")  IParameterized::setParameterValue "void IParameterized::setParameterValue(const std::string &name, double value)
";

%feature("docstring")  IParameterized::setVectorValue "void IParameterized::setVectorValue(const std::string &base_name, kvector_t value)
";

%feature("docstring")  IParameterized::parameter "RealParameter * IParameterized::parameter(const std::string &name) const

Returns parameter with given 'name'. 
";

%feature("docstring")  IParameterized::onChange "virtual void IParameterized::onChange()

Action to be taken in inherited class when a parameter has changed. 
";

%feature("docstring")  IParameterized::removeParameter "void IParameterized::removeParameter(const std::string &name)
";

%feature("docstring")  IParameterized::removeVector "void IParameterized::removeVector(const std::string &base_name)
";

%feature("docstring")  IParameterized::setName "void IParameterized::setName(const std::string &name)
";

%feature("docstring")  IParameterized::getName "const std::string& IParameterized::getName() const
";


// File: classIterationStrategy.xml
%feature("docstring") IterationStrategy "

Abstract base class for tree traversal strategies, for use in  INodeVisitor.

For definition of different strategies see https://en.wikipedia.org/wiki/Tree_traversal.

C++ includes: IterationStrategy.h
";

%feature("docstring")  IterationStrategy::clone "virtual IterationStrategy* IterationStrategy::clone() const =0
";

%feature("docstring")  IterationStrategy::first "virtual IteratorMemento IterationStrategy::first(const INode *p_root)=0
";

%feature("docstring")  IterationStrategy::next "virtual void IterationStrategy::next(IteratorMemento &iterator_stack) const =0
";

%feature("docstring")  IterationStrategy::isDone "virtual bool IterationStrategy::isDone(IteratorMemento &iterator_stack) const =0
";


// File: classIteratorMemento.xml
%feature("docstring") IteratorMemento "

Holds all iterator states encountered for SampleTreeIterator.

C++ includes: NodeIterator.h
";

%feature("docstring")  IteratorMemento::IteratorMemento "IteratorMemento::IteratorMemento()
";

%feature("docstring")  IteratorMemento::~IteratorMemento "virtual IteratorMemento::~IteratorMemento()
";

%feature("docstring")  IteratorMemento::push_state "void IteratorMemento::push_state(const IteratorState &state)
";

%feature("docstring")  IteratorMemento::pop_state "void IteratorMemento::pop_state()
";

%feature("docstring")  IteratorMemento::get_state "IteratorState& IteratorMemento::get_state()
";

%feature("docstring")  IteratorMemento::empty "bool IteratorMemento::empty() const
";

%feature("docstring")  IteratorMemento::reset "void IteratorMemento::reset()
";

%feature("docstring")  IteratorMemento::getCurrent "const INode* IteratorMemento::getCurrent()
";

%feature("docstring")  IteratorMemento::next "void IteratorMemento::next()
";

%feature("docstring")  IteratorMemento::size "size_t IteratorMemento::size() const
";


// File: classIteratorState.xml
%feature("docstring") IteratorState "

Holds state of iterator at single level for SampleTreeIterator.

C++ includes: NodeIterator.h
";

%feature("docstring")  IteratorState::IteratorState "IteratorState::IteratorState(const INode *single_element)
";

%feature("docstring")  IteratorState::IteratorState "IteratorState::IteratorState(std::vector< const INode *> samples)
";

%feature("docstring")  IteratorState::~IteratorState "virtual IteratorState::~IteratorState()
";

%feature("docstring")  IteratorState::getCurrent "const INode* IteratorState::getCurrent() const
";

%feature("docstring")  IteratorState::isEnd "bool IteratorState::isEnd() const
";

%feature("docstring")  IteratorState::next "void IteratorState::next()
";


// File: classNodeIterator.xml
%feature("docstring") NodeIterator "

Iterator through  INode tree of objects.

Usage example: SampleTreeIterator<Strategy> it(&sample); it.first(); while( !it.is_done() ) {  INode *p_sample = it.get_current(); it.next(); }

C++ includes: NodeIterator.h
";

%feature("docstring")  NodeIterator::NodeIterator "NodeIterator< Strategy >::NodeIterator(const INode *root)
";

%feature("docstring")  NodeIterator::~NodeIterator "virtual NodeIterator< Strategy >::~NodeIterator()
";

%feature("docstring")  NodeIterator::first "void NodeIterator< Strategy >::first()
";

%feature("docstring")  NodeIterator::next "void NodeIterator< Strategy >::next()
";

%feature("docstring")  NodeIterator::getCurrent "const INode * NodeIterator< Strategy >::getCurrent()
";

%feature("docstring")  NodeIterator::isDone "bool NodeIterator< Strategy >::isDone() const
";

%feature("docstring")  NodeIterator::depth "int NodeIterator< Strategy >::depth() const
";


// File: structNodeMeta.xml
%feature("docstring") NodeMeta "

Metadata of one model node.

C++ includes: INode.h
";


// File: structParaMeta.xml
%feature("docstring") ParaMeta "

Metadata of one model parameter.

C++ includes: INode.h
";


// File: classParameterDistribution.xml
%feature("docstring") ParameterDistribution "

A parametric distribution function, for use with any model parameter.

C++ includes: ParameterDistribution.h
";

%feature("docstring")  ParameterDistribution::ParameterDistribution "ParameterDistribution::ParameterDistribution(const std::string &par_name, const IDistribution1D &distribution, size_t nbr_samples, double sigma_factor=0.0, const RealLimits &limits=RealLimits())
";

%feature("docstring")  ParameterDistribution::ParameterDistribution "ParameterDistribution::ParameterDistribution(const std::string &par_name, const IDistribution1D &distribution, size_t nbr_samples, double xmin, double xmax)
";

%feature("docstring")  ParameterDistribution::ParameterDistribution "ParameterDistribution::ParameterDistribution(const ParameterDistribution &other)
";

%feature("docstring")  ParameterDistribution::~ParameterDistribution "ParameterDistribution::~ParameterDistribution()
";

%feature("docstring")  ParameterDistribution::linkParameter "ParameterDistribution & ParameterDistribution::linkParameter(std::string par_name)
";

%feature("docstring")  ParameterDistribution::getMainParameterName "std::string ParameterDistribution::getMainParameterName() const

get the main parameter's name 
";

%feature("docstring")  ParameterDistribution::getNbrSamples "size_t ParameterDistribution::getNbrSamples() const

get number of samples for this distribution 
";

%feature("docstring")  ParameterDistribution::getSigmaFactor "double ParameterDistribution::getSigmaFactor() const

get the sigma factor 
";

%feature("docstring")  ParameterDistribution::getDistribution "const IDistribution1D * ParameterDistribution::getDistribution() const
";

%feature("docstring")  ParameterDistribution::getDistribution "IDistribution1D * ParameterDistribution::getDistribution()
";

%feature("docstring")  ParameterDistribution::generateSamples "std::vector< ParameterSample > ParameterDistribution::generateSamples() const

generate list of sampled values with their weight 
";

%feature("docstring")  ParameterDistribution::getLinkedParameterNames "std::vector<std::string> ParameterDistribution::getLinkedParameterNames() const

get list of linked parameter names 
";

%feature("docstring")  ParameterDistribution::getLimits "RealLimits ParameterDistribution::getLimits() const
";

%feature("docstring")  ParameterDistribution::getMinValue "double ParameterDistribution::getMinValue() const
";

%feature("docstring")  ParameterDistribution::getMaxValue "double ParameterDistribution::getMaxValue() const
";


// File: classParameterPattern.xml
%feature("docstring") ParameterPattern "

Helper class for constructing parameter patterns.

C++ includes: ParameterPattern.h
";

%feature("docstring")  ParameterPattern::ParameterPattern "ParameterPattern::ParameterPattern()
";

%feature("docstring")  ParameterPattern::ParameterPattern "ParameterPattern::ParameterPattern(std::string root_object)
";

%feature("docstring")  ParameterPattern::beginsWith "ParameterPattern & ParameterPattern::beginsWith(std::string start_type)
";

%feature("docstring")  ParameterPattern::add "ParameterPattern & ParameterPattern::add(std::string object_type)
";

%feature("docstring")  ParameterPattern::toStdString "std::string ParameterPattern::toStdString() const
";


// File: classParameterPool.xml
%feature("docstring") ParameterPool "

Container with parameters for  IParameterized object.

C++ includes: ParameterPool.h
";

%feature("docstring")  ParameterPool::ParameterPool "ParameterPool::ParameterPool()

Constructs an empty parameter pool. 
";

%feature("docstring")  ParameterPool::~ParameterPool "ParameterPool::~ParameterPool()
";

%feature("docstring")  ParameterPool::clone "ParameterPool * ParameterPool::clone() const

Returns a literal clone. 
";

%feature("docstring")  ParameterPool::copyToExternalPool "void ParameterPool::copyToExternalPool(const std::string &prefix, ParameterPool *other_pool) const

Copies parameters of given pool to  other pool, prepeding  prefix to the parameter names. 
";

%feature("docstring")  ParameterPool::clear "void ParameterPool::clear()

Clears the parameter map. 
";

%feature("docstring")  ParameterPool::size "size_t ParameterPool::size() const

Returns number of parameters in the pool. 
";

%feature("docstring")  ParameterPool::empty "bool ParameterPool::empty() const
";

%feature("docstring")  ParameterPool::addParameter "RealParameter & ParameterPool::addParameter(RealParameter *newPar)

Adds parameter to the pool, and returns reference to the input pointer.

Returning the input pointer allows us to concatenate function calls like pool->addParameter( new  RealParameter(...) ).setLimits(-1,+1).setFixed().setUnit(\"nm\") 
";

%feature("docstring")  ParameterPool::parameter "RealParameter * ParameterPool::parameter(const std::string &name)

Returns parameter with given  name. 
";

%feature("docstring")  ParameterPool::parameter "const RealParameter * ParameterPool::parameter(const std::string &name) const

Returns parameter with given  name. 
";

%feature("docstring")  ParameterPool::parameters "const std::vector<RealParameter*> ParameterPool::parameters() const

Returns full vector of parameters. 
";

%feature("docstring")  ParameterPool::getMatchedParameters "std::vector< RealParameter * > ParameterPool::getMatchedParameters(const std::string &pattern) const

Returns nonempty vector of parameters that match the  pattern ('*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::getUniqueMatch "RealParameter * ParameterPool::getUniqueMatch(const std::string &pattern) const

Returns the one parameter that matches the  pattern (wildcards '*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::setParameterValue "void ParameterPool::setParameterValue(const std::string &name, double value)

Sets parameter value. 
";

%feature("docstring")  ParameterPool::setMatchedParametersValue "int ParameterPool::setMatchedParametersValue(const std::string &wildcards, double value)

Sets value of the nonzero parameters that match  pattern ('*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::setUniqueMatchValue "void ParameterPool::setUniqueMatchValue(const std::string &pattern, double value)

Sets value of the one parameter that matches  pattern ('*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::parameterNames "std::vector< std::string > ParameterPool::parameterNames() const
";

%feature("docstring")  ParameterPool::removeParameter "void ParameterPool::removeParameter(const std::string &name)

Removes parameter with given name from the pool. 
";


// File: classParameterSample.xml
%feature("docstring") ParameterSample "

A parameter value with a weight, as obtained when sampling from a distribution.

C++ includes: ParameterSample.h
";

%feature("docstring")  ParameterSample::ParameterSample "ParameterSample::ParameterSample(double _value=0., double _weight=1.)
";


// File: classPostorderStrategy.xml
%feature("docstring") PostorderStrategy "

Traverse tree; visit children before their parents.

C++ includes: IterationStrategy.h
";

%feature("docstring")  PostorderStrategy::PostorderStrategy "PostorderStrategy::PostorderStrategy()
";

%feature("docstring")  PostorderStrategy::clone "PostorderStrategy * PostorderStrategy::clone() const
";

%feature("docstring")  PostorderStrategy::first "IteratorMemento PostorderStrategy::first(const INode *p_root)
";

%feature("docstring")  PostorderStrategy::next "void PostorderStrategy::next(IteratorMemento &iterator_stack) const
";

%feature("docstring")  PostorderStrategy::isDone "bool PostorderStrategy::isDone(IteratorMemento &iterator_stack) const
";


// File: classPreorderStrategy.xml
%feature("docstring") PreorderStrategy "

Traverse tree; visit parents before their children.

C++ includes: IterationStrategy.h
";

%feature("docstring")  PreorderStrategy::PreorderStrategy "PreorderStrategy::PreorderStrategy()
";

%feature("docstring")  PreorderStrategy::clone "PreorderStrategy * PreorderStrategy::clone() const
";

%feature("docstring")  PreorderStrategy::first "IteratorMemento PreorderStrategy::first(const INode *p_root)
";

%feature("docstring")  PreorderStrategy::next "void PreorderStrategy::next(IteratorMemento &iterator_stack) const
";

%feature("docstring")  PreorderStrategy::isDone "bool PreorderStrategy::isDone(IteratorMemento &iterator_stack) const
";


// File: classRangedDistribution.xml
%feature("docstring") RangedDistribution "

Interface for one-dimensional ranged distributions. All derived distributions allow for generating samples in-place for known mean and standard deviation (except for  RangedDistributionLorentz which uses median and hwhm).

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistribution::RangedDistribution "RangedDistribution::RangedDistribution()
";

%feature("docstring")  RangedDistribution::RangedDistribution "RangedDistribution::RangedDistribution(size_t n_samples, double sigma_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistribution::RangedDistribution "RangedDistribution::RangedDistribution(size_t n_samples, double sigma_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  sigma_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistribution::clone "RangedDistribution* RangedDistribution::clone() const override=0
";

%feature("docstring")  RangedDistribution::~RangedDistribution "RangedDistribution::~RangedDistribution() override
";

%feature("docstring")  RangedDistribution::generateSamples "std::vector< ParameterSample > RangedDistribution::generateSamples(double mean, double stddev) const
";

%feature("docstring")  RangedDistribution::generateSamples "std::vector< std::vector< ParameterSample > > RangedDistribution::generateSamples(const std::vector< double > &mean, const std::vector< double > &stddev) const

Generates list of sampled values with their weights from given means and standard deviations. 
";

%feature("docstring")  RangedDistribution::distribution "std::unique_ptr< IDistribution1D > RangedDistribution::distribution(double mean, double stddev) const

Public interface function to underlying  IDistribution1D object. 
";

%feature("docstring")  RangedDistribution::limits "RealLimits RangedDistribution::limits() const

Returns current limits of the distribution. 
";

%feature("docstring")  RangedDistribution::sigmaFactor "double RangedDistribution::sigmaFactor() const

Returns sigma factor to use during sampling. 
";

%feature("docstring")  RangedDistribution::nSamples "size_t RangedDistribution::nSamples() const

Returns number of samples to generate. 
";

%feature("docstring")  RangedDistribution::setLimits "void RangedDistribution::setLimits(const RealLimits &limits)
";

%feature("docstring")  RangedDistribution::pyString "std::string RangedDistribution::pyString() const

Prints python-formatted definition of the distribution. 
";


// File: classRangedDistributionCosine.xml
%feature("docstring") RangedDistributionCosine "

Cosine distribution.

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistributionCosine::RangedDistributionCosine "RangedDistributionCosine::RangedDistributionCosine()
";

%feature("docstring")  RangedDistributionCosine::RangedDistributionCosine "RangedDistributionCosine::RangedDistributionCosine(size_t n_samples, double sigma_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistributionCosine::RangedDistributionCosine "RangedDistributionCosine::RangedDistributionCosine(size_t n_samples, double sigma_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  sigma_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistributionCosine::clone "RangedDistributionCosine * RangedDistributionCosine::clone() const override
";

%feature("docstring")  RangedDistributionCosine::~RangedDistributionCosine "RangedDistributionCosine::~RangedDistributionCosine() override=default
";


// File: classRangedDistributionGate.xml
%feature("docstring") RangedDistributionGate "

Uniform distribution function.

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistributionGate::RangedDistributionGate "RangedDistributionGate::RangedDistributionGate()
";

%feature("docstring")  RangedDistributionGate::RangedDistributionGate "RangedDistributionGate::RangedDistributionGate(size_t n_samples, double sigma_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistributionGate::RangedDistributionGate "RangedDistributionGate::RangedDistributionGate(size_t n_samples, double sigma_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  sigma_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistributionGate::clone "RangedDistributionGate * RangedDistributionGate::clone() const override
";

%feature("docstring")  RangedDistributionGate::~RangedDistributionGate "RangedDistributionGate::~RangedDistributionGate() override=default
";


// File: classRangedDistributionGaussian.xml
%feature("docstring") RangedDistributionGaussian "

Gaussian distribution with standard deviation std_dev.

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistributionGaussian::RangedDistributionGaussian "RangedDistributionGaussian::RangedDistributionGaussian()
";

%feature("docstring")  RangedDistributionGaussian::RangedDistributionGaussian "RangedDistributionGaussian::RangedDistributionGaussian(size_t n_samples, double sigma_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistributionGaussian::RangedDistributionGaussian "RangedDistributionGaussian::RangedDistributionGaussian(size_t n_samples, double sigma_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  sigma_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistributionGaussian::clone "RangedDistributionGaussian * RangedDistributionGaussian::clone() const override
";

%feature("docstring")  RangedDistributionGaussian::~RangedDistributionGaussian "RangedDistributionGaussian::~RangedDistributionGaussian() override=default
";


// File: classRangedDistributionLogNormal.xml
%feature("docstring") RangedDistributionLogNormal "

Log-normal distribution.

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistributionLogNormal::RangedDistributionLogNormal "RangedDistributionLogNormal::RangedDistributionLogNormal()
";

%feature("docstring")  RangedDistributionLogNormal::RangedDistributionLogNormal "RangedDistributionLogNormal::RangedDistributionLogNormal(size_t n_samples, double sigma_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistributionLogNormal::RangedDistributionLogNormal "RangedDistributionLogNormal::RangedDistributionLogNormal(size_t n_samples, double sigma_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  sigma_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistributionLogNormal::clone "RangedDistributionLogNormal * RangedDistributionLogNormal::clone() const override
";

%feature("docstring")  RangedDistributionLogNormal::~RangedDistributionLogNormal "RangedDistributionLogNormal::~RangedDistributionLogNormal() override=default
";


// File: classRangedDistributionLorentz.xml
%feature("docstring") RangedDistributionLorentz "

Lorentz distribution with median and hwhm.

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistributionLorentz::RangedDistributionLorentz "RangedDistributionLorentz::RangedDistributionLorentz()
";

%feature("docstring")  RangedDistributionLorentz::RangedDistributionLorentz "RangedDistributionLorentz::RangedDistributionLorentz(size_t n_samples, double hwhm_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistributionLorentz::RangedDistributionLorentz "RangedDistributionLorentz::RangedDistributionLorentz(size_t n_samples, double hwhm_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  hwhm_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistributionLorentz::clone "RangedDistributionLorentz * RangedDistributionLorentz::clone() const override
";

%feature("docstring")  RangedDistributionLorentz::~RangedDistributionLorentz "RangedDistributionLorentz::~RangedDistributionLorentz() override=default
";


// File: classRealParameter.xml
%feature("docstring") RealParameter "

Wraps a parameter of type double. In addition to name and on-change callback held by the parent class  IParameter, this class holds Limits, Attributes (currently only fixed or not), and a  Unit.

C++ includes: RealParameter.h
";

%feature("docstring")  RealParameter::RealParameter "RealParameter::RealParameter(const std::string &name, double *par, const std::string &parent_name=\"\", const std::function< void()> &onChange=std::function< void()>(), const RealLimits &limits=RealLimits::limitless(), const Attributes &attr=Attributes::free())
";

%feature("docstring")  RealParameter::~RealParameter "virtual RealParameter::~RealParameter()=default
";

%feature("docstring")  RealParameter::clone "RealParameter * RealParameter::clone(const std::string &new_name=\"\") const
";

%feature("docstring")  RealParameter::setValue "void RealParameter::setValue(double value)

Sets value of wrapped parameter and emit signal. 
";

%feature("docstring")  RealParameter::value "double RealParameter::value() const

Returns value of wrapped parameter. 
";

%feature("docstring")  RealParameter::setLimits "RealParameter & RealParameter::setLimits(const RealLimits &limits)
";

%feature("docstring")  RealParameter::limits "RealLimits RealParameter::limits() const
";

%feature("docstring")  RealParameter::setLimited "RealParameter & RealParameter::setLimited(double lower, double upper)
";

%feature("docstring")  RealParameter::setPositive "RealParameter & RealParameter::setPositive()
";

%feature("docstring")  RealParameter::setNonnegative "RealParameter & RealParameter::setNonnegative()
";

%feature("docstring")  RealParameter::setUnit "RealParameter & RealParameter::setUnit(const std::string &name)
";

%feature("docstring")  RealParameter::unit "std::string RealParameter::unit() const
";


// File: classUnit.xml
%feature("docstring") Unit "

A physical unit.

C++ includes: Unit.h
";

%feature("docstring")  Unit::Unit "Unit::Unit(const std::string &name=\"\")
";

%feature("docstring")  Unit::setUnit "void Unit::setUnit(const std::string &name)
";

%feature("docstring")  Unit::getName "const std::string& Unit::getName() const
";


// File: namespace_0D12.xml


// File: namespace_0D16.xml


// File: namespace_0D24.xml


// File: namespace_0D29.xml


// File: namespaceNodeUtils.xml
%feature("docstring")  NodeUtils::nodeToString "std::string NodeUtils::nodeToString(const INode &node)

Returns multiline string representing tree structure starting from given node. 
";

%feature("docstring")  NodeUtils::nodePath "std::string NodeUtils::nodePath(const INode &node, const INode *root=nullptr)

Returns path composed of node's displayName, with respect to root node. 
";


// File: namespaceParameterUtils.xml
%feature("docstring")  ParameterUtils::isAngleRelated "bool ParameterUtils::isAngleRelated(const std::string &par_name)

Returns true if given parameter name is related to angles. 
";

%feature("docstring")  ParameterUtils::poolParameterUnits "std::string ParameterUtils::poolParameterUnits(const IParameterized &node, const std::string &parName)

Returns units of main parameter. 
";


// File: namespacepyfmt.xml
%feature("docstring")  pyfmt::printRealLimits "std::string pyfmt::printRealLimits(const RealLimits &limits, const std::string &units)
";

%feature("docstring")  pyfmt::printRealLimitsArg "std::string pyfmt::printRealLimitsArg(const RealLimits &limits, const std::string &units)

Prints RealLimits in the form of argument (in the context of  ParameterDistribution and similar). Default RealLimits will not be printed, any other will be printed as \", ba.RealLimits.limited(1*deg, 2*deg)\" 
";


// File: IParameter_8h.xml


// File: IParameterized_8cpp.xml


// File: IParameterized_8h.xml


// File: IterationStrategy_8cpp.xml


// File: IterationStrategy_8h.xml


// File: ParameterPool_8cpp.xml


// File: ParameterPool_8h.xml


// File: RealParameter_8cpp.xml


// File: RealParameter_8h.xml


// File: Unit_8h.xml


// File: DistributionHandler_8cpp.xml


// File: DistributionHandler_8h.xml


// File: Distributions_8cpp.xml


// File: Distributions_8h.xml


// File: ParameterDistribution_8cpp.xml


// File: ParameterDistribution_8h.xml


// File: RangedDistributions_8cpp.xml


// File: RangedDistributions_8h.xml


// File: INode_8cpp.xml
%feature("docstring")  nodeMetaUnion "NodeMeta nodeMetaUnion(const std::vector< ParaMeta > &base, const NodeMeta &other)
";


// File: INode_8h.xml
%feature("docstring")  nodeMetaUnion "NodeMeta nodeMetaUnion(const std::vector< ParaMeta > &base, const NodeMeta &other)
";


// File: INodeVisitor_8cpp.xml
%feature("docstring")  VisitNodesPreorder "void VisitNodesPreorder(const INode &node, INodeVisitor &visitor)
";

%feature("docstring")  VisitNodesPostorder "void VisitNodesPostorder(const INode &node, INodeVisitor &visitor)
";


// File: INodeVisitor_8h.xml
%feature("docstring")  VisitNodesPreorder "void VisitNodesPreorder(const INode &node, INodeVisitor &visitor)
";

%feature("docstring")  VisitNodesPostorder "void VisitNodesPostorder(const INode &node, INodeVisitor &visitor)
";


// File: NodeIterator_8cpp.xml


// File: NodeIterator_8h.xml


// File: NodeUtils_8cpp.xml


// File: NodeUtils_8h.xml


// File: ParameterPattern_8cpp.xml


// File: ParameterPattern_8h.xml


// File: ParameterSample_8h.xml


// File: ParameterUtils_8cpp.xml


// File: ParameterUtils_8h.xml


// File: PyFmtLimits_8cpp.xml


// File: PyFmtLimits_8h.xml


// File: dir_a1f38e94e849d0203a55ad5a19f2f15a.xml


// File: dir_dabc42ad3745509abd3a496944bb880e.xml


// File: dir_a98fb20d64e2aea67a6e042d91197081.xml


// File: dir_d452a16c8784395bb8c21da516e88a7f.xml


// File: dir_dda74d2e7a2b62d18fb900593a370493.xml

