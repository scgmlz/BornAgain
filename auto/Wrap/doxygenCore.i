
// File: index.xml

// File: classAngularSpecScan.xml
%feature("docstring") AngularSpecScan "

Scan type with inclination angles as coordinate values and a unique wavelength. Features footprint correction.

C++ includes: AngularSpecScan.h
";

%feature("docstring")  AngularSpecScan::AngularSpecScan "AngularSpecScan::AngularSpecScan(double wl, std::vector< double > inc_angle)
";

%feature("docstring")  AngularSpecScan::AngularSpecScan "AngularSpecScan::AngularSpecScan(double wl, const IAxis &inc_angle)
";

%feature("docstring")  AngularSpecScan::AngularSpecScan "AngularSpecScan::AngularSpecScan(double wl, int nbins, double alpha_i_min, double alpha_i_max)

Sets angle-defined specular scan. The first parameter is always a wavelength in nm. Second parameter is either a numpy array of incident angles in radians or an IAxis object with angle values. Alternatively an axis can be defined in-place, then the second passed parameter is the number of bins, third - minimum on-axis angle value, fourth - maximum on-axis angle value. 
";

%feature("docstring")  AngularSpecScan::~AngularSpecScan "AngularSpecScan::~AngularSpecScan() override
";

%feature("docstring")  AngularSpecScan::clone "AngularSpecScan * AngularSpecScan::clone() const override
";

%feature("docstring")  AngularSpecScan::generateSimulationElements "std::vector< SpecularSimulationElement > AngularSpecScan::generateSimulationElements(const Instrument &instrument) const override

Generates simulation elements for specular simulations. 
";

%feature("docstring")  AngularSpecScan::coordinateAxis "virtual const IAxis* AngularSpecScan::coordinateAxis() const override

Returns coordinate axis assigned to the data holder. 
";

%feature("docstring")  AngularSpecScan::footprintFactor "virtual const IFootprintFactor* AngularSpecScan::footprintFactor() const override

Returns IFootprintFactor object pointer. 
";

%feature("docstring")  AngularSpecScan::footprint "std::vector< double > AngularSpecScan::footprint(size_t i, size_t n_elements) const override

Returns footprint correction factor for a range of simulation elements of size  n_elements and starting from element with index  i. 
";

%feature("docstring")  AngularSpecScan::numberOfSimulationElements "size_t AngularSpecScan::numberOfSimulationElements() const override

Returns the number of simulation elements. 
";

%feature("docstring")  AngularSpecScan::createIntensities "std::vector< double > AngularSpecScan::createIntensities(const std::vector< SpecularSimulationElement > &sim_elements) const override

Returns intensity vector corresponding to convolution of given simulation elements. 
";

%feature("docstring")  AngularSpecScan::wavelength "double AngularSpecScan::wavelength() const
";

%feature("docstring")  AngularSpecScan::wavelengthResolution "const ScanResolution* AngularSpecScan::wavelengthResolution() const
";

%feature("docstring")  AngularSpecScan::angleResolution "const ScanResolution* AngularSpecScan::angleResolution() const
";

%feature("docstring")  AngularSpecScan::setFootprintFactor "void AngularSpecScan::setFootprintFactor(const IFootprintFactor *f_factor)

Sets footprint correction factor. 
";

%feature("docstring")  AngularSpecScan::setWavelengthResolution "void AngularSpecScan::setWavelengthResolution(const ScanResolution &resolution)

Sets wavelength resolution values via ScanResolution object. 
";

%feature("docstring")  AngularSpecScan::setRelativeWavelengthResolution "void AngularSpecScan::setRelativeWavelengthResolution(const IRangedDistribution &distr, double rel_dev)
";

%feature("docstring")  AngularSpecScan::setRelativeWavelengthResolution "void AngularSpecScan::setRelativeWavelengthResolution(const IRangedDistribution &distr, const std::vector< double > &rel_dev)

Sets wavelength resolution values via IRangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAbsoluteWavelengthResolution "void AngularSpecScan::setAbsoluteWavelengthResolution(const IRangedDistribution &distr, double std_dev)
";

%feature("docstring")  AngularSpecScan::setAbsoluteWavelengthResolution "void AngularSpecScan::setAbsoluteWavelengthResolution(const IRangedDistribution &distr, const std::vector< double > &std_dev)

Sets wavelength resolution values via IRangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAngleResolution "void AngularSpecScan::setAngleResolution(const ScanResolution &resolution)

Sets angle resolution values via ScanResolution object. 
";

%feature("docstring")  AngularSpecScan::setRelativeAngularResolution "void AngularSpecScan::setRelativeAngularResolution(const IRangedDistribution &distr, double rel_dev)
";

%feature("docstring")  AngularSpecScan::setRelativeAngularResolution "void AngularSpecScan::setRelativeAngularResolution(const IRangedDistribution &distr, const std::vector< double > &rel_dev)

Sets angular resolution values via IRangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAbsoluteAngularResolution "void AngularSpecScan::setAbsoluteAngularResolution(const IRangedDistribution &distr, double std_dev)
";

%feature("docstring")  AngularSpecScan::setAbsoluteAngularResolution "void AngularSpecScan::setAbsoluteAngularResolution(const IRangedDistribution &distr, const std::vector< double > &std_dev)

Sets angular resolution values via IRangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";


// File: classChi2Metric.xml
%feature("docstring") Chi2Metric "

Implementation of the standard  $ \\\\chi^2 $ metric derived from maximum likelihood with Gaussian uncertainties. With default L2 norm corresponds to the formula  \\\\[\\\\chi^2 = \\\\sum \\\\frac{(I - D)^2}{\\\\delta_D^2}\\\\]

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  Chi2Metric::Chi2Metric "Chi2Metric::Chi2Metric()
";

%feature("docstring")  Chi2Metric::clone "Chi2Metric * Chi2Metric::clone() const override
";

%feature("docstring")  Chi2Metric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  Chi2Metric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";


// File: classChiModuleWrapper.xml
%feature("docstring") ChiModuleWrapper "

Metric wrapper for back-compaptibility with old scripts. 
";

%feature("docstring")  ChiModuleWrapper::ChiModuleWrapper "ChiModuleWrapper::ChiModuleWrapper(std::unique_ptr< IChiSquaredModule > module)
";

%feature("docstring")  ChiModuleWrapper::compute "double ChiModuleWrapper::compute(const std::vector< SimDataPair > &fit_objects, size_t n_pars) const override
";


// File: classChiSquaredModule.xml
%feature("docstring") ChiSquaredModule "

Calculation of chi2 between two data sets.

C++ includes: ChiSquaredModule.h
";

%feature("docstring")  ChiSquaredModule::ChiSquaredModule "ChiSquaredModule::ChiSquaredModule()
";

%feature("docstring")  ChiSquaredModule::ChiSquaredModule "ChiSquaredModule::ChiSquaredModule(const ChiSquaredModule &other)
";

%feature("docstring")  ChiSquaredModule::~ChiSquaredModule "virtual ChiSquaredModule::~ChiSquaredModule()
";

%feature("docstring")  ChiSquaredModule::clone "virtual ChiSquaredModule* ChiSquaredModule::clone() const

clone method 
";

%feature("docstring")  ChiSquaredModule::residual "double ChiSquaredModule::residual(double a, double b, double weight)
";


// File: classComponentKeyHandler.xml
%feature("docstring") ComponentKeyHandler "

Stores IComponent instances, associates them with given tag, and provides unique keys.

C++ includes: ComponentKeyHandler.h
";

%feature("docstring")  ComponentKeyHandler::insertModel "void ComponentKeyHandler::insertModel(const std::string &tag, const IComponent *s)
";

%feature("docstring")  ComponentKeyHandler::objectsOfType "std::vector< const T * > ComponentKeyHandler::objectsOfType() const
";

%feature("docstring")  ComponentKeyHandler::obj2key "std::string ComponentKeyHandler::obj2key(const IComponent *s) const
";


// File: classComputationStatus.xml
%feature("docstring") ComputationStatus "

Completion status (flag and text) of a numeric computation.

C++ includes: ComputationStatus.h
";

%feature("docstring")  ComputationStatus::ComputationStatus "ComputationStatus::ComputationStatus()
";

%feature("docstring")  ComputationStatus::isCompleted "bool ComputationStatus::isCompleted() const
";

%feature("docstring")  ComputationStatus::errorMessage "std::string ComputationStatus::errorMessage() const
";

%feature("docstring")  ComputationStatus::setRunning "void ComputationStatus::setRunning()
";

%feature("docstring")  ComputationStatus::setCompleted "void ComputationStatus::setCompleted()
";

%feature("docstring")  ComputationStatus::setFailed "void ComputationStatus::setFailed(const std::string &message)
";


// File: classConstantBackground.xml
%feature("docstring") ConstantBackground "

Class representing a constant background signal

C++ includes: ConstantBackground.h
";

%feature("docstring")  ConstantBackground::ConstantBackground "ConstantBackground::ConstantBackground(const std::vector< double > P)
";

%feature("docstring")  ConstantBackground::ConstantBackground "ConstantBackground::ConstantBackground(double background_value)
";

%feature("docstring")  ConstantBackground::clone "ConstantBackground * ConstantBackground::clone() const final
";

%feature("docstring")  ConstantBackground::backgroundValue "double ConstantBackground::backgroundValue() const
";

%feature("docstring")  ConstantBackground::accept "void ConstantBackground::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  ConstantBackground::addBackground "double ConstantBackground::addBackground(double intensity) const final
";


// File: classDepthProbeComputation.xml
%feature("docstring") DepthProbeComputation "

Performs a single-threaded depth probe computation with given sample.

Controlled by the multi-threading machinery in ISimulation::runSingleSimulation().

C++ includes: DepthProbeComputation.h
";

%feature("docstring")  DepthProbeComputation::DepthProbeComputation "DepthProbeComputation::DepthProbeComputation(const MultiLayer &multilayer, const SimulationOptions &options, ProgressHandler &progress, DepthProbeElementIter begin_it, DepthProbeElementIter end_it)
";

%feature("docstring")  DepthProbeComputation::~DepthProbeComputation "DepthProbeComputation::~DepthProbeComputation() override
";


// File: classDepthProbeComputationTerm.xml
%feature("docstring") DepthProbeComputationTerm "";

%feature("docstring")  DepthProbeComputationTerm::DepthProbeComputationTerm "DepthProbeComputationTerm::DepthProbeComputationTerm(const ProcessedSample *p_sample)
";

%feature("docstring")  DepthProbeComputationTerm::~DepthProbeComputationTerm "DepthProbeComputationTerm::~DepthProbeComputationTerm()
";

%feature("docstring")  DepthProbeComputationTerm::setProgressHandler "void DepthProbeComputationTerm::setProgressHandler(ProgressHandler *p_progress)
";

%feature("docstring")  DepthProbeComputationTerm::compute "void DepthProbeComputationTerm::compute(DepthProbeElement &elem) const
";


// File: classDepthProbeElement.xml
%feature("docstring") DepthProbeElement "";

%feature("docstring")  DepthProbeElement::DepthProbeElement "DepthProbeElement::DepthProbeElement(double wavelength, double alpha_i, const IAxis *z_positions)
";

%feature("docstring")  DepthProbeElement::DepthProbeElement "DepthProbeElement::DepthProbeElement(const DepthProbeElement &other)
";

%feature("docstring")  DepthProbeElement::DepthProbeElement "DepthProbeElement::DepthProbeElement(DepthProbeElement &&other) noexcept
";

%feature("docstring")  DepthProbeElement::~DepthProbeElement "DepthProbeElement::~DepthProbeElement()
";

