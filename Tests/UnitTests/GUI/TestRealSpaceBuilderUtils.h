#ifndef TESTREALSPACEBUILDERUTILS_H
#define TESTREALSPACEBUILDERUTILS_H

#include "google_test.h"
#include <QObject>
#include "RealSpaceBuilderUtils.h"
#include "RealSpaceBuilder.h"
#include "SampleModel.h"
#include "ParticleLayoutItem.h"
#include "ParticleItem.h"
#include "IFormFactor.h"
#include "IFormFactorDecorator.h"
#include "Particle.h"
#include "ApplicationModels.h"
#include "TransformTo3D.h"
#include "RealSpaceModel.h"

class TestRealSpaceBuilderUtils : public ::testing::Test
{
public:
    ~TestRealSpaceBuilderUtils();
};

TestRealSpaceBuilderUtils::~TestRealSpaceBuilderUtils() = default;

TEST_F(TestRealSpaceBuilderUtils, test_RealSpaceModelandParticle)
{
    RealSpaceModel realSpaceModel;

    auto cylinder3D = std::make_unique<RealSpace::Particles::Cylinder>(5, 10);
    QVector3D lattice_position1(0,0,0);
    cylinder3D->addTranslation(lattice_position1);
    realSpaceModel.add(cylinder3D.release());

// Causes a failure as one cannot add an already added particle to the model
//    QVector3D lattice_position2(10,10,10);
//    cylinder3D->addTranslation(lattice_position2);
//    realSpaceModel.add(cylinder3D);
}

TEST_F(TestRealSpaceBuilderUtils, test_cumulativeAbundance)
{
    SampleModel sampleModel;
    auto layout
        = dynamic_cast<ParticleLayoutItem*>(sampleModel.insertNewItem(Constants::ParticleLayoutType));

    auto particle1 = sampleModel.insertNewItem(Constants::ParticleType, sampleModel.indexOfItem(layout),
                                         -1, ParticleLayoutItem::T_PARTICLES);
    EXPECT_EQ(particle1->parent(), layout);

    SessionItem* particle2 = sampleModel.insertNewItem(Constants::ParticleType);
    EXPECT_EQ(particle2->parent(), sampleModel.rootItem());

    sampleModel.moveItem(particle2, layout, -1, ParticleLayoutItem::T_PARTICLES);
    EXPECT_EQ(particle2->parent(), layout);

    particle1->setItemValue(ParticleItem::P_ABUNDANCE, 8.0);
    particle2->setItemValue(ParticleItem::P_ABUNDANCE, 2.0);

    EXPECT_EQ(RealSpaceBuilderUtils::computeCumulativeAbundances(*layout).last(), 10.0);

}

TEST_F(TestRealSpaceBuilderUtils, test_Particle3DType)
{
    Particle3DType p1;

    EXPECT_EQ((p1.get3Dparticles()).size(), 0);
    EXPECT_EQ(p1.getCumulativeAbundance(), 0);
    EXPECT_EQ(p1.getType(), "");

    // Create 3D cylinder using corresponding constructor RealSpace::Particles::Cylinder()
    auto cylinder3D = std::make_unique<RealSpace::Particles::Cylinder>(5, 10);

    // Associate it to a Particle3DType object
    p1.add3DParticle(cylinder3D.release());
    p1.setCumulativeAbundance(1);
    p1.setType(Constants::ParticleType);

    EXPECT_EQ(p1.get3Dparticles().size(), 1);
    EXPECT_EQ(p1.getCumulativeAbundance(), 1);
    EXPECT_EQ(p1.getType(), Constants::ParticleType);

    RealSpaceModel realSpaceModel;

    // Test Copy constructor
    // If copy constructor (DEEP copy) is not implemented then p2/p3 is basically
    // the same as p1 and cannot be added to the RealSpaceModel once p1 is added
    Particle3DType p2(p1);

    EXPECT_EQ(p2.get3Dparticles().size(), 1);
    EXPECT_EQ(p2.getCumulativeAbundance(), 1);
    EXPECT_EQ(p2.getType(), Constants::ParticleType);

    Particle3DType p3 = Particle3DType(p1);

    EXPECT_EQ(p3.get3Dparticles().size(), 1);
    EXPECT_EQ(p3.getCumulativeAbundance(), 1);
    EXPECT_EQ(p3.getType(), Constants::ParticleType);

    // Test assignment operator
    // If assignment operator (DEEP) is not implemented then p4 is basically
    // the same as p1 and cannot be added to the RealSpaceModel once p1 is added
    Particle3DType p4;
    p4 = p1;

    EXPECT_EQ(p4.get3Dparticles().size(), 1);
    EXPECT_EQ(p4.getCumulativeAbundance(), 1);
    EXPECT_EQ(p4.getType(), Constants::ParticleType);

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

    // The normal raw instances p1, p2 etc. get deleted by the destructor of Particle3DType
}

