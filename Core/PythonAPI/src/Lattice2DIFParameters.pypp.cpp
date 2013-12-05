// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "PythonCoreList.h"
#include "Lattice2DIFParameters.pypp.h"

namespace bp = boost::python;

void register_Lattice2DIFParameters_class(){

    { //::Lattice2DIFParameters
        typedef bp::class_< Lattice2DIFParameters > Lattice2DIFParameters_exposer_t;
        Lattice2DIFParameters_exposer_t Lattice2DIFParameters_exposer = Lattice2DIFParameters_exposer_t( "Lattice2DIFParameters", bp::init< >() );
        bp::scope Lattice2DIFParameters_scope( Lattice2DIFParameters_exposer );
        Lattice2DIFParameters_exposer.def_readwrite( "m_angle", &Lattice2DIFParameters::m_angle );
        Lattice2DIFParameters_exposer.def_readwrite( "m_corr_length_1", &Lattice2DIFParameters::m_corr_length_1 );
        Lattice2DIFParameters_exposer.def_readwrite( "m_corr_length_2", &Lattice2DIFParameters::m_corr_length_2 );
        Lattice2DIFParameters_exposer.def_readwrite( "m_length_1", &Lattice2DIFParameters::m_length_1 );
        Lattice2DIFParameters_exposer.def_readwrite( "m_length_2", &Lattice2DIFParameters::m_length_2 );
        Lattice2DIFParameters_exposer.def_readwrite( "m_xi", &Lattice2DIFParameters::m_xi );
    }

}
