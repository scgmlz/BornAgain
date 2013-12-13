// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
#include "PythonCoreList.h"
#include "LayerRoughness.pypp.h"

namespace bp = boost::python;

struct LayerRoughness_wrapper : LayerRoughness, bp::wrapper< LayerRoughness > {

    LayerRoughness_wrapper( )
    : LayerRoughness( )
      , bp::wrapper< LayerRoughness >(){
        // null constructor
    
    }

    LayerRoughness_wrapper(double sigma, double hurstParameter, double latteralCorrLength )
    : LayerRoughness( sigma, hurstParameter, latteralCorrLength )
      , bp::wrapper< LayerRoughness >(){
        // constructor
    
    }

    virtual ::LayerRoughness * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->LayerRoughness::clone(  );
        }
    }
    
    ::LayerRoughness * default_clone(  ) const  {
        return LayerRoughness::clone( );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else{
            return this->IParameterized::areParametersChanged(  );
        }
    }
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else{
            this->IParameterized::clearParameterPool(  );
        }
    }
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual ::ISample * cloneInvertB(  ) const  {
        if( bp::override func_cloneInvertB = this->get_override( "cloneInvertB" ) )
            return func_cloneInvertB(  );
        else{
            return this->ISample::cloneInvertB(  );
        }
    }
    
    ::ISample * default_cloneInvertB(  ) const  {
        return ISample::cloneInvertB( );
    }

    virtual bool containsMagneticMaterial(  ) const  {
        if( bp::override func_containsMagneticMaterial = this->get_override( "containsMagneticMaterial" ) )
            return func_containsMagneticMaterial(  );
        else{
            return this->ISample::containsMagneticMaterial(  );
        }
    }
    
    bool default_containsMagneticMaterial(  ) const  {
        return ISample::containsMagneticMaterial( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else{
            return this->IParameterized::createParameterTree(  );
        }
    }
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual ::ICompositeSample * getCompositeSample(  ) {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ISample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ISample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ISample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ISample::getCompositeSample( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else{
            this->IParameterized::printParameters(  );
        }
    }
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void printSampleTree(  ) {
        if( bp::override func_printSampleTree = this->get_override( "printSampleTree" ) )
            func_printSampleTree(  );
        else{
            this->ISample::printSampleTree(  );
        }
    }
    
    void default_printSampleTree(  ) {
        ISample::printSampleTree( );
    }

    virtual void registerParameter( ::std::string const & name, double * parpointer ) {
        namespace bpl = boost::python;
        if( bpl::override func_registerParameter = this->get_override( "registerParameter" ) ){
            bpl::object py_result = bpl::call<bpl::object>( func_registerParameter.ptr(), name, parpointer );
        }
        else{
            IParameterized::registerParameter( name, parpointer );
        }
    }
    
    static void default_registerParameter( ::IParameterized & inst, ::std::string const & name, long unsigned int parpointer ){
        if( dynamic_cast< LayerRoughness_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else{
            return this->IParameterized::setParameterValue( name, value );
        }
    }
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else{
            this->IParameterized::setParametersAreChanged(  );
        }
    }
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

};

void register_LayerRoughness_class(){

    { //::LayerRoughness
        typedef bp::class_< LayerRoughness_wrapper, boost::noncopyable > LayerRoughness_exposer_t;
        LayerRoughness_exposer_t LayerRoughness_exposer = LayerRoughness_exposer_t( "LayerRoughness", bp::init< >() );
        bp::scope LayerRoughness_scope( LayerRoughness_exposer );
        LayerRoughness_exposer.def( bp::init< double, double, double >(( bp::arg("sigma"), bp::arg("hurstParameter"), bp::arg("latteralCorrLength") )) );
        { //::LayerRoughness::clone
        
            typedef ::LayerRoughness * ( ::LayerRoughness::*clone_function_type )(  ) const;
            typedef ::LayerRoughness * ( LayerRoughness_wrapper::*default_clone_function_type )(  ) const;
            
            LayerRoughness_exposer.def( 
                "clone"
                , clone_function_type(&::LayerRoughness::clone)
                , default_clone_function_type(&LayerRoughness_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::LayerRoughness::getCorrFun
        
            typedef double ( ::LayerRoughness::*getCorrFun_function_type )( ::kvector_t const & ) const;
            
            LayerRoughness_exposer.def( 
                "getCorrFun"
                , getCorrFun_function_type( &::LayerRoughness::getCorrFun )
                , ( bp::arg("k") ) );
        
        }
        { //::LayerRoughness::getHurstParameter
        
            typedef double ( ::LayerRoughness::*getHurstParameter_function_type )(  ) const;
            
            LayerRoughness_exposer.def( 
                "getHurstParameter"
                , getHurstParameter_function_type( &::LayerRoughness::getHurstParameter ) );
        
        }
        { //::LayerRoughness::getLatteralCorrLength
        
            typedef double ( ::LayerRoughness::*getLatteralCorrLength_function_type )(  ) const;
            
            LayerRoughness_exposer.def( 
                "getLatteralCorrLength"
                , getLatteralCorrLength_function_type( &::LayerRoughness::getLatteralCorrLength ) );
        
        }
        { //::LayerRoughness::getSigma
        
            typedef double ( ::LayerRoughness::*getSigma_function_type )(  ) const;
            
            LayerRoughness_exposer.def( 
                "getSigma"
                , getSigma_function_type( &::LayerRoughness::getSigma ) );
        
        }
        { //::LayerRoughness::getSpectralFun
        
            typedef double ( ::LayerRoughness::*getSpectralFun_function_type )( ::kvector_t const & ) const;
            
            LayerRoughness_exposer.def( 
                "getSpectralFun"
                , getSpectralFun_function_type( &::LayerRoughness::getSpectralFun )
                , ( bp::arg("kvec") ) );
        
        }
        { //::LayerRoughness::setHurstParameter
        
            typedef void ( ::LayerRoughness::*setHurstParameter_function_type )( double ) ;
            
            LayerRoughness_exposer.def( 
                "setHurstParameter"
                , setHurstParameter_function_type( &::LayerRoughness::setHurstParameter )
                , ( bp::arg("hurstParameter") ) );
        
        }
        { //::LayerRoughness::setLatteralCorrLength
        
            typedef void ( ::LayerRoughness::*setLatteralCorrLength_function_type )( double ) ;
            
            LayerRoughness_exposer.def( 
                "setLatteralCorrLength"
                , setLatteralCorrLength_function_type( &::LayerRoughness::setLatteralCorrLength )
                , ( bp::arg("latteralCorrLength") ) );
        
        }
        { //::LayerRoughness::setSigma
        
            typedef void ( ::LayerRoughness::*setSigma_function_type )( double ) ;
            
            LayerRoughness_exposer.def( 
                "setSigma"
                , setSigma_function_type( &::LayerRoughness::setSigma )
                , ( bp::arg("sigma") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( LayerRoughness_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            LayerRoughness_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&LayerRoughness_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( LayerRoughness_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            LayerRoughness_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&LayerRoughness_wrapper::default_clearParameterPool) );
        
        }
        { //::ISample::cloneInvertB
        
            typedef ::ISample * ( ::ISample::*cloneInvertB_function_type )(  ) const;
            typedef ::ISample * ( LayerRoughness_wrapper::*default_cloneInvertB_function_type )(  ) const;
            
            LayerRoughness_exposer.def( 
                "cloneInvertB"
                , cloneInvertB_function_type(&::ISample::cloneInvertB)
                , default_cloneInvertB_function_type(&LayerRoughness_wrapper::default_cloneInvertB)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ISample::containsMagneticMaterial
        
            typedef bool ( ::ISample::*containsMagneticMaterial_function_type )(  ) const;
            typedef bool ( LayerRoughness_wrapper::*default_containsMagneticMaterial_function_type )(  ) const;
            
            LayerRoughness_exposer.def( 
                "containsMagneticMaterial"
                , containsMagneticMaterial_function_type(&::ISample::containsMagneticMaterial)
                , default_containsMagneticMaterial_function_type(&LayerRoughness_wrapper::default_containsMagneticMaterial) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( LayerRoughness_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            LayerRoughness_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&LayerRoughness_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ISample::getCompositeSample
        
            typedef ::ICompositeSample * ( ::ISample::*getCompositeSample_function_type )(  ) ;
            typedef ::ICompositeSample * ( LayerRoughness_wrapper::*default_getCompositeSample_function_type )(  ) ;
            
            LayerRoughness_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ISample::getCompositeSample)
                , default_getCompositeSample_function_type(&LayerRoughness_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ISample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ISample::*getCompositeSample_function_type )(  ) const;
            typedef ::ICompositeSample const * ( LayerRoughness_wrapper::*default_getCompositeSample_function_type )(  ) const;
            
            LayerRoughness_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ISample::getCompositeSample)
                , default_getCompositeSample_function_type(&LayerRoughness_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( LayerRoughness_wrapper::*default_printParameters_function_type )(  ) const;
            
            LayerRoughness_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&LayerRoughness_wrapper::default_printParameters) );
        
        }
        { //::ISample::printSampleTree
        
            typedef void ( ::ISample::*printSampleTree_function_type )(  ) ;
            typedef void ( LayerRoughness_wrapper::*default_printSampleTree_function_type )(  ) ;
            
            LayerRoughness_exposer.def( 
                "printSampleTree"
                , printSampleTree_function_type(&::ISample::printSampleTree)
                , default_printSampleTree_function_type(&LayerRoughness_wrapper::default_printSampleTree) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            LayerRoughness_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &LayerRoughness_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( LayerRoughness_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            LayerRoughness_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&LayerRoughness_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( LayerRoughness_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            LayerRoughness_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&LayerRoughness_wrapper::default_setParametersAreChanged) );
        
        }
    }

}