TEST_F(TestRealSpaceBuilderUtils, test_getSingleParticle3DType)
{
    ApplicationModels models;
    SampleModel* sampleModel = models.sampleModel();

    auto particle = sampleModel->insertNewItem(Constants::ParticleType);
    EXPECT_EQ(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);
    EXPECT_EQ(particle->getGroupItem(ParticleItem::P_FORM_FACTOR)->modelType(), Constants::CylinderType);

    particle->setItemValue(ParticleItem::P_ABUNDANCE, 8.0);
    EXPECT_EQ(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 8.0);
    particle->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::BoxType);
    EXPECT_EQ(particle->getGroupItem(ParticleItem::P_FORM_FACTOR)->modelType(), Constants::BoxType);

    // Create a 3D particle from particleItem and associate it to a Particle3DType object
    auto singleParticle3DType = RealSpaceBuilderUtils::getSingleParticle3DType(particle, 8);

    EXPECT_EQ(singleParticle3DType.get3Dparticles().size(), 1);
    //EXPECT_TRUE(singleParticle3DType.m_3Dparticles.at(0) != nullptr);
    EXPECT_EQ(singleParticle3DType.getCumulativeAbundance(), 1);
    EXPECT_EQ(singleParticle3DType.getType(), Constants::ParticleType);
}

TEST_F(TestRealSpaceBuilderUtils, test_getParticle3DTypeVector)
{
    ApplicationModels models;
    SampleModel* sampleModel = models.sampleModel();

    auto layout
        = dynamic_cast<ParticleLayoutItem*>(sampleModel->insertNewItem(Constants::ParticleLayoutType));

    auto particle1 = sampleModel->insertNewItem(Constants::ParticleType);
    auto particle2 = sampleModel->insertNewItem(Constants::ParticleType);
    auto particle3 = sampleModel->insertNewItem(Constants::ParticleType);

    sampleModel->moveItem(particle1, layout, -1, ParticleLayoutItem::T_PARTICLES);
    sampleModel->moveItem(particle2, layout, -1, ParticleLayoutItem::T_PARTICLES);
    sampleModel->moveItem(particle3, layout, -1, ParticleLayoutItem::T_PARTICLES);

    particle1->setItemValue(ParticleItem::P_ABUNDANCE, 5.0);
    particle2->setItemValue(ParticleItem::P_ABUNDANCE, 3.0);
    particle3->setItemValue(ParticleItem::P_ABUNDANCE, 2.0);

    double total_abundance = RealSpaceBuilderUtils::computeCumulativeAbundances(*layout).last();
    EXPECT_EQ(total_abundance, 10.0);

    particle1->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::BoxType);
    particle2->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::ConeType);
    particle3->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::PyramidType);

    auto particle3DType_vector = RealSpaceBuilderUtils::getParticle3DTypeVector(*layout);

    EXPECT_EQ(particle3DType_vector.size(), 3);

    EXPECT_EQ(particle3DType_vector.at(0).get3Dparticles().size(), 1);
    EXPECT_EQ(particle3DType_vector.at(0).getCumulativeAbundance(), 0.5);
    EXPECT_EQ(particle3DType_vector.at(0).getType(), Constants::ParticleType);

    EXPECT_EQ(particle3DType_vector.at(1).get3Dparticles().size(), 1);
    EXPECT_EQ(particle3DType_vector.at(1).getCumulativeAbundance(), 0.8);
    EXPECT_EQ(particle3DType_vector.at(1).getType(), Constants::ParticleType);

    EXPECT_EQ(particle3DType_vector.at(2).get3Dparticles().size(), 1);
    EXPECT_EQ(particle3DType_vector.at(2).getCumulativeAbundance(), 1.0);
    EXPECT_EQ(particle3DType_vector.at(2).getType(), Constants::ParticleType);
}


#endif // TESTREALSPACEBUILDERUTILS_H
