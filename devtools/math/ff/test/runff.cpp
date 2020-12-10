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
#include "FormFactorTriangle.h"

using std::cout;
using std::cerr;
using std::vector;

static complex_t I(0.,1.);
static double eps(2e-16);

Diagnosis diagnosis;

int nshape = 13;

extern int n_limit;
extern double q_limit_series;
extern double qpa_limit_series;

//! Returns a pointer to a particle, according to given code

IFormFactorBorn* make_particle( int ishape )
{
    if       ( ishape==1 ) {
        return new FormFactorDodecahedron(3.);
    } else if( ishape==2 ) {
        return new FormFactorIcosahedron(15.);
    } else if( ishape==3 ) { // true tetrahedron
        double alpha = 72 * Units::degree;
        return new FormFactorTetrahedron(1., tan(alpha)/2/sqrt(3), alpha);
    } else if( ishape==4 ) { // tetrahedral frustum
        double alpha = 72 * Units::degree;
        return new FormFactorTetrahedron(1., 0.5*tan(alpha)/2/sqrt(3), alpha);
    } else if( ishape==5 ) { // tetrahedral frustum, flat one
        double alpha = 80 * Units::degree;
        return new FormFactorTetrahedron(1., 0.1*tan(alpha)/2/sqrt(3), alpha);
    } else if( ishape==6 ) { // tetrahedral frustum as in BasicTest
        return new FormFactorTetrahedron(16., 4., .8);
    } else if( ishape==7 ) {
        double alpha = 72 * Units::degree;
        return new FormFactorCone6(10., 10., alpha);
    } else if( ishape==8 ) {
        return new FormFactorPyramid(1.5, .24, 1.);
    } else if( ishape==9 ) {
        return new FormFactorAnisoPyramid(2, .4, .24, 1.);
    } else if( ishape==10) {
        return new FormFactorPrism3(1.2, 1.);
    } else if( ishape==11) {
        return new FormFactorPrism6(1., 1.);
    } else if( ishape==12) {
        return new FormFactorTruncatedCube(4., 1.);
    } else if( ishape==13 ) {
        double alpha = 73 * Units::degree;
        return new FormFactorCuboctahedron(1., 1., .8, alpha);
    } else if( ishape==90 ) {
        return new FormFactorTriangle(1.);
    } else
        throw "Shape not implemented";
}

//! Print q in a form that can be easily pasted to the command line for further investigation

