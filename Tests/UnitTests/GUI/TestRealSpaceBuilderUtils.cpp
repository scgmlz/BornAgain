#include "Core/Particle/Particle.h"
#include "Core/Scattering/IFormFactor.h"
#include "Core/Scattering/IFormFactorDecorator.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/ParticleLayoutItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Views/RealSpaceWidgets/Particle3DContainer.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceModel.h"
#include "GUI/coregui/Views/RealSpaceWidgets/TransformTo3D.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QObject>

class TestRealSpaceBuilderUtils : public ::testing::Test
{
};

TEST_F(TestRealSpaceBuilderUtils, test_RealSpaceModelandParticle)
{
    RealSpaceModel realSpaceModel;

    auto cylinder3D = std::make_unique<RealSpace::Particles::Cylinder>(5, 10);
    QVector3D lattice_position1(0, 0, 0);
    cylinder3D->addTranslation(lattice_position1);
    realSpaceModel.add(cylinder3D.release());

    // Causes a failure as one cannot add an already added particle to the model
    //    QVector3D lattice_position2(10,10,10);
    //    cylinder3D->addTranslation(lattice_position2);
    //    realSpaceModel.add(cylinder3D.release());
}

TEST_F(TestRealSpaceBuilderUtils, test_computeCumulativeAbundances)
{
    SampleModel sampleModel;
    auto layout = dynamic_cast<ParticleLayoutItem*>(sampleModel.insertNewItem("ParticleLayout"));

    auto particle1 = sampleModel.insertNewItem("Particle", sampleModel.indexOfItem(layout), -1,
                                               ParticleLayoutItem::T_PARTICLES);
    EXPECT_EQ(particle1->parent(), layout);

    SessionItem* particle2 = sampleModel.insertNewItem("Particle");
    EXPECT_EQ(particle2->parent(), sampleModel.rootItem());

    sampleModel.moveItem(particle2, layout, -1, ParticleLayoutItem::T_PARTICLES);
    EXPECT_EQ(particle2->parent(), layout);

    particle1->setItemValue(ParticleItem::P_ABUNDANCE, 8.0);
    particle2->setItemValue(ParticleItem::P_ABUNDANCE, 2.0);

    EXPECT_EQ(RealSpaceBuilderUtils::computeCumulativeAbundances(*layout).last(), 10.0);
}

TEST_F(TestRealSpaceBuilderUtils, test_Particle3DContainer)
{
    Particle3DContainer p1;

    EXPECT_EQ(p1.containerSize(), 0u);
    EXPECT_EQ(p1.cumulativeAbundance(), 0);
    EXPECT_EQ(p1.particleType(), "");

    // Create 3D cylinder using corresponding constructor RealSpace::Particles::Cylinder()
    auto cylinder3D = std::make_unique<RealSpace::Particles::Cylinder>(5, 10);

    // Associate it to a Particle3DContainer object
    p1.addParticle(cylinder3D.release(), false);
    p1.setCumulativeAbundance(1);
    p1.setParticleType("Particle");

    EXPECT_EQ(p1.containerSize(), 1u);
    EXPECT_EQ(p1.cumulativeAbundance(), 1);
    EXPECT_EQ(p1.particleType(), "Particle");
    EXPECT_FALSE(p1.particle3DBlend(0u));

    RealSpaceModel realSpaceModel;

    // Test copy constructor
    // If copy constructor (DEEP copy) is not implemented then p2/p3 is basically
    // the same as p1 and cannot be added to the RealSpaceModel once p1 is added
    Particle3DContainer p2(p1);

    EXPECT_EQ(p2.containerSize(), 1u);
    EXPECT_EQ(p2.cumulativeAbundance(), 1);
    EXPECT_EQ(p2.particleType(), "Particle");
    EXPECT_FALSE(p2.particle3DBlend(0u));

    Particle3DContainer p3 = {p1};

    EXPECT_EQ(p3.containerSize(), 1u);
    EXPECT_EQ(p3.cumulativeAbundance(), 1);
    EXPECT_EQ(p3.particleType(), "Particle");
    EXPECT_FALSE(p3.particle3DBlend(0u));

    // Test copy assignment operator
    // If assignment operator (DEEP) is not implemented then p4 is basically
    // the same as p1 and cannot be added to the RealSpaceModel once p1 is added
    Particle3DContainer p4;
    p4 = p1;

    EXPECT_EQ(p4.containerSize(), 1u);
    EXPECT_EQ(p4.cumulativeAbundance(), 1);
    EXPECT_EQ(p4.particleType(), "Particle");
    EXPECT_FALSE(p4.particle3DBlend(0u));

    // Add particle to RealSpaceModel by first creating a unique instance of it and then
    // releasing (transfer ownership) to the model which deletes the new particle instance later on
    auto p1_unique = p1.createParticle(0);
    auto p2_unique = p2.createParticle(0);
    auto p3_unique = p3.createParticle(0);
    auto p4_unique = p4.createParticle(0);

    realSpaceModel.add(p1_unique.release());
    realSpaceModel.add(p2_unique.release());
    realSpaceModel.add(p3_unique.release());
    realSpaceModel.add(p4_unique.release());

    // Test move constructor
    Particle3DContainer p5(std::move(p4));

    // Test the contents of the Particle3DContainer being moved-from
    EXPECT_EQ(p4.containerSize(), 0u);      // move empties the std::vector container
    EXPECT_EQ(p4.cumulativeAbundance(), 1); // move doesn't affect int data member
    EXPECT_EQ(p4.particleType(), "");       // move empties the QString

    // Test the contents of the Particle3DContainer being moved-to
    EXPECT_EQ(p5.containerSize(), 1u);
    EXPECT_EQ(p5.cumulativeAbundance(), 1);
    EXPECT_EQ(p5.particleType(), "Particle");
    EXPECT_FALSE(p5.particle3DBlend(0u));

    auto p5_unique = p5.createParticle(0);
    realSpaceModel.add(p5_unique.release());

    Particle3DContainer p6 = Particle3DContainer(std::move(p5));

    EXPECT_EQ(p5.containerSize(), 0u);
    EXPECT_EQ(p5.cumulativeAbundance(), 1);
    EXPECT_EQ(p5.particleType(), "");

    EXPECT_EQ(p6.containerSize(), 1u);
    EXPECT_EQ(p6.cumulativeAbundance(), 1);
    EXPECT_EQ(p6.particleType(), "Particle");
    EXPECT_FALSE(p6.particle3DBlend(0u));

    auto p6_unique = p6.createParticle(0);
    realSpaceModel.add(p6_unique.release());

    // Test move assignment operator
    Particle3DContainer p7;
    p7 = std::move(p6);

    EXPECT_EQ(p6.containerSize(), 0u);
    EXPECT_EQ(p6.cumulativeAbundance(), 1);
    EXPECT_EQ(p6.particleType(), "");

    EXPECT_EQ(p7.containerSize(), 1u);
    EXPECT_EQ(p7.cumulativeAbundance(), 1);
    EXPECT_EQ(p7.particleType(), "Particle");
    EXPECT_FALSE(p7.particle3DBlend(0u));

    auto p7_unique = p7.createParticle(0);
    realSpaceModel.add(p7_unique.release());

    // The normal raw instances p1, p2 etc. get deleted by the destructor of Particle3DContainer
}

