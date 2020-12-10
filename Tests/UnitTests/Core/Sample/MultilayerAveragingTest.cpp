#include "Sample/Aggregate/InterferenceFunction2DLattice.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Processed/ProcessedSample.h"
#include "Sample/RT/SimulationOptions.h"
#include "Tests/GTestWrapper/google_test.h"

class MultilayerAveragingTest : public ::testing::Test {
protected:
    MultilayerAveragingTest()
        : vacuum(HomogeneousMaterial("vac", 0.0, 0.0))
        , stone(HomogeneousMaterial("stone", 4e-4, 8e-7)) {}

    const Material vacuum, stone;
};

TEST_F(MultilayerAveragingTest, AverageMultilayer) {
    // particles
    FormFactorCylinder cylinder_ff(1.0, 3.0);
    Particle particle(stone, cylinder_ff);

    // interferences
    InterferenceFunction2DLattice interf_1(BasicLattice2D(10.0, 10.0, 120.0, 0.0));
    InterferenceFunction2DLattice interf_2(BasicLattice2D(10.0, 10.0, 120.0, 0.0));

    // layouts
    ParticleLayout layout_1;
    layout_1.addParticle(particle);
    layout_1.setInterferenceFunction(interf_1);
    EXPECT_DOUBLE_EQ(layout_1.weight(), 1.0);

    ParticleLayout layout_2;
    layout_2.addParticle(particle);
    layout_2.setInterferenceFunction(interf_2);
    EXPECT_DOUBLE_EQ(layout_2.weight(), 1.0);

    std::unique_ptr<ProcessedSample> sample_1;
    {
        Layer layer_1(vacuum);
        Layer layer_2(stone);

        layer_1.addLayout(layout_1);

        MultiLayer m_layer;
        m_layer.addLayer(layer_1);
        m_layer.addLayer(layer_2);

        SimulationOptions opts;
        opts.setUseAvgMaterials(true);

        sample_1 = std::make_unique<ProcessedSample>(m_layer, opts);
    }

    layout_1.setWeight(0.5);
    EXPECT_DOUBLE_EQ(layout_1.weight(), 0.5);
    layout_2.setWeight(0.5);
    EXPECT_DOUBLE_EQ(layout_2.weight(), 0.5);

    std::unique_ptr<ProcessedSample> sample_2;
    {
        Layer layer_1(vacuum);
        Layer layer_2(stone);

        layer_1.addLayout(layout_1);
        layer_1.addLayout(layout_2);

        MultiLayer m_layer;
        m_layer.addLayer(layer_1);
        m_layer.addLayer(layer_2);

        SimulationOptions opts;
        opts.setUseAvgMaterials(true);

        sample_2 = std::make_unique<ProcessedSample>(m_layer, opts);
    }

    EXPECT_EQ(sample_1->numberOfSlices(), sample_2->numberOfSlices());

    for (size_t i = 0; i < sample_1->numberOfSlices(); ++i) {
        auto mat_1 = sample_1->slices()[i].material().materialData();
        auto mat_2 = sample_2->slices()[i].material().materialData();
        EXPECT_DOUBLE_EQ(mat_1.real(), mat_2.real());
        EXPECT_DOUBLE_EQ(mat_1.imag(), mat_2.imag());
    }
}
