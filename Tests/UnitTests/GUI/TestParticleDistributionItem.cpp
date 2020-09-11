#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleDistribution.h"
#include "Core/includeIncludes/FormFactors.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DistributionItems.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/RealLimitsItems.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/TransformFromDomain.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialEditor.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QXmlStreamWriter>

namespace
{
const QStringList expectedCylinderParams = {"None",
                                            "Particle/Cylinder/Radius",
                                            "Particle/Cylinder/Height",
                                            "Particle/Position Offset/X",
                                            "Particle/Position Offset/Y",
                                            "Particle/Position Offset/Z"};

const QStringList expectedBoxParams = {"None",
                                       "Particle/Box/Length",
                                       "Particle/Box/Width",
                                       "Particle/Box/Height",
                                       "Particle/Position Offset/X",
                                       "Particle/Position Offset/Y",
                                       "Particle/Position Offset/Z"};
} // namespace

class TestParticleDistributionItem : public ::testing::Test
{
};

TEST_F(TestParticleDistributionItem, test_InitialState)
{
    SampleModel model;
    SessionItem* distItem = model.insertNewItem("ParticleDistribution");

    EXPECT_EQ(distItem->displayName(), "ParticleDistribution");
    EXPECT_EQ(distItem->displayName(), distItem->itemName());

    // xpos, ypos, P_ABUNDANCE, P_DISTRIBUTION, P_DISTRIBUTED_PARAMETER
    EXPECT_EQ(distItem->children().size(), 6);

    EXPECT_EQ(distItem->defaultTag(), ParticleDistributionItem::T_PARTICLES);

    EXPECT_EQ(distItem->acceptableDefaultItemTypes(), QVector<QString>() << "Particle"
                                                                         << "ParticleCoreShell"
                                                                         << "ParticleComposition"
                                                                         << "MesoCrystal");

    // main parameter
    ComboProperty prop = distItem->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                             .value<ComboProperty>();
    EXPECT_EQ(prop.getValues(), QStringList() << ParticleDistributionItem::NO_SELECTION);
    EXPECT_EQ(prop.getValue(), ParticleDistributionItem::NO_SELECTION);

    // linked parameter
    prop =
        distItem->getItemValue(ParticleDistributionItem::P_LINKED_PARAMETER).value<ComboProperty>();
    EXPECT_EQ(prop.getValues(), QStringList());
    EXPECT_EQ(prop.getValue(), "");
}

TEST_F(TestParticleDistributionItem, test_AddParticle)
{
    SampleModel model;
    SessionItem* dist = model.insertNewItem("ParticleDistribution");

    // adding default particle and checking list of available parameters
    SessionItem* particle = model.insertNewItem("Particle", dist->index());

    EXPECT_EQ(dist->getItems().size(), 1);

    ComboProperty prop = dist->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                             .value<ComboProperty>();

    EXPECT_EQ(prop.getValues(), expectedCylinderParams);
    EXPECT_EQ(prop.getValue(), ParticleDistributionItem::NO_SELECTION);

    // linked parameter
    prop = dist->getItemValue(ParticleDistributionItem::P_LINKED_PARAMETER).value<ComboProperty>();

    QStringList expectedLinked = expectedCylinderParams;
    expectedLinked.removeAll(ParticleDistributionItem::NO_SELECTION);
    EXPECT_EQ(prop.getValues(), expectedLinked);
    EXPECT_EQ(prop.getValue(), "");

    // changing form factor of the particle
    particle->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Box");

    prop = dist->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
               .value<ComboProperty>();

    EXPECT_EQ(prop.getValues(), expectedBoxParams);
    EXPECT_EQ(prop.getValue(), ParticleDistributionItem::NO_SELECTION);

    // cheking linked
    prop = dist->getItemValue(ParticleDistributionItem::P_LINKED_PARAMETER).value<ComboProperty>();

    expectedLinked = expectedBoxParams;
    expectedLinked.removeAll(ParticleDistributionItem::NO_SELECTION);
    EXPECT_EQ(prop.getValues(), expectedLinked);
    EXPECT_EQ(prop.getValue(), "");
    EXPECT_EQ(prop.selectedValues(), QStringList());
}

