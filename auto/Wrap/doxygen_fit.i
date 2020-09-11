
// File: index.xml

// File: classAlgorithmInfo.xml
%feature("docstring") AlgorithmInfo "

A name and a description.

C++ includes: MinimizerInfo.h
";

%feature("docstring")  AlgorithmInfo::AlgorithmInfo "AlgorithmInfo::AlgorithmInfo()=delete
";

%feature("docstring")  AlgorithmInfo::AlgorithmInfo "AlgorithmInfo::AlgorithmInfo(const std::string &itemName, const std::string &itemDescription)
";

%feature("docstring")  AlgorithmInfo::name "std::string AlgorithmInfo::name() const
";

%feature("docstring")  AlgorithmInfo::description "std::string AlgorithmInfo::description() const
";


// File: classAttLimits.xml
%feature("docstring") AttLimits "

Attributes and limits of a fit parameter, and coupling between these properties.

C++ includes: AttLimits.h
";

%feature("docstring")  AttLimits::AttLimits "AttLimits::AttLimits()
";

%feature("docstring")  AttLimits::isFixed "bool AttLimits::isFixed() const
";

%feature("docstring")  AttLimits::isLimited "bool AttLimits::isLimited() const
";

%feature("docstring")  AttLimits::isUpperLimited "bool AttLimits::isUpperLimited() const
";

%feature("docstring")  AttLimits::isLowerLimited "bool AttLimits::isLowerLimited() const
";

%feature("docstring")  AttLimits::isLimitless "bool AttLimits::isLimitless() const
";

%feature("docstring")  AttLimits::lowerLimit "double AttLimits::lowerLimit() const
";

%feature("docstring")  AttLimits::upperLimit "double AttLimits::upperLimit() const
";

%feature("docstring")  AttLimits::setFixed "void AttLimits::setFixed(bool isFixed)
";

%feature("docstring")  AttLimits::toString "std::string AttLimits::toString() const
";


// File: classAttributes.xml
%feature("docstring") Attributes "

Attributes for a fit parameter. Currently, the only attribute is fixed/free.

C++ includes: Attributes.h
";

%feature("docstring")  Attributes::Attributes "Attributes::Attributes()
";

%feature("docstring")  Attributes::setFixed "void Attributes::setFixed(bool is_fixed)
";

%feature("docstring")  Attributes::isFixed "bool Attributes::isFixed() const
";

%feature("docstring")  Attributes::isFree "bool Attributes::isFree() const
";


// File: classFitOptions.xml
%feature("docstring") FitOptions "

General fitting options.

C++ includes: FitOptions.h
";

%feature("docstring")  FitOptions::FitOptions "FitOptions::FitOptions()
";

%feature("docstring")  FitOptions::derivEpsilon "double FitOptions::derivEpsilon() const
";

%feature("docstring")  FitOptions::setDerivEpsilon "void FitOptions::setDerivEpsilon(double deriv_epsilon)
";

%feature("docstring")  FitOptions::stepFactor "double FitOptions::stepFactor() const
";

%feature("docstring")  FitOptions::setStepFactor "void FitOptions::setStepFactor(double step_factor)
";


// File: classGeneticMinimizer.xml
%feature("docstring") GeneticMinimizer "

Wrapper for the CERN ROOT Genetic minimizer.

C++ includes: GeneticMinimizer.h
";

%feature("docstring")  GeneticMinimizer::GeneticMinimizer "GeneticMinimizer::GeneticMinimizer()
";

%feature("docstring")  GeneticMinimizer::~GeneticMinimizer "GeneticMinimizer::~GeneticMinimizer()
";

%feature("docstring")  GeneticMinimizer::setTolerance "void GeneticMinimizer::setTolerance(double value)

Sets tolerance on the function value at the minimum. Minimization will stop when the estimated vertical distance to the minimum (EDM) is less than 0.001*tolerance*ErrorDef. Here ErrorDef=1.0 for chi squared fit and ErrorDef=0.5 for negative log likelihood fit. 
";

%feature("docstring")  GeneticMinimizer::tolerance "double GeneticMinimizer::tolerance() const
";

%feature("docstring")  GeneticMinimizer::setPrintLevel "void GeneticMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. 
";

%feature("docstring")  GeneticMinimizer::printLevel "int GeneticMinimizer::printLevel() const
";

%feature("docstring")  GeneticMinimizer::setMaxIterations "void GeneticMinimizer::setMaxIterations(int value)

Sets maximum number of iterations to try at each step. 
";

%feature("docstring")  GeneticMinimizer::maxIterations "int GeneticMinimizer::maxIterations() const
";

%feature("docstring")  GeneticMinimizer::setPopulationSize "void GeneticMinimizer::setPopulationSize(int value)

Sets population size. 
";

%feature("docstring")  GeneticMinimizer::populationSize "int GeneticMinimizer::populationSize() const
";

%feature("docstring")  GeneticMinimizer::setRandomSeed "void GeneticMinimizer::setRandomSeed(int value)

Sets random seed. 
";

%feature("docstring")  GeneticMinimizer::randomSeed "int GeneticMinimizer::randomSeed() const
";

%feature("docstring")  GeneticMinimizer::statusToString "std::string GeneticMinimizer::statusToString() const override

Returns string representation of current minimizer status. 
";

%feature("docstring")  GeneticMinimizer::statusMap "std::map< std::string, std::string > GeneticMinimizer::statusMap() const override

Returns map of string representing different minimizer statuses. 
";


// File: classGSLLevenbergMarquardtMinimizer.xml
%feature("docstring") GSLLevenbergMarquardtMinimizer "

