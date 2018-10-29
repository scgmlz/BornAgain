// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDistributions1D.h
//! @brief     Defines interface class IFTDistribution1D, and children thereof
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IDistribution2DSampler.h"
#include <random>

#include <iostream>

namespace
{
    double sigma_scale = 3.0;
    size_t n_boxes = 256; // number of boxes for Ziggurat sampling

    struct BA_CORE_API_ ZigguratBox
    {
        ZigguratBox(double x_min, double x_max, double y_max, double y_lower) :
            m_x_min(x_min), m_x_max(x_max), m_y_max(y_max), m_y_lower(y_lower) {}

        double m_x_min; // left edge of the box
        double m_x_max; // right edge of the box
        // m_y_min is inherently 0 for every box and hence hasn't been defined
        double m_y_max; // height of box
        double m_y_lower; // minimum height of the box for which points below that height
                          // are located below the density function curve in the box
    };

    std::pair<double, double> samplingZiggurat(
            double r, double x_func_max, double (*func_phi)(double))
    {
        // This sampling is based on vertical boxes instead of the conventional
        // Ziggurat sampling that is done with horizontal boxes

        std::random_device rd;  // random device class instance
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<double> uniformDist(0.0, 1.0);

        double box_width = (x_func_max + r)/n_boxes; // r = rightmost box's right-edge from x_func_max
        std::vector<ZigguratBox> boxes;
        std::vector<double> cum_area_vector;

        double x_min = 0, x_max = 0, y_max = 0, y_lower = 0, cum_area_box = 0;

        for( size_t i = 0; i < n_boxes; ++i)
        {
            if (i != 0)
                x_min = x_max;

            x_max += box_width;

            if (x_func_max >= x_max)
            {
                y_max = func_phi(x_max);
                y_lower = func_phi(x_min);
            }
            else if (x_func_max > x_min && x_func_max <= x_max )
            {
                y_max = func_phi(x_func_max);
                y_lower = std::min(func_phi(x_min), func_phi(x_max));
            }
            else
            {
                y_max = func_phi(x_min);
                y_lower = func_phi(x_max);
            }

            boxes.emplace_back(ZigguratBox(x_min, x_max, y_max, y_lower));

            cum_area_box += box_width*y_max;
            cum_area_vector.emplace_back(cum_area_box);
        }

        // Normalizing the cumulative area to 1
        for( size_t i = 0; i < n_boxes; ++i)
        {
            cum_area_vector[i] = cum_area_vector[i]/cum_area_vector.back();
            std::cout<<"---------------------------------------------"<<std::endl;
            std::cout<<"Box # "<<i+1<<std::endl;
            std::cout<<boxes[i].m_x_min<<" "<<boxes[i].m_x_max<<" "<<
                       boxes[i].m_y_max<<" "<<boxes[i].m_y_lower<<std::endl;
            std::cout<<cum_area_vector[i]<<std::endl;
        }


        // Sampling a phi value
        double phi = 0;
        bool solnFound(false);

        while(!solnFound)
        {
            double random_cum_area = uniformDist(gen);

            for( size_t i = 0; i < n_boxes; ++i)
            {
                if (random_cum_area <= cum_area_vector[i])
                {
                    double random_y = uniformDist(gen)*boxes[i].m_y_max;
                    std::uniform_real_distribution<double> uniformDistAB(boxes[i].m_x_min, boxes[i].m_x_max);
                    double phi_attempt = uniformDistAB(gen);
                    if (random_y <= boxes[i].m_y_lower)
                    {
                        phi = phi_attempt;
                        solnFound = true;
                    }
                    else
                    {
                        if (random_y <= func_phi(phi_attempt))
                        {
                            phi = phi_attempt;
                            solnFound = true;
                        }
                    }
                    break;
                }
            }
        }

        double alpha = uniformDist(gen);

        return std::make_pair(phi, alpha);
    }

    double func_phi_Cauchy(double phi)
    {
        // The independent "phi" density function of the 2D Cauchy distribution
        return phi*std::exp(-phi);
    }

    double func_phi_Cone(double phi)
    {
        // The independent "phi" density function of the 2D Cone distribution
        return 6*(1-phi)*phi;
    }
}

IDistribution2DSampler::~IDistribution2DSampler() = default;