//! Values available for linking should depend on main parameter.

TEST_F(TestParticleDistributionItem, test_MainLinkedCorrelation)
{
    SampleModel model;
    SessionItem* dist = model.insertNewItem("ParticleDistribution");
    model.insertNewItem("Particle", dist->index());

    ComboProperty mainCombo = dist->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                                  .value<ComboProperty>();

    EXPECT_EQ(mainCombo.getValues(), expectedCylinderParams);
    EXPECT_EQ(mainCombo.getValue(), ParticleDistributionItem::NO_SELECTION);

    // linked parameter
    ComboProperty linkedCombo =
        dist->getItemValue(ParticleDistributionItem::P_LINKED_PARAMETER).value<ComboProperty>();

    QStringList expectedLinked = expectedCylinderParams;
    expectedLinked.removeAll(ParticleDistributionItem::NO_SELECTION);
    EXPECT_EQ(linkedCombo.getValues(), expectedLinked);
    EXPECT_EQ(linkedCombo.getValue(), "");
    EXPECT_EQ(linkedCombo.selectedValues(), QStringList());

    // selecting main parameter
    QString mainPar("Particle/Cylinder/Radius");
    mainCombo.setValue(mainPar);
    dist->setItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER, mainCombo.variant());

    // linked parameter shouldn't have main parameter in the list
    expectedLinked = expectedCylinderParams;
    expectedLinked.removeAll(ParticleDistributionItem::NO_SELECTION);
    expectedLinked.removeAll(mainPar);

    linkedCombo =
        dist->getItemValue(ParticleDistributionItem::P_LINKED_PARAMETER).value<ComboProperty>();
    EXPECT_EQ(linkedCombo.getValues(), expectedLinked);
    EXPECT_EQ(linkedCombo.getValue(), "");
    EXPECT_EQ(linkedCombo.selectedValues(), QStringList());

    // --- Scenario 2

    // selecting linked parameter
    linkedCombo.setSelected("Particle/Cylinder/Height");
    dist->setItemValue(ParticleDistributionItem::P_LINKED_PARAMETER, linkedCombo.variant());

    // selecting another main parameter
    mainPar = "Particle/Position Offset/X";
    mainCombo.setValue(mainPar);
    dist->setItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER, mainCombo.variant());

    // checking linked
    linkedCombo =
        dist->getItemValue(ParticleDistributionItem::P_LINKED_PARAMETER).value<ComboProperty>();
    expectedLinked = expectedCylinderParams;
    expectedLinked.removeAll(ParticleDistributionItem::NO_SELECTION);
    expectedLinked.removeAll(mainPar);

    EXPECT_EQ(linkedCombo.getValues(), expectedLinked);
    EXPECT_EQ(linkedCombo.getValue(), "Particle/Cylinder/Height");
    EXPECT_EQ(linkedCombo.selectedValues(), QStringList("Particle/Cylinder/Height"));
}

TEST_F(TestParticleDistributionItem, test_FromDomain)
{
    const std::string pattern("/Particle/Cylinder/Radius");

    // creating domain distribution
    FormFactorCylinder cylinder(1.0, 2.0);
    Particle particle(HomogeneousMaterial("Particle", 6e-4, 2e-8), cylinder);
    DistributionGaussian gauss(1.0, 0.1);
    ParameterDistribution par_distr(pattern, gauss, 100, 3.0);

    ParticleDistribution particle_collection(particle, par_distr);

    // creating GUI distribution
    SampleModel model;
    SessionItem* distItem = model.insertNewItem("ParticleDistribution");
    SessionItem* particleItem = model.insertNewItem("Particle", distItem->index());

    particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "AnisoPyramid");

    // Sets it from domain
    TransformFromDomain::setParticleDistributionItem(distItem, particle_collection);

    ComboProperty prop = distItem->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                             .value<ComboProperty>();

    EXPECT_EQ(prop.getValue(), ParticleDistributionItem::NO_SELECTION);

    // changing particle type and check that distribution picked up domain name
    particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Cylinder");
    prop = distItem->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
               .value<ComboProperty>();

    EXPECT_EQ(prop.getValue(), "Particle/Cylinder/Radius");
}