std::string nice_q( cvector_t q )
{
    std::ostringstream ret;
    double qmax = 0;
    ret << std::setprecision(16);
    for( int i=0; i<3; ++i )
        qmax = std::max( qmax, q[i].real() );
    for( int i=0; i<3; ++i )
        ret << q[i].real()/qmax << " " << q[i].imag()/qmax << " ";
    ret << qmax;
    return ret.str();
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
        double step = std::abs(ri-rf);
        double relstep = step/aval;
        if( relstep>maxrelstep){
            cout<<"ishape="<<ishape<<": relstep "<<std::setprecision(8)<<relstep<<"="<<step<<"/"<<std::setprecision(16)<<aval<<" for "<<di<<"->"<<df<<" at q between "<<nice_q(qi)<<" and "<<nice_q(qf)<<"\n";
            maxrelstep = relstep;
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

//! Computes form factor, and prints result according to outfilter.

void run( const IFormFactorBorn* polyh, int ishape, cvector_t q, int outfilter )
{
    complex_t ret = polyh->evaluate_for_q(q);
    cout<<std::scientific<<std::setprecision(16)<<std::setfill('0');
    if     ( outfilter==0 )
        cout<<q.mag()<<" "<<std::abs(ret)<<" "<<ret.real()<<" "<<ret.imag()<<" "<<
            diagnosis.nExpandedFaces<<std::noshowpos<<" "<<diagnosis.maxOrder;
    else if( outfilter==1 )
        cout<<ret.real();
    else if( outfilter==2 )
        cout<<ret.imag();
    cout<<"\n";
}

//! Compute a form factor with modified control parameter settings

complex_t ff_modified( cvector_t q, const IFormFactorBorn* polyh, bool expand_qpa, bool expand_q )
{
    PolyhedralFace::setLimits( expand_qpa ? 1e99 : 1e-99, 80 );
    FormFactorPolyhedron::setLimits( expand_q ? 1e99 : 1e-99, 80 );
    return polyh->evaluate_for_q( q );
}

void test_matching( int ishape, const vector<vector<cvector_t>>& scans )
{
    cout<<ishape<<"\n";
    cerr<<"shape "<<ishape<<" ...\n";
    IFormFactorBorn* polyh( make_particle( ishape ) );
    int n_mag = 25;
    double mag_i = 1e-3;
    double mag_f = 1e1;
    for( int i=1; i<n_mag; ++i ) {
        double mag = mag_i*pow(mag_f/mag_i,i/(n_mag-1.));
        double res = 0;
        for( const vector<cvector_t>& q_scan: scans ) {
            assert( q_scan.size()== 1 );
            cvector_t uq = q_scan[0];
            const cvector_t q = mag * uq;
            complex_t ff[2];

            ff[0] = ff_modified( q, polyh, false, false );
            ff[1] = ff_modified( q, polyh, true, false );

            double dev = std::abs(ff[0]-ff[1])*2/(std::abs(ff[0])+std::abs(ff[1]));
            res = std::max(res, dev );
            if( 0 && dev>.1 )
                cerr<<ishape<<" "<<mag<<" "<<std::setprecision(16)<<
                    dev<<" "<<ff[0]<<" "<<ff[1]<<" @ "<<q<<"\n";
        }
        cout<<" "<<mag*polyh->getRadius()<<" "<<std::setprecision(8)<<res<<"\n";
    }
    cout<<"\n";
}

double test_continuity( int ishape, const vector<vector<cvector_t>>& scans )
{
    IFormFactorBorn* polyh( make_particle( ishape ) );
    double maxrelstep = 0;
    for( size_t j=0; j<scans.size(); ++j ) {
        if( !(j%100) )
            fprintf( stderr, "%2i: %8li/%li\r", ishape, j, scans.size() );
        const vector<cvector_t>& q_scan = scans[j];
        for( size_t i=1; i<q_scan.size(); ++i ) {
            complex_t last_ret = polyh->evaluate_for_q(q_scan[i-1]);
            Diagnosis last_diag = diagnosis;
            complex_t ret = polyh->evaluate_for_q(q_scan[i]);
            Diagnosis diag = diagnosis;
            if( diag!=last_diag )
                bisect( polyh, ishape, q_scan[i].mag(),
                        q_scan[i-1], last_ret, last_diag,
                        q_scan[i], ret, diag,
                        maxrelstep );
        }
    }
    fprintf( stderr, "\n" );
    cout<<"shape "<<ishape<<" => max rel step = "<<maxrelstep<<"\n";
    return maxrelstep;
}

void loop_one_shape( int ishape, const vector<vector<cvector_t>>& scans )
{
    IFormFactorBorn* polyh( make_particle( ishape ) );
    for( size_t j=0; j<scans.size(); ++j ) {
        if( !(j%100) )
            fprintf( stderr, "%2i: %8li/%li\r", ishape, j, scans.size() );
        const vector<cvector_t>& q_scan = scans[j];
        for( const cvector_t q: q_scan ) {
            complex_t ret = polyh->evaluate_for_q(q);
            cout <<
                ishape<<" " <<
                std::setprecision(16) <<
                q[0].real()<<" "<<q[0].imag()<<" " <<
                q[1].real()<<" "<<q[1].imag()<<" " <<
                q[2].real()<<" "<<q[2].imag()<<" " <<
                std::setprecision(17) <<
                q.mag()<<" " <<
                ret.real()<<" "<<ret.imag()<<" "<<std::abs(ret)<<" " <<
                diagnosis.nExpandedFaces<<" "<<diagnosis.maxOrder<<"\n";
        }
    }
}

vector<vector<cvector_t>> create_scans( int mode )
{
    static int n_dir = 7;
    cvector_t dir[n_dir] = {
        { 1., 0., 0. },
        { 0., 1., 0. },
        { 0., 0., 1. },

        { 0., 1., 1. },
        { 1., 0., 1. },
        { 1., 1., 0. },

        { 1., 1., 1. }
    };

    static int n_absdir = 8; // absorption component
    cvector_t absdir[n_absdir] = {
        { 0., 0., 0. },
        { 1e-15*I, 0., 0. },
        { 0., 1e-10*I, 0. },
        { 0., 0., 1e-5*I },
        { .1*I, 0., 0. },
        { 0., .1*I, 0. },
        { 0., 0., .1*I },
        { .1*I, .1*I, .1*I }
    };

    vector<double> mag;
    if ( mode==0 ) {
        mag.resize(1);
        mag[0] = 1;
    } else if ( mode==1 ) {
        mag = vector<double>( { 0, 1e-12, 1e-10, 1e-8, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3,
                    .01, .06, .2, .5, 1, 2, 5, 10, 20, 50, 100 } );
    } else if (mode==2 ) {
        mag.resize(1001);
        mag[0] = 0.;
        for( size_t i=1; i<mag.size(); ++i )
            mag[i] = 1e-10*pow(1e13,(i-1.)/(mag.size()-2));
    }

    static const int n_difmag = 17;
    static double difmag[n_difmag] =
        { 0., 3e-16, 1e-15, 3e-15, 1e-14, 1e-13, 1e-12, 1e-11, 1e-9, 1e-7,
          1e-5, 1e-3, .01, .03, .1, .2, .3 };

    vector<vector<cvector_t>> scans;
    for( int i=0; i<n_dir; ++i ) {
        for( int j=0; j<n_dir; ++j ) {
            if( i==j )
                continue;
            for( int k=0; k<n_difmag; ++k ) {
                for( int l=0; l<n_absdir; ++l ) {
                    cvector_t uq = ( dir[i].unit() + difmag[k]*dir[j] + absdir[l] ).unit();
                    vector<cvector_t> scan;
                    for( size_t m=0; m<mag.size(); ++m )
                        scan.push_back( mag[m] * uq );
                    scans.push_back( scan );
                }
            }
        }
    }
    return scans;
}

void help_and_exit()
{
    cerr<<"fftest limits inmode debmsg outfilter shape qxr qxi qyr qyi qzr qzi [q]\n";
    cerr<<"  limits:    \"def\" | qlim qpalim nlim\n";
    cerr<<"  inmode:    get q from 0:stdin | 1:cmdline | 2:loop\n";
    cerr<<"  debmsg:    0..6 (only if inmode=1)\n";
    cerr<<"  outfilter: return 0:all | 1:real | 2:imag\n";
    cerr<<"fftest limits loop shape\n";
    cerr<<"  limits:    \"def\" | qlim qpalim nlim\n";
    cerr<<"  loop:      3[cont_test] | 4[matching_test] | 5[for_plot]\n";
    cerr<<"  shape:     0[all] | 1..[specific]\n";
    exit(0);
}

#define NEXTARG if( (++arg)-argv >= argc ) help_and_exit()
#define MULTIARG(n) if( (arg+=n)-argv >= argc ) help_and_exit()

int main (int argc, const char *argv[])
{
    try {
        diagnosis.debmsg = 0;
        diagnosis.request_convergence = false;
        const char** arg = argv;
        NEXTARG;
        if ( !strncmp( *arg, "def", 3 ) ) {
            // do nothing
        } else {
            double q_limit = atof( *arg );
            NEXTARG;
            double qpa_limit = atof( *arg );
            NEXTARG;
            int n_limit = atoi( *arg );
            FormFactorPolyhedron::setLimits( q_limit, n_limit );
            PolyhedralFace::setLimits( qpa_limit, n_limit );
        }
        NEXTARG;
        int inmode = atoi( *arg );
        if( inmode==1 ) {
            NEXTARG;
            diagnosis.debmsg = atoi( *arg );
        }
        if( inmode<=2 ) {
            NEXTARG;
            int outfilter = atoi( *arg );
            NEXTARG;
            int ishape = atoi( *arg );
            IFormFactorBorn* P( make_particle( ishape ) );
            MULTIARG(6);
            cvector_t uq(
                complex_t( atof(*(arg-5)), atof(*(arg-4)) ),
                complex_t( atof(*(arg-3)), atof(*(arg-2)) ),
                complex_t( atof(*(arg-1)), atof(*(arg-0)) ) );
            double mag;
            if( inmode==0 ) {
                // for use through Frida
                int nop;
                std::cin >> nop;
                while( std::cin >> mag )
                    run( P, ishape, mag*uq, outfilter );
            } else if( inmode==1 ) {
                NEXTARG;
                mag = atof( *arg );
                run( P, ishape, mag*uq, outfilter );
            } else if( inmode==2 ) {
                int n_mag = 2001;
                double mag_i = 1e-20;
                double mag_f = 1e4;
                for( int i=1; i<n_mag; ++i ) {
                    //mag = 180.*i/(n_mag-1);
                    mag = mag_i*pow(mag_f/mag_i,i/(n_mag-1.));
                    run( P, ishape, mag*uq, outfilter );
                }
            }
            exit(0);
        }
        // it's some loop
        NEXTARG;
        int ishapepar = atoi( *arg );

        if( inmode==3 ) { // continuity test
            diagnosis.request_convergence = true;
            vector<vector<cvector_t>> scans = create_scans( 1 );
            double totmaxrelstep = 0;
            if( ishapepar==0 ) {
                for( int ishape=1; ishape<=nshape; ++ishape )
                    totmaxrelstep = std::max( totmaxrelstep, test_continuity( ishape, scans ) );
                cout<<"grand total max rel step = "<<totmaxrelstep<<"\n";
            } else {
                test_continuity( ishapepar, scans );
            }
            exit (0);
        }
        if( inmode==4 ) { // compare computation methods
            vector<vector<cvector_t>> scans = create_scans( 0 );
            if( ishapepar==0 ) {
                for( int ishape=1; ishape<=nshape; ++ishape )
                    test_matching( ishape, scans );
            } else
                test_matching( ishapepar, scans );
            exit (0);
        }
        // it's a straight loop over q
        vector<vector<cvector_t>> scans = create_scans( 2 );
        if( ishapepar==0 ) {
            for( int ishape=1; ishape<=nshape; ++ishape )
                loop_one_shape( ishape, scans );
        } else
            loop_one_shape( ishapepar, scans );
        exit(0);

    } catch( const char* ex ) {
        cerr<<"F(q) failed: "<<ex<<"\n";
        exit(0);
    }
}
