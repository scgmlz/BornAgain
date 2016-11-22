// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IsGISAXSDetector.h
//! @brief     Defines class IsGISAXSDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXSDETECTOR_H
#define ISGISAXSDETECTOR_H

#include "SphericalDetector.h"

//! A spherical detector used for validation with IsGISAXS results.
//! @ingroup simulation

class BA_CORE_API_ IsGISAXSDetector : public SphericalDetector
{
public:
    IsGISAXSDetector();
    IsGISAXSDetector(size_t n_phi, double phi_min, double phi_max,
                     size_t n_alpha, double alpha_min, double alpha_max);
    IsGISAXSDetector(const IsGISAXSDetector &other);

    IsGISAXSDetector* clone() const override;

protected:
    void print(std::ostream &ostr) const override;

    //! Generates an axis with correct name and default binning for given index
    IAxis* createAxis(size_t index, size_t n_bins, double min, double max) const override;

    //! Returns index of pixel that contains the specular wavevector.
    //! If no pixel contains this specular wavevector, the number of pixels is
    //! returned. This corresponds to an overflow index.
    size_t getIndexOfSpecular(const Beam& beam) const override;
};

#endif // ISGISAXSDETECTOR_H
