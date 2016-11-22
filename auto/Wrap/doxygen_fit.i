
// File: index.xml

// File: classAttLimits.xml
%feature("docstring") AttLimits "

The  AttLimits class defines limited/free attribute of fit parameter and provides coupling between them.

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


// File: classFitKernel.xml
%feature("docstring") FitKernel "

Main class to setup and run the minimization.

C++ includes: FitKernel.h
";

%feature("docstring")  FitKernel::FitKernel "FitKernel::FitKernel()
";

%feature("docstring")  FitKernel::~FitKernel "FitKernel::~FitKernel()
";

%feature("docstring")  FitKernel::clear "void FitKernel::clear()
";

%feature("docstring")  FitKernel::setMinimizer "void FitKernel::setMinimizer(const std::string &minimizerName, const std::string &algorithmName=std::string())

Sets minimizer with given name and algorithm type

Parameters:
-----------

minimizerName: 
The name of the minimizer

algorithmName: 
Optional name of the minimizer's algorithm 
";

%feature("docstring")  FitKernel::setMinimizer "void FitKernel::setMinimizer(IMinimizer *minimizer)
";

%feature("docstring")  FitKernel::minimizer "const IMinimizer * FitKernel::minimizer() const

Returns minimizer. 
";

%feature("docstring")  FitKernel::addFitParameter "void FitKernel::addFitParameter(const std::string &name, double value, const AttLimits &limits, double step)

Adds fit parameter. 
";

%feature("docstring")  FitKernel::setObjectiveFunction "void FitKernel::setObjectiveFunction(objective_function_t func)
";

%feature("docstring")  FitKernel::setGradientFunction "void FitKernel::setGradientFunction(gradient_function_t func, int ndatasize)
";

%feature("docstring")  FitKernel::minimize "void FitKernel::minimize()
";

%feature("docstring")  FitKernel::reportResults "std::string FitKernel::reportResults() const

Reports results of minimization in the form of multi-line string. 
";

%feature("docstring")  FitKernel::fitParameters "FitParameterSet * FitKernel::fitParameters()
";

%feature("docstring")  FitKernel::fitParameters "const FitParameterSet * FitKernel::fitParameters() const
";

%feature("docstring")  FitKernel::functionCalls "int FitKernel::functionCalls() const

Number of objective function calls. 
";


// File: classFitKernelImpl.xml
%feature("docstring") FitKernelImpl "

The  FitKernel implementation.

C++ includes: FitKernelImpl.h
";

%feature("docstring")  FitKernelImpl::FitKernelImpl "FitKernelImpl::FitKernelImpl()
";

%feature("docstring")  FitKernelImpl::~FitKernelImpl "FitKernelImpl::~FitKernelImpl()
";

%feature("docstring")  FitKernelImpl::clear "void FitKernelImpl::clear()
";

%feature("docstring")  FitKernelImpl::setMinimizer "void FitKernelImpl::setMinimizer(IMinimizer *minimizer)

Sets minimizer. 
";

%feature("docstring")  FitKernelImpl::addFitParameter "void FitKernelImpl::addFitParameter(FitParameter *par)

Adds fit parameter. 
";

%feature("docstring")  FitKernelImpl::setObjectiveFunction "void FitKernelImpl::setObjectiveFunction(objective_function_t func)
";

%feature("docstring")  FitKernelImpl::setGradientFunction "void FitKernelImpl::setGradientFunction(gradient_function_t func, int ndatasize)
";

%feature("docstring")  FitKernelImpl::minimize "void FitKernelImpl::minimize()
";

%feature("docstring")  FitKernelImpl::reportResults "std::string FitKernelImpl::reportResults() const

Reports results of minimization in the form of multi-line string. 
";

%feature("docstring")  FitKernelImpl::fitParameters "FitParameterSet * FitKernelImpl::fitParameters()
";

%feature("docstring")  FitKernelImpl::minimizer "IMinimizer * FitKernelImpl::minimizer()
";

%feature("docstring")  FitKernelImpl::functionCalls "int FitKernelImpl::functionCalls() const

Number of objective function calls. 
";


// File: classFitOptions.xml
%feature("docstring") FitOptions "

General fitting options.

C++ includes: FitOptions.h
";

%feature("docstring")  FitOptions::FitOptions "FitOptions::FitOptions()
";

%feature("docstring")  FitOptions::~FitOptions "FitOptions::~FitOptions()
";

%feature("docstring")  FitOptions::derivEpsilon "double FitOptions::derivEpsilon() const
";

%feature("docstring")  FitOptions::setDerivEpsilon "void FitOptions::setDerivEpsilon(double deriv_epsilon)
";

%feature("docstring")  FitOptions::stepFactor "double FitOptions::stepFactor() const
";

%feature("docstring")  FitOptions::setStepFactor "void FitOptions::setStepFactor(double step_factor)
";


// File: classFitParameter.xml
%feature("docstring") FitParameter "

The  FitParameter represents fittable parameter with value, error, step, and limits.

C++ includes: FitParameter.h
";

%feature("docstring")  FitParameter::FitParameter "FitParameter::FitParameter()
";

%feature("docstring")  FitParameter::FitParameter "FitParameter::FitParameter(const std::string &name, double value, const AttLimits &limits=AttLimits::limitless(), double step=0.0)
";

%feature("docstring")  FitParameter::~FitParameter "virtual FitParameter::~FitParameter()
";

%feature("docstring")  FitParameter::clone "FitParameter * FitParameter::clone() const
";

%feature("docstring")  FitParameter::name "std::string FitParameter::name() const
";

%feature("docstring")  FitParameter::startValue "double FitParameter::startValue() const
";

%feature("docstring")  FitParameter::value "double FitParameter::value() const
";

%feature("docstring")  FitParameter::setValue "void FitParameter::setValue(double value)
";

%feature("docstring")  FitParameter::step "double FitParameter::step() const
";