/*
std::pair<double, double> Distribution2DCauchySampler::randomSample() const
{
    std::random_device rd;  // random device class instance
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> uniformDist(0.0, 1.0);

    double cdf_value_phi = uniformDist(gen);

    // solve for phi from the cdf of radial marginalzed distribution using Newton-Raphson method
    double func = 0.0, funcDeriv = 0.0, phi = 0.0;

    // initial guess for phi
    phi = 0.25;

    bool convergedSoln = false;
    while (!convergedSoln) {
        func = (phi + 1)*std::exp(-phi) + cdf_value_phi - 1;
        funcDeriv = -phi*std::exp(-phi);

        phi = phi - func / funcDeriv;

        if (std::abs(func / funcDeriv) < 0.001)
        {
            if (phi < 0)
                phi = uniformDist(gen); // make another guess as only positive solution for phi is acceptable
            else
                convergedSoln = true;
        }
    }

    double alpha = uniformDist(gen);

    return std::make_pair(m_omega_x*phi*std::cos(2*M_PI*alpha),
                          m_omega_y*phi*std::sin(2*M_PI*alpha));
}

std::pair<double, double> Distribution2DGaussSampler::randomSample() const
{
    std::random_device rd;  // random device class instance
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> uniformDist(0.0, 1.0);

    double cdf_value_phi = uniformDist(gen);

    // solve for phi from the cdf of radial marginalzed distribution
    double phi = std::sqrt(-2*std::log(1-cdf_value_phi));
    double alpha = uniformDist(gen);

    return std::make_pair(m_omega_x*phi*std::cos(2*M_PI*alpha),
                          m_omega_y*phi*std::sin(2*M_PI*alpha));
}

std::pair<double, double> Distribution2DGateSampler::randomSample() const
{
    std::random_device rd;  // random device class instance
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> uniformDist(0.0, 1.0);

    double cdf_value_phi = uniformDist(gen);

    // solve for phi from the cdf of radial marginalzed distribution
    double phi = std::sqrt(cdf_value_phi);
    double alpha = uniformDist(gen);

    return std::make_pair(m_omega_x*phi*std::cos(2*M_PI*alpha),
                          m_omega_y*phi*std::sin(2*M_PI*alpha));
}

std::pair<double, double> Distribution2DConeSampler::randomSample() const
{
    std::random_device rd;  // random device class instance
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> uniformDist(0.0, 1.0);

    double cdf_value_phi = uniformDist(gen);

    // solve for phi from the cdf of radial marginalzed distribution using Newton-Raphson method
    double func = 0.0, funcDeriv = 0.0, phi = 0.0;

    // initial guess for phi
    phi = 0.5;

    bool convergedSoln = false;
    while (!convergedSoln) {
        func = 2*std::pow(phi,3) - 3*std::pow(phi,2) + cdf_value_phi;
        funcDeriv = 6*std::pow(phi,2) - 6*phi;

        phi = phi - func / funcDeriv;

        if (std::abs(func / funcDeriv) < 0.001)
        {
            if (phi < 0 || phi > 1)
                phi = uniformDist(gen); // only accept a solution for phi if it lies within [0,1]
            else
                convergedSoln = true;
        }
    }

    double alpha = uniformDist(gen);

    return std::make_pair(m_omega_x*phi*std::cos(2*M_PI*alpha),
                          m_omega_y*phi*std::sin(2*M_PI*alpha));
}
*/

std::pair<double, double> Distribution2DCauchySampler::randomSample() const
{
    double phi_max_Cauchy = 1.0;

    // rightmost box's right-edge from phi_max_Cauchy for Ziggurat Sampling
    double r = sigma_scale*std::sqrt(2); // standard dev of func_phi_Cauchy is sqrt(2)

    std::pair<double, double> samples =
            samplingZiggurat(r, phi_max_Cauchy, func_phi_Cauchy);

    return std::make_pair(m_omega_x*samples.first*std::cos(2*M_PI*samples.second),
                          m_omega_y*samples.first*std::sin(2*M_PI*samples.second));
}

std::pair<double, double> Distribution2DGaussSampler::randomSample() const
{
    std::random_device rd;  // random device class instance
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> uniformDist(0.0, 1.0);

    double cdf_value_phi = uniformDist(gen);

    // solve for phi from the cdf of radial marginalzed distribution
    double phi = std::sqrt(-2*std::log(1-cdf_value_phi));
    double alpha = uniformDist(gen);

    return std::make_pair(m_omega_x*phi*std::cos(2*M_PI*alpha),
                          m_omega_y*phi*std::sin(2*M_PI*alpha));
}

std::pair<double, double> Distribution2DGateSampler::randomSample() const
{
    std::random_device rd;  // random device class instance
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> uniformDist(0.0, 1.0);

    double cdf_value_phi = uniformDist(gen);

    // solve for phi from the cdf of radial marginalzed distribution
    double phi = std::sqrt(cdf_value_phi);
    double alpha = uniformDist(gen);

    return std::make_pair(m_omega_x*phi*std::cos(2*M_PI*alpha),
                          m_omega_y*phi*std::sin(2*M_PI*alpha));
}

std::pair<double, double> Distribution2DConeSampler::randomSample() const
{
    double phi_max_Cone = 0.5;

    // rightmost box's right-edge from phi_max_Cone for Ziggurat Sampling
    double r = 0.5;

    std::pair<double, double> samples = samplingZiggurat(r, phi_max_Cone, func_phi_Cone);

    return std::make_pair(m_omega_x*samples.first*std::cos(2*M_PI*samples.second),
                          m_omega_y*samples.first*std::sin(2*M_PI*samples.second));
}
