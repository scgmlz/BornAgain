// Form factor computation: test program
// JWu 2016

// Reference:
//   Joachim Wuttke
//   "Form factor (Fourier shape transform) of polygon and polyhedron."

// To use these tests, FormFactorPolyhedron.cpp must be compiled
// with flag -D POLYHEDRAL_DIAGNOSTIC=ON

#include <cassert>
#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>

#include "ParticleShapes.h"

using std::cout;
using std::cerr;

static complex_t I(0.,1.);
static double eps(2e-16);

Diagnosis diagnosis;

int nshape = 11;

//! Returns a polyhedron, according to given code

IFormFactorBorn* make_polyhedron( int ishape )
{
    if       ( ishape==0 ) {
        return new FormFactorDodecahedron(3.);
    } else if( ishape==1 ) {
        return new FormFactorIcosahedron(15.);
    } else if( ishape==2 ) { // true tetrahedron
        double alpha = 72 * Units::degree;
        return new FormFactorTetrahedron(1., tan(alpha)/2/sqrt(3), alpha);
    } else if( ishape==3 ) { // tetrahedral frustum
        double alpha = 72 * Units::degree;
        return new FormFactorTetrahedron(1., 0.5*tan(alpha)/2/sqrt(3), alpha);
    } else if( ishape==4 ) {
        double alpha = 72 * Units::degree;
        return new FormFactorCone6(10., 10., alpha);
    } else if( ishape==5 ) {
        double alpha = 72 * Units::degree;
        return new FormFactorPyramid(10., 10., alpha);
    } else if( ishape==6 ) {
        return new FormFactorPrism3(1., 10.);
    } else if( ishape==7 ) {
        return new FormFactorPrism3(10., 1.);
    } else if( ishape==8 ) {
        return new FormFactorPrism6(1., 1.);
    } else if( ishape==9 ) {
        return new FormFactorTruncatedCube(4., 1.);
    } else if( ishape==10 ) {
        double alpha = 72 * Units::degree;
        return new FormFactorCuboctahedron(1., 1., .8, alpha);
    } else
        throw "Shape not implemented";
}

//! Bisect between two q's to find possible discontinuities

void bisect(
    const IFormFactorBorn* polyh, int ishape, double q0mag,
    cvector_t qi, complex_t ri, const Diagnosis di,
    cvector_t qf, complex_t rf, const Diagnosis df,
    double& maxrelstep )
{
    assert( di!=df );
    if( (qi-qf).mag()<4*eps*q0mag ) {
        // narrowed down to minimal step, now check for continuity
        double aval = (std::abs(ri) + std::abs(rf))/2;
        double relstep = std::abs(ri-rf)/aval;
        maxrelstep = std::max( maxrelstep, relstep );
        if( relstep>1e-9 ){
            cerr<<"ishape="<<ishape<<": step "<<std::setprecision(8)<<relstep<<" @ "<<std::setprecision(16)<<aval<<" for "<<di<<"->"<<df<<" at q between "<< std::setprecision(16)<<qi<<" and "<<qf<<"\n";
        }
        return;
    }
    cvector_t q2 = (qi + qf)/2.;
    complex_t r2 = polyh->evaluate_for_q(q2);
    Diagnosis d2 = diagnosis;
    if( d2!=di )
        bisect( polyh, ishape, q0mag, qi, ri, di, q2, r2, d2, maxrelstep );
    if( d2!=df )
        bisect( polyh, ishape, q0mag, q2, r2, d2, qf, rf, df, maxrelstep );
}

//! Computes form factor or runs bisection, and prints result according to outfilter.

void run(
    const IFormFactorBorn* polyh,
    double step, int ishape, cvector_t q, cvector_t qlast,
    int outfilter, double& maxrelstep )
{
    complex_t ret;
    static complex_t last_ret = 0;
    static Diagnosis last_diag;
    Diagnosis diag = diagnosis;
    ret = polyh->evaluate_for_q(q);

    if( outfilter==6 ) {
        if( qlast!=cvector_t() && diag!=last_diag )
            bisect( polyh, ishape, q.mag(), q, ret, diag, qlast, last_ret, last_diag, maxrelstep );
        last_ret = ret;
        last_diag = diag;
        return;
        throw "define POLYHEDRAL_DIAGNOSTIC to run continuity test";
    }
    if( outfilter==9 )
        return;
    cout << std::setprecision(16) << step << " " << ishape << " " << std::setprecision(12) <<
        q[0].real() << " " << q[0].imag() << " " <<
        q[1].real() << " " << q[1].imag() << " " <<
        q[2].real() << " " << q[2].imag() << " " << std::setprecision(12);
    if     ( outfilter==0 )
        cout << ret;
    else if( outfilter==1 )
        cout << ret.real();
    else if( outfilter==2 )
        cout << ret.imag();
    else if( outfilter==7 || outfilter==8 )
        cout << ret.real() << " " << ret.imag();
    else
        throw "invalid outfilter";
#ifdef POLYHEDRAL_DIAGNOSTIC
    cout << " " << diagnosis.nExpandedFaces << " " << diagnosis.maxOrder << "\n";
#endif
}