%feature("docstring")  FitParameter::setStep "FitParameter & FitParameter::setStep(double value)
";

%feature("docstring")  FitParameter::error "double FitParameter::error() const
";

%feature("docstring")  FitParameter::setError "void FitParameter::setError(double value)
";

%feature("docstring")  FitParameter::limits "const AttLimits & FitParameter::limits() const
";

%feature("docstring")  FitParameter::limits "AttLimits & FitParameter::limits()
";

%feature("docstring")  FitParameter::setLimits "FitParameter & FitParameter::setLimits(const AttLimits &limits)
";

%feature("docstring")  FitParameter::setLowerLimited "FitParameter & FitParameter::setLowerLimited(double bound_value)
";

%feature("docstring")  FitParameter::setPositive "FitParameter & FitParameter::setPositive()
";

%feature("docstring")  FitParameter::setNonnegative "FitParameter & FitParameter::setNonnegative()
";

%feature("docstring")  FitParameter::setUpperLimited "FitParameter & FitParameter::setUpperLimited(double bound_value)
";

%feature("docstring")  FitParameter::setLimited "FitParameter & FitParameter::setLimited(double left_bound_value, double right_bound_value)
";

%feature("docstring")  FitParameter::setFixed "FitParameter & FitParameter::setFixed()
";

%feature("docstring")  FitParameter::toString "std::string FitParameter::toString() const
";


// File: classFitParameterSet.xml
%feature("docstring") FitParameterSet "

The  FitParameterSet represents collection of fit parameters for the minimizer.

C++ includes: FitParameterSet.h
";

%feature("docstring")  FitParameterSet::FitParameterSet "FitParameterSet::FitParameterSet()
";

%feature("docstring")  FitParameterSet::~FitParameterSet "FitParameterSet::~FitParameterSet()
";

%feature("docstring")  FitParameterSet::clear "void FitParameterSet::clear()

container specific

Clears all defined parameters. 
";

%feature("docstring")  FitParameterSet::size "size_t FitParameterSet::size() const

Returns number of parameters. 
";

%feature("docstring")  FitParameterSet::begin "FitParameterSet::iterator FitParameterSet::begin()

Container iterators. 
";

%feature("docstring")  FitParameterSet::begin "FitParameterSet::const_iterator FitParameterSet::begin() const
";

%feature("docstring")  FitParameterSet::end "FitParameterSet::iterator FitParameterSet::end()
";

%feature("docstring")  FitParameterSet::end "FitParameterSet::const_iterator FitParameterSet::end() const
";

%feature("docstring")  FitParameterSet::addFitParameter "void FitParameterSet::addFitParameter(FitParameter *par)

adding fit parameters

Adds fit parameter. 
";

%feature("docstring")  FitParameterSet::fitParameter "const FitParameter * FitParameterSet::fitParameter(const std::string &name) const

accessing fit parameters

Returns fit parameter by given name. 
";

%feature("docstring")  FitParameterSet::fitParameter "FitParameter * FitParameterSet::fitParameter(const std::string &name)
";

%feature("docstring")  FitParameterSet::values "std::vector< double > FitParameterSet::values() const

fit parameter's values and errors

Returns values of all defined parameters. 
";

%feature("docstring")  FitParameterSet::setValues "void FitParameterSet::setValues(const std::vector< double > &pars_values)

Sets values for all defined parameters. 
";

%feature("docstring")  FitParameterSet::valuesDifferFrom "bool FitParameterSet::valuesDifferFrom(const std::vector< double > &par_values, double tolerance=2.0) const

Returns true if parameters already have the given values. 
";

%feature("docstring")  FitParameterSet::errors "std::vector< double > FitParameterSet::errors() const

Returns errors of all defined parameters. 
";

%feature("docstring")  FitParameterSet::setErrors "void FitParameterSet::setErrors(const std::vector< double > &pars_errors)

Sets errors to all parameters. 
";

%feature("docstring")  FitParameterSet::freeFitParameterCount "size_t FitParameterSet::freeFitParameterCount() const

Make parameters fixed and free.

Returns number of free parameters. 
";

%feature("docstring")  FitParameterSet::fixAll "void FitParameterSet::fixAll()

Fix all parameters. 
";

%feature("docstring")  FitParameterSet::releaseAll "void FitParameterSet::releaseAll()

Release all parameters. 
";

%feature("docstring")  FitParameterSet::setFixed "void FitParameterSet::setFixed(const std::vector< std::string > &pars, bool is_fixed)

Set fixed flag for parameters from the list. 
";

%feature("docstring")  FitParameterSet::parametersToString "std::string FitParameterSet::parametersToString() const

Printing and reporting. 
";

%feature("docstring")  FitParameterSet::reportResults "std::string FitParameterSet::reportResults() const
";

%feature("docstring")  FitParameterSet::correlationMatrix "corr_matrix_t FitParameterSet::correlationMatrix() const
";

%feature("docstring")  FitParameterSet::setCorrelationMatrix "void FitParameterSet::setCorrelationMatrix(const corr_matrix_t &matrix)
";

%feature("docstring")  FitParameterSet::isExistingName "bool FitParameterSet::isExistingName(const std::string &name) const

Returns true if parameter with such name exists. 
";


// File: classGeneticMinimizer.xml
%feature("docstring") GeneticMinimizer "

Wrapper for ROOT Genetic minimizer.

C++ includes: GeneticMinimizer.h
";

%feature("docstring")  GeneticMinimizer::GeneticMinimizer "GeneticMinimizer::GeneticMinimizer()
";

%feature("docstring")  GeneticMinimizer::~GeneticMinimizer "GeneticMinimizer::~GeneticMinimizer()

Sets tolerance on the function value at the minimum. Minimization will stop when the estimated vertical distance to the minimum (EDM) is less than 0.001*tolerance*ErrorDef. Here ErrorDef=1.0 for chi squared fit and ErrorDef=0.5 for negative log likelihood fit. Default value is 0.01. 
";

