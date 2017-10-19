#include "HomogeneousMaterial.h"
#include "WavevectorInfo.h"
#include "Transform3D.h"
#include <memory>
#include <typeinfo>

// this prefactor is equal to m_n*g_n*mu_N / (hbar^2), with
// m_n: neutron mass
// g_n: neutron g-factor (-3.826)
// mu_N: nuclear magneton
// hbar: reduced Planck constant
// Units are: 1/(nm^2 * T)
static const double Magnetic_Prefactor = -2.91042993836710484e-3;

static const double Thomson_Scattering_Length = 2.8179403227e-15;
static const double Bohr_Magneton = 9.274009994e-24;
// The neutron's magnetic moment is Gamma_Neutron times the nuclear magneton
static const double Gamma_Neutron = 1.91304272;
// The factor 1e-18 is here to have unit: m/A*nm^-2
static const double Magnetization_Prefactor = (Gamma_Neutron*Thomson_Scattering_Length
                                               /2.0/Bohr_Magneton)*1e-18;

// Unit 2x2 matrix
static const Eigen::Matrix2cd Unit_Matrix(Eigen::Matrix2cd::Identity());

// Imaginary unit
namespace {
    const complex_t I(0,1);
}

// Pauli matrices
static const Eigen::Matrix2cd Pauli_X((Eigen::Matrix2cd() << 0,  1,
                                                             1,  0).finished());
static const Eigen::Matrix2cd Pauli_Y((Eigen::Matrix2cd() << 0, -I,
                                                             I,  0).finished());
static const Eigen::Matrix2cd Pauli_Z((Eigen::Matrix2cd() << 1,  0,
                                                             0, -1).finished());

namespace {
// Used in experimental calculation of scattering matrix:
cvector_t OrthogonalToBaseVector(cvector_t base, const kvector_t vector)
{
    if (base.mag2()==0.0) return cvector_t {};
    cvector_t projection = (base.dot(vector)/base.mag2())*base;
    return vector.complex() - projection;
}
}

HomogeneousMaterial::HomogeneousMaterial()
    : INamed("vacuum")
    , m_refractive_index(1)
{}

HomogeneousMaterial::HomogeneousMaterial(
        const std::string& name, const complex_t refractive_index, kvector_t magnetization)
    : INamed(name)
    , m_refractive_index(refractive_index)
    , m_magnetization(magnetization)
{}

HomogeneousMaterial::HomogeneousMaterial(
        const std::string& name, double refractive_index_delta,
        double refractive_index_beta, kvector_t magnetization)
    : INamed(name)
    , m_refractive_index(complex_t(1.0 - refractive_index_delta, refractive_index_beta))
    , m_magnetization(magnetization)
{}

HomogeneousMaterial::HomogeneousMaterial(const std::string& name, complex_t sld, double wavelength,
                                         kvector_t magnetization)
    : INamed(name), m_refractive_index(std::sqrt(1.0 - wavelength * wavelength * sld / M_PI))
    , m_magnetization(magnetization)
{}

HomogeneousMaterial* HomogeneousMaterial::clone() const
{
    return new HomogeneousMaterial(*this);
}

HomogeneousMaterial* HomogeneousMaterial::inverted() const
{
    std::string name = isScalarMaterial() ? getName()
                                          : getName()+"_inv";
    std::unique_ptr<HomogeneousMaterial> result(clone());
    result->setMagnetization(-magnetization());
    result->setName(name);

    return result.release();
}

complex_t HomogeneousMaterial::refractiveIndex() const
{
    return m_refractive_index;
}

complex_t HomogeneousMaterial::refractiveIndex2() const
{
    return m_refractive_index * m_refractive_index;
}

void HomogeneousMaterial::setRefractiveIndex(const complex_t refractive_index)
{
    m_refractive_index = refractive_index;
}

void HomogeneousMaterial::setMaterialData(complex_t sld, double wavelength)
{
    m_refractive_index = std::sqrt(1.0 - wavelength * wavelength * sld / M_PI);
}

bool HomogeneousMaterial::isScalarMaterial() const
{
    return m_magnetization == kvector_t {};
}

kvector_t HomogeneousMaterial::magnetization() const
{
    return m_magnetization;
}

void HomogeneousMaterial::setMagnetization(const kvector_t magnetic_field)
{
    m_magnetization = magnetic_field;
}

complex_t HomogeneousMaterial::scalarSubstrSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    double prefactor = M_PI/wavelength/wavelength;
    complex_t refractive_index = refractiveIndex();
    return prefactor * refractive_index * refractive_index;
}

Eigen::Matrix2cd HomogeneousMaterial::polarizedSubstrSLD(const WavevectorInfo& wavevectors) const
{
    cvector_t mag_ortho = OrthogonalToBaseVector(wavevectors.getQ(), m_magnetization);
    complex_t unit_factor = scalarSubstrSLD(wavevectors);
    Eigen::Matrix2cd result;
    result = unit_factor*Unit_Matrix
            + Magnetization_Prefactor*Pauli_X*mag_ortho[0]
            + Magnetization_Prefactor*Pauli_Y*mag_ortho[1]
            + Magnetization_Prefactor*Pauli_Z*mag_ortho[2];
    return result;
}

HomogeneousMaterial* HomogeneousMaterial::transformedMaterial(const Transform3D& transform) const
{
    kvector_t transformed_field = transform.transformed(m_magnetization);
    std::unique_ptr<HomogeneousMaterial> result(clone());
    result->setMagnetization(transformed_field);
    return result.release();
}

void HomogeneousMaterial::print(std::ostream& ostr) const
{
    ostr << "HomMat:" << getName() << "<" << this << ">{ "
         << "R=" << m_refractive_index << ", B=" << m_magnetization << "}";
}

std::ostream& operator<<(std::ostream& ostr, const HomogeneousMaterial& m)
{
    m.print(ostr);
    return ostr;
}

complex_t ScalarReducedPotential(complex_t n, kvector_t k, double n_ref)
{
    return n*n - n_ref*n_ref*k.sin2Theta();
}

Eigen::Matrix2cd PolarizedReducedPotential(complex_t n, kvector_t b_field,
                                           kvector_t k, double n_ref)
{
    Eigen::Matrix2cd result;
    double factor = Magnetic_Prefactor/k.mag2();
    complex_t unit_factor = ScalarReducedPotential(n, k, n_ref);
    result = unit_factor*Unit_Matrix
            + factor*Pauli_X*b_field[0]
            + factor*Pauli_Y*b_field[1]
            + factor*Pauli_Z*b_field[2];
    return result;
}

bool operator==(const HomogeneousMaterial& left, const HomogeneousMaterial& right)
{
    if (left.getName() != right.getName()) return false;
    if (left.magnetization() != right.magnetization()) return false;
    if (typeid(left).hash_code() != typeid(right).hash_code()) return false;
    if (left.refractiveIndex() != right.refractiveIndex()) return false;
    return true;
}

bool operator!=(const HomogeneousMaterial& left, const HomogeneousMaterial& right)
{
    return !(left==right);
}