TEST_F(TestRealSpaceBuilderUtils, test_singleParticle3DContainer)
{
    ApplicationModels models;
    SampleModel* sampleModel = models.sampleModel();

    auto particleItem = sampleModel->insertNewItem("Particle");
    EXPECT_EQ(particleItem->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);
    EXPECT_EQ(particleItem->getGroupItem(ParticleItem::P_FORM_FACTOR)->modelType(), "Cylinder");

    particleItem->setItemValue(ParticleItem::P_ABUNDANCE, 8.0);
    EXPECT_EQ(particleItem->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 8.0);
    particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Box");
    EXPECT_EQ(particleItem->getGroupItem(ParticleItem::P_FORM_FACTOR)->modelType(), "Box");

    // Create a 3D particle from particleItem and associate it to a Particle3DContainer object
    auto pItem = dynamic_cast<const ParticleItem*>(particleItem);
    auto particle = pItem->createParticle();
    auto singleParticle3DContainer = RealSpaceBuilderUtils::singleParticle3DContainer(*particle, 8);

    EXPECT_EQ(singleParticle3DContainer.containerSize(), 1u);
    EXPECT_EQ(singleParticle3DContainer.cumulativeAbundance(), 1);
    EXPECT_EQ(singleParticle3DContainer.particleType(), "Particle");
    EXPECT_FALSE(singleParticle3DContainer.particle3DBlend(0u));
}

TEST_F(TestRealSpaceBuilderUtils, test_particle3DContainerVector)
{
    ApplicationModels models;
    SampleModel* sampleModel = models.sampleModel();

    auto layout = dynamic_cast<ParticleLayoutItem*>(sampleModel->insertNewItem("ParticleLayout"));

    auto particle1 = sampleModel->insertNewItem("Particle");
    auto particle2 = sampleModel->insertNewItem("Particle");
    auto particle3 = sampleModel->insertNewItem("Particle");

    sampleModel->moveItem(particle1, layout, -1, ParticleLayoutItem::T_PARTICLES);
    sampleModel->moveItem(particle2, layout, -1, ParticleLayoutItem::T_PARTICLES);
    sampleModel->moveItem(particle3, layout, -1, ParticleLayoutItem::T_PARTICLES);

    particle1->setItemValue(ParticleItem::P_ABUNDANCE, 5.0);
    particle2->setItemValue(ParticleItem::P_ABUNDANCE, 3.0);
    particle3->setItemValue(ParticleItem::P_ABUNDANCE, 2.0);

    double total_abundance = RealSpaceBuilderUtils::computeCumulativeAbundances(*layout).last();
    EXPECT_EQ(total_abundance, 10.0);

    particle1->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Box");
    particle2->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Cone");
    particle3->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Pyramid");

    auto particle3DContainer_vector = RealSpaceBuilderUtils::particle3DContainerVector(*layout);

    EXPECT_EQ(particle3DContainer_vector.size(), static_cast<size_t>(3));

    EXPECT_EQ(particle3DContainer_vector.at(0).containerSize(), 1u);
    EXPECT_EQ(particle3DContainer_vector.at(0).cumulativeAbundance(), 0.5);
    EXPECT_EQ(particle3DContainer_vector.at(0).particleType(), "Particle");

    EXPECT_EQ(particle3DContainer_vector.at(1).containerSize(), 1u);
    EXPECT_EQ(particle3DContainer_vector.at(1).cumulativeAbundance(), 0.8);
    EXPECT_EQ(particle3DContainer_vector.at(1).particleType(), "Particle");

    EXPECT_EQ(particle3DContainer_vector.at(2).containerSize(), 1u);
    EXPECT_EQ(particle3DContainer_vector.at(2).cumulativeAbundance(), 1.0);
    EXPECT_EQ(particle3DContainer_vector.at(2).particleType(), "Particle");
}