%feature("docstring")  GeneticMinimizer::setTolerance "void GeneticMinimizer::setTolerance(double value)
";

%feature("docstring")  GeneticMinimizer::tolerance "double GeneticMinimizer::tolerance() const
";

%feature("docstring")  GeneticMinimizer::setPrintLevel "void GeneticMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. Default value is 0 (silent). 
";

%feature("docstring")  GeneticMinimizer::printLevel "int GeneticMinimizer::printLevel() const
";

%feature("docstring")  GeneticMinimizer::setMaxIterations "void GeneticMinimizer::setMaxIterations(int value)

Sets maximum number of iterations to try at each step. Default values is 3. 
";

%feature("docstring")  GeneticMinimizer::maxIterations "int GeneticMinimizer::maxIterations() const
";

%feature("docstring")  GeneticMinimizer::setPopulationSize "void GeneticMinimizer::setPopulationSize(int value)

Sets population size. Default value is 300. 
";

%feature("docstring")  GeneticMinimizer::populationSize "int GeneticMinimizer::populationSize() const
";

%feature("docstring")  GeneticMinimizer::setRandomSeed "void GeneticMinimizer::setRandomSeed(int value)

Sets random seed. Default value is 0. 
";

%feature("docstring")  GeneticMinimizer::randomSeed "int GeneticMinimizer::randomSeed() const
";

%feature("docstring")  GeneticMinimizer::setParameter "void GeneticMinimizer::setParameter(size_t index, const FitParameter *par)

Sets minimizer parameter. Overload is required to check that parameter is properly limited. 
";

%feature("docstring")  GeneticMinimizer::statusToString "std::string GeneticMinimizer::statusToString() const

Returns string representation of current minimizer status. 
";

%feature("docstring")  GeneticMinimizer::statusMap "std::map< std::string, std::string > GeneticMinimizer::statusMap() const

Returns map of string representing different minimizer statuses. 
";


// File: classGSLLevenbergMarquardtMinimizer.xml
%feature("docstring") GSLLevenbergMarquardtMinimizer "

Wrapper for GSL Levenberg-Marquardt minimizer. http://www.gnu.org/software/gsl/manual/html_node/Nonlinear-Least_002dSquares-Fitting.html.

C++ includes: GSLLevenbergMarquardtMinimizer.h
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::GSLLevenbergMarquardtMinimizer "GSLLevenbergMarquardtMinimizer::GSLLevenbergMarquardtMinimizer()
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::~GSLLevenbergMarquardtMinimizer "GSLLevenbergMarquardtMinimizer::~GSLLevenbergMarquardtMinimizer()

Sets tolerance on the function value at the minimum. Default value is 0.01. 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::setTolerance "void GSLLevenbergMarquardtMinimizer::setTolerance(double value)
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::tolerance "double GSLLevenbergMarquardtMinimizer::tolerance() const
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::setPrintLevel "void GSLLevenbergMarquardtMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. Default value is 0 (silent). 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::printLevel "int GSLLevenbergMarquardtMinimizer::printLevel() const
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::setMaxIterations "void GSLLevenbergMarquardtMinimizer::setMaxIterations(int value)

Sets maximum number of iterations. This is an internal minimizer setting which has no direct relation to the number of objective function calls (e.g. numberOfIteraction=5 might correspond to ~100 objective function calls). 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::maxIterations "int GSLLevenbergMarquardtMinimizer::maxIterations() const
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::statusToString "std::string GSLLevenbergMarquardtMinimizer::statusToString() const

Returns string representation of current minimizer status. 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::statusMap "std::map< std::string, std::string > GSLLevenbergMarquardtMinimizer::statusMap() const

Returns map of string representing different minimizer statuses. 
";


// File: classGSLMultiMinimizer.xml
%feature("docstring") GSLMultiMinimizer "

Wrapper for GSL multi minimizer (gradient descent based) family.

C++ includes: GSLMultiMinimizer.h
";

%feature("docstring")  GSLMultiMinimizer::GSLMultiMinimizer "GSLMultiMinimizer::GSLMultiMinimizer(const std::string &algorithmName=AlgorithmNames::ConjugateFR)
";

%feature("docstring")  GSLMultiMinimizer::~GSLMultiMinimizer "GSLMultiMinimizer::~GSLMultiMinimizer()
";

%feature("docstring")  GSLMultiMinimizer::setPrintLevel "void GSLMultiMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. Default value is 0 (silent). 
";

%feature("docstring")  GSLMultiMinimizer::printLevel "int GSLMultiMinimizer::printLevel() const
";

%feature("docstring")  GSLMultiMinimizer::setMaxIterations "void GSLMultiMinimizer::setMaxIterations(int value)

Sets maximum number of iterations. This is an internal minimizer setting which has no direct relation to the number of objective function calls (e.g. numberOfIteraction=5 might correspond to ~100 objective function calls). 
";

%feature("docstring")  GSLMultiMinimizer::maxIterations "int GSLMultiMinimizer::maxIterations() const
";

%feature("docstring")  GSLMultiMinimizer::statusToString "std::string GSLMultiMinimizer::statusToString() const

Returns string representation of current minimizer status. 
";


// File: classIFitParameter.xml
%feature("docstring") IFitParameter "

The  IFitParameter is a base class for fit parameters.

C++ includes: IFitParameter.h
";

%feature("docstring")  IFitParameter::IFitParameter "IFitParameter::IFitParameter()
";

%feature("docstring")  IFitParameter::~IFitParameter "virtual IFitParameter::~IFitParameter()
";

%feature("docstring")  IFitParameter::IFitParameter "IFitParameter::IFitParameter(const IFitParameter &)=delete
";

%feature("docstring")  IFitParameter::clone "virtual IFitParameter* IFitParameter::clone() const =0
";


