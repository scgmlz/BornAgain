// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SpecularScan.h
//! @brief     Declares SpecularScan class tree.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARDATAHANDLER_H
#define SPECULARDATAHANDLER_H

#include "ICloneable.h"

#include <memory>
#include <string>
#include <vector>

class IAxis;
class IFootprintFactor;
class SpecularSimulationElement;

//! Base abstract class for all types of specular scans.
class ISpecularScan : public ICloneable
{
public:
    enum SPECULAR_DATA_TYPE {angle, q};

    ISpecularScan(SPECULAR_DATA_TYPE data_type);
    ~ISpecularScan() override;
    ISpecularScan* clone() const override = 0;

#ifndef SWIG
    //! Generates simulation elements for specular simulations
    virtual std::vector<SpecularSimulationElement> generateSimulationElements() const = 0;

    //! Returns coordinate axis assigned to the data holder
    virtual const IAxis* coordinateAxis() const = 0;

    //! Returns IFootprintFactor object pointer
    virtual const IFootprintFactor* footprintFactor() const = 0;

    //! Returns footprint correction factor for simulation element with index _i_
    virtual double footprint(size_t i) const = 0;

    //! Returns the number of simulation elements
    virtual size_t numberOfSimulationElements() const = 0;

    //! Print scan definition in python format
    virtual std::string print() const = 0;
#endif //SWIG

    SPECULAR_DATA_TYPE dataType() const {return m_data_type;}

private:
    SPECULAR_DATA_TYPE m_data_type;
};

//! Scan type with inclination angles as coordinate
//! values. Features footprint correction.
class AngularSpecScan : public ISpecularScan
{
public:
    AngularSpecScan(double wl, std::vector<double> inc_angle);
    AngularSpecScan(double wl, const IAxis& inc_angle);
    //! Sets angle-defined specular scan. The first parameter is always a wavelength in nm.
    //! Second parameter is either a numpy array of incident angles in radians or an IAxis object
    //! with angle values. Alternatively an axis can be defined in-place, then
    //! the second passed parameter is the number of bins, third - minimum on-axis angle value,
    //! fourth - maximum on-axis  angle value.
    AngularSpecScan(double wl, int nbins, double alpha_i_min, double alpha_i_max);
    ~AngularSpecScan() override;
    AngularSpecScan* clone() const override;

#ifndef SWIG
    //! Generates simulation elements for specular simulations
    std::vector<SpecularSimulationElement> generateSimulationElements() const override;

    //! Returns coordinate axis assigned to the data holder
    virtual const IAxis* coordinateAxis() const override {return m_inc_angle.get();}

    //! Returns IFootprintFactor object pointer
    virtual const IFootprintFactor* footprintFactor() const override {return m_footprint.get();}

    //! Returns footprint correction factor for simulation element with index _i_
    double footprint(size_t i) const override;

    //! Returns the number of simulation elements
    size_t numberOfSimulationElements() const override;

    //! Print scan definition in python format
    std::string print() const override;

    double wavelength() const {return m_wl;}
#endif //SWIG

    //! Sets footprint correction factor
    void setFootprintFactor(const IFootprintFactor* f_factor);

private:
    void checkInitialization();

    double m_wl;
    std::unique_ptr<IAxis> m_inc_angle;
    std::unique_ptr<IFootprintFactor> m_footprint;
};

//! Scan type with z-components of scattering vector
//! as coordinate values. Wavelength and incident angles
//! are not accessible separately.
class QSpecScan : public ISpecularScan
{
public:
    //! Accepts qz-value vector (in inverse nm)
    QSpecScan(std::vector<double> qs_nm);
    QSpecScan(const IAxis& qs_nm);
    //! Sets q-defined specular scan. Accepts either numpy array of q-values sorted in ascending
    //! order or an IAxis object with q-values. Alternatively an axis can be defined in-place, then
    //! the first passed parameter is the number of bins, second - minimum on-axis q-value,
    //! third - maximum on-axis q_value.
    QSpecScan(int nbins, double qz_min, double qz_max);

    ~QSpecScan() override;
    QSpecScan* clone() const override;

#ifndef SWIG
    //! Generates simulation elements for specular simulations
    std::vector<SpecularSimulationElement> generateSimulationElements() const override;

    //! Returns coordinate axis assigned to the data holder
    virtual const IAxis* coordinateAxis() const override {return m_qs.get();}

    //! Returns IFootprintFactor object pointer
    virtual const IFootprintFactor* footprintFactor() const override { return nullptr; }

    //! Returns footprint correction factor for simulation element with index _i_
    double footprint(size_t i) const override;

    //! Returns the number of simulation elements
    size_t numberOfSimulationElements() const override;

    //! Print scan definition in python format
    std::string print() const override;
#endif //SWIG

private:
    void checkInitialization();
    std::unique_ptr<IAxis> m_qs;
};

inline std::ostream& operator<<(std::ostream& os, const ISpecularScan& scan)
{
    return os << scan.print();
}
#endif // SPECULARDATAHANDLER_H