//! Constructing from domain distribution with linked parameter defined

TEST_F(TestParticleDistributionItem, test_FromDomainLinked)
{
    const std::string pattern("/Particle/Cylinder/Radius");
    const std::string linked("/Particle/Cylinder/Height");

    // creating domain distribution
    FormFactorCylinder cylinder(1.0, 2.0);
    Particle particle(HomogeneousMaterial("Particle", 6e-4, 2e-8), cylinder);
    DistributionGaussian gauss(1.0, 0.1);
    ParameterDistribution par_distr(pattern, gauss, 100, 3.0);
    par_distr.linkParameter(linked);

    ParticleDistribution particle_collection(particle, par_distr);

    // creating GUI distribution
    SampleModel model;
    SessionItem* distItem = model.insertNewItem("ParticleDistribution");
    SessionItem* particleItem = model.insertNewItem("Particle", distItem->index());

    particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "AnisoPyramid");

    // Sets it from domain
    TransformFromDomain::setParticleDistributionItem(distItem, particle_collection);

    ComboProperty prop = distItem->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                             .value<ComboProperty>();
    EXPECT_EQ(prop.getValue(), ParticleDistributionItem::NO_SELECTION);

    ComboProperty linkedProp =
        distItem->getItemValue(ParticleDistributionItem::P_LINKED_PARAMETER).value<ComboProperty>();
    EXPECT_EQ(linkedProp.getValue(), "");

    // changing particle type and check that distribution picked up domain name
    particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Cylinder");

    prop = distItem->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
               .value<ComboProperty>();
    EXPECT_EQ(prop.getValue(), "Particle/Cylinder/Radius");

    linkedProp =
        distItem->getItemValue(ParticleDistributionItem::P_LINKED_PARAMETER).value<ComboProperty>();
    QStringList expectedLinked = QStringList() << "Particle/Cylinder/Height";
    EXPECT_EQ(linkedProp.selectedValues(), expectedLinked);
    EXPECT_EQ(linkedProp.getValue(), expectedLinked.at(0));
}

TEST_F(TestParticleDistributionItem, test_FromDomainWithLimits)
{
    const std::string pattern("/Particle/Cylinder/Radius");

    // creating domain distribution
    FormFactorCylinder cylinder(1.0, 2.0);
    Particle particle(HomogeneousMaterial("Particle", 6e-4, 2e-8), cylinder);
    DistributionGaussian gauss(1.0, 0.1);

    RealLimits domainLimits = RealLimits::limited(1.0, 2.0);
    ParameterDistribution par_distr(pattern, gauss, 100, 3.0, domainLimits);

    ParticleDistribution particle_collection(particle, par_distr);

    // creating GUI distribution
    SampleModel model;
    SessionItem* partDistItem = model.insertNewItem("ParticleDistribution");
    model.insertNewItem("Particle", partDistItem->index());

    // Sets it from domain
    TransformFromDomain::setParticleDistributionItem(partDistItem, particle_collection);

    SessionItem* distItem = partDistItem->getGroupItem(ParticleDistributionItem::P_DISTRIBUTION);
    ASSERT(distItem);
    RealLimitsItem* limitsItem =
        dynamic_cast<RealLimitsItem*>(distItem->getGroupItem(DistributionItem::P_LIMITS));
    ASSERT(limitsItem);

    EXPECT_EQ(limitsItem->createRealLimits(), domainLimits);
}

TEST_F(TestParticleDistributionItem, test_Clone)
{
    std::unique_ptr<MaterialModel> P_materialModel(new MaterialModel());

    SampleModel model1;
    SessionItem* dist = model1.insertNewItem("ParticleDistribution");
    model1.insertNewItem("Particle", dist->index());

    QString buffer1;
    QXmlStreamWriter writer1(&buffer1);
    model1.writeTo(&writer1);

    std::unique_ptr<SampleModel> model2(model1.createCopy());
    QString buffer2;
    QXmlStreamWriter writer2(&buffer2);
    model2->writeTo(&writer2);

    EXPECT_EQ(buffer1, buffer2);
}