// File: classIMinimizer.xml
%feature("docstring") IMinimizer "

Pure virtual interface for all kind minimizers.

C++ includes: IMinimizer.h
";

%feature("docstring")  IMinimizer::IMinimizer "IMinimizer::IMinimizer()
";

%feature("docstring")  IMinimizer::~IMinimizer "virtual IMinimizer::~IMinimizer()
";

%feature("docstring")  IMinimizer::IMinimizer "IMinimizer::IMinimizer(const IMinimizer &other)=delete
";

%feature("docstring")  IMinimizer::minimizerName "virtual std::string IMinimizer::minimizerName() const =0

return name of the minimizer 
";

%feature("docstring")  IMinimizer::algorithmName "virtual std::string IMinimizer::algorithmName() const =0

return name of the minimization algorithm 
";

%feature("docstring")  IMinimizer::minimize "void IMinimizer::minimize()

run minimization 
";

%feature("docstring")  IMinimizer::clear "void IMinimizer::clear()

clear resources (parameters) for consecutives minimizations 
";

%feature("docstring")  IMinimizer::setParameters "void IMinimizer::setParameters(const FitParameterSet &parameters)

Sets internal minimizer parameters using external parameter list. 
";

%feature("docstring")  IMinimizer::setObjectiveFunction "virtual void IMinimizer::setObjectiveFunction(objective_function_t)
";

%feature("docstring")  IMinimizer::setGradientFunction "virtual void IMinimizer::setGradientFunction(gradient_function_t, int)
";

%feature("docstring")  IMinimizer::minValue "double IMinimizer::minValue() const

Returns minimum function value. 
";

%feature("docstring")  IMinimizer::reportResults "std::string IMinimizer::reportResults() const

Prints fit results. 
";

%feature("docstring")  IMinimizer::propagateResults "void IMinimizer::propagateResults(FitParameterSet &parameters)

Propagates results of minimization to fit parameter set. 
";

%feature("docstring")  IMinimizer::setOptions "void IMinimizer::setOptions(const std::string &options)

Sets option string to the minimizer. 
";


// File: classInfoItem.xml
%feature("docstring") InfoItem "

Simple item to hold the name and the description.

C++ includes: MinimizerInfo.h
";

%feature("docstring")  InfoItem::InfoItem "InfoItem::InfoItem()
";

%feature("docstring")  InfoItem::InfoItem "InfoItem::InfoItem(const std::string &itemName, const std::string &itemDescription)
";

%feature("docstring")  InfoItem::name "std::string InfoItem::name() const
";

%feature("docstring")  InfoItem::description "std::string InfoItem::description() const
";


// File: classMSG_1_1Logger.xml
%feature("docstring") MSG::Logger "

Provides message service.

C++ includes: Logger.h
";

%feature("docstring")  MSG::Logger::Logger "MSG::Logger::Logger(EMessageLevel level)
";

%feature("docstring")  MSG::Logger::~Logger "MSG::Logger::~Logger()
";

%feature("docstring")  MSG::Logger::NowTime "std::string MSG::Logger::NowTime()
";

%feature("docstring")  MSG::Logger::ToString "const std::string & MSG::Logger::ToString(EMessageLevel level)
";


// File: classMinimizerCatalogue.xml
%feature("docstring") MinimizerCatalogue "

The  MinimizerCatalogue class contains information over all minimizers available.

C++ includes: MinimizerCatalogue.h
";

%feature("docstring")  MinimizerCatalogue::MinimizerCatalogue "MinimizerCatalogue::MinimizerCatalogue()
";

%feature("docstring")  MinimizerCatalogue::toString "std::string MinimizerCatalogue::toString() const

Returns multiline string representing catalogue content. 
";

%feature("docstring")  MinimizerCatalogue::algorithmNames "std::vector< std::string > MinimizerCatalogue::algorithmNames(const std::string &minimizerName) const

Returns list of algorithms defined for the minimizer with a given name. 
";

%feature("docstring")  MinimizerCatalogue::algorithmDescriptions "std::vector< std::string > MinimizerCatalogue::algorithmDescriptions(const std::string &minimizerName) const

Returns list of algorithm's descriptions for the minimizer with a given name . 
";


// File: classMinimizerFactory.xml
%feature("docstring") MinimizerFactory "

Factory to create minimizers.

Minimizer | Algorithms

Minuit2 | Migrad Simplex Combined Scan Fumili GSLMultiMin | SteepestDescent ConjugateFR ConjugatePR BFGS BFGS2 GSLLMA | Default GSLSimAn | Default Genetic | Default

C++ includes: MinimizerFactory.h
";


// File: classMinimizerInfo.xml
%feature("docstring") MinimizerInfo "

The  MinimizerInfo class provides info about the minimizer, including list of defined minimization algorithms.

C++ includes: MinimizerInfo.h
";

%feature("docstring")  MinimizerInfo::MinimizerInfo "MinimizerInfo::MinimizerInfo()
";

%feature("docstring")  MinimizerInfo::MinimizerInfo "MinimizerInfo::MinimizerInfo(const std::string &minimizerType, const std::string &minimizerDescription)
";

%feature("docstring")  MinimizerInfo::setAlgorithmName "void MinimizerInfo::setAlgorithmName(const std::string &algorithmName)

Sets currently active algorithm. 
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

The  MinimizerOptions class holds collection of internal minimizer settings.

C++ includes: MinimizerOptions.h
";

%feature("docstring")  MinimizerOptions::toOptionString "std::string MinimizerOptions::toOptionString() const