%feature("docstring")  DepthProbeElement::wavelength "double DepthProbeElement::wavelength() const
";

%feature("docstring")  DepthProbeElement::getAlphaI "double DepthProbeElement::getAlphaI() const
";

%feature("docstring")  DepthProbeElement::getKi "kvector_t DepthProbeElement::getKi() const
";

%feature("docstring")  DepthProbeElement::setIntensities "void DepthProbeElement::setIntensities(T &&intensities)
";

%feature("docstring")  DepthProbeElement::getIntensities "const std::valarray<double>& DepthProbeElement::getIntensities() const
";

%feature("docstring")  DepthProbeElement::setZPositions "void DepthProbeElement::setZPositions(const IAxis *z_positions)
";

%feature("docstring")  DepthProbeElement::getZPositions "const IAxis* DepthProbeElement::getZPositions() const
";

%feature("docstring")  DepthProbeElement::size "size_t DepthProbeElement::size() const
";

%feature("docstring")  DepthProbeElement::setCalculationFlag "void DepthProbeElement::setCalculationFlag(bool calculation_flag)

Set calculation flag (if it's false, zero intensity is assigned to the element) 
";

%feature("docstring")  DepthProbeElement::isCalculated "bool DepthProbeElement::isCalculated() const
";


// File: classDepthProbeSimulation.xml
%feature("docstring") DepthProbeSimulation "";

%feature("docstring")  DepthProbeSimulation::DepthProbeSimulation "DepthProbeSimulation::DepthProbeSimulation()
";

%feature("docstring")  DepthProbeSimulation::~DepthProbeSimulation "DepthProbeSimulation::~DepthProbeSimulation() override
";

%feature("docstring")  DepthProbeSimulation::clone "DepthProbeSimulation * DepthProbeSimulation::clone() const override
";

%feature("docstring")  DepthProbeSimulation::accept "void DepthProbeSimulation::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  DepthProbeSimulation::result "SimulationResult DepthProbeSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
";

%feature("docstring")  DepthProbeSimulation::setBeamParameters "void DepthProbeSimulation::setBeamParameters(double lambda, int nbins, double alpha_i_min, double alpha_i_max, const IFootprintFactor *beam_shape=nullptr)

Sets beam parameters with alpha_i of the beam defined in the range. 
";

%feature("docstring")  DepthProbeSimulation::setZSpan "void DepthProbeSimulation::setZSpan(size_t n_bins, double z_min, double z_max)

Set z positions for intensity calculations. Negative z's correspond to the area under sample surface. The more negative z is, the deeper layer corresponds to it. 
";

%feature("docstring")  DepthProbeSimulation::getAlphaAxis "const IAxis * DepthProbeSimulation::getAlphaAxis() const

Returns a pointer to incident angle axis. 
";

%feature("docstring")  DepthProbeSimulation::getZAxis "const IAxis * DepthProbeSimulation::getZAxis() const

Returns a pointer to z-position axis. 
";

%feature("docstring")  DepthProbeSimulation::intensityMapSize "size_t DepthProbeSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";

%feature("docstring")  DepthProbeSimulation::createUnitConverter "std::unique_ptr< IUnitConverter > DepthProbeSimulation::createUnitConverter() const
";


// File: classDWBAComputation.xml
%feature("docstring") DWBAComputation "

Performs a single-threaded DWBA computation with given sample and simulation parameters.

Controlled by the multi-threading machinery in ISimulation::runSingleSimulation().

C++ includes: DWBAComputation.h
";

%feature("docstring")  DWBAComputation::DWBAComputation "DWBAComputation::DWBAComputation(const MultiLayer &multilayer, const SimulationOptions &options, ProgressHandler &progress, std::vector< SimulationElement >::iterator begin_it, std::vector< SimulationElement >::iterator end_it)
";

%feature("docstring")  DWBAComputation::~DWBAComputation "DWBAComputation::~DWBAComputation() override
";


// File: classDWBASingleComputation.xml
%feature("docstring") DWBASingleComputation "

Class that handles all the computations involved in GISAS (particles, roughness,...) for a single detector bin.

Called by DWBASimulation on each detector bin.

C++ includes: DWBASingleComputation.h
";

%feature("docstring")  DWBASingleComputation::DWBASingleComputation "DWBASingleComputation::DWBASingleComputation()
";

%feature("docstring")  DWBASingleComputation::~DWBASingleComputation "DWBASingleComputation::~DWBASingleComputation()
";

%feature("docstring")  DWBASingleComputation::setProgressHandler "void DWBASingleComputation::setProgressHandler(ProgressHandler *p_progress)
";

%feature("docstring")  DWBASingleComputation::addLayoutComputation "void DWBASingleComputation::addLayoutComputation(ParticleLayoutComputation *p_layout_comp)
";

%feature("docstring")  DWBASingleComputation::setRoughnessComputation "void DWBASingleComputation::setRoughnessComputation(RoughMultiLayerComputation *p_roughness_comp)
";

%feature("docstring")  DWBASingleComputation::setSpecularBinComputation "void DWBASingleComputation::setSpecularBinComputation(GISASSpecularComputation *p_spec_comp)
";

%feature("docstring")  DWBASingleComputation::compute "void DWBASingleComputation::compute(SimulationElement &elem) const
";


// File: classFitObjective.xml
%feature("docstring") FitObjective "

Holds vector of   SimDataPairs (experimental data and simulation results) for use in fitting.

C++ includes: FitObjective.h
";

%feature("docstring")  FitObjective::FitObjective "FitObjective::FitObjective()
";

%feature("docstring")  FitObjective::~FitObjective "FitObjective::~FitObjective()
";

%feature("docstring")  FitObjective::addSimulationAndData "void FitObjective::addSimulationAndData(simulation_builder_t builder, const OutputData< double > &data, std::unique_ptr< OutputData< double >> uncertainties, double weight=1.0)

Constructs simulation/data pair for later fit.

Parameters:
-----------

builder: 
simulation builder capable of producing simulations

data: 
experimental data array

uncertainties: 
data uncertainties array

weight: 
weight of dataset in metric calculations 
";

%feature("docstring")  FitObjective::addSimulationAndData "void FitObjective::addSimulationAndData(PyBuilderCallback &callback, const T &data, double weight=1.0)

Constructs simulation/data pair for later fit.

Parameters:
-----------

callback: 
simulation builder capable of producing simulations

data: 
experimental data array

weight: 
weight of dataset in metric calculations 
";

%feature("docstring")  FitObjective::addSimulationAndData "void FitObjective::addSimulationAndData(PyBuilderCallback &callback, const T &data, const T &uncertainties, double weight=1.0)

Constructs simulation/data pair for later fit.

Parameters:
-----------

callback: 
simulation builder capable of producing simulations

data: 
experimental data array

uncertainties: 
data uncertainties array

weight: 
weight of dataset in metric calculations 
";

%feature("docstring")  FitObjective::evaluate "double FitObjective::evaluate(const mumufit::Parameters &params)
";

%feature("docstring")  FitObjective::evaluate_residuals "std::vector< double > FitObjective::evaluate_residuals(const mumufit::Parameters &params)
";

%feature("docstring")  FitObjective::numberOfFitElements "size_t FitObjective::numberOfFitElements() const
";

%feature("docstring")  FitObjective::simulationResult "SimulationResult FitObjective::simulationResult(size_t i_item=0) const

Returns simulation result in the form of SimulationResult. 
";

%feature("docstring")  FitObjective::experimentalData "SimulationResult FitObjective::experimentalData(size_t i_item=0) const

Returns experimental data in the form of SimulationResult. 
";

%feature("docstring")  FitObjective::uncertaintyData "SimulationResult FitObjective::uncertaintyData(size_t i_item=0) const

Returns experimental data uncertainties in the form of SimulationResult. 
";

%feature("docstring")  FitObjective::relativeDifference "SimulationResult FitObjective::relativeDifference(size_t i_item=0) const

Returns relative difference between simulation and experimental data in the form of SimulationResult. 
";

%feature("docstring")  FitObjective::absoluteDifference "SimulationResult FitObjective::absoluteDifference(size_t i_item=0) const

Returns absolute value of difference between simulation and experimental data in the form of SimulationResult. 
";

%feature("docstring")  FitObjective::experimental_array "std::vector< double > FitObjective::experimental_array() const

Returns one dimensional array representing merged experimental data. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::simulation_array "std::vector< double > FitObjective::simulation_array() const

Returns one dimensional array representing merged simulated intensities data. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::uncertainties "std::vector< double > FitObjective::uncertainties() const

Returns one-dimensional array representing merged data uncertainties. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::weights_array "std::vector< double > FitObjective::weights_array() const

Returns one-dimensional array representing merged user weights. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::initPrint "void FitObjective::initPrint(int every_nth)

Initializes printing to standard output on every_nth fit iteration. 
";

%feature("docstring")  FitObjective::initPlot "void FitObjective::initPlot(int every_nth, PyObserverCallback &callback)

Initializes observer callback to be called on every_nth fit iteration. 
";

%feature("docstring")  FitObjective::iterationInfo "IterationInfo FitObjective::iterationInfo() const
";

%feature("docstring")  FitObjective::minimizerResult "mumufit::MinimizerResult FitObjective::minimizerResult() const
";

%feature("docstring")  FitObjective::finalize "void FitObjective::finalize(const mumufit::MinimizerResult &result)

Should be explicitely called on last iteration to notify all observers. 
";

%feature("docstring")  FitObjective::fitObjectCount "unsigned FitObjective::fitObjectCount() const
";

%feature("docstring")  FitObjective::run_simulations "void FitObjective::run_simulations(const mumufit::Parameters &params)
";

%feature("docstring")  FitObjective::setChiSquaredModule "void FitObjective::setChiSquaredModule(const IChiSquaredModule &module)
";

%feature("docstring")  FitObjective::setObjectiveMetric "void FitObjective::setObjectiveMetric(const std::string &metric)
";

%feature("docstring")  FitObjective::setObjectiveMetric "void FitObjective::setObjectiveMetric(const std::string &metric, const std::string &norm)

Sets objective metric to the  FitObjective.

Parameters:
-----------

metric: 
metric name

norm: 
metric norm name (defaults to L2-norm) 
";

%feature("docstring")  FitObjective::containsUncertainties "bool FitObjective::containsUncertainties(size_t i_item) const

Returns true if the specified DataPair element contains uncertainties. 
";

%feature("docstring")  FitObjective::allPairsHaveUncertainties "bool FitObjective::allPairsHaveUncertainties() const

Returns true if all the data pairs in  FitObjective instance contain uncertainties. 
";

%feature("docstring")  FitObjective::dataPair "const SimDataPair & FitObjective::dataPair(size_t i_item=0) const

Returns a reference to i-th  SimDataPair. 
";

%feature("docstring")  FitObjective::initPlot "void FitObjective::initPlot(int every_nth, fit_observer_t observer)
";

%feature("docstring")  FitObjective::isCompleted "bool FitObjective::isCompleted() const
";

%feature("docstring")  FitObjective::interruptFitting "void FitObjective::interruptFitting()
";

%feature("docstring")  FitObjective::isInterrupted "bool FitObjective::isInterrupted() const
";

%feature("docstring")  FitObjective::isFirstIteration "bool FitObjective::isFirstIteration() const
";

%feature("docstring")  FitObjective::setObjectiveMetric "void FitObjective::setObjectiveMetric(std::unique_ptr< ObjectiveMetric > metric)
";


// File: classFitObserver.xml
%feature("docstring") FitObserver "

Contains collection of observers and call them at specified intervals. Each observer will be called at first iteration and every-nth iterations.

C++ includes: FitObserver.h
";

%feature("docstring")  FitObserver::FitObserver "FitObserver< T >::FitObserver()
";

%feature("docstring")  FitObserver::addObserver "void FitObserver< T >::addObserver(int every_nth, observer_t observer)

Adds observer to the list.

Parameters:
-----------

every_nth: 
An observer function will be called every_nth iterations.

observer: 
Observer function to be called. 
";

%feature("docstring")  FitObserver::notify "void FitObserver< T >::notify(const T &data)

Notifies all observers at their personally specified intervals.

Parameters:
-----------

data: 
The data which will be passed to the observer. 
";

%feature("docstring")  FitObserver::notify_all "void FitObserver< T >::notify_all(const T &data)
";


// File: classFitPrintService.xml
%feature("docstring") FitPrintService "

Prints fit statistics to standard output during minimizer iterations.

C++ includes: FitPrintService.h
";

%feature("docstring")  FitPrintService::FitPrintService "FitPrintService::FitPrintService()
";

%feature("docstring")  FitPrintService::print "void FitPrintService::print(const FitObjective &objective)
";


// File: classFitStatus.xml
%feature("docstring") FitStatus "

Contains status of the fitting (running, interupted etc) and all intermediate information which has to be collected during the fit. Owned by  FitObjective.

C++ includes: FitStatus.h
";

%feature("docstring")  FitStatus::FitStatus "FitStatus::FitStatus(const FitObjective *fit_objective)
";

%feature("docstring")  FitStatus::~FitStatus "FitStatus::~FitStatus()
";

%feature("docstring")  FitStatus::setInterrupted "void FitStatus::setInterrupted()
";

%feature("docstring")  FitStatus::isInterrupted "bool FitStatus::isInterrupted() const
";

%feature("docstring")  FitStatus::isCompleted "bool FitStatus::isCompleted() const
";

%feature("docstring")  FitStatus::update "void FitStatus::update(const mumufit::Parameters &params, double chi2)
";

%feature("docstring")  FitStatus::initPrint "void FitStatus::initPrint(int every_nth)
";

%feature("docstring")  FitStatus::addObserver "void FitStatus::addObserver(int every_nth, fit_observer_t)
";

%feature("docstring")  FitStatus::iterationInfo "IterationInfo FitStatus::iterationInfo() const
";

%feature("docstring")  FitStatus::minimizerResult "mumufit::MinimizerResult FitStatus::minimizerResult() const
";

%feature("docstring")  FitStatus::finalize "void FitStatus::finalize(const mumufit::MinimizerResult &result)

Should be explicitely called on last iteration to notify all observers. 
";


// File: classGISASSimulation.xml
%feature("docstring") GISASSimulation "

Main class to run a Grazing-Incidence Small-Angle Scattering simulation.

C++ includes: GISASSimulation.h
";

%feature("docstring")  GISASSimulation::GISASSimulation "GISASSimulation::GISASSimulation(const Beam &beam, const MultiLayer &sample, const IDetector &detector)
";

%feature("docstring")  GISASSimulation::GISASSimulation "GISASSimulation::GISASSimulation()
";

%feature("docstring")  GISASSimulation::~GISASSimulation "GISASSimulation::~GISASSimulation()
";

%feature("docstring")  GISASSimulation::clone "GISASSimulation* GISASSimulation::clone() const override
";

%feature("docstring")  GISASSimulation::accept "void GISASSimulation::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  GISASSimulation::prepareSimulation "void GISASSimulation::prepareSimulation() override

Put into a clean state for running a simulation. 
";

%feature("docstring")  GISASSimulation::result "SimulationResult GISASSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
";

%feature("docstring")  GISASSimulation::setBeamParameters "void GISASSimulation::setBeamParameters(double wavelength, double alpha_i, double phi_i)

Sets beam parameters from here (forwarded to Instrument) 
";

%feature("docstring")  GISASSimulation::intensityMapSize "size_t GISASSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";


// File: classGISASSpecularComputation.xml
%feature("docstring") GISASSpecularComputation "

Computes the specular signal in the bin where q_parallel = 0. Used by  DWBAComputation.

C++ includes: GISASSpecularComputation.h
";

%feature("docstring")  GISASSpecularComputation::GISASSpecularComputation "GISASSpecularComputation::GISASSpecularComputation(const IFresnelMap *p_fresnel_map)
";

%feature("docstring")  GISASSpecularComputation::compute "void GISASSpecularComputation::compute(SimulationElement &elem) const
";


// File: classIBackground.xml
%feature("docstring") IBackground "

Interface for a simulating the background signal

C++ includes: IBackground.h
";

%feature("docstring")  IBackground::IBackground "IBackground::IBackground(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IBackground::~IBackground "IBackground::~IBackground()
";

%feature("docstring")  IBackground::clone "virtual IBackground* IBackground::clone() const =0
";

%feature("docstring")  IBackground::addBackground "virtual double IBackground::addBackground(double element) const =0
";


// File: classIChiSquaredModule.xml
%feature("docstring") IChiSquaredModule "

Interface residual calculations.

C++ includes: IChiSquaredModule.h
";

%feature("docstring")  IChiSquaredModule::IChiSquaredModule "IChiSquaredModule::IChiSquaredModule()
";

%feature("docstring")  IChiSquaredModule::~IChiSquaredModule "IChiSquaredModule::~IChiSquaredModule()
";

%feature("docstring")  IChiSquaredModule::clone "virtual IChiSquaredModule* IChiSquaredModule::clone() const =0

clone method 
";

%feature("docstring")  IChiSquaredModule::varianceFunction "const IVarianceFunction * IChiSquaredModule::varianceFunction() const

Returns squared function. 
";

%feature("docstring")  IChiSquaredModule::setVarianceFunction "void IChiSquaredModule::setVarianceFunction(const IVarianceFunction &variance_function)

Sets squared function. 
";

%feature("docstring")  IChiSquaredModule::getIntensityFunction "const IIntensityFunction * IChiSquaredModule::getIntensityFunction() const

Returns data rescaler. 
";

%feature("docstring")  IChiSquaredModule::setIntensityFunction "void IChiSquaredModule::setIntensityFunction(const IIntensityFunction &intensity_function)

Sets data rescaler. 
";

%feature("docstring")  IChiSquaredModule::residual "virtual double IChiSquaredModule::residual(double a, double b, double weight)=0
";


// File: classIComputation.xml
%feature("docstring") IComputation "

Interface for a single-threaded computation with given range of SimulationElements and ProgressHandler.

Controlled by the multi-threading machinery in ISimulation::runSingleSimulation().

C++ includes: IComputation.h
";

%feature("docstring")  IComputation::IComputation "IComputation::IComputation(const MultiLayer &sample, const SimulationOptions &options, ProgressHandler &progress)
";

%feature("docstring")  IComputation::~IComputation "IComputation::~IComputation()
";

%feature("docstring")  IComputation::run "void IComputation::run()
";

%feature("docstring")  IComputation::isCompleted "bool IComputation::isCompleted() const
";

%feature("docstring")  IComputation::errorMessage "std::string IComputation::errorMessage() const
";


// File: classIIntensityFunction.xml
%feature("docstring") IIntensityFunction "

Interface for applying arbitrary function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IIntensityFunction::~IIntensityFunction "IIntensityFunction::~IIntensityFunction()
";

%feature("docstring")  IIntensityFunction::clone "virtual IIntensityFunction* IIntensityFunction::clone() const =0
";

%feature("docstring")  IIntensityFunction::evaluate "virtual double IIntensityFunction::evaluate(double value) const =0
";


// File: classIMetricWrapper.xml
%feature("docstring") IMetricWrapper "";

%feature("docstring")  IMetricWrapper::~IMetricWrapper "IMetricWrapper::~IMetricWrapper()
";

%feature("docstring")  IMetricWrapper::compute "virtual double IMetricWrapper::compute(const std::vector< SimDataPair > &fit_objects, size_t n_pars) const =0
";


// File: classIntensityFunctionLog.xml
%feature("docstring") IntensityFunctionLog "

Algorithm for applying log function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IntensityFunctionLog::clone "IntensityFunctionLog * IntensityFunctionLog::clone() const
";

%feature("docstring")  IntensityFunctionLog::evaluate "double IntensityFunctionLog::evaluate(double value) const
";


// File: classIntensityFunctionSqrt.xml
%feature("docstring") IntensityFunctionSqrt "

Algorithm for applying sqrt function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IntensityFunctionSqrt::clone "IntensityFunctionSqrt * IntensityFunctionSqrt::clone() const
";

%feature("docstring")  IntensityFunctionSqrt::evaluate "double IntensityFunctionSqrt::evaluate(double value) const
";


// File: classISimulation.xml
%feature("docstring") ISimulation "

Abstract base class of  OffSpecularSimulation,  GISASSimulation and  SpecularSimulation. Holds the common infrastructure to run a simulation: multithreading, batch processing, weighting over parameter distributions, ...

C++ includes: ISimulation.h
";

%feature("docstring")  ISimulation::ISimulation "ISimulation::ISimulation(const Beam &beam, const MultiLayer &sample, const IDetector &detector)
";

%feature("docstring")  ISimulation::ISimulation "ISimulation::ISimulation()
";

%feature("docstring")  ISimulation::~ISimulation "ISimulation::~ISimulation()
";

%feature("docstring")  ISimulation::clone "virtual ISimulation* ISimulation::clone() const =0
";

%feature("docstring")  ISimulation::prepareSimulation "void ISimulation::prepareSimulation()

Put into a clean state for running a simulation. 
";

%feature("docstring")  ISimulation::runSimulation "void ISimulation::runSimulation()

Run a simulation, possibly averaged over parameter distributions.

Run simulation with possible averaging over parameter distributions. 
";

%feature("docstring")  ISimulation::runMPISimulation "void ISimulation::runMPISimulation()

Run a simulation in a MPI environment. 
";

%feature("docstring")  ISimulation::setInstrument "void ISimulation::setInstrument(const Instrument &instrument_)
";

%feature("docstring")  ISimulation::instrument "const Instrument& ISimulation::instrument() const
";

%feature("docstring")  ISimulation::instrument "Instrument& ISimulation::instrument()
";

%feature("docstring")  ISimulation::beam "Beam& ISimulation::beam()
";

%feature("docstring")  ISimulation::beam "const Beam& ISimulation::beam() const
";

%feature("docstring")  ISimulation::detector "IDetector& ISimulation::detector()
";

%feature("docstring")  ISimulation::detector "const IDetector& ISimulation::detector() const
";

%feature("docstring")  ISimulation::setDetectorResolutionFunction "void ISimulation::setDetectorResolutionFunction(const IResolutionFunction2D &resolution_function)
";

%feature("docstring")  ISimulation::setAnalyzerProperties "void ISimulation::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  ISimulation::setSample "void ISimulation::setSample(const MultiLayer &sample)

The MultiLayer object will not be owned by the  ISimulation object. 
";

%feature("docstring")  ISimulation::sample "const MultiLayer * ISimulation::sample() const
";

%feature("docstring")  ISimulation::setSampleBuilder "void ISimulation::setSampleBuilder(const std::shared_ptr< ISampleBuilder > &sample_builder)
";

%feature("docstring")  ISimulation::setBackground "void ISimulation::setBackground(const IBackground &bg)
";

%feature("docstring")  ISimulation::background "const IBackground* ISimulation::background() const
";

%feature("docstring")  ISimulation::intensityMapSize "virtual size_t ISimulation::intensityMapSize() const =0

Returns the total number of the intensity values in the simulation result. 
";

%feature("docstring")  ISimulation::result "virtual SimulationResult ISimulation::result() const =0

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
";

%feature("docstring")  ISimulation::addParameterDistribution "void ISimulation::addParameterDistribution(const std::string &param_name, const IDistribution1D &distribution, size_t nbr_samples, double sigma_factor=0.0, const RealLimits &limits=RealLimits())
";

%feature("docstring")  ISimulation::addParameterDistribution "void ISimulation::addParameterDistribution(const ParameterDistribution &par_distr)
";

%feature("docstring")  ISimulation::getDistributionHandler "const DistributionHandler& ISimulation::getDistributionHandler() const
";

%feature("docstring")  ISimulation::setOptions "void ISimulation::setOptions(const SimulationOptions &options)
";

%feature("docstring")  ISimulation::getOptions "const SimulationOptions& ISimulation::getOptions() const
";

%feature("docstring")  ISimulation::getOptions "SimulationOptions& ISimulation::getOptions()
";

%feature("docstring")  ISimulation::subscribe "void ISimulation::subscribe(ProgressHandler::Callback_t inform)
";

%feature("docstring")  ISimulation::setTerminalProgressMonitor "void ISimulation::setTerminalProgressMonitor()

Initializes a progress monitor that prints to stdout. 
";

%feature("docstring")  ISimulation::getChildren "std::vector< const INode * > ISimulation::getChildren() const
";

%feature("docstring")  ISimulation::convertData "SimulationResult ISimulation::convertData(const OutputData< double > &data, bool put_masked_areas_to_zero=true)

Convert user data to SimulationResult object for later drawing in various axes units. User data will be cropped to the ROI defined in the simulation, amplitudes in areas corresponding to the masked areas of the detector will be set to zero. 
";


// File: classISimulation2D.xml
%feature("docstring") ISimulation2D "

Abstract base class of  OffSpecularSimulation and  GISASSimulation. Holds the common implementations for simulations with a 2D detector

C++ includes: ISimulation2D.h
";

%feature("docstring")  ISimulation2D::ISimulation2D "ISimulation2D::ISimulation2D(const Beam &beam, const MultiLayer &sample, const IDetector &detector)
";

%feature("docstring")  ISimulation2D::ISimulation2D "ISimulation2D::ISimulation2D()
";

%feature("docstring")  ISimulation2D::~ISimulation2D "ISimulation2D::~ISimulation2D() override
";

%feature("docstring")  ISimulation2D::clone "ISimulation2D* ISimulation2D::clone() const override=0
";

%feature("docstring")  ISimulation2D::prepareSimulation "void ISimulation2D::prepareSimulation() override

Put into a clean state for running a simulation. 
";

%feature("docstring")  ISimulation2D::setDetectorParameters "void ISimulation2D::setDetectorParameters(size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min, double alpha_max)

Sets spherical detector parameters using angle ranges

Parameters:
-----------

n_phi: 
number of phi-axis bins

phi_min: 
low edge of first phi-bin

phi_max: 
upper edge of last phi-bin

n_alpha: 
number of alpha-axis bins

alpha_min: 
low edge of first alpha-bin

alpha_max: 
upper edge of last alpha-bin 
";

%feature("docstring")  ISimulation2D::setDetector "void ISimulation2D::setDetector(const IDetector2D &detector)

Sets the detector (axes can be overwritten later) 
";

%feature("docstring")  ISimulation2D::addMask "void ISimulation2D::addMask(const IShape2D &shape, bool mask_value=true)

Adds mask of given shape to the stack of detector masks. The mask value 'true' means that the channel will be excluded from the simulation. The mask which is added last has priority.

Parameters:
-----------

shape: 
The shape of mask (Rectangle, Polygon, Line, Ellipse)

mask_value: 
The value of mask 
";

%feature("docstring")  ISimulation2D::maskAll "void ISimulation2D::maskAll()

Put the mask for all detector channels (i.e. exclude whole detector from the analysis) 
";

%feature("docstring")  ISimulation2D::setRegionOfInterest "void ISimulation2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)

Sets rectangular region of interest with lower left and upper right corners defined. 
";


// File: classISpecularScan.xml
%feature("docstring") ISpecularScan "

Abstract base class for all types of specular scans.

C++ includes: ISpecularScan.h
";

%feature("docstring")  ISpecularScan::clone "ISpecularScan* ISpecularScan::clone() const override=0
";

%feature("docstring")  ISpecularScan::generateSimulationElements "virtual std::vector<SpecularSimulationElement> ISpecularScan::generateSimulationElements(const Instrument &instrument) const =0

Generates simulation elements for specular simulations. 
";

%feature("docstring")  ISpecularScan::coordinateAxis "virtual const IAxis* ISpecularScan::coordinateAxis() const =0

Returns coordinate axis assigned to the data holder. 
";

%feature("docstring")  ISpecularScan::footprintFactor "virtual const IFootprintFactor* ISpecularScan::footprintFactor() const =0

Returns IFootprintFactor object pointer. 
";

%feature("docstring")  ISpecularScan::footprint "virtual std::vector<double> ISpecularScan::footprint(size_t i, size_t n_elements) const =0

Returns footprint correction factor for a range of simulation elements of size  n_elements and starting from element with index  i. 
";

%feature("docstring")  ISpecularScan::numberOfSimulationElements "virtual size_t ISpecularScan::numberOfSimulationElements() const =0

Returns the number of simulation elements. 
";

%feature("docstring")  ISpecularScan::createIntensities "virtual std::vector<double> ISpecularScan::createIntensities(const std::vector< SpecularSimulationElement > &sim_elements) const =0

Returns intensity vector corresponding to convolution of given simulation elements. 
";


// File: classIterationInfo.xml
%feature("docstring") IterationInfo "

Stores fit iteration info to track fit flow from various observers. Used in context of  FitObjective.

C++ includes: IterationInfo.h
";

%feature("docstring")  IterationInfo::IterationInfo "IterationInfo::IterationInfo()
";

%feature("docstring")  IterationInfo::update "void IterationInfo::update(const mumufit::Parameters &params, double chi2)
";

%feature("docstring")  IterationInfo::iterationCount "unsigned IterationInfo::iterationCount() const

Returns current number of minimizer iterations. 
";

%feature("docstring")  IterationInfo::chi2 "double IterationInfo::chi2() const
";

%feature("docstring")  IterationInfo::parameters "mumufit::Parameters IterationInfo::parameters() const
";

%feature("docstring")  IterationInfo::parameterMap "std::map< std::string, double > IterationInfo::parameterMap() const

Returns map of fit parameter names and its current values. 
";


// File: classIVarianceFunction.xml
%feature("docstring") IVarianceFunction "

Variance function interface.

C++ includes: VarianceFunctions.h
";

%feature("docstring")  IVarianceFunction::IVarianceFunction "IVarianceFunction::IVarianceFunction()=default
";

%feature("docstring")  IVarianceFunction::~IVarianceFunction "virtual IVarianceFunction::~IVarianceFunction()=default
";

%feature("docstring")  IVarianceFunction::IVarianceFunction "IVarianceFunction::IVarianceFunction(const IVarianceFunction &)=delete
";

%feature("docstring")  IVarianceFunction::clone "virtual IVarianceFunction* IVarianceFunction::clone() const =0
";

%feature("docstring")  IVarianceFunction::variance "virtual double IVarianceFunction::variance(double real_value, double simulated_value) const =0
";


// File: classLogMetric.xml
%feature("docstring") LogMetric "

Implementation of the standard  $ \\\\chi^2 $ metric with intensity  $I$ and experimental data  $D$ being replaced by  $ \\\\log_{10} I $ and  $\\\\log_{10} D$ accordingly. With default L2 norm corresponds to the formula  \\\\[\\\\chi^2 = \\\\sum \\\\frac{(\\\\log_{10} I - log_{10} D)^2 D^2 \\\\ln^2{10}}{\\\\delta_D^2}\\\\]

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  LogMetric::LogMetric "LogMetric::LogMetric()
";

%feature("docstring")  LogMetric::clone "LogMetric * LogMetric::clone() const override
";

%feature("docstring")  LogMetric::computeFromArrays "double LogMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  LogMetric::computeFromArrays "double LogMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";


// File: classMaterialKeyHandler.xml
%feature("docstring") MaterialKeyHandler "

Stores Material instances, associates them with given tag, and provides unique keys.

C++ includes: MaterialKeyHandler.h
";

%feature("docstring")  MaterialKeyHandler::insertMaterial "void MaterialKeyHandler::insertMaterial(const Material *sample)
";

%feature("docstring")  MaterialKeyHandler::materialMap "const std::map< const std::string, const Material * > & MaterialKeyHandler::materialMap() const
";

%feature("docstring")  MaterialKeyHandler::mat2key "const std::string & MaterialKeyHandler::mat2key(const Material *sample) const
";


// File: classMPISimulation.xml
%feature("docstring") MPISimulation "";

%feature("docstring")  MPISimulation::runSimulation "void MPISimulation::runSimulation(ISimulation *simulation)
";


// File: classObjectiveMetric.xml
%feature("docstring") ObjectiveMetric "

Base class for metric implementations.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  ObjectiveMetric::ObjectiveMetric "ObjectiveMetric::ObjectiveMetric(std::function< double(double)> norm)
";

%feature("docstring")  ObjectiveMetric::clone "ObjectiveMetric* ObjectiveMetric::clone() const override=0
";

%feature("docstring")  ObjectiveMetric::compute "double ObjectiveMetric::compute(const SimDataPair &data_pair, bool use_weights) const

Computes metric value from  SimDataPair object. Calls computeFromArrays internally.

Parameters:
-----------

data_pair: 
 SimDataPair object. Can optionally contain data uncertainties

use_weights: 
boolean, defines if data uncertainties should be taken into account 
";

%feature("docstring")  ObjectiveMetric::computeFromArrays "virtual double ObjectiveMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const =0

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  ObjectiveMetric::computeFromArrays "virtual double ObjectiveMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const =0

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  ObjectiveMetric::setNorm "void ObjectiveMetric::setNorm(std::function< double(double)> norm)
";

%feature("docstring")  ObjectiveMetric::norm "auto ObjectiveMetric::norm() const

Returns a copy of the normalization function used. 
";


// File: classObjectiveMetricWrapper.xml
%feature("docstring") ObjectiveMetricWrapper "";

%feature("docstring")  ObjectiveMetricWrapper::ObjectiveMetricWrapper "ObjectiveMetricWrapper::ObjectiveMetricWrapper(std::unique_ptr< ObjectiveMetric > module)
";

%feature("docstring")  ObjectiveMetricWrapper::compute "double ObjectiveMetricWrapper::compute(const std::vector< SimDataPair > &fit_objects, size_t n_pars) const override
";


// File: classFitObserver_1_1ObserverData.xml


// File: classOffSpecularSimulation.xml
%feature("docstring") OffSpecularSimulation "

Main class to run an off-specular simulation.

C++ includes: OffSpecularSimulation.h
";

%feature("docstring")  OffSpecularSimulation::OffSpecularSimulation "OffSpecularSimulation::OffSpecularSimulation(const Beam &beam, const MultiLayer &sample, const IDetector &detector)
";

%feature("docstring")  OffSpecularSimulation::OffSpecularSimulation "OffSpecularSimulation::OffSpecularSimulation()
";

%feature("docstring")  OffSpecularSimulation::~OffSpecularSimulation "OffSpecularSimulation::~OffSpecularSimulation() override
";

%feature("docstring")  OffSpecularSimulation::clone "OffSpecularSimulation* OffSpecularSimulation::clone() const override
";

%feature("docstring")  OffSpecularSimulation::accept "void OffSpecularSimulation::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  OffSpecularSimulation::prepareSimulation "void OffSpecularSimulation::prepareSimulation() override

Put into a clean state for running a simulation. 
";

%feature("docstring")  OffSpecularSimulation::result "SimulationResult OffSpecularSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
";

%feature("docstring")  OffSpecularSimulation::setBeamParameters "void OffSpecularSimulation::setBeamParameters(double wavelength, const IAxis &alpha_axis, double phi_i)

Sets beam parameters from here (forwarded to Instrument) 
";

%feature("docstring")  OffSpecularSimulation::beamAxis "const IAxis * OffSpecularSimulation::beamAxis() const

Returns axis of the beam. 
";

%feature("docstring")  OffSpecularSimulation::createUnitConverter "std::unique_ptr< IUnitConverter > OffSpecularSimulation::createUnitConverter() const
";

%feature("docstring")  OffSpecularSimulation::intensityMapSize "size_t OffSpecularSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";


// File: classOutputData.xml
%feature("docstring") OutputData "";


// File: classParticleLayoutComputation.xml
%feature("docstring") ParticleLayoutComputation "

Computes the scattering contribution from one particle layout. Used by  DWBAComputation.

C++ includes: ParticleLayoutComputation.h
";

%feature("docstring")  ParticleLayoutComputation::ParticleLayoutComputation "ParticleLayoutComputation::ParticleLayoutComputation(const ProcessedLayout &layout, const SimulationOptions &options, bool polarized)
";

%feature("docstring")  ParticleLayoutComputation::~ParticleLayoutComputation "ParticleLayoutComputation::~ParticleLayoutComputation()
";

%feature("docstring")  ParticleLayoutComputation::compute "void ParticleLayoutComputation::compute(SimulationElement &elem) const
";

%feature("docstring")  ParticleLayoutComputation::mergeRegionMap "void ParticleLayoutComputation::mergeRegionMap(std::map< size_t, std::vector< HomogeneousRegion >> &region_map) const

Merges its region map into the given one (notice non-const reference parameter) 
";


// File: classPoissonLikeMetric.xml
%feature("docstring") PoissonLikeMetric "

Implementation of  $ \\\\chi^2 $ metric with standard deviation  $\\\\sigma = max(\\\\sqrt{I}, 1)$, where  $I$ is the simulated intensity. With default L2 norm corresponds to the formula  \\\\[\\\\chi^2 = \\\\sum \\\\frac{(I - D)^2}{max(I, 1)}\\\\] for unweighted experimental data. Falls to standard  Chi2Metric when data uncertainties are taken into account.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  PoissonLikeMetric::PoissonLikeMetric "PoissonLikeMetric::PoissonLikeMetric()
";

%feature("docstring")  PoissonLikeMetric::clone "PoissonLikeMetric * PoissonLikeMetric::clone() const override
";

%feature("docstring")  PoissonLikeMetric::computeFromArrays "double PoissonLikeMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  PoissonLikeMetric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  PoissonLikeMetric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";


// File: classPoissonNoiseBackground.xml
%feature("docstring") PoissonNoiseBackground "

Class representing Poisson noise on top of the scattered intensity

C++ includes: PoissonNoiseBackground.h
";

%feature("docstring")  PoissonNoiseBackground::PoissonNoiseBackground "PoissonNoiseBackground::PoissonNoiseBackground()
";

%feature("docstring")  PoissonNoiseBackground::clone "PoissonNoiseBackground * PoissonNoiseBackground::clone() const final
";

%feature("docstring")  PoissonNoiseBackground::accept "void PoissonNoiseBackground::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  PoissonNoiseBackground::addBackground "double PoissonNoiseBackground::addBackground(double intensity) const final
";


// File: classPyBuilderCallback.xml
%feature("docstring") PyBuilderCallback "

Builds simulation object using a Python callable. Base class to wrap Python callable and pass it to C++. Used in swig interface file, intended to be overloaded from Python.

C++ includes: PyFittingCallbacks.h
";

%feature("docstring")  PyBuilderCallback::PyBuilderCallback "PyBuilderCallback::PyBuilderCallback()
";

%feature("docstring")  PyBuilderCallback::~PyBuilderCallback "PyBuilderCallback::~PyBuilderCallback()
";

%feature("docstring")  PyBuilderCallback::build_simulation "ISimulation * PyBuilderCallback::build_simulation(mumufit::Parameters)
";


// File: classPyObserverCallback.xml
%feature("docstring") PyObserverCallback "

Observer for  FitObjective based on Python callable. Base class to wrap Python callable and pass it to C++. Used in swig interface file, intended to be overloaded from Python.

C++ includes: PyFittingCallbacks.h
";

%feature("docstring")  PyObserverCallback::PyObserverCallback "PyObserverCallback::PyObserverCallback()
";

%feature("docstring")  PyObserverCallback::~PyObserverCallback "PyObserverCallback::~PyObserverCallback()
";

%feature("docstring")  PyObserverCallback::update "void PyObserverCallback::update(const FitObjective &)
";


// File: classQSpecScan.xml
%feature("docstring") QSpecScan "

Scan type with z-components of scattering vector as coordinate values. Wavelength and incident angles are not accessible separately.

C++ includes: QSpecScan.h
";

%feature("docstring")  QSpecScan::QSpecScan "QSpecScan::QSpecScan(std::vector< double > qs_nm)

Accepts qz-value vector (in inverse nm) 
";

%feature("docstring")  QSpecScan::QSpecScan "QSpecScan::QSpecScan(const IAxis &qs_nm)
";

%feature("docstring")  QSpecScan::QSpecScan "QSpecScan::QSpecScan(int nbins, double qz_min, double qz_max)

Sets q-defined specular scan. Accepts either numpy array of q-values sorted in ascending order or an IAxis object with q-values. Alternatively an axis can be defined in-place, then the first passed parameter is the number of bins, second - minimum on-axis q-value, third - maximum on-axis q_value. 
";

%feature("docstring")  QSpecScan::~QSpecScan "QSpecScan::~QSpecScan() override
";

%feature("docstring")  QSpecScan::clone "QSpecScan * QSpecScan::clone() const override
";

%feature("docstring")  QSpecScan::resolution "const ScanResolution* QSpecScan::resolution() const
";

%feature("docstring")  QSpecScan::generateSimulationElements "std::vector< SpecularSimulationElement > QSpecScan::generateSimulationElements(const Instrument &instrument) const override

Generates simulation elements for specular simulations. 
";

%feature("docstring")  QSpecScan::coordinateAxis "virtual const IAxis* QSpecScan::coordinateAxis() const override

Returns coordinate axis assigned to the data holder. 
";

%feature("docstring")  QSpecScan::footprintFactor "virtual const IFootprintFactor* QSpecScan::footprintFactor() const override

Returns IFootprintFactor object pointer. 
";

%feature("docstring")  QSpecScan::footprint "std::vector< double > QSpecScan::footprint(size_t i, size_t n_elements) const override

Returns footprint correction factor for a range of simulation elements of size  n_elements and starting from element with index  i. 
";

%feature("docstring")  QSpecScan::numberOfSimulationElements "size_t QSpecScan::numberOfSimulationElements() const override

Returns the number of simulation elements. 
";

%feature("docstring")  QSpecScan::createIntensities "std::vector< double > QSpecScan::createIntensities(const std::vector< SpecularSimulationElement > &sim_elements) const override

Returns intensity vector corresponding to convolution of given simulation elements. 
";

%feature("docstring")  QSpecScan::setQResolution "void QSpecScan::setQResolution(const ScanResolution &resolution)

Sets q resolution values via ScanResolution object. 
";

%feature("docstring")  QSpecScan::setRelativeQResolution "void QSpecScan::setRelativeQResolution(const IRangedDistribution &distr, double rel_dev)
";

%feature("docstring")  QSpecScan::setRelativeQResolution "void QSpecScan::setRelativeQResolution(const IRangedDistribution &distr, const std::vector< double > &rel_dev)

Sets qz resolution values via IRangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the qz-axis. 
";

%feature("docstring")  QSpecScan::setAbsoluteQResolution "void QSpecScan::setAbsoluteQResolution(const IRangedDistribution &distr, double std_dev)
";

%feature("docstring")  QSpecScan::setAbsoluteQResolution "void QSpecScan::setAbsoluteQResolution(const IRangedDistribution &distr, const std::vector< double > &std_dev)

Sets qz resolution values via IRangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the qz-axis. 
";


// File: classRelativeDifferenceMetric.xml
%feature("docstring") RelativeDifferenceMetric "

Implementation of relative difference metric. With default L2 norm and weighting off corresponds to the formula  \\\\[Result = \\\\sum \\\\frac{(I - D)^2}{(I + D)^2}\\\\] where  $I$ is the simulated intensity,  $D$ - experimental data. If weighting is on, falls back to the standard  $\\\\chi^2$ metric.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  RelativeDifferenceMetric::RelativeDifferenceMetric "RelativeDifferenceMetric::RelativeDifferenceMetric()
";

%feature("docstring")  RelativeDifferenceMetric::clone "RelativeDifferenceMetric * RelativeDifferenceMetric::clone() const override
";

%feature("docstring")  RelativeDifferenceMetric::computeFromArrays "double RelativeDifferenceMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  RelativeDifferenceMetric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  RelativeDifferenceMetric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";


// File: classRoughMultiLayerComputation.xml
%feature("docstring") RoughMultiLayerComputation "

Computes the diffuse reflection from the rough interfaces of a multilayer. Used by  DWBAComputation.

C++ includes: RoughMultiLayerComputation.h
";

%feature("docstring")  RoughMultiLayerComputation::RoughMultiLayerComputation "RoughMultiLayerComputation::RoughMultiLayerComputation(const ProcessedSample *p_sample)
";

%feature("docstring")  RoughMultiLayerComputation::compute "void RoughMultiLayerComputation::compute(SimulationElement &elem) const
";


// File: classRQ4Metric.xml
%feature("docstring") RQ4Metric "

Implementation of relative difference metric. With default L2 norm and weighting off corresponds to the formula  \\\\[Result = \\\\sum (I \\\\cdot Q^4 - D \\\\cdot Q^4)^2\\\\] where  $Q$ is the scattering vector magnitude. If weighting is on, coincides with the metric provided by  Chi2Metric class.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  RQ4Metric::RQ4Metric "RQ4Metric::RQ4Metric()
";

%feature("docstring")  RQ4Metric::clone "RQ4Metric * RQ4Metric::clone() const override
";

%feature("docstring")  RQ4Metric::compute "double RQ4Metric::compute(const SimDataPair &data_pair, bool use_weights) const override

Computes metric value from  SimDataPair object. Calls computeFromArrays internally.

Parameters:
-----------

data_pair: 
 SimDataPair object. Can optionally contain data uncertainties

use_weights: 
boolean, defines if data uncertainties should be taken into account 
";


// File: classSampleToPython.xml
%feature("docstring") SampleToPython "

Generates Python code snippet from domain (C++) objects representing sample construction.

C++ includes: SampleToPython.h
";

%feature("docstring")  SampleToPython::SampleToPython "SampleToPython::SampleToPython()
";

%feature("docstring")  SampleToPython::~SampleToPython "SampleToPython::~SampleToPython()
";

%feature("docstring")  SampleToPython::generateSampleCode "std::string SampleToPython::generateSampleCode(const MultiLayer &multilayer)
";


// File: classSimDataPair.xml
%feature("docstring") SimDataPair "

Holds pair of simulation/experimental data to fit.

C++ includes: SimDataPair.h
";

%feature("docstring")  SimDataPair::SimDataPair "SimDataPair::SimDataPair(simulation_builder_t builder, const OutputData< double > &data, std::unique_ptr< OutputData< double >> uncertainties, double user_weight=1.0)
";

%feature("docstring")  SimDataPair::SimDataPair "SimDataPair::SimDataPair(simulation_builder_t builder, const OutputData< double > &data, std::unique_ptr< OutputData< double >> uncertainties, std::unique_ptr< OutputData< double >> user_weights)
";

%feature("docstring")  SimDataPair::SimDataPair "SimDataPair::SimDataPair(SimDataPair &&other)
";

%feature("docstring")  SimDataPair::~SimDataPair "SimDataPair::~SimDataPair()
";

%feature("docstring")  SimDataPair::runSimulation "void SimDataPair::runSimulation(const mumufit::Parameters &params)
";

%feature("docstring")  SimDataPair::containsUncertainties "bool SimDataPair::containsUncertainties() const
";

%feature("docstring")  SimDataPair::numberOfFitElements "size_t SimDataPair::numberOfFitElements() const

Returns the number of elements in the fit area. 
";

%feature("docstring")  SimDataPair::simulationResult "SimulationResult SimDataPair::simulationResult() const

Returns the result of last computed simulation. 
";

%feature("docstring")  SimDataPair::experimentalData "SimulationResult SimDataPair::experimentalData() const

Returns the experimental data cut to the ROI area. 
";

%feature("docstring")  SimDataPair::uncertainties "SimulationResult SimDataPair::uncertainties() const

Returns the data uncertainties cut to the ROI area If no uncertainties present, returns zero-filled SimulationResult. 
";

%feature("docstring")  SimDataPair::userWeights "SimulationResult SimDataPair::userWeights() const

Returns the user uncertainties cut to the ROI area. 
";

%feature("docstring")  SimDataPair::relativeDifference "SimulationResult SimDataPair::relativeDifference() const

Returns relative difference between simulation and experimental data.

Returns the relative difference between simulated and experimental data cut to the ROI area 
";

%feature("docstring")  SimDataPair::absoluteDifference "SimulationResult SimDataPair::absoluteDifference() const

Returns the absolute difference between simulated and experimental data cut to the ROI area 
";

%feature("docstring")  SimDataPair::simulation_array "std::vector< double > SimDataPair::simulation_array() const

Returns the flattened simulated intensities cut to the ROI area. 
";

%feature("docstring")  SimDataPair::experimental_array "std::vector< double > SimDataPair::experimental_array() const

Returns the flattened experimental data cut to the ROI area. 
";

%feature("docstring")  SimDataPair::uncertainties_array "std::vector< double > SimDataPair::uncertainties_array() const

Returns the flattened experimental uncertainties cut to the ROI area. If no uncertainties are available, returns a zero-filled array sized to the ROI area. 
";

%feature("docstring")  SimDataPair::user_weights_array "std::vector< double > SimDataPair::user_weights_array() const

Returns a flat array of user weights cut to the ROI area. 
";


// File: classSimulationFactory.xml
%feature("docstring") SimulationFactory "

Registry to create standard pre-defined simulations. Used in functional tests, performance measurements, etc.

C++ includes: SimulationFactory.h
";

%feature("docstring")  SimulationFactory::SimulationFactory "SimulationFactory::SimulationFactory()
";


// File: classSimulationToPython.xml
%feature("docstring") SimulationToPython "

Write a Python script that allows to run the current simulation.

C++ includes: SimulationToPython.h
";

%feature("docstring")  SimulationToPython::generateSimulationCode "std::string SimulationToPython::generateSimulationCode(const ISimulation &simulation)

Returns a Python script that sets up a simulation and runs it if invoked as main program. 
";


// File: classSpecularComputation.xml
%feature("docstring") SpecularComputation "

Performs a single-threaded specular computation with given sample.

Controlled by the multi-threading machinery in ISimulation::runSingleSimulation().

C++ includes: SpecularComputation.h
";

%feature("docstring")  SpecularComputation::SpecularComputation "SpecularComputation::SpecularComputation(const MultiLayer &multilayer, const SimulationOptions &options, ProgressHandler &progress, SpecularElementIter begin_it, SpecularElementIter end_it)
";

%feature("docstring")  SpecularComputation::~SpecularComputation "SpecularComputation::~SpecularComputation() override
";


// File: classSpecularComputationTerm.xml
%feature("docstring") SpecularComputationTerm "

Computes the specular scattering. Used by  SpecularComputation.

Abstract base class of  SpecularScalarTerm,  SpecularMatrixTerm

C++ includes: SpecularComputationTerm.h
";

%feature("docstring")  SpecularComputationTerm::SpecularComputationTerm "SpecularComputationTerm::SpecularComputationTerm(std::unique_ptr< ISpecularStrategy > strategy)
";

%feature("docstring")  SpecularComputationTerm::~SpecularComputationTerm "SpecularComputationTerm::~SpecularComputationTerm()
";

%feature("docstring")  SpecularComputationTerm::SpecularComputationTerm "SpecularComputationTerm::SpecularComputationTerm(const SpecularComputationTerm &other)=delete
";

%feature("docstring")  SpecularComputationTerm::setProgressHandler "void SpecularComputationTerm::setProgressHandler(ProgressHandler *p_progress)
";

%feature("docstring")  SpecularComputationTerm::computeIntensity "void SpecularComputationTerm::computeIntensity(SpecularSimulationElement &elem, const std::vector< Slice > &slices) const
";


// File: classSpecularMatrixTerm.xml
%feature("docstring") SpecularMatrixTerm "

Computes the specular scattering for a magnetic sample Used by  SpecularComputation.

C++ includes: SpecularComputationTerm.h
";

%feature("docstring")  SpecularMatrixTerm::SpecularMatrixTerm "SpecularMatrixTerm::SpecularMatrixTerm(std::unique_ptr< ISpecularStrategy > strategy)
";


// File: classSpecularScalarTerm.xml
%feature("docstring") SpecularScalarTerm "

Computes the specular scattering for a scalar sample Used by  SpecularComputation.

C++ includes: SpecularComputationTerm.h
";

%feature("docstring")  SpecularScalarTerm::SpecularScalarTerm "SpecularScalarTerm::SpecularScalarTerm(std::unique_ptr< ISpecularStrategy > strategy)
";


// File: classSpecularSimulation.xml
%feature("docstring") SpecularSimulation "

Main class to run a specular simulation.

C++ includes: SpecularSimulation.h
";

%feature("docstring")  SpecularSimulation::SpecularSimulation "SpecularSimulation::SpecularSimulation()
";

%feature("docstring")  SpecularSimulation::~SpecularSimulation "SpecularSimulation::~SpecularSimulation() override
";

%feature("docstring")  SpecularSimulation::clone "SpecularSimulation * SpecularSimulation::clone() const override
";

%feature("docstring")  SpecularSimulation::prepareSimulation "void SpecularSimulation::prepareSimulation() override

Put into a clean state for running a simulation. 
";

%feature("docstring")  SpecularSimulation::accept "void SpecularSimulation::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  SpecularSimulation::result "SimulationResult SpecularSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays. If simulation was not run, returns an array of proper size filled with zeros. 
";

%feature("docstring")  SpecularSimulation::setScan "void SpecularSimulation::setScan(const ISpecularScan &scan)

Sets chosen specular scan to the simulation. 
";

%feature("docstring")  SpecularSimulation::coordinateAxis "const IAxis * SpecularSimulation::coordinateAxis() const

Returns a pointer to coordinate axis. 
";

%feature("docstring")  SpecularSimulation::footprintFactor "const IFootprintFactor * SpecularSimulation::footprintFactor() const

Returns a pointer to footprint factor holder. 
";

%feature("docstring")  SpecularSimulation::intensityMapSize "size_t SpecularSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";

%feature("docstring")  SpecularSimulation::dataHandler "const ISpecularScan* SpecularSimulation::dataHandler() const

Returns internal data handler. 
";


// File: classSpecularSimulationElement.xml
%feature("docstring") SpecularSimulationElement "

Data stucture containing both input and output of a single image pixel for specular simulation.

C++ includes: SpecularSimulationElement.h
";

%feature("docstring")  SpecularSimulationElement::SpecularSimulationElement "SpecularSimulationElement::SpecularSimulationElement(double kz, const Instrument &instrument, bool computable)
";

%feature("docstring")  SpecularSimulationElement::SpecularSimulationElement "SpecularSimulationElement::SpecularSimulationElement(double wavelength, double alpha, const Instrument &instrument, bool computable)
";

%feature("docstring")  SpecularSimulationElement::SpecularSimulationElement "SpecularSimulationElement::SpecularSimulationElement(const SpecularSimulationElement &other)
";

%feature("docstring")  SpecularSimulationElement::SpecularSimulationElement "SpecularSimulationElement::SpecularSimulationElement(SpecularSimulationElement &&other) noexcept
";

%feature("docstring")  SpecularSimulationElement::~SpecularSimulationElement "SpecularSimulationElement::~SpecularSimulationElement()
";

%feature("docstring")  SpecularSimulationElement::polarizationHandler "const PolarizationHandler& SpecularSimulationElement::polarizationHandler() const

Returns assigned PolarizationHandler. 
";

%feature("docstring")  SpecularSimulationElement::intensity "double SpecularSimulationElement::intensity() const
";

%feature("docstring")  SpecularSimulationElement::setIntensity "void SpecularSimulationElement::setIntensity(double intensity)
";

%feature("docstring")  SpecularSimulationElement::isCalculated "bool SpecularSimulationElement::isCalculated() const

Returns calculation flag (if it's false, zero intensity is assigned to the element) 
";

%feature("docstring")  SpecularSimulationElement::produceKz "std::vector< complex_t > SpecularSimulationElement::produceKz(const std::vector< Slice > &slices)

Returns kz values for Abeles computation of reflection/transition coefficients. 
";


// File: classUnitConverter1D.xml
%feature("docstring") UnitConverter1D "

Conversion of axis units for the case of 1D simulation result.

C++ includes: UnitConverter1D.h
";

%feature("docstring")  UnitConverter1D::~UnitConverter1D "UnitConverter1D::~UnitConverter1D() override=default
";

%feature("docstring")  UnitConverter1D::clone "UnitConverter1D* UnitConverter1D::clone() const override=0
";

%feature("docstring")  UnitConverter1D::dimension "size_t UnitConverter1D::dimension() const override

Returns dimensionality of converted canvas. 
";

%feature("docstring")  UnitConverter1D::calculateMin "double UnitConverter1D::calculateMin(size_t i_axis, Axes::Units units_type) const override

Calculates minimum on-axis value in given units. 
";

%feature("docstring")  UnitConverter1D::calculateMax "double UnitConverter1D::calculateMax(size_t i_axis, Axes::Units units_type) const override

Calculates maximum on-axis value in given units. 
";

%feature("docstring")  UnitConverter1D::createConvertedAxis "std::unique_ptr< IAxis > UnitConverter1D::createConvertedAxis(size_t i_axis, Axes::Units units) const override

Creates axis in converted units. 
";

%feature("docstring")  UnitConverter1D::createConvertedData "std::unique_ptr< OutputData< double > > UnitConverter1D::createConvertedData(const OutputData< double > &data, Axes::Units units) const override

Creates  OutputData array in converter units. 
";


// File: classUnitConverterConvSpec.xml
%feature("docstring") UnitConverterConvSpec "

Conversion of axis units for the case of conventional (angle-based) reflectometry.

C++ includes: UnitConverter1D.h
";

%feature("docstring")  UnitConverterConvSpec::UnitConverterConvSpec "UnitConverterConvSpec::UnitConverterConvSpec(const Beam &beam, const IAxis &axis, Axes::Units axis_units=Axes::Units::RADIANS)

Constructs the object for unit conversion. 
";

%feature("docstring")  UnitConverterConvSpec::UnitConverterConvSpec "UnitConverterConvSpec::UnitConverterConvSpec(const AngularSpecScan &handler)
";

%feature("docstring")  UnitConverterConvSpec::~UnitConverterConvSpec "UnitConverterConvSpec::~UnitConverterConvSpec() override
";

%feature("docstring")  UnitConverterConvSpec::clone "UnitConverterConvSpec * UnitConverterConvSpec::clone() const override
";

%feature("docstring")  UnitConverterConvSpec::axisSize "size_t UnitConverterConvSpec::axisSize(size_t i_axis) const override

Returns the size of underlying axis. 
";

%feature("docstring")  UnitConverterConvSpec::availableUnits "std::vector< Axes::Units > UnitConverterConvSpec::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterConvSpec::defaultUnits "Axes::Units UnitConverterConvSpec::defaultUnits() const override

Returns default units to convert to. 
";


// File: classUnitConverterQSpec.xml
%feature("docstring") UnitConverterQSpec "

Conversion of axis units for the case of q-defined reflectometry.

C++ includes: UnitConverter1D.h
";

%feature("docstring")  UnitConverterQSpec::UnitConverterQSpec "UnitConverterQSpec::UnitConverterQSpec(const QSpecScan &handler)
";

%feature("docstring")  UnitConverterQSpec::~UnitConverterQSpec "UnitConverterQSpec::~UnitConverterQSpec() override
";

%feature("docstring")  UnitConverterQSpec::clone "UnitConverterQSpec * UnitConverterQSpec::clone() const override
";

%feature("docstring")  UnitConverterQSpec::axisSize "size_t UnitConverterQSpec::axisSize(size_t i_axis) const override

Returns the size of underlying axis. 
";

%feature("docstring")  UnitConverterQSpec::availableUnits "std::vector< Axes::Units > UnitConverterQSpec::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterQSpec::defaultUnits "Axes::Units UnitConverterQSpec::defaultUnits() const override

Returns default units to convert to. 
";


// File: classVarianceConstantFunction.xml
%feature("docstring") VarianceConstantFunction "

Returns 1.0 as variance value

C++ includes: VarianceFunctions.h
";

%feature("docstring")  VarianceConstantFunction::clone "VarianceConstantFunction * VarianceConstantFunction::clone() const override
";

%feature("docstring")  VarianceConstantFunction::variance "double VarianceConstantFunction::variance(double, double) const override
";


// File: classVarianceSimFunction.xml
%feature("docstring") VarianceSimFunction "

Returns max(sim, epsilon)

C++ includes: VarianceFunctions.h
";

%feature("docstring")  VarianceSimFunction::VarianceSimFunction "VarianceSimFunction::VarianceSimFunction(double epsilon=1.0)
";

%feature("docstring")  VarianceSimFunction::clone "VarianceSimFunction * VarianceSimFunction::clone() const override
";

%feature("docstring")  VarianceSimFunction::variance "double VarianceSimFunction::variance(double exp, double sim) const override
";


// File: namespace_0d15.xml


// File: namespace_0d19.xml


// File: namespace_0d40.xml


// File: namespace_0d42.xml


// File: namespace_0d47.xml


// File: namespace_0d54.xml


// File: namespace_0d56.xml


// File: namespace_0d60.xml


// File: namespace_0d70.xml


// File: namespace_0d75.xml


// File: namespace_0d77.xml


// File: namespace_0d81.xml


// File: namespace_0d91.xml


// File: namespace_0d93.xml


// File: namespace_0d99.xml


// File: namespaceExportToPython.xml
%feature("docstring")  ExportToPython::generateSampleCode "std::string ExportToPython::generateSampleCode(const MultiLayer &multilayer)
";

%feature("docstring")  ExportToPython::generateSimulationCode "std::string ExportToPython::generateSimulationCode(const ISimulation &simulation)
";


// File: namespacemumufit.xml


// File: namespacenode__progeny.xml
%feature("docstring")  node_progeny::ChildNodesOfType "std::vector<const T*> node_progeny::ChildNodesOfType(const INode &node)
";

%feature("docstring")  node_progeny::OnlyChildOfType "const T* node_progeny::OnlyChildOfType(const INode &node)
";

%feature("docstring")  node_progeny::AllDescendantsOfType "std::vector<const T*> node_progeny::AllDescendantsOfType(const INode &node)
";


// File: namespaceObjectiveMetricUtils.xml
%feature("docstring")  ObjectiveMetricUtils::l1Norm "const std::function< double(double)> ObjectiveMetricUtils::l1Norm()

Returns L1 normalization function. 
";

%feature("docstring")  ObjectiveMetricUtils::l2Norm "const std::function< double(double)> ObjectiveMetricUtils::l2Norm()

Returns L2 normalization function. 
";

%feature("docstring")  ObjectiveMetricUtils::createMetric "std::unique_ptr< ObjectiveMetric > ObjectiveMetricUtils::createMetric(const std::string &metric)

Creates the specified metric with the default norm. 
";

%feature("docstring")  ObjectiveMetricUtils::createMetric "std::unique_ptr< ObjectiveMetric > ObjectiveMetricUtils::createMetric(std::string metric, std::string norm)

Creates the metric with the specified norm. 
";

%feature("docstring")  ObjectiveMetricUtils::availableMetricOptions "std::string ObjectiveMetricUtils::availableMetricOptions()

Prints available metric options. 
";

%feature("docstring")  ObjectiveMetricUtils::normNames "std::vector< std::string > ObjectiveMetricUtils::normNames()

Returns the names of the norms used by  ObjectiveMetric. 
";

%feature("docstring")  ObjectiveMetricUtils::metricNames "std::vector< std::string > ObjectiveMetricUtils::metricNames()

Returns the names of the objective metrics used. 
";

%feature("docstring")  ObjectiveMetricUtils::defaultNormName "std::string ObjectiveMetricUtils::defaultNormName()

Returns default norm name. 
";

%feature("docstring")  ObjectiveMetricUtils::defaultMetricName "std::string ObjectiveMetricUtils::defaultMetricName()

Returns default metric name. 
";


// File: namespacepyfmt.xml
%feature("docstring")  pyfmt::scriptPreamble "std::string pyfmt::scriptPreamble()
";

%feature("docstring")  pyfmt::printBool "std::string pyfmt::printBool(double value)
";

%feature("docstring")  pyfmt::printDouble "std::string pyfmt::printDouble(double input)
";

%feature("docstring")  pyfmt::printNm "std::string pyfmt::printNm(double input)
";

%feature("docstring")  pyfmt::printNm2 "std::string pyfmt::printNm2(double input)
";

%feature("docstring")  pyfmt::printScientificDouble "std::string pyfmt::printScientificDouble(double input)
";

%feature("docstring")  pyfmt::printDegrees "std::string pyfmt::printDegrees(double input)
";

%feature("docstring")  pyfmt::printValue "std::string pyfmt::printValue(double value, const std::string &units)
";

%feature("docstring")  pyfmt::printString "std::string pyfmt::printString(const std::string &value)
";

%feature("docstring")  pyfmt::isSquare "bool pyfmt::isSquare(double length1, double length2, double angle)
";

%feature("docstring")  pyfmt::isHexagonal "bool pyfmt::isHexagonal(double length1, double length2, double angle)
";

%feature("docstring")  pyfmt::printKvector "std::string pyfmt::printKvector(const kvector_t value)
";

%feature("docstring")  pyfmt::indent "std::string pyfmt::indent(size_t width)

Returns a string of blanks with given width. By default the width equals standard offset in python files. 
";

%feature("docstring")  pyfmt::printInt "std::string pyfmt::printInt(int value)
";

%feature("docstring")  pyfmt::printRealLimits "std::string pyfmt::printRealLimits(const RealLimits &limits, const std::string &units)
";

%feature("docstring")  pyfmt::printRealLimitsArg "std::string pyfmt::printRealLimitsArg(const RealLimits &limits, const std::string &units)

Prints RealLimits in the form of argument (in the context of ParameterDistribution and similar). Default RealLimits will not be printed, any other will be printed as \", ba.RealLimits.limited(1*deg, 2*deg)\" 
";


// File: namespacepyfmt2.xml
%feature("docstring")  pyfmt2::representShape2D "std::string pyfmt2::representShape2D(const std::string &indent, const IShape2D *ishape, bool mask_value, std::function< std::string(double)> printValueFunc)

Returns fixed Python code snippet that defines the function \"runSimulation\". 
";

%feature("docstring")  pyfmt2::valueTimesUnit "std::string pyfmt2::valueTimesUnit(const RealParameter *par)

Returns parameter value, followed by its unit multiplicator (like \"* nm\"). 
";

%feature("docstring")  pyfmt2::argumentList "std::string pyfmt2::argumentList(const IParametricComponent *ip)

Returns comma-separated list of parameter values, including unit multiplicator (like \"* nm\"). 
";

%feature("docstring")  pyfmt2::printAxis "std::string pyfmt2::printAxis(const IAxis *axis, const std::string &unit)

Prints an axis. 
";

%feature("docstring")  pyfmt2::printDistribution "std::string pyfmt2::printDistribution(const IDistribution1D &par_distr, const std::string &units)

Prints distribution with constructor parameters in given units. ba.DistributionGaussian(2.0*deg, 0.02*deg) 
";

%feature("docstring")  pyfmt2::printParameterDistribution "std::string pyfmt2::printParameterDistribution(const ParameterDistribution &par_distr, const std::string &distVarName, const std::string &units)
";

%feature("docstring")  pyfmt2::printRangedDistribution "std::string pyfmt2::printRangedDistribution(const IRangedDistribution &distr)
";


// File: namespaceStandardSimulations.xml
%feature("docstring")  StandardSimulations::BasicGISAS "GISASSimulation * StandardSimulations::BasicGISAS()

Basic GISAS simulation with the detector phi[0,2], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::BasicGISAS00 "GISASSimulation * StandardSimulations::BasicGISAS00()

Basic GISAS for polarization studies. 
";

%feature("docstring")  StandardSimulations::BasicPolarizedGISAS "GISASSimulation * StandardSimulations::BasicPolarizedGISAS()

Basic GISAS simulation for spin flip channel. 
";

%feature("docstring")  StandardSimulations::MiniGISAS "GISASSimulation * StandardSimulations::MiniGISAS()

GISAS simulation with small detector and phi[-2,2], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::MiniGISAS_v2 "GISASSimulation * StandardSimulations::MiniGISAS_v2()

GISAS simulation with small detector and phi[-1,1], theta[0,1]. 
";

%feature("docstring")  StandardSimulations::MiniGISASBeamDivergence "GISASSimulation * StandardSimulations::MiniGISASBeamDivergence()

GISAS simulation with beam divergence applied. 
";

%feature("docstring")  StandardSimulations::MiniGISASDetectorResolution "GISASSimulation * StandardSimulations::MiniGISASDetectorResolution()

GISAS simulation with detector resolution. 
";

%feature("docstring")  StandardSimulations::MiniGISASSpecularPeak "GISASSimulation * StandardSimulations::MiniGISASSpecularPeak()

GISAS simulation with small detector and including specular peak. 
";

%feature("docstring")  StandardSimulations::GISASWithMasks "GISASSimulation * StandardSimulations::GISASWithMasks()

GISAS simulation with multiple masks on the detector plane. 
";

%feature("docstring")  StandardSimulations::MaxiGISAS "GISASSimulation * StandardSimulations::MaxiGISAS()

GISAS simulation with large detector to test performance. 
";

%feature("docstring")  StandardSimulations::MaxiGISAS00 "GISASSimulation * StandardSimulations::MaxiGISAS00()

Basic GISAS for polarization studies. 
";

%feature("docstring")  StandardSimulations::IsGISAXSSimulation1 "GISASSimulation * StandardSimulations::IsGISAXSSimulation1()

Typical IsGISAXS simulation with the detector phi[-1,1], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::IsGISAXSSimulation2 "GISASSimulation * StandardSimulations::IsGISAXSSimulation2()

Typical IsGISAXS simulation with the detector phi[0,2], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::RectDetectorGeneric "GISASSimulation * StandardSimulations::RectDetectorGeneric()

GISAS simulation with generic rectangular detector. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToSample "GISASSimulation * StandardSimulations::RectDetectorPerpToSample()

GISAS simulation with the rectangular detector perpendicular to the sample. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToDirectBeam "GISASSimulation * StandardSimulations::RectDetectorPerpToDirectBeam()

GISAS simulation with the rectangular detector perpendicular to the direct beam. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToReflectedBeam "GISASSimulation * StandardSimulations::RectDetectorPerpToReflectedBeam()

GISAS simulation with the rectangular detector perpendicular to the reflected beam. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToReflectedBeamDpos "GISASSimulation * StandardSimulations::RectDetectorPerpToReflectedBeamDpos()

GISAS simulation with the rectangular detector perpendicular to the reflected beam when the coordinates of direct beam are known. 
";

%feature("docstring")  StandardSimulations::MiniGISASMonteCarlo "GISASSimulation * StandardSimulations::MiniGISASMonteCarlo()

GISAS simulation with Monte-Carlo integration switched ON. 
";

%feature("docstring")  StandardSimulations::SphericalDetWithRoi "GISASSimulation * StandardSimulations::SphericalDetWithRoi()

GISAS simulation with spherical detector, region of interest and mask. 
";

%feature("docstring")  StandardSimulations::RectDetWithRoi "GISASSimulation * StandardSimulations::RectDetWithRoi()

GISAS simulation with rectangular detector, region of interest and mask. 
";

%feature("docstring")  StandardSimulations::ConstantBackgroundGISAS "GISASSimulation * StandardSimulations::ConstantBackgroundGISAS()
";

%feature("docstring")  StandardSimulations::MiniGISASFit "GISASSimulation * StandardSimulations::MiniGISASFit()

ISimulation with fitting. Beam intensity set to provide reasonably large values in detector channels. 
";

%feature("docstring")  StandardSimulations::ExtraLongWavelengthGISAS "GISASSimulation * StandardSimulations::ExtraLongWavelengthGISAS()

GISAS simulation with an extra long wavelength. 
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationPP "GISASSimulation * StandardSimulations::MiniGISASPolarizationPP()
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationPM "GISASSimulation * StandardSimulations::MiniGISASPolarizationPM()
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationMP "GISASSimulation * StandardSimulations::MiniGISASPolarizationMP()
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationMM "GISASSimulation * StandardSimulations::MiniGISASPolarizationMM()
";

%feature("docstring")  StandardSimulations::BasicSpecular "SpecularSimulation * StandardSimulations::BasicSpecular()
";

%feature("docstring")  StandardSimulations::BasicSpecularQ "SpecularSimulation * StandardSimulations::BasicSpecularQ()
";

%feature("docstring")  StandardSimulations::SpecularWithGaussianBeam "SpecularSimulation * StandardSimulations::SpecularWithGaussianBeam()
";

%feature("docstring")  StandardSimulations::SpecularWithSquareBeam "SpecularSimulation * StandardSimulations::SpecularWithSquareBeam()
";

%feature("docstring")  StandardSimulations::SpecularDivergentBeam "SpecularSimulation * StandardSimulations::SpecularDivergentBeam()
";

%feature("docstring")  StandardSimulations::TOFRWithRelativeResolution "SpecularSimulation * StandardSimulations::TOFRWithRelativeResolution()
";

%feature("docstring")  StandardSimulations::TOFRWithPointwiseResolution "SpecularSimulation * StandardSimulations::TOFRWithPointwiseResolution()
";

%feature("docstring")  StandardSimulations::BasicSpecularPP "SpecularSimulation * StandardSimulations::BasicSpecularPP()
";

%feature("docstring")  StandardSimulations::BasicSpecularMM "SpecularSimulation * StandardSimulations::BasicSpecularMM()
";

%feature("docstring")  StandardSimulations::BasicSpecularPM "SpecularSimulation * StandardSimulations::BasicSpecularPM()
";

%feature("docstring")  StandardSimulations::BasicSpecularMP "SpecularSimulation * StandardSimulations::BasicSpecularMP()
";

%feature("docstring")  StandardSimulations::BasicSpecularQPP "SpecularSimulation * StandardSimulations::BasicSpecularQPP()
";

%feature("docstring")  StandardSimulations::BasicSpecularQMM "SpecularSimulation * StandardSimulations::BasicSpecularQMM()
";

%feature("docstring")  StandardSimulations::BasicSpecularQPM "SpecularSimulation * StandardSimulations::BasicSpecularQPM()
";

%feature("docstring")  StandardSimulations::BasicSpecularQMP "SpecularSimulation * StandardSimulations::BasicSpecularQMP()
";

%feature("docstring")  StandardSimulations::MiniOffSpecular "OffSpecularSimulation * StandardSimulations::MiniOffSpecular()
";

%feature("docstring")  StandardSimulations::BasicDepthProbe "DepthProbeSimulation * StandardSimulations::BasicDepthProbe()
";


// File: namespaceUnitConverterUtils.xml
%feature("docstring")  UnitConverterUtils::createOutputData "std::unique_ptr< OutputData< double > > UnitConverterUtils::createOutputData(const IUnitConverter &converter, Axes::Units units)

Returns zero-valued output data array in specified units. 
";

%feature("docstring")  UnitConverterUtils::createConverterForGISAS "std::unique_ptr< IUnitConverter > UnitConverterUtils::createConverterForGISAS(const Instrument &instrument)

Helper factory function to use in  GISASSimulation. Depending on the type of detector, returns either RectangularConverter or SphericalConverter. 
";

%feature("docstring")  UnitConverterUtils::createConverter "std::unique_ptr< IUnitConverter > UnitConverterUtils::createConverter(const ISimulation &simulation)
";


// File: ComputationStatus_8h.xml


// File: ConstantBackground_8cpp.xml


// File: ConstantBackground_8h.xml


// File: DepthProbeComputation_8cpp.xml


// File: DepthProbeComputation_8h.xml


// File: DWBAComputation_8cpp.xml


// File: DWBAComputation_8h.xml


// File: DWBASingleComputation_8cpp.xml


// File: DWBASingleComputation_8h.xml


// File: GISASSpecularComputation_8cpp.xml


// File: GISASSpecularComputation_8h.xml


// File: IBackground_8cpp.xml


// File: IBackground_8h.xml


// File: IComputation_8cpp.xml


// File: IComputation_8h.xml


// File: ParticleLayoutComputation_8cpp.xml


// File: ParticleLayoutComputation_8h.xml


// File: PoissonNoiseBackground_8cpp.xml


// File: PoissonNoiseBackground_8h.xml


// File: RoughMultiLayerComputation_8cpp.xml


// File: RoughMultiLayerComputation_8h.xml


// File: SpecularComputation_8cpp.xml


// File: SpecularComputation_8h.xml


// File: DepthProbeElement_8cpp.xml


// File: DepthProbeElement_8h.xml


// File: SpecularSimulationElement_8cpp.xml


// File: SpecularSimulationElement_8h.xml


// File: ComponentKeyHandler_8cpp.xml


// File: ComponentKeyHandler_8h.xml


// File: ExportToPython_8cpp.xml


// File: ExportToPython_8h.xml


// File: MaterialKeyHandler_8cpp.xml


// File: MaterialKeyHandler_8h.xml


// File: NodeProgeny_8h.xml


// File: PyFmt_8cpp.xml


// File: PyFmt_8h.xml


// File: PyFmt2_8cpp.xml


// File: PyFmt2_8h.xml


// File: PyFmtLimits_8cpp.xml


// File: PyFmtLimits_8h.xml


// File: SampleToPython_8cpp.xml


// File: SampleToPython_8h.xml


// File: SimulationToPython_8cpp.xml


// File: SimulationToPython_8h.xml


// File: FitObjective_8cpp.xml


// File: FitObjective_8h.xml


// File: FitObserver_8h.xml


// File: FitPrintService_8cpp.xml


// File: FitPrintService_8h.xml


// File: FitStatus_8cpp.xml


// File: FitStatus_8h.xml


// File: FitTypes_8h.xml


// File: IterationInfo_8cpp.xml


// File: IterationInfo_8h.xml


// File: ObjectiveMetric_8cpp.xml


// File: ObjectiveMetric_8h.xml


// File: ObjectiveMetricUtils_8cpp.xml


// File: ObjectiveMetricUtils_8h.xml


// File: PyFittingCallbacks_8cpp.xml


// File: PyFittingCallbacks_8h.xml


// File: SimDataPair_8cpp.xml


// File: SimDataPair_8h.xml


// File: ChiSquaredModule_8cpp.xml


// File: ChiSquaredModule_8h.xml


// File: IChiSquaredModule_8cpp.xml


// File: IChiSquaredModule_8h.xml


// File: IIntensityFunction_8cpp.xml


// File: IIntensityFunction_8h.xml


// File: VarianceFunctions_8cpp.xml


// File: VarianceFunctions_8h.xml


// File: AngularSpecScan_8cpp.xml


// File: AngularSpecScan_8h.xml


// File: ISpecularScan_8h.xml


// File: QSpecScan_8cpp.xml


// File: QSpecScan_8h.xml


// File: UnitConverter1D_8cpp.xml


// File: UnitConverter1D_8h.xml


// File: DepthProbeSimulation_8cpp.xml


// File: DepthProbeSimulation_8h.xml


// File: GISASSimulation_8cpp.xml


// File: GISASSimulation_8h.xml


// File: ISimulation_8cpp.xml


// File: ISimulation_8h.xml


// File: ISimulation2D_8cpp.xml


// File: ISimulation2D_8h.xml


// File: MPISimulation_8cpp.xml


// File: MPISimulation_8h.xml


// File: OffSpecularSimulation_8cpp.xml


// File: OffSpecularSimulation_8h.xml


// File: SimulationFactory_8cpp.xml


// File: SimulationFactory_8h.xml


// File: SpecularSimulation_8cpp.xml


// File: SpecularSimulation_8h.xml


// File: StandardSimulations_8cpp.xml


// File: StandardSimulations_8h.xml


// File: UnitConverterUtils_8cpp.xml


// File: UnitConverterUtils_8h.xml


// File: DepthProbeComputationTerm_8cpp.xml


// File: DepthProbeComputationTerm_8h.xml


// File: SpecularComputationTerm_8cpp.xml


// File: SpecularComputationTerm_8h.xml


// File: dir_7de90f35ae2a2c7b4fa95823d333cc96.xml


// File: dir_c6310732a22f63c0c2fc5595561e68f1.xml


// File: dir_e40015403c3f1f9058463bc2c73ff8d5.xml


// File: dir_cca9b87b2505f372a6ce58947a507789.xml


// File: dir_4470199ae7eb44153ffe31d163ed0f28.xml


// File: dir_bfeb1e458a74587b0ec5055179ee8176.xml


// File: dir_6de83e740cfcd9d0abfe8dffab2832a5.xml


// File: dir_d7a24665a95cfc15308ebd7b07b5ebd6.xml


// File: dir_52128420a621ebf8ad4a4626c50b78b3.xml

