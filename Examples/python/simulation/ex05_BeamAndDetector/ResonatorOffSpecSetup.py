"""
Resonator in off-specular experiment.
"""
import bornagain as ba
from bornagain import deg, nm, micrometer, angstrom


def get_sample(nlayers = 3):
    """
    Construct resonator with given number of Ti/Pt double layers nlayers.
    """

    # define materials
    m_Si = ba.HomogeneousMaterial("Si", 8.25218379931e-06, 0.0)
    m_Ti = ba.HomogeneousMaterial("Ti", -7.6593316363e-06, 3.81961616312e-09)
    m_TiO2 = ba.HomogeneousMaterial("TiO2", 1.04803530026e-05, 2.03233519385e-09)
    m_Pt = ba.HomogeneousMaterial("Pt", 2.52936993309e-05, 7.54553992473e-09)
    m_D2O = ba.HomogeneousMaterial("D2O", 2.52897204573e-05, 4.5224432814e-13)

    # create layers
    l_TiO2 = ba.Layer(m_TiO2, 3.0*nm)
    l_Ti_top = ba.Layer(m_Ti, 10.0*nm)
    l_Ti = ba.Layer(m_Ti, 13.0*nm)
    l_Si = ba.Layer(m_Si)    # consider it as an ambient layer
    l_Pt = ba.Layer(m_Pt, 32.0*nm)
    l_D2O = ba.Layer(m_D2O)  # thickness is not given, seems to be like a substrate

    # describe layer roughness
    roughness = ba.LayerRoughness()
    roughness.setSigma(2.0*nm)
    roughness.setHurstParameter(0.8)
    roughness.setLatteralCorrLength(10.0*micrometer)

    # assemble multilayer
    sample = ba.MultiLayer()
    sample.addLayer(l_Si)  # Assume huge Si block to be infinite

    for i in range(nlayers):
        sample.addLayerWithTopRoughness(l_Ti, roughness)
        sample.addLayerWithTopRoughness(l_Pt, roughness)

    sample.addLayerWithTopRoughness(l_Ti_top, roughness)
    sample.addLayerWithTopRoughness(l_TiO2, roughness)
    sample.addLayerWithTopRoughness(l_D2O, roughness)

    sample.setCrossCorrLength(400*nm)

    return sample


def get_offspec_simulation():
    """
    characterizing the input beam and output detector
    """

    # create OffSpecular simulation
    simulation = ba.OffSpecSimulation()
    simulation.setTerminalProgressMonitor()

    # define detector parameters
    n_alpha, alpha_min, alpha_max = 300, 0.0*deg, 4.0*deg
    n_phi, phi_min, phi_max = 10, -0.1*deg, 0.1*deg
    simulation.setDetectorParameters(
        n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max)

    # define the beam with alpha_i varied between alpha_i_min and alpha_i_max
    n_scan_points, alpha_i_min, alpha_i_max = n_alpha, alpha_min, alpha_max
    alpha_i_axis = ba.FixedBinAxis(
        "alpha_i", n_scan_points, alpha_i_min, alpha_i_max)
    simulation.setBeamParameters(5.0*angstrom, alpha_i_axis, 0.0)

    simulation.setBeamIntensity(1e9)
    simulation.getOptions().setIncludeSpecular(True)

    # define detector resolution function with smearing depending on bin size
    d_alpha = (alpha_max - alpha_min)/n_alpha
    d_phi = (phi_max-phi_min)/n_phi
    sigma_factor = 1.0
    simulation.setDetectorResolutionFunction(
        ba.ResolutionFunction2DGaussian(sigma_factor*d_alpha, sigma_factor*d_phi))

    return simulation


def run_simulation():
    sample = get_sample(nlayers=3)
    simulation = get_offspec_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, zmin=1e-03)