Returns string with all options (i.e. \"Strategy=1;Tolerance=0.01;\") 
";

%feature("docstring")  MinimizerOptions::setOptionString "void MinimizerOptions::setOptionString(const std::string &options)

Set options from their string representation. 
";


// File: classMinimizerResultsHelper.xml
%feature("docstring") MinimizerResultsHelper "

The  MinimizerResultsHelper class contains all logic to generate reports with the result of minimization.

C++ includes: MinimizerResultsHelper.h
";

%feature("docstring")  MinimizerResultsHelper::MinimizerResultsHelper "MinimizerResultsHelper::MinimizerResultsHelper()
";

%feature("docstring")  MinimizerResultsHelper::reportResults "std::string MinimizerResultsHelper::reportResults(const RootMinimizerAdapter *minimizer) const

Reports results of minimization in the form of multi-line string. 
";

%feature("docstring")  MinimizerResultsHelper::reportResults "std::string MinimizerResultsHelper::reportResults(const FitParameterSet *parameters) const

Reports fit parameters settings and final results. 
";


// File: classMinuit2Minimizer.xml
%feature("docstring") Minuit2Minimizer "

The  Minuit2Minimizer class is a wrapper for ROOT Minuit2 minimizer See Minuit2 user manual https://root.cern.ch/root/htmldoc/guides/minuit2/Minuit2.pdf.

C++ includes: Minuit2Minimizer.h
";

%feature("docstring")  Minuit2Minimizer::Minuit2Minimizer "Minuit2Minimizer::Minuit2Minimizer(const std::string &algorithmName=AlgorithmNames::Migrad)
";

%feature("docstring")  Minuit2Minimizer::~Minuit2Minimizer "Minuit2Minimizer::~Minuit2Minimizer()
";

%feature("docstring")  Minuit2Minimizer::setStrategy "void Minuit2Minimizer::setStrategy(int value)

Sets minimization strategy (0-low, 1-medium, 2-high minimization quality). At low quality number of function calls will be economized. Default value is 1. 
";

%feature("docstring")  Minuit2Minimizer::strategy "int Minuit2Minimizer::strategy() const
";

%feature("docstring")  Minuit2Minimizer::setErrorDefinition "void Minuit2Minimizer::setErrorDefinition(double value)

Sets error definition factor for parameter error calculation. If objective function (OF) is the usual chisquare function and if the user wants the usual one-standard-deviation errors, then the error definition should be 1.0. If OF is a negative-log-likelihood function, then 0.5. If OF is a chisquare, but the user wants two-standard-deviation errors, 4.0. Default value is 1.0. 
";

%feature("docstring")  Minuit2Minimizer::errorDefinition "double Minuit2Minimizer::errorDefinition() const

Sets tolerance on the function value at the minimum. Minimization will stop when the estimated vertical distance to the minimum (EDM) is less than 0.001*tolerance*ErrorDef. Here ErrorDef=1.0 for chi squared fit and ErrorDef=0.5 for negative log likelihood fit. Default value is 0.01. 
";

%feature("docstring")  Minuit2Minimizer::setTolerance "void Minuit2Minimizer::setTolerance(double value)
";

%feature("docstring")  Minuit2Minimizer::tolerance "double Minuit2Minimizer::tolerance() const

Sets relative floating point arithmetic precision. Should be adjusted when the user knows that objectiove function value is not calculated to the nominal machine accuracy. Typical values are between 10^-5 and 10^-14. Default value is -1.0 (minimizer specific will be used). 
";

%feature("docstring")  Minuit2Minimizer::setPrecision "void Minuit2Minimizer::setPrecision(double value)
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

%feature("docstring")  Minuit2Minimizer::statusToString "std::string Minuit2Minimizer::statusToString() const

Returns string representation of current minimizer status. 
";

%feature("docstring")  Minuit2Minimizer::statusMap "std::map< std::string, std::string > Minuit2Minimizer::statusMap() const

Returns map of string representing different minimizer statuses. 
";


// File: classMultiOption.xml
%feature("docstring") MultiOption "

The  MultiOption class is intended to store a single option for minimization algorithm. Int, double, string values are available. Relies on boost::variant, will be switched to std::variant in C++-17. (before was https://github.com/mapbox/variant.

C++ includes: MultiOption.h
";

%feature("docstring")  MultiOption::MultiOption "MultiOption::MultiOption(const std::string &name=std::string())
";

%feature("docstring")  MultiOption::MultiOption "MultiOption::MultiOption(const std::string &name, const T &t, const std::string &descripion=std::string())
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


// File: classObjectiveFunction.xml
%feature("docstring") ObjectiveFunction "

The  ObjectiveFunction class represents function to minimize.

C++ includes: ObjectiveFunction.h
";

%feature("docstring")  ObjectiveFunction::ObjectiveFunction "ObjectiveFunction::ObjectiveFunction()
";

%feature("docstring")  ObjectiveFunction::setObjectiveFunction "void ObjectiveFunction::setObjectiveFunction(objective_function_t func)
";

%feature("docstring")  ObjectiveFunction::setGradientFunction "void ObjectiveFunction::setGradientFunction(gradient_function_t func, int ndatasize)
";

%feature("docstring")  ObjectiveFunction::evaluate "double ObjectiveFunction::evaluate(const std::vector< double > &pars)

Evaluates the value of the function for given vector of function parameters using callback mechanism. 
";

%feature("docstring")  ObjectiveFunction::evaluate_gradient "double ObjectiveFunction::evaluate_gradient(const std::vector< double > &pars, int index, std::vector< double > &gradient)

Evaluates residual and gradients of the function for given vector of function parameters and index of dataelement using callback mechanism. 
";

%feature("docstring")  ObjectiveFunction::functionCalls "int ObjectiveFunction::functionCalls() const
";

%feature("docstring")  ObjectiveFunction::sizeOfData "int ObjectiveFunction::sizeOfData() const
";


// File: classOptionContainer.xml
%feature("docstring") OptionContainer "

The  OptionContainer class stores multi option (int,double,string) in a container.

C++ includes: OptionContainer.h
";

%feature("docstring")  OptionContainer::OptionContainer "OptionContainer::OptionContainer()
";

%feature("docstring")  OptionContainer::OptionContainer "OptionContainer::OptionContainer(const OptionContainer &other)

Returns true if option with such name already exists. 
";

%feature("docstring")  OptionContainer::addOption "OptionContainer::option_t OptionContainer::addOption(const std::string &optionName, T value, const std::string &description=std::string())
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

%feature("docstring")  RealLimits::getLowerLimit "double RealLimits::getLowerLimit() const

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

%feature("docstring")  RealLimits::getUpperLimit "double RealLimits::getUpperLimit() const

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


// File: classRootGradientFunction.xml
%feature("docstring") RootGradientFunction "

Minimizer function with access to single data element residuals. Required by Fumili, Fumili2 and GSLMultiMin minimizers.

C++ includes: RootMinimizerFunctions.h
";

%feature("docstring")  RootGradientFunction::RootGradientFunction "RootGradientFunction::RootGradientFunction(root_gradient_t fun_gradient, size_t npars, size_t ndatasize)
";

%feature("docstring")  RootGradientFunction::Type "Type_t RootGradientFunction::Type() const
";

%feature("docstring")  RootGradientFunction::Clone "BA_ROOT::Math::IMultiGenFunction* RootGradientFunction::Clone() const
";

%feature("docstring")  RootGradientFunction::DataElement "double RootGradientFunction::DataElement(const double *pars, unsigned int i_data, double *gradient=0) const

evaluation of single data element residual 
";


// File: classRootMinimizerAdapter.xml
%feature("docstring") RootMinimizerAdapter "

The  RootMinimizerAdapter class adapts ROOT minimizer interface to our  IMinimizer.

C++ includes: RootMinimizerAdapter.h
";

%feature("docstring")  RootMinimizerAdapter::~RootMinimizerAdapter "RootMinimizerAdapter::~RootMinimizerAdapter()
";

%feature("docstring")  RootMinimizerAdapter::minimize "void RootMinimizerAdapter::minimize() override

run minimization 
";

%feature("docstring")  RootMinimizerAdapter::minimizerName "std::string RootMinimizerAdapter::minimizerName() const override final

Returns name of the minimizer. 
";

%feature("docstring")  RootMinimizerAdapter::algorithmName "std::string RootMinimizerAdapter::algorithmName() const override final

Returns name of the minimization algorithm. 
";

%feature("docstring")  RootMinimizerAdapter::setParameters "void RootMinimizerAdapter::setParameters(const FitParameterSet &parameters) override final

Sets internal minimizer parameters using external parameter list. 
";

%feature("docstring")  RootMinimizerAdapter::setObjectiveFunction "void RootMinimizerAdapter::setObjectiveFunction(objective_function_t func) override final
";

%feature("docstring")  RootMinimizerAdapter::setGradientFunction "void RootMinimizerAdapter::setGradientFunction(gradient_function_t func, int ndatasize) override final
";

%feature("docstring")  RootMinimizerAdapter::minValue "double RootMinimizerAdapter::minValue() const override final

Returns minimum function value. 
";

%feature("docstring")  RootMinimizerAdapter::reportResults "std::string RootMinimizerAdapter::reportResults() const override final

Prints fit results. 
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

%feature("docstring")  RootMinimizerAdapter::propagateResults "void RootMinimizerAdapter::propagateResults(FitParameterSet &parameters) override

Propagates results of minimization to fit parameter set. 
";

%feature("docstring")  RootMinimizerAdapter::setOptions "void RootMinimizerAdapter::setOptions(const std::string &optionString) override final

Sets option string to the minimizer. 
";


// File: classRootObjectiveFunction.xml
%feature("docstring") RootObjectiveFunction "

minimizer chi2 function

C++ includes: RootMinimizerFunctions.h
";

%feature("docstring")  RootObjectiveFunction::RootObjectiveFunction "RootObjectiveFunction::RootObjectiveFunction(root_objective_t fcn, int ndims)
";


// File: classRootObjectiveFunctionAdapter.xml
%feature("docstring") RootObjectiveFunctionAdapter "

The  RootObjectiveFunctionAdapter class adapts our objective functions to ROOT.

C++ includes: RootObjectiveFuncAdapter.h
";

%feature("docstring")  RootObjectiveFunctionAdapter::RootObjectiveFunctionAdapter "RootObjectiveFunctionAdapter::RootObjectiveFunctionAdapter()
";

%feature("docstring")  RootObjectiveFunctionAdapter::setObjectiveCallback "void RootObjectiveFunctionAdapter::setObjectiveCallback(objective_function_t func)

Sets the function which will be used for finding objective function minimum value. 
";

%feature("docstring")  RootObjectiveFunctionAdapter::setGradientCallback "void RootObjectiveFunctionAdapter::setGradientCallback(gradient_function_t func, int ndatasize)

Sets the function which will be used for gradient calculations. 
";

%feature("docstring")  RootObjectiveFunctionAdapter::setNumberOfParameters "void RootObjectiveFunctionAdapter::setNumberOfParameters(int nparameters)

Sets number of fit parameters (needed to construct correct ROOT's functions). 
";

%feature("docstring")  RootObjectiveFunctionAdapter::rootChiSquaredFunction "const RootObjectiveFunction * RootObjectiveFunctionAdapter::rootChiSquaredFunction()

Creates and returns objective function suitable for ROOT minimizers. 
";

%feature("docstring")  RootObjectiveFunctionAdapter::rootGradientFunction "const RootGradientFunction * RootObjectiveFunctionAdapter::rootGradientFunction()

Creates and returns gradient function suitable for ROOT minimizers. 
";


// File: classSimAnMinimizer.xml
%feature("docstring") SimAnMinimizer "

Wrapper for ROOT GSL simmulated annealing minimizer.

C++ includes: SimAnMinimizer.h
";

%feature("docstring")  SimAnMinimizer::SimAnMinimizer "SimAnMinimizer::SimAnMinimizer()
";

%feature("docstring")  SimAnMinimizer::~SimAnMinimizer "SimAnMinimizer::~SimAnMinimizer()
";

%feature("docstring")  SimAnMinimizer::setPrintLevel "void SimAnMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. Default value is 0 (silent). 
";

%feature("docstring")  SimAnMinimizer::printLevel "int SimAnMinimizer::printLevel() const
";

%feature("docstring")  SimAnMinimizer::setMaxIterations "void SimAnMinimizer::setMaxIterations(int value)

Sets maximum number of iterations to try at each step. Default values is 100. 
";

%feature("docstring")  SimAnMinimizer::maxIterations "int SimAnMinimizer::maxIterations() const
";

%feature("docstring")  SimAnMinimizer::setIterationsAtEachTemp "void SimAnMinimizer::setIterationsAtEachTemp(int value)

Sets number of iterations at each temperature. Default value is 10. 
";

%feature("docstring")  SimAnMinimizer::iterationsAtEachTemp "int SimAnMinimizer::iterationsAtEachTemp() const
";

%feature("docstring")  SimAnMinimizer::setStepSize "void SimAnMinimizer::setStepSize(double value)

Sets max step size used in random walk. Default value is 1.0. 
";

%feature("docstring")  SimAnMinimizer::stepSize "double SimAnMinimizer::stepSize() const
";

%feature("docstring")  SimAnMinimizer::setBoltzmannK "void SimAnMinimizer::setBoltzmannK(double value)

Sets Boltzmann distribution parameter: k. Default value 1.0. 
";

%feature("docstring")  SimAnMinimizer::boltzmannK "double SimAnMinimizer::boltzmannK() const
";

%feature("docstring")  SimAnMinimizer::setBoltzmannInitialTemp "void SimAnMinimizer::setBoltzmannInitialTemp(double value)

Sets Boltzmann distribution parameter: initial temperature. Default value 50.0. 
";

%feature("docstring")  SimAnMinimizer::boltzmannInitialTemp "double SimAnMinimizer::boltzmannInitialTemp() const
";

%feature("docstring")  SimAnMinimizer::setBoltzmannMu "void SimAnMinimizer::setBoltzmannMu(double value)

Sets Boltzmann distribution parameter: mu. Default value 1.05. 
";

%feature("docstring")  SimAnMinimizer::boltzmannMu "double SimAnMinimizer::boltzmannMu() const
";

%feature("docstring")  SimAnMinimizer::setBoltzmannMinTemp "void SimAnMinimizer::setBoltzmannMinTemp(double value)

Sets Boltzmann distribution parameter: minimal temperature. Default value 0.1. 
";

%feature("docstring")  SimAnMinimizer::boltzmannMinTemp "double SimAnMinimizer::boltzmannMinTemp() const
";

%feature("docstring")  SimAnMinimizer::statusMap "std::map< std::string, std::string > SimAnMinimizer::statusMap() const

Returns map of string representing different minimizer statuses. 
";

%feature("docstring")  SimAnMinimizer::isGradientBasedAgorithm "virtual bool SimAnMinimizer::isGradientBasedAgorithm()
";


// File: classTestMinimizer.xml
%feature("docstring") TestMinimizer "

A trivial minimizer that calls the objective function once. Used to test the whole chain.

C++ includes: TestMinimizer.h
";

%feature("docstring")  TestMinimizer::TestMinimizer "TestMinimizer::TestMinimizer()
";

%feature("docstring")  TestMinimizer::~TestMinimizer "TestMinimizer::~TestMinimizer()
";

%feature("docstring")  TestMinimizer::minimizerName "std::string TestMinimizer::minimizerName() const final

return name of the minimizer 
";

%feature("docstring")  TestMinimizer::algorithmName "std::string TestMinimizer::algorithmName() const final

return name of the minimization algorithm 
";

%feature("docstring")  TestMinimizer::minimize "void TestMinimizer::minimize() override

run minimization 
";

%feature("docstring")  TestMinimizer::setParameters "void TestMinimizer::setParameters(const FitParameterSet &parameters) override

Sets internal minimizer parameters using external parameter list. 
";

%feature("docstring")  TestMinimizer::setObjectiveFunction "void TestMinimizer::setObjectiveFunction(objective_function_t func) override
";

%feature("docstring")  TestMinimizer::reportResults "std::string TestMinimizer::reportResults() const override

Prints fit results. 
";


// File: classTimeInterval.xml
%feature("docstring") TimeInterval "";

%feature("docstring")  TimeInterval::TimeInterval "TimeInterval::TimeInterval()
";

%feature("docstring")  TimeInterval::~TimeInterval "TimeInterval::~TimeInterval()
";

%feature("docstring")  TimeInterval::start "void TimeInterval::start()
";

%feature("docstring")  TimeInterval::stop "void TimeInterval::stop()
";

%feature("docstring")  TimeInterval::runTime "double TimeInterval::runTime() const

returns run time in sec.msec 
";


// File: classTimeIntervalImp.xml
%feature("docstring") TimeIntervalImp "";

%feature("docstring")  TimeIntervalImp::TimeIntervalImp "TimeIntervalImp::TimeIntervalImp()
";


// File: namespace_0D0.xml


// File: namespace_0D15.xml


// File: namespace_0D17.xml


// File: namespace_0D39.xml


// File: namespace_0D41.xml


// File: namespace_0D45.xml


// File: namespaceAlgorithmNames.xml


// File: namespaceBA__ROOT.xml


// File: namespaceBA__ROOT_1_1Math.xml


// File: namespaceBA__ROOT_1_1Minuit2.xml


// File: namespaceMinimizerNames.xml


// File: namespaceMinimizerUtil.xml
%feature("docstring")  MinimizerUtil::toString "std::string MinimizerUtil::toString(const std::vector< std::string > &v, const std::string &delim=\"\")
";

%feature("docstring")  MinimizerUtil::gslErrorDescriptionMap "std::map< int, std::string > MinimizerUtil::gslErrorDescriptionMap()

Returns translation of GSL error code to string. 
";

%feature("docstring")  MinimizerUtil::gslErrorDescription "std::string MinimizerUtil::gslErrorDescription(int errorCode)
";

%feature("docstring")  MinimizerUtil::numbersDiffer "bool MinimizerUtil::numbersDiffer(double a, double b, double tol)
";

%feature("docstring")  MinimizerUtil::sectionString "std::string MinimizerUtil::sectionString(const std::string &sectionName=std::string(), int report_width=80)

Returns horizontal line of 80 characters length with section name in it. 
";


// File: namespaceMSG.xml
%feature("docstring")  MSG::SetLevel "BA_CORE_API_ void MSG::SetLevel(EMessageLevel level)
";

%feature("docstring")  MSG::SetLevel "BA_CORE_API_ void MSG::SetLevel(const std::string &levelname)
";


// File: namespaceOptionNames.xml


// File: namespaceStringUtil.xml
%feature("docstring")  StringUtil::matchesPattern "bool StringUtil::matchesPattern(const std::string &text, const std::string &wildcardPattern)

Returns true if text matches pattern with wildcards '*' and '?'. 
";

%feature("docstring")  StringUtil::padRight "std::string StringUtil::padRight(const std::string &name, int length)

Returns string right-padded with blanks. 
";

%feature("docstring")  StringUtil::split "std::vector< std::string > StringUtil::split(const std::string &text, const std::string &delimeter)

Split string into vector of string using delimeter.

Returns token vector obtained by splitting string at delimiters. 
";

%feature("docstring")  StringUtil::replaceItemsFromString "void StringUtil::replaceItemsFromString(std::string &text, const std::vector< std::string > &items, const std::string &replacement=std::string(\"\"))

Replaces all occurences of items from string text with delimiter. 
";

%feature("docstring")  StringUtil::join "std::string StringUtil::join(const std::vector< std::string > &joinable, const std::string &joint)

Returns string obtain by joining vector elements. 
";

%feature("docstring")  StringUtil::removeSubstring "std::string StringUtil::removeSubstring(const std::string &text, const std::string &substr)

Removes multiple occurences of given substring from a string and returns result. 
";


// File: FitKernel_8cpp.xml


// File: FitKernel_8h.xml


// File: FitKernelImpl_8cpp.xml


// File: FitKernelImpl_8h.xml


// File: FitOptions_8h.xml


// File: IMinimizer_8cpp.xml


// File: IMinimizer_8h.xml


// File: KernelTypes_8h.xml


// File: MinimizerCatalogue_8cpp.xml


// File: MinimizerCatalogue_8h.xml


// File: MinimizerConstants_8h.xml


// File: MinimizerFactory_8cpp.xml


// File: MinimizerFactory_8h.xml


// File: MinimizerInfo_8cpp.xml


// File: MinimizerInfo_8h.xml


// File: MinimizerOptions_8cpp.xml


// File: MinimizerOptions_8h.xml


// File: MinimizerResultsHelper_8cpp.xml


// File: MinimizerResultsHelper_8h.xml
%feature("docstring")  to_string_with_precision "std::string to_string_with_precision(const T a_value, int precision=10, int width=0)
";

%feature("docstring")  to_string_scientific "std::string to_string_scientific(const T a_value, int n=10)
";


// File: MinimizerUtils_8cpp.xml


// File: MinimizerUtils_8h.xml


// File: MultiOption_8cpp.xml


// File: MultiOption_8h.xml


// File: ObjectiveFunction_8cpp.xml


// File: ObjectiveFunction_8h.xml


// File: OptionContainer_8cpp.xml


// File: OptionContainer_8h.xml


// File: TestMinimizer_8cpp.xml


// File: TestMinimizer_8h.xml


// File: AttLimits_8cpp.xml


// File: AttLimits_8h.xml


// File: Attributes_8h.xml


// File: FitParameter_8cpp.xml


// File: FitParameter_8h.xml


// File: FitParameterSet_8cpp.xml


// File: FitParameterSet_8h.xml


// File: IFitParameter_8h.xml


// File: RealLimits_8cpp.xml


// File: RealLimits_8h.xml


// File: GeneticMinimizer_8cpp.xml


// File: GeneticMinimizer_8h.xml


// File: GSLLevenbergMarquardtMinimizer_8cpp.xml


// File: GSLLevenbergMarquardtMinimizer_8h.xml


// File: GSLMultiMinimizer_8cpp.xml


// File: GSLMultiMinimizer_8h.xml


// File: Minuit2Minimizer_8cpp.xml


// File: Minuit2Minimizer_8h.xml


// File: RootMinimizerAdapter_8cpp.xml


// File: RootMinimizerAdapter_8h.xml


// File: RootMinimizerFunctions_8h.xml


// File: RootObjectiveFuncAdapter_8cpp.xml


// File: RootObjectiveFuncAdapter_8h.xml


// File: SimAnMinimizer_8cpp.xml


// File: SimAnMinimizer_8h.xml


// File: Logger_8cpp.xml


// File: Logger_8h.xml


// File: StringUtils_8cpp.xml


// File: StringUtils_8h.xml


// File: TimeInterval_8cpp.xml


// File: TimeInterval_8h.xml


// File: dir_892d84e8d1420bf45a9053cf0eede900.xml


// File: dir_ddbc8017d498762c6500a9e593e25277.xml


// File: dir_17bde39ef6b5d64be6f6883a061c9058.xml


// File: dir_5e88eb7454533834afc0f9fdcde3e277.xml


// File: dir_c742711e288b52ad835463ef3a11378f.xml