It's a facade to ROOT::Math::GSLNLSMinimizer which, in turn, is a facade to the actual GSL's gsl_multifit_fdfsolver_type (http://www.gnu.org/software/gsl/manual/html_node/Nonlinear-Least_002dSquares-Fitting.html).

C++ includes: GSLLevenbergMarquardtMinimizer.h
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::GSLLevenbergMarquardtMinimizer "GSLLevenbergMarquardtMinimizer::GSLLevenbergMarquardtMinimizer()
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::~GSLLevenbergMarquardtMinimizer "GSLLevenbergMarquardtMinimizer::~GSLLevenbergMarquardtMinimizer() override
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::setTolerance "void GSLLevenbergMarquardtMinimizer::setTolerance(double value)

Sets tolerance on the function value at the minimum. 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::tolerance "double GSLLevenbergMarquardtMinimizer::tolerance() const
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::setPrintLevel "void GSLLevenbergMarquardtMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::printLevel "int GSLLevenbergMarquardtMinimizer::printLevel() const
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::setMaxIterations "void GSLLevenbergMarquardtMinimizer::setMaxIterations(int value)

Sets maximum number of iterations. This is an internal minimizer setting which has no direct relation to the number of objective function calls (e.g. numberOfIteraction=5 might correspond to ~100 objective function calls). 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::maxIterations "int GSLLevenbergMarquardtMinimizer::maxIterations() const
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::statusToString "std::string GSLLevenbergMarquardtMinimizer::statusToString() const override

Returns string representation of current minimizer status. 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::statusMap "std::map< std::string, std::string > GSLLevenbergMarquardtMinimizer::statusMap() const override

Returns map of string representing different minimizer statuses. 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::requiresResiduals "bool GSLLevenbergMarquardtMinimizer::requiresResiduals() override

Returns true if minimizer computations are residual-based, false otherwise. 
";


// File: classGSLMultiMinimizer.xml
%feature("docstring") GSLMultiMinimizer "

Wrapper for the CERN ROOT facade of the GSL multi minimizer family (gradient descent based).

C++ includes: GSLMultiMinimizer.h
";

%feature("docstring")  GSLMultiMinimizer::GSLMultiMinimizer "GSLMultiMinimizer::GSLMultiMinimizer(const std::string &algorithmName=\"ConjugateFR\")
";

%feature("docstring")  GSLMultiMinimizer::~GSLMultiMinimizer "GSLMultiMinimizer::~GSLMultiMinimizer()
";

%feature("docstring")  GSLMultiMinimizer::setPrintLevel "void GSLMultiMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. 
";

%feature("docstring")  GSLMultiMinimizer::printLevel "int GSLMultiMinimizer::printLevel() const
";

%feature("docstring")  GSLMultiMinimizer::setMaxIterations "void GSLMultiMinimizer::setMaxIterations(int value)

Sets maximum number of iterations. This is an internal minimizer setting which has no direct relation to the number of objective function calls (e.g. numberOfIteraction=5 might correspond to ~100 objective function calls). 
";

%feature("docstring")  GSLMultiMinimizer::maxIterations "int GSLMultiMinimizer::maxIterations() const
";

%feature("docstring")  GSLMultiMinimizer::statusToString "std::string GSLMultiMinimizer::statusToString() const override

Returns string representation of current minimizer status. 
";


// File: classIFactory.xml
%feature("docstring") IFactory "

Base class for all factories.

C++ includes: IFactory.h
";

%feature("docstring")  IFactory::createItem "AbstractProduct* IFactory< Key, AbstractProduct >::createItem(const Key &item_key) const

Creates object by calling creation function corresponded to given identifier. 
";

%feature("docstring")  IFactory::createItemPtr "std::unique_ptr<AbstractProduct> IFactory< Key, AbstractProduct >::createItemPtr(const Key &item_key) const
";

%feature("docstring")  IFactory::registerItem "bool IFactory< Key, AbstractProduct >::registerItem(const Key &item_key, CreateItemCallback CreateFn)

Registers object's creation function. 
";

%feature("docstring")  IFactory::contains "bool IFactory< Key, AbstractProduct >::contains(const Key &item_key) const
";

%feature("docstring")  IFactory::size "size_t IFactory< Key, AbstractProduct >::size() const

Returns number of registered objects. 
";


// File: classFit_1_1IFunctionAdapter.xml
%feature("docstring") Fit::IFunctionAdapter "

Base class for objective function adapters, which converts user functions to minimize into the function which minimization machinery expects.

C++ includes: IFunctionAdapter.h
";

%feature("docstring")  Fit::IFunctionAdapter::IFunctionAdapter "IFunctionAdapter::IFunctionAdapter()
";

%feature("docstring")  Fit::IFunctionAdapter::~IFunctionAdapter "IFunctionAdapter::~IFunctionAdapter()
";

%feature("docstring")  Fit::IFunctionAdapter::numberOfCalls "int IFunctionAdapter::numberOfCalls() const
";

%feature("docstring")  Fit::IFunctionAdapter::numberOfGradientCalls "int IFunctionAdapter::numberOfGradientCalls() const
";


// File: classIMinimizer.xml
%feature("docstring") IMinimizer "

Pure virtual interface for all kind minimizers.

C++ includes: IMinimizer.h
";

%feature("docstring")  IMinimizer::IMinimizer "IMinimizer::IMinimizer()
";

%feature("docstring")  IMinimizer::~IMinimizer "IMinimizer::~IMinimizer()
";

%feature("docstring")  IMinimizer::IMinimizer "IMinimizer::IMinimizer(const IMinimizer &other)=delete
";

%feature("docstring")  IMinimizer::minimizerName "virtual std::string IMinimizer::minimizerName() const =0

return name of the minimizer 
";

%feature("docstring")  IMinimizer::algorithmName "virtual std::string IMinimizer::algorithmName() const =0

return name of the minimization algorithm 
";

%feature("docstring")  IMinimizer::minimize_scalar "Fit::MinimizerResult IMinimizer::minimize_scalar(fcn_scalar_t, Fit::Parameters)

run minimization 
";

%feature("docstring")  IMinimizer::minimize_residual "Fit::MinimizerResult IMinimizer::minimize_residual(fcn_residual_t, Fit::Parameters)
";

%feature("docstring")  IMinimizer::clear "virtual void IMinimizer::clear()

clear resources (parameters) for consecutives minimizations 
";

%feature("docstring")  IMinimizer::minValue "double IMinimizer::minValue() const

Returns minimum function value. 
";

%feature("docstring")  IMinimizer::setOptions "void IMinimizer::setOptions(const std::string &options)

Sets option string to the minimizer. 
";

%feature("docstring")  IMinimizer::requiresResiduals "virtual bool IMinimizer::requiresResiduals()

Returns true if minimizer computations are residual-based, false otherwise. 
";


// File: classFit_1_1Kernel.xml
%feature("docstring") Fit::Kernel "

A main class to run fitting.

C++ includes: Kernel.h
";

%feature("docstring")  Fit::Kernel::Kernel "Kernel::Kernel()
";

%feature("docstring")  Fit::Kernel::~Kernel "Kernel::~Kernel()
";

%feature("docstring")  Fit::Kernel::setMinimizer "void Kernel::setMinimizer(const std::string &minimizerName, const std::string &algorithmName=\"\", const std::string &options=\"\")
";

%feature("docstring")  Fit::Kernel::setMinimizer "void Kernel::setMinimizer(IMinimizer *minimizer)
";

%feature("docstring")  Fit::Kernel::minimize "MinimizerResult Kernel::minimize(fcn_scalar_t fcn, const Parameters &parameters)
";

%feature("docstring")  Fit::Kernel::minimize "MinimizerResult Kernel::minimize(fcn_residual_t fcn, const Parameters &parameters)
";


// File: classFit_1_1Minimizer.xml
%feature("docstring") Fit::Minimizer "

A main class to run fitting.

C++ includes: Minimizer.h
";

%feature("docstring")  Fit::Minimizer::Minimizer "Minimizer::Minimizer()
";

%feature("docstring")  Fit::Minimizer::~Minimizer "Minimizer::~Minimizer()
";

%feature("docstring")  Fit::Minimizer::setMinimizer "void Minimizer::setMinimizer(const std::string &minimizerName, const std::string &algorithmName=\"\", const std::string &options=\"\")
";

%feature("docstring")  Fit::Minimizer::setMinimizer "void Minimizer::setMinimizer(IMinimizer *minimizer)
";

%feature("docstring")  Fit::Minimizer::minimize "MinimizerResult Minimizer::minimize(fcn_scalar_t fcn, const Parameters &parameters)
";

%feature("docstring")  Fit::Minimizer::minimize "MinimizerResult Minimizer::minimize(fcn_residual_t fcn, const Parameters &parameters)
";

%feature("docstring")  Fit::Minimizer::minimize "MinimizerResult Minimizer::minimize(PyCallback &callback, const Parameters &parameters)

Finds minimum of user objective function (to be called from Python). 
";


// File: classMinimizerCatalog.xml
%feature("docstring") MinimizerCatalog "

Hard-coded information about all minimizers available.

C++ includes: MinimizerCatalog.h
";

%feature("docstring")  MinimizerCatalog::MinimizerCatalog "MinimizerCatalog::MinimizerCatalog()
";

%feature("docstring")  MinimizerCatalog::toString "std::string MinimizerCatalog::toString() const

Returns multiline string representing catalog content. 
";

%feature("docstring")  MinimizerCatalog::minimizerNames "std::vector< std::string > MinimizerCatalog::minimizerNames() const
";

%feature("docstring")  MinimizerCatalog::algorithmNames "std::vector< std::string > MinimizerCatalog::algorithmNames(const std::string &minimizerName) const

Returns list of algorithms defined for the minimizer with a given name. 
";

%feature("docstring")  MinimizerCatalog::algorithmDescriptions "std::vector< std::string > MinimizerCatalog::algorithmDescriptions(const std::string &minimizerName) const

Returns list of algorithm's descriptions for the minimizer with a given name . 
";

%feature("docstring")  MinimizerCatalog::minimizerInfo "const MinimizerInfo & MinimizerCatalog::minimizerInfo(const std::string &minimizerName) const

Returns info for minimizer with given name. 
";


// File: classMinimizerFactory.xml
%feature("docstring") MinimizerFactory "

Factory to create minimizers.

C++ includes: MinimizerFactory.h
";


// File: classMinimizerInfo.xml
%feature("docstring") MinimizerInfo "

Info about a minimizer, including list of defined minimization algorithms.

C++ includes: MinimizerInfo.h
";

%feature("docstring")  MinimizerInfo::MinimizerInfo "MinimizerInfo::MinimizerInfo()=delete
";

%feature("docstring")  MinimizerInfo::MinimizerInfo "MinimizerInfo::MinimizerInfo(const std::string &minimizerType, const std::string &minimizerDescription)
";

%feature("docstring")  MinimizerInfo::setAlgorithmName "void MinimizerInfo::setAlgorithmName(const std::string &algorithmName)

Sets currently active algorithm. 
";

%feature("docstring")  MinimizerInfo::name "std::string MinimizerInfo::name() const
";

%feature("docstring")  MinimizerInfo::description "std::string MinimizerInfo::description() const
";

%feature("docstring")  MinimizerInfo::algorithmName "std::string MinimizerInfo::algorithmName() const
";

%feature("docstring")  MinimizerInfo::algorithmNames "std::vector< std::string > MinimizerInfo::algorithmNames() const

Return list of defined algorithm names. 
";

%feature("docstring")  MinimizerInfo::algorithmDescriptions "std::vector< std::string > MinimizerInfo::algorithmDescriptions() const

Returns list of string with description of all available algorithms. 
";


// File: classMinimizerOptions.xml
%feature("docstring") MinimizerOptions "

Collection of internal minimizer settings.

C++ includes: MinimizerOptions.h
";

%feature("docstring")  MinimizerOptions::toOptionString "std::string MinimizerOptions::toOptionString() const

Returns string with all options (i.e. \"Strategy=1;Tolerance=0.01;\") 
";

%feature("docstring")  MinimizerOptions::setOptionString "void MinimizerOptions::setOptionString(const std::string &options)

Set options from their string representation. 
";


// File: classFit_1_1MinimizerResult.xml
%feature("docstring") Fit::MinimizerResult "

Result of minimization round.

C++ includes: MinimizerResult.h
";

%feature("docstring")  Fit::MinimizerResult::MinimizerResult "MinimizerResult::MinimizerResult()
";

%feature("docstring")  Fit::MinimizerResult::setParameters "void MinimizerResult::setParameters(const Parameters &parameters)
";

%feature("docstring")  Fit::MinimizerResult::parameters "Parameters MinimizerResult::parameters() const
";

%feature("docstring")  Fit::MinimizerResult::setMinValue "void MinimizerResult::setMinValue(double value)
";

%feature("docstring")  Fit::MinimizerResult::minValue "double MinimizerResult::minValue() const

Minimum value of objective function found by minimizer. 
";

%feature("docstring")  Fit::MinimizerResult::toString "std::string MinimizerResult::toString() const

Returns multi-line string representing minimization results. 
";

%feature("docstring")  Fit::MinimizerResult::setReport "void MinimizerResult::setReport(const std::string &value)
";

%feature("docstring")  Fit::MinimizerResult::setDuration "void MinimizerResult::setDuration(double value)
";

%feature("docstring")  Fit::MinimizerResult::setNumberOfCalls "void MinimizerResult::setNumberOfCalls(int value)
";

%feature("docstring")  Fit::MinimizerResult::setNumberOfGradientCalls "void MinimizerResult::setNumberOfGradientCalls(int value)
";


// File: classMinimizerTestPlan.xml
%feature("docstring") MinimizerTestPlan "

Defines objective function to fit, expected minimum, initial fit parameters and expected values of fit parameters at minimum.

C++ includes: MinimizerTestPlan.h
";

%feature("docstring")  MinimizerTestPlan::MinimizerTestPlan "MinimizerTestPlan::MinimizerTestPlan(const std::string &name)
";

%feature("docstring")  MinimizerTestPlan::~MinimizerTestPlan "MinimizerTestPlan::~MinimizerTestPlan()
";

%feature("docstring")  MinimizerTestPlan::addParameter "void MinimizerTestPlan::addParameter(const Fit::Parameter &param, double expected_value, double tolerance=0.01)
";

%feature("docstring")  MinimizerTestPlan::name "std::string MinimizerTestPlan::name() const
";

%feature("docstring")  MinimizerTestPlan::checkMinimizer "virtual bool MinimizerTestPlan::checkMinimizer(Fit::Minimizer &minimizer)=0

Runs minimization and check minimization result. 
";


// File: classMinuit2Minimizer.xml
%feature("docstring") Minuit2Minimizer "

Wrapper for the CERN ROOT facade of the Minuit2 minimizer. See Minuit2 user manual https://root.cern.ch/root/htmldoc/guides/minuit2/Minuit2.pdf.

C++ includes: Minuit2Minimizer.h
";

%feature("docstring")  Minuit2Minimizer::Minuit2Minimizer "Minuit2Minimizer::Minuit2Minimizer(const std::string &algorithmName=\"Migrad\")
";

%feature("docstring")  Minuit2Minimizer::~Minuit2Minimizer "Minuit2Minimizer::~Minuit2Minimizer()
";

%feature("docstring")  Minuit2Minimizer::setStrategy "void Minuit2Minimizer::setStrategy(int value)

Sets minimization strategy (0-low, 1-medium, 2-high minimization quality). At low quality number of function calls will be economized. 
";

%feature("docstring")  Minuit2Minimizer::strategy "int Minuit2Minimizer::strategy() const
";

%feature("docstring")  Minuit2Minimizer::setErrorDefinition "void Minuit2Minimizer::setErrorDefinition(double value)

Sets error definition factor for parameter error calculation. If objective function (OF) is the usual chisquare function and if the user wants the usual one-standard-deviation errors, then the error definition should be 1.0. If OF is a negative-log-likelihood function, then 0.5. If OF is a chisquare, but the user wants two-standard-deviation errors, 4.0. 
";

%feature("docstring")  Minuit2Minimizer::errorDefinition "double Minuit2Minimizer::errorDefinition() const
";

%feature("docstring")  Minuit2Minimizer::setTolerance "void Minuit2Minimizer::setTolerance(double value)

Sets tolerance on the function value at the minimum. Minimization will stop when the estimated vertical distance to the minimum (EDM) is less than 0.001*tolerance*ErrorDef. Here ErrorDef=1.0 for chi squared fit and ErrorDef=0.5 for negative log likelihood fit. 
";

%feature("docstring")  Minuit2Minimizer::tolerance "double Minuit2Minimizer::tolerance() const
";

%feature("docstring")  Minuit2Minimizer::setPrecision "void Minuit2Minimizer::setPrecision(double value)

Sets relative floating point arithmetic precision. Should be adjusted when the user knows that objectiove function value is not calculated to the nominal machine accuracy. Typical values are between 10^-5 and 10^-14. 
";

%feature("docstring")  Minuit2Minimizer::precision "double Minuit2Minimizer::precision() const
";

%feature("docstring")  Minuit2Minimizer::setPrintLevel "void Minuit2Minimizer::setPrintLevel(int value)

Sets minimizer internal print level. Default value is 0 (silent). 
";

%feature("docstring")  Minuit2Minimizer::printLevel "int Minuit2Minimizer::printLevel() const
";

%feature("docstring")  Minuit2Minimizer::setMaxFunctionCalls "void Minuit2Minimizer::setMaxFunctionCalls(int value)

Sets maximum number of objective function calls. 
";

%feature("docstring")  Minuit2Minimizer::maxFunctionCalls "int Minuit2Minimizer::maxFunctionCalls() const
";

%feature("docstring")  Minuit2Minimizer::statusToString "std::string Minuit2Minimizer::statusToString() const override

Returns string representation of current minimizer status. 
";

%feature("docstring")  Minuit2Minimizer::statusMap "std::map< std::string, std::string > Minuit2Minimizer::statusMap() const override

Returns map of string representing different minimizer statuses. 
";

%feature("docstring")  Minuit2Minimizer::requiresResiduals "bool Minuit2Minimizer::requiresResiduals() override

Returns true if minimizer computations are residual-based, false otherwise. 
";


// File: classMultiOption.xml
%feature("docstring") MultiOption "

Stores a single option for minimization algorithm. Int, double, string values are available. Relies on boost::variant, will be switched to std::variant in C++-17.

C++ includes: MultiOption.h
";

%feature("docstring")  MultiOption::MultiOption "MultiOption::MultiOption(const std::string &name=\"\")
";

%feature("docstring")  MultiOption::MultiOption "MultiOption::MultiOption(const std::string &name, const T &t, const std::string &descripion=\"\")
";

%feature("docstring")  MultiOption::name "std::string MultiOption::name() const
";

%feature("docstring")  MultiOption::description "std::string MultiOption::description() const
";

%feature("docstring")  MultiOption::setDescription "void MultiOption::setDescription(const std::string &description)
";

%feature("docstring")  MultiOption::value "MultiOption::variant_t & MultiOption::value()
";

%feature("docstring")  MultiOption::defaultValue "MultiOption::variant_t & MultiOption::defaultValue()
";

%feature("docstring")  MultiOption::get "T MultiOption::get() const

Returns the option's value. 
";

%feature("docstring")  MultiOption::getDefault "T MultiOption::getDefault() const

Returns the option's default value (i.e. used during construction) 
";

%feature("docstring")  MultiOption::setFromString "void MultiOption::setFromString(const std::string &value)

Sets the value of option from string. TODO find more elegant way (without if/else and boost::lexical_cast 
";


// File: classFit_1_1ObjectiveFunctionAdapter.xml
%feature("docstring") Fit::ObjectiveFunctionAdapter "

Converts user objective function to function ROOT expects. Handles time of life of function objects.

C++ includes: ObjectiveFunctionAdapter.h
";

%feature("docstring")  Fit::ObjectiveFunctionAdapter::ObjectiveFunctionAdapter "ObjectiveFunctionAdapter::ObjectiveFunctionAdapter()
";

%feature("docstring")  Fit::ObjectiveFunctionAdapter::~ObjectiveFunctionAdapter "ObjectiveFunctionAdapter::~ObjectiveFunctionAdapter()
";

%feature("docstring")  Fit::ObjectiveFunctionAdapter::rootObjectiveFunction "const RootScalarFunction * ObjectiveFunctionAdapter::rootObjectiveFunction(fcn_scalar_t fcn, const Parameters &parameters)
";

%feature("docstring")  Fit::ObjectiveFunctionAdapter::rootResidualFunction "const RootResidualFunction * ObjectiveFunctionAdapter::rootResidualFunction(fcn_residual_t fcn, const Parameters &parameters)
";

%feature("docstring")  Fit::ObjectiveFunctionAdapter::numberOfCalls "int ObjectiveFunctionAdapter::numberOfCalls() const
";

%feature("docstring")  Fit::ObjectiveFunctionAdapter::numberOfGradientCalls "int ObjectiveFunctionAdapter::numberOfGradientCalls() const
";


// File: classOptionContainer.xml
%feature("docstring") OptionContainer "

Stores multi option (int,double,string) in a container.

C++ includes: OptionContainer.h
";

%feature("docstring")  OptionContainer::OptionContainer "OptionContainer::OptionContainer()
";

%feature("docstring")  OptionContainer::OptionContainer "OptionContainer::OptionContainer(const OptionContainer &other)

Returns true if option with such name already exists. 
";

%feature("docstring")  OptionContainer::addOption "OptionContainer::option_t OptionContainer::addOption(const std::string &optionName, T value, const std::string &description=\"\")
";

%feature("docstring")  OptionContainer::option "OptionContainer::option_t OptionContainer::option(const std::string &optionName)
";

%feature("docstring")  OptionContainer::option "const OptionContainer::option_t OptionContainer::option(const std::string &optionName) const
";

%feature("docstring")  OptionContainer::optionValue "T OptionContainer::optionValue(const std::string &optionName) const
";

%feature("docstring")  OptionContainer::setOptionValue "void OptionContainer::setOptionValue(const std::string &optionName, T value)

Sets the value of option. Option should hold same value type already. 
";

%feature("docstring")  OptionContainer::begin "iterator OptionContainer::begin()
";

%feature("docstring")  OptionContainer::begin "const_iterator OptionContainer::begin() const
";

%feature("docstring")  OptionContainer::end "iterator OptionContainer::end()
";

%feature("docstring")  OptionContainer::end "const_iterator OptionContainer::end() const
";

%feature("docstring")  OptionContainer::size "size_t OptionContainer::size() const
";


// File: classFit_1_1Parameter.xml
%feature("docstring") Fit::Parameter "

A fittable parameter with value, error, step, and limits.

C++ includes: Parameter.h
";

%feature("docstring")  Fit::Parameter::Parameter "Parameter::Parameter()
";

%feature("docstring")  Fit::Parameter::Parameter "Parameter::Parameter(const std::string &name, double value, const AttLimits &limits=AttLimits::limitless(), double step=0.0)

Fit parameter constructor.

Parameters:
-----------

name: 
unique name of fit parameters

value: 
starting value of fit parameter

limits: 
fit parameter limits

step: 
initial step of fit parameter during the minimization, will be calculated automatically, if zero. 
";

%feature("docstring")  Fit::Parameter::name "std::string Parameter::name() const
";

%feature("docstring")  Fit::Parameter::startValue "double Parameter::startValue() const
";

%feature("docstring")  Fit::Parameter::limits "AttLimits Parameter::limits() const
";

%feature("docstring")  Fit::Parameter::value "double Parameter::value() const
";

%feature("docstring")  Fit::Parameter::setValue "void Parameter::setValue(double value)
";

%feature("docstring")  Fit::Parameter::step "double Parameter::step() const
";

%feature("docstring")  Fit::Parameter::error "double Parameter::error() const
";

%feature("docstring")  Fit::Parameter::setError "void Parameter::setError(double value)
";


// File: classParameterPlan.xml
%feature("docstring") ParameterPlan "

Defines initial settings of single fit parameter and the final value which has to be found in the course of the fit.

C++ includes: ParameterPlan.h
";

%feature("docstring")  ParameterPlan::ParameterPlan "ParameterPlan::ParameterPlan(const Fit::Parameter &param, double expected_value, double tolerance=0.01)
";

%feature("docstring")  ParameterPlan::fitParameter "Fit::Parameter ParameterPlan::fitParameter() const
";

%feature("docstring")  ParameterPlan::expectedValue "double ParameterPlan::expectedValue() const
";

%feature("docstring")  ParameterPlan::tolerance "double ParameterPlan::tolerance() const
";

%feature("docstring")  ParameterPlan::setTolerance "void ParameterPlan::setTolerance(double tolerance)
";


// File: classFit_1_1Parameters.xml
%feature("docstring") Fit::Parameters "

A collection of fit parameters.

C++ includes: Parameters.h
";

%feature("docstring")  Fit::Parameters::Parameters "Fit::Parameters::Parameters()=default
";

%feature("docstring")  Fit::Parameters::add "void Parameters::add(const Parameter &par)
";

%feature("docstring")  Fit::Parameters::begin "Parameters::const_iterator Parameters::begin() const
";

%feature("docstring")  Fit::Parameters::end "Parameters::const_iterator Parameters::end() const
";

%feature("docstring")  Fit::Parameters::begin "Parameters::iterator Parameters::begin()
";

%feature("docstring")  Fit::Parameters::end "Parameters::iterator Parameters::end()
";

%feature("docstring")  Fit::Parameters::size "size_t Parameters::size() const
";

%feature("docstring")  Fit::Parameters::values "std::vector< double > Parameters::values() const
";

%feature("docstring")  Fit::Parameters::setValues "void Parameters::setValues(const std::vector< double > &values)
";

%feature("docstring")  Fit::Parameters::errors "std::vector< double > Parameters::errors() const
";

%feature("docstring")  Fit::Parameters::setErrors "void Parameters::setErrors(const std::vector< double > &errors)
";

%feature("docstring")  Fit::Parameters::correlationMatrix "Parameters::corr_matrix_t Parameters::correlationMatrix() const
";

%feature("docstring")  Fit::Parameters::setCorrelationMatrix "void Parameters::setCorrelationMatrix(const corr_matrix_t &matrix)
";

%feature("docstring")  Fit::Parameters::freeParameterCount "size_t Parameters::freeParameterCount() const

Returns number of free parameters. 
";


// File: classPyCallback.xml
%feature("docstring") PyCallback "

Base class to wrap Python callable and pass it to C++. Used in swig interface file, intended to be overloaded from Python.

C++ includes: PyCallback.h
";

%feature("docstring")  PyCallback::PyCallback "PyCallback::PyCallback(CallbackType callback_type=SCALAR)
";

%feature("docstring")  PyCallback::~PyCallback "PyCallback::~PyCallback()
";

%feature("docstring")  PyCallback::callback_type "PyCallback::CallbackType PyCallback::callback_type() const
";

%feature("docstring")  PyCallback::call_scalar "double PyCallback::call_scalar(Fit::Parameters pars)

Call Python callable and returns its result. Intended to be overloaded in Python.

Parameters:
-----------

pars: 
 Fit parameters object (intentionally passed by value).

value of objective function. 
";

%feature("docstring")  PyCallback::call_residuals "std::vector< double > PyCallback::call_residuals(Fit::Parameters)

Call Python callable and returns its result. Intended to be overloaded in Python.

Parameters:
-----------

pars: 
 Fit parameters object (intentionally passed by value).

vector of residuals 
";


// File: classRealLimits.xml
%feature("docstring") RealLimits "

Limits for a real fit parameter.

C++ includes: RealLimits.h
";

%feature("docstring")  RealLimits::RealLimits "RealLimits::RealLimits()
";

%feature("docstring")  RealLimits::hasLowerLimit "bool RealLimits::hasLowerLimit() const

if has lower limit 
";

%feature("docstring")  RealLimits::lowerLimit "double RealLimits::lowerLimit() const

Returns lower limit. 
";

%feature("docstring")  RealLimits::setLowerLimit "void RealLimits::setLowerLimit(double value)

Sets lower limit. 
";

%feature("docstring")  RealLimits::removeLowerLimit "void RealLimits::removeLowerLimit()

remove lower limit 
";

%feature("docstring")  RealLimits::hasUpperLimit "bool RealLimits::hasUpperLimit() const

if has upper limit 
";

%feature("docstring")  RealLimits::upperLimit "double RealLimits::upperLimit() const

Returns upper limit. 
";

%feature("docstring")  RealLimits::setUpperLimit "void RealLimits::setUpperLimit(double value)

Sets upper limit. 
";

%feature("docstring")  RealLimits::removeUpperLimit "void RealLimits::removeUpperLimit()

remove upper limit 
";

%feature("docstring")  RealLimits::hasLowerAndUpperLimits "bool RealLimits::hasLowerAndUpperLimits() const

if has lower and upper limit 
";

%feature("docstring")  RealLimits::setLimits "void RealLimits::setLimits(double xmin, double xmax)

Sets lower and upper limits. 
";

%feature("docstring")  RealLimits::removeLimits "void RealLimits::removeLimits()

remove limits 
";

%feature("docstring")  RealLimits::isInRange "bool RealLimits::isInRange(double value) const

returns true if proposed value is in limits range 
";

%feature("docstring")  RealLimits::toString "std::string RealLimits::toString() const
";

%feature("docstring")  RealLimits::isLimitless "bool RealLimits::isLimitless() const
";

%feature("docstring")  RealLimits::isPositive "bool RealLimits::isPositive() const
";

%feature("docstring")  RealLimits::isNonnegative "bool RealLimits::isNonnegative() const
";

%feature("docstring")  RealLimits::isLowerLimited "bool RealLimits::isLowerLimited() const
";

%feature("docstring")  RealLimits::isUpperLimited "bool RealLimits::isUpperLimited() const
";

%feature("docstring")  RealLimits::isLimited "bool RealLimits::isLimited() const
";


// File: classFit_1_1ResidualFunctionAdapter.xml
%feature("docstring") Fit::ResidualFunctionAdapter "

Provides  RootResidualFunction which will be minimizer by ROOT. Converts ROOT calls to the call of fcn_residual_t.

C++ includes: ResidualFunctionAdapter.h
";

%feature("docstring")  Fit::ResidualFunctionAdapter::ResidualFunctionAdapter "ResidualFunctionAdapter::ResidualFunctionAdapter(fcn_residual_t func, const Parameters &parameters)
";

%feature("docstring")  Fit::ResidualFunctionAdapter::rootResidualFunction "const RootResidualFunction * ResidualFunctionAdapter::rootResidualFunction()
";


// File: classRootMinimizerAdapter.xml
%feature("docstring") RootMinimizerAdapter "

Pure virtual interface that adapts the CERN ROOT minimizer to our  IMinimizer.

C++ includes: RootMinimizerAdapter.h
";

%feature("docstring")  RootMinimizerAdapter::~RootMinimizerAdapter "RootMinimizerAdapter::~RootMinimizerAdapter() override
";

%feature("docstring")  RootMinimizerAdapter::minimize_scalar "MinimizerResult RootMinimizerAdapter::minimize_scalar(fcn_scalar_t fcn, Fit::Parameters parameters) override

run minimization 
";

%feature("docstring")  RootMinimizerAdapter::minimize_residual "MinimizerResult RootMinimizerAdapter::minimize_residual(fcn_residual_t fcn, Fit::Parameters parameters) override
";

%feature("docstring")  RootMinimizerAdapter::minimizerName "std::string RootMinimizerAdapter::minimizerName() const override final

Returns name of the minimizer. 
";

%feature("docstring")  RootMinimizerAdapter::algorithmName "std::string RootMinimizerAdapter::algorithmName() const override final

Returns name of the minimization algorithm. 
";

%feature("docstring")  RootMinimizerAdapter::setParameters "void RootMinimizerAdapter::setParameters(const Fit::Parameters &parameters)
";

%feature("docstring")  RootMinimizerAdapter::minValue "double RootMinimizerAdapter::minValue() const override final

Returns minimum function value. 
";

%feature("docstring")  RootMinimizerAdapter::options "MinimizerOptions& RootMinimizerAdapter::options()
";

%feature("docstring")  RootMinimizerAdapter::options "const MinimizerOptions& RootMinimizerAdapter::options() const
";

%feature("docstring")  RootMinimizerAdapter::statusToString "std::string RootMinimizerAdapter::statusToString() const

Returns string representation of current minimizer status. 
";

%feature("docstring")  RootMinimizerAdapter::providesError "bool RootMinimizerAdapter::providesError() const

Returns true if minimizer provides error and error matrix. 
";

%feature("docstring")  RootMinimizerAdapter::statusMap "std::map< std::string, std::string > RootMinimizerAdapter::statusMap() const

Returns map of string representing different minimizer statuses. 
";

%feature("docstring")  RootMinimizerAdapter::setOptions "void RootMinimizerAdapter::setOptions(const std::string &optionString) override final

Sets option string to the minimizer. 
";


// File: classRootResidualFunction.xml
%feature("docstring") RootResidualFunction "

Minimizer function with access to single data element residuals, required by Fumili2 and GSLMultiMin minimizers.

C++ includes: RootResidualFunction.h
";

%feature("docstring")  RootResidualFunction::RootResidualFunction "RootResidualFunction::RootResidualFunction(scalar_function_t objective_fun, gradient_function_t gradient_fun, size_t npars, size_t ndatasize)

Constructs  RootResidualFunction

Parameters:
-----------

fun_gradient: 
user function to call

npars: 
number of fit parameters

ndatasize: 
number of residual elements in dataset 
";

%feature("docstring")  RootResidualFunction::Type "RootResidualFunction::Type_t RootResidualFunction::Type() const override
";

%feature("docstring")  RootResidualFunction::Clone "ROOT::Math::IMultiGenFunction * RootResidualFunction::Clone() const override
";

%feature("docstring")  RootResidualFunction::DataElement "double RootResidualFunction::DataElement(const double *pars, unsigned int index, double *gradients=0) const override

Evaluation of single data element residual. Will be called by ROOT minimizer.

Returns residual value for given data element index. Transform call of ancient pointer based function to safer gradient_function_t.

Parameters:
-----------

pars: 
array of fit parameter values from the minimizer

index: 
index of residual element

gradients: 
if not zero, then array where we have to put gradients

value of residual for given data element index 
";


// File: classRootScalarFunction.xml
%feature("docstring") RootScalarFunction "

The chi2 function for use in minimizers.

C++ includes: RootScalarFunction.h
";

%feature("docstring")  RootScalarFunction::RootScalarFunction "RootScalarFunction::RootScalarFunction(root_scalar_t fcn, int ndims)
";


// File: classFit_1_1ScalarFunctionAdapter.xml
%feature("docstring") Fit::ScalarFunctionAdapter "

Converts user objective function to chi2 like function which ROOT expects.

More precisely, ROOT call to std::function<double(const double*)> will cause the call of user function std::function<double(std::vector<double>)>, where function input parameters will be current values fit parameters.

C++ includes: ScalarFunctionAdapter.h
";

%feature("docstring")  Fit::ScalarFunctionAdapter::ScalarFunctionAdapter "ScalarFunctionAdapter::ScalarFunctionAdapter(fcn_scalar_t func, const Parameters &parameters)
";

%feature("docstring")  Fit::ScalarFunctionAdapter::rootObjectiveFunction "const RootScalarFunction * ScalarFunctionAdapter::rootObjectiveFunction()
";


// File: classSimAnMinimizer.xml
%feature("docstring") SimAnMinimizer "

Wrapper for the CERN ROOT facade of the GSL simmulated annealing minimizer.

C++ includes: SimAnMinimizer.h
";

%feature("docstring")  SimAnMinimizer::SimAnMinimizer "SimAnMinimizer::SimAnMinimizer()
";

%feature("docstring")  SimAnMinimizer::~SimAnMinimizer "SimAnMinimizer::~SimAnMinimizer() override
";

%feature("docstring")  SimAnMinimizer::setPrintLevel "void SimAnMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. Default value is 0 (silent). 
";

%feature("docstring")  SimAnMinimizer::printLevel "int SimAnMinimizer::printLevel() const
";

%feature("docstring")  SimAnMinimizer::setMaxIterations "void SimAnMinimizer::setMaxIterations(int value)

Sets maximum number of iterations to try at each step. 
";

%feature("docstring")  SimAnMinimizer::maxIterations "int SimAnMinimizer::maxIterations() const
";

%feature("docstring")  SimAnMinimizer::setIterationsAtEachTemp "void SimAnMinimizer::setIterationsAtEachTemp(int value)

Sets number of iterations at each temperature. 
";

%feature("docstring")  SimAnMinimizer::iterationsAtEachTemp "int SimAnMinimizer::iterationsAtEachTemp() const
";

%feature("docstring")  SimAnMinimizer::setStepSize "void SimAnMinimizer::setStepSize(double value)

Sets max step size used in random walk. 
";

%feature("docstring")  SimAnMinimizer::stepSize "double SimAnMinimizer::stepSize() const
";

%feature("docstring")  SimAnMinimizer::setBoltzmannK "void SimAnMinimizer::setBoltzmannK(double value)

Sets Boltzmann distribution parameter: k. 
";

%feature("docstring")  SimAnMinimizer::boltzmannK "double SimAnMinimizer::boltzmannK() const
";

%feature("docstring")  SimAnMinimizer::setBoltzmannInitialTemp "void SimAnMinimizer::setBoltzmannInitialTemp(double value)

Sets Boltzmann distribution parameter: initial temperature. 
";

%feature("docstring")  SimAnMinimizer::boltzmannInitialTemp "double SimAnMinimizer::boltzmannInitialTemp() const
";

%feature("docstring")  SimAnMinimizer::setBoltzmannMu "void SimAnMinimizer::setBoltzmannMu(double value)

Sets Boltzmann distribution parameter: mu. 
";

%feature("docstring")  SimAnMinimizer::boltzmannMu "double SimAnMinimizer::boltzmannMu() const
";

%feature("docstring")  SimAnMinimizer::setBoltzmannMinTemp "void SimAnMinimizer::setBoltzmannMinTemp(double value)

Sets Boltzmann distribution parameter: minimal temperature. 
";

%feature("docstring")  SimAnMinimizer::boltzmannMinTemp "double SimAnMinimizer::boltzmannMinTemp() const
";

%feature("docstring")  SimAnMinimizer::statusMap "std::map< std::string, std::string > SimAnMinimizer::statusMap() const override

Returns map of string representing different minimizer statuses. 
";


// File: classTestMinimizer.xml
%feature("docstring") TestMinimizer "

A trivial minimizer that calls the objective function once. Used to test the whole chain.

C++ includes: TestMinimizer.h
";

%feature("docstring")  TestMinimizer::TestMinimizer "TestMinimizer::TestMinimizer()
";

%feature("docstring")  TestMinimizer::~TestMinimizer "TestMinimizer::~TestMinimizer() override
";

%feature("docstring")  TestMinimizer::minimizerName "std::string TestMinimizer::minimizerName() const final

return name of the minimizer 
";

%feature("docstring")  TestMinimizer::algorithmName "std::string TestMinimizer::algorithmName() const final

return name of the minimization algorithm 
";

%feature("docstring")  TestMinimizer::minimize_scalar "MinimizerResult TestMinimizer::minimize_scalar(fcn_scalar_t fcn, Fit::Parameters parameters) override

run minimization 
";


// File: classWallclockTimer.xml
%feature("docstring") WallclockTimer "

A timer for measuring real (wall-clock) time spent between 'start' and 'stop' commands.

C++ includes: WallclockTimer.h
";

%feature("docstring")  WallclockTimer::WallclockTimer "WallclockTimer::WallclockTimer()
";

%feature("docstring")  WallclockTimer::~WallclockTimer "WallclockTimer::~WallclockTimer()
";

%feature("docstring")  WallclockTimer::start "void WallclockTimer::start()
";

%feature("docstring")  WallclockTimer::stop "void WallclockTimer::stop()
";

%feature("docstring")  WallclockTimer::runTime "double WallclockTimer::runTime() const

returns run time in sec. 
";


// File: structWallclockTimerState.xml
%feature("docstring") WallclockTimerState "

Internal state of a  WallclockTimer object. 
";


// File: namespace_0d11.xml


// File: namespace_0d25.xml


// File: namespace_0d29.xml


// File: namespace_0d31.xml


// File: namespace_0d35.xml


// File: namespace_0d37.xml


// File: namespace_0d4.xml


// File: namespace_0d41.xml


// File: namespaceFit.xml


// File: namespaceMinimizerResultUtils.xml
%feature("docstring")  MinimizerResultUtils::reportToString "std::string MinimizerResultUtils::reportToString(const RootMinimizerAdapter &minimizer)

Reports results of minimization in the form of multi-line string. 
";

%feature("docstring")  MinimizerResultUtils::reportParameters "std::string MinimizerResultUtils::reportParameters(const Fit::Parameters &parameters)

Reports fit parameters settings and final results. 
";


// File: namespaceMinimizerUtils.xml
%feature("docstring")  MinimizerUtils::toString "std::string MinimizerUtils::toString(const std::vector< std::string > &v, const std::string &delim=\"\")
";

%feature("docstring")  MinimizerUtils::gslErrorDescriptionMap "std::map< int, std::string > MinimizerUtils::gslErrorDescriptionMap()

Returns translation of GSL error code to string. 
";

%feature("docstring")  MinimizerUtils::gslErrorDescription "std::string MinimizerUtils::gslErrorDescription(int errorCode)
";

%feature("docstring")  MinimizerUtils::numbersDiffer "bool MinimizerUtils::numbersDiffer(double a, double b, double tol)
";

%feature("docstring")  MinimizerUtils::sectionString "std::string MinimizerUtils::sectionString(const std::string &sectionName=\"\", size_t report_width=80)

Returns horizontal line of 80 characters length with section name in it. 
";


// File: namespaceNumeric.xml
%feature("docstring")  Numeric::AreAlmostEqual "bool BA_CORE_API_ Numeric::AreAlmostEqual(double a, double b, double tolerance)

Returns true if two doubles agree within epsilon*tolerance. 
";

%feature("docstring")  Numeric::GetAbsoluteDifference "double BA_CORE_API_ Numeric::GetAbsoluteDifference(double a, double b)

Returns the absolute value of the difference between a and b. 
";

%feature("docstring")  Numeric::GetRelativeDifference "double BA_CORE_API_ Numeric::GetRelativeDifference(double a, double b)

Returns the safe relative difference, which is 2(|a-b|)/(|a|+|b|) except in special cases. 
";

%feature("docstring")  Numeric::GetLogDifference "double BA_CORE_API_ Numeric::GetLogDifference(double a, double b)

Returns the difference of the logarithm; input values are truncated at the minimum positive value 
";


// File: namespaceROOT.xml


// File: namespaceROOT_1_1Math.xml


// File: namespaceROOT_1_1Minuit2.xml


// File: namespaceStringUtils.xml
%feature("docstring")  StringUtils::matchesPattern "bool StringUtils::matchesPattern(const std::string &text, const std::string &wildcardPattern)

Returns true if text matches pattern with wildcards '*' and '?'. 
";

%feature("docstring")  StringUtils::padRight "std::string StringUtils::padRight(const std::string &name, size_t length)

Returns string right-padded with blanks. 
";

%feature("docstring")  StringUtils::split "std::vector< std::string > StringUtils::split(const std::string &text, const std::string &delimeter)

Split string into vector of string using delimeter.

Returns token vector obtained by splitting string at delimiters. 
";

%feature("docstring")  StringUtils::replaceItemsFromString "void StringUtils::replaceItemsFromString(std::string &text, const std::vector< std::string > &items, const std::string &replacement=\"\")

Replaces all occurences of items from string text with delimiter. 
";

%feature("docstring")  StringUtils::join "std::string StringUtils::join(const std::vector< std::string > &joinable, const std::string &joint)

Returns string obtain by joining vector elements. 
";

%feature("docstring")  StringUtils::removeSubstring "std::string StringUtils::removeSubstring(const std::string &text, const std::string &substr)

Removes multiple occurences of given substring from a string and returns result. 
";

%feature("docstring")  StringUtils::scientific "std::string StringUtils::scientific(const T value, int n=10)

Returns scientific string representing given value of any numeric type. 
";

%feature("docstring")  StringUtils::to_lower "std::string StringUtils::to_lower(std::string text)

Returns new string which is lower case of text. 
";


// File: FitOptions_8cpp.xml


// File: FitOptions_8h.xml


// File: IFunctionAdapter_8cpp.xml


// File: IFunctionAdapter_8h.xml


// File: Kernel_8cpp.xml


// File: Kernel_8h.xml


// File: KernelTypes_8h.xml


// File: Minimizer_8cpp.xml


// File: Minimizer_8h.xml


// File: MinimizerResult_8cpp.xml


// File: MinimizerResult_8h.xml


// File: Parameter_8cpp.xml


// File: Parameter_8h.xml


// File: Parameters_8cpp.xml


// File: Parameters_8h.xml


// File: PyCallback_8cpp.xml


// File: PyCallback_8h.xml


// File: IMinimizer_8cpp.xml


// File: IMinimizer_8h.xml


// File: MinimizerCatalog_8cpp.xml


// File: MinimizerCatalog_8h.xml


// File: MinimizerFactory_8cpp.xml


// File: MinimizerFactory_8h.xml


// File: MinimizerInfo_8cpp.xml


// File: MinimizerInfo_8h.xml


// File: MinimizerOptions_8cpp.xml


// File: MinimizerOptions_8h.xml


// File: TestMinimizer_8cpp.xml


// File: TestMinimizer_8h.xml


// File: GeneticMinimizer_8cpp.xml


// File: GeneticMinimizer_8h.xml


// File: GSLLevenbergMarquardtMinimizer_8cpp.xml


// File: GSLLevenbergMarquardtMinimizer_8h.xml


// File: GSLMultiMinimizer_8cpp.xml


// File: GSLMultiMinimizer_8h.xml


// File: MinimizerResultUtils_8cpp.xml


// File: MinimizerResultUtils_8h.xml


// File: Minuit2Minimizer_8cpp.xml


// File: Minuit2Minimizer_8h.xml


// File: ObjectiveFunctionAdapter_8cpp.xml


// File: ObjectiveFunctionAdapter_8h.xml


// File: ResidualFunctionAdapter_8cpp.xml


// File: ResidualFunctionAdapter_8h.xml


// File: RootMinimizerAdapter_8cpp.xml


// File: RootMinimizerAdapter_8h.xml


// File: RootResidualFunction_8cpp.xml


// File: RootResidualFunction_8h.xml


// File: RootScalarFunction_8cpp.xml


// File: RootScalarFunction_8h.xml


// File: ScalarFunctionAdapter_8cpp.xml


// File: ScalarFunctionAdapter_8h.xml


// File: SimAnMinimizer_8cpp.xml


// File: SimAnMinimizer_8h.xml


// File: IFactory_8h.xml
%feature("docstring")  create_new "T* create_new()

Returns new instance of class T.

This templated function is used in catalogs in form of a function pointer 'create_new<T>', with no function arguments supplied. Equivalently, we could use a lambda function '[](){return new T;}'. 
";


// File: MinimizerTestPlan_8cpp.xml


// File: MinimizerTestPlan_8h.xml


// File: Numeric_8cpp.xml


// File: Numeric_8h.xml


// File: ParameterPlan_8h.xml


// File: AttLimits_8cpp.xml


// File: AttLimits_8h.xml


// File: Attributes_8h.xml


// File: MinimizerUtils_8cpp.xml


// File: MinimizerUtils_8h.xml


// File: MultiOption_8cpp.xml


// File: MultiOption_8h.xml


// File: OptionContainer_8cpp.xml


// File: OptionContainer_8h.xml


// File: RealLimits_8cpp.xml


// File: RealLimits_8h.xml


// File: StringUtils_8cpp.xml


// File: StringUtils_8h.xml


// File: WallclockTimer_8cpp.xml


// File: WallclockTimer_8h.xml


// File: dir_892d84e8d1420bf45a9053cf0eede900.xml


// File: dir_ddbc8017d498762c6500a9e593e25277.xml


// File: dir_7c95011753c2f8fb6f2a9c22c1fbdc50.xml


// File: dir_5e88eb7454533834afc0f9fdcde3e277.xml


// File: dir_03da15e295bc2986014d40bf58034da8.xml


// File: dir_e87cef4d6f8e4c4c298cf0a4783d30f5.xml

