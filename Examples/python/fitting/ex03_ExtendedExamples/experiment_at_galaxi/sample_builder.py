"""
3 layers system (substrate, teflon, air).
Air layer is populated with spheres with size distribution.
"""
import bornagain as ba


class SampleBuilder:
    """
    Builds complex sample from set of parameters.
    """
    def __init__(self):
        """
        Init SampleBuilder with default sample parameters.
        """
        self.radius = 5.75*ba.nm
        self.sigma = 0.4
        self.distance = 53.6*ba.nm
        self.disorder = 10.5*ba.nm
        self.kappa = 17.5
        self.ptfe_thickness = 22.1*ba.nm
        self.hmdso_thickness = 18.5*ba.nm

    def create_sample(self, params):
        """
        Create sample from given set of parameters.

        Args:
            params: A dictionary containing parameter map.

        Returns:
            A multi layer.
        """
        self.radius = params["radius"]
        self.sigma = params["sigma"]
        self.distance = params["distance"]
        return self.multilayer()

    def multilayer(self):
        """
        Constructs the sample from current parameter values.
        """

        # defining materials
        m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
        m_Si = ba.HomogeneousMaterial("Si", 5.78164736e-6, 1.02294578e-7)
        m_Ag = ba.HomogeneousMaterial("Ag", 2.24749529E-5, 1.61528396E-6)
        m_PTFE = ba.HomogeneousMaterial("PTFE", 5.20508729E-6, 1.96944292E-8)
        m_HMDSO = ba.HomogeneousMaterial("HMDSO", 2.0888308E-6, 1.32605651E-8)

        # collection of particles with size distribution
        nparticles = 20
        nfwhm = 2.0
        sphere_ff = ba.FormFactorFullSphere(self.radius)

        sphere = ba.Particle(m_Ag, sphere_ff)
        position = ba.kvector_t(0*ba.nm, 0*ba.nm,-1.0*self.hmdso_thickness)
        sphere.setPosition(position)
        ln_distr = ba.DistributionLogNormal(self.radius, self.sigma)
        par_distr = ba.ParameterDistribution(
            "/Particle/FullSphere/Radius", ln_distr, nparticles, nfwhm,
            ba.RealLimits.limited(0.0, self.hmdso_thickness/2.0))
        part_coll = ba.ParticleDistribution(sphere, par_distr)

        # interference function
        interference = ba.InterferenceFunctionRadialParaCrystal(
            self.distance, 1e6*ba.nm)
        interference.setKappa(self.kappa)
        interference.setDomainSize(20000.0)
        pdf = ba.FTDistribution1DGauss(self.disorder)
        interference.setProbabilityDistribution(pdf)

        # assembling particle layout
        layout = ba.ParticleLayout()
        layout.addParticle(part_coll, 1.0)
        layout.setInterferenceFunction(interference)
        layout.setApproximation(ba.ILayout.SSCA)
        layout.setTotalParticleSurfaceDensity(1)

        # roughness
        r_ptfe = ba.LayerRoughness(2.3*ba.nm, 0.3, 5.0*ba.nm)
        r_hmdso = ba.LayerRoughness(1.1*ba.nm, 0.3, 5.0*ba.nm)

        # layers
        air_layer = ba.Layer(m_air)
        hmdso_layer = ba.Layer(m_HMDSO, self.hmdso_thickness)
        hmdso_layer.addLayout(layout)
        ptfe_layer = ba.Layer(m_PTFE, self.ptfe_thickness)
        substrate_layer = ba.Layer(m_Si)

        # assembling multilayer
        multi_layer = ba.MultiLayer()
        multi_layer.addLayer(air_layer)
        multi_layer.addLayerWithTopRoughness(hmdso_layer, r_hmdso)
        multi_layer.addLayerWithTopRoughness(ptfe_layer, r_ptfe)
        multi_layer.addLayer(substrate_layer)

        return multi_layer