void test_loop( int outfilter )
{
    double totmaxrelstep = 0;
    static int n_qdir = 10;
    int nsteps;
    if( outfilter==7 )
        nsteps = 201;
    else if( outfilter==8 )
        nsteps = 17;
    else
        nsteps = 3001;
    if( !(nsteps&1) )
        throw "nsteps must be odd";
    std::vector<double> steps(nsteps);
    steps[0] = 0;
    steps[nsteps-1] = 1;
    int n2 = (nsteps-1)/2;
    steps[n2] = .5;
    for( int i=1; i<n2; ++i ){
        steps[i] = pow(.5, (i-1)/((double)(n2-1))) * pow(1e-12, (n2-i)/((double)(n2-1)));
        steps[nsteps-1-i] = 1-steps[i];
    }
    double steps_short[3] = { 0., 1e-12, 1e-6 };
    cvector_t qdirs[n_qdir+1] = {
        { 1., 0., 0. },
        { 0., 1.+.01*I, 0. },
        { .001*I, 1., 1. },
        { 1.+.01*I, 1.-.01*I, 0. },
        { 0., 0., 1. },
        { 1., 1., 1. },
        { 1., 0., 1. },
        { 1., 2., 0. },
        { 0., 2., 3. },
        { 1., 2.71813+0.1*I, 3.14158-0.2*I, },
        { -200.+I, 30000.-I, 1. } };
    for( int ishape=0; ishape<nshape; ++ishape ){
        double maxrelstep = 0;
        IFormFactorBorn* polyh( make_polyhedron( ishape ) );
        // For different directions ...
        for( int idx_qdir=0; idx_qdir<n_qdir; ++idx_qdir ){
            for( int irot=0; irot<3; ++irot ){
                double rot = steps_short[irot];
                cvector_t uq = ((1-rot)*qdirs[idx_qdir] + rot*qdirs[idx_qdir+1]).unit();
                // ... sweep |q|
                cvector_t qlast;
                for( int idx_qmag=0; idx_qmag<nsteps; ++idx_qmag ) {
                    double qmag = pow(10.,-12+15.*idx_qmag/(nsteps-1));
                    cvector_t q = qmag * uq;
                    run( polyh, qmag, ishape, q, qlast, outfilter, maxrelstep );
                    qlast = q;
                }
            }
        }
        // For different |q| ...
        for( int idx_qmag=0; idx_qmag<7; ++idx_qmag ) {
            double qmag = pow(10.,-12+14.*idx_qmag/(7-1));
            // ... sweep direction
            for( int idx_qdir=0; idx_qdir<n_qdir; ++idx_qdir ){
                cvector_t qlast;
                for( int irot=0; irot<nsteps; ++irot ){
                    double rot = steps[irot];
                    cvector_t uq = ((1-rot)*qdirs[idx_qdir] + rot*qdirs[idx_qdir+1]).unit();
                    cvector_t q = qmag * uq;
                    run( polyh, rot, ishape, q, qlast, outfilter, maxrelstep );
                    qlast = q;
                }
            }
        }
        if( outfilter==6 )
            cout << "shape " << ishape << " => max rel step = " << maxrelstep << "\n";
        totmaxrelstep = std::max( maxrelstep, totmaxrelstep );
    }
    if( outfilter==6 )
        cout << "grand total max rel step = " << totmaxrelstep << "\n";
}

void help_and_exit()
{
    cerr << "Usage: fftest inmode outfilter [shape qxr qxi qyr qyi qzr qzi q]\n";
    cerr << "inmode: q from 0 stdin, 1 cmdline, 2 loop\n";
    cerr << "outfilter: return 0 all, 1 real, 2 imag, 6 cont_test, 7 plot_tab, 8 ref_tab, 9 nil\n";
    cerr << "shape: 0 dodeka, 1 icosa\n";
    exit(0);
}

int main (int argc, char *argv[])
{
    try {
        if( argc< 3 )
            help_and_exit();
        int inmode = atoi( argv[1] );
        int outfilter = atoi( argv[2] );
        if( inmode==2 ) {
            if( argc!=3 )
                help_and_exit();
            test_loop( outfilter );
            exit(0);
        }
        if( argc!=11 )
            help_and_exit();
        int ishape = atoi( argv[3] );
        IFormFactorBorn* polyh( make_polyhedron( ishape ) );
        cvector_t uq( complex_t(atof(argv[4]),atof(argv[5])),
                      complex_t(atof(argv[6]),atof(argv[7])),
                      complex_t(atof(argv[8]),atof(argv[9])) );
        double qmag;
        double dummy;
        if( inmode==1 ) {
            qmag = atof(argv[10]);
            run( polyh, 1., ishape, qmag*uq, cvector_t(), outfilter, dummy );
        } else if( inmode==0 ) {
            int nop;
            std::cin >> nop;
            while( std::cin >> qmag )
                run( polyh, 1., ishape, qmag*uq, cvector_t(), outfilter, dummy );
        } else
            throw "invalid inmode";
    } catch( const char* ex ) {
        cerr << "F(q) failed: " << ex << "\n";
        exit(0);
    }
}
