#include "Core/Aggregate/InterferenceFunction2DParaCrystal.h"
#include "Core/Basics/Units.h"
#include "Core/Correlations/FTDistributions2D.h"
#include "Core/Lattice/Lattice2D.h"
#include "GUI/coregui/Models/FTDistributionItems.h"
#include "GUI/coregui/Models/InterferenceFunctionItems.h"
#include "GUI/coregui/Models/Lattice2DItems.h"
#include "GUI/coregui/Models/ParticleLayoutItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/TransformFromDomain.h"
#include "Tests/GTestWrapper/google_test.h"

class TestParaCrystalItems : public ::testing::Test
{
};

TEST_F(TestParaCrystalItems, test_Para2D_fromToDomain)
{
    double length1(10.0), length2(20.0), angle(45.0), xi(90.0);
    double damping_length(1000.0), domain_size1(50.0), domain_size2(100.0);

    InterferenceFunction2DParaCrystal orig(length1, length2, angle * Units::deg, xi * Units::deg,
                                           damping_length);
    orig.setDomainSizes(domain_size1, domain_size2);

    double clength_x(1.0), clength_y(2.0), gamma(3.0);
    orig.setProbabilityDistributions(
        FTDistribution2DCauchy(clength_x, clength_y, gamma * Units::deg),
        FTDistribution2DGauss(clength_x, clength_y, gamma * Units::deg));

    // from domain
    InterferenceFunction2DParaCrystalItem item;
    TransformFromDomain::set2DParaCrystalItem(&item, orig);

    EXPECT_EQ(item.getItemValue(InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH).toDouble(),
              orig.dampingLength());
    EXPECT_EQ(item.getItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1).toDouble(),
              orig.domainSizes()[0]);
    EXPECT_EQ(item.getItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2).toDouble(),
              orig.domainSizes()[1]);
    EXPECT_EQ(orig.integrationOverXi(), false);
    EXPECT_EQ(item.getItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION).toBool(),
              orig.integrationOverXi());

    SessionItem* latticeItem = item.getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
    EXPECT_EQ(latticeItem->modelType(), "BasicLattice");
    EXPECT_EQ(latticeItem->getItemValue(BasicLatticeItem::P_LATTICE_LENGTH1).toDouble(), length1);
    EXPECT_EQ(latticeItem->getItemValue(BasicLatticeItem::P_LATTICE_LENGTH2).toDouble(), length2);
    EXPECT_EQ(latticeItem->getItemValue(BasicLatticeItem::P_LATTICE_ANGLE).toDouble(), angle);
    EXPECT_EQ(latticeItem->getItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE).toDouble(), xi);

    SessionItem* pdfItem1 = item.getGroupItem(InterferenceFunction2DParaCrystalItem::P_PDF1);
    EXPECT_EQ(pdfItem1->modelType(), "FTDistribution2DCauchy");
    EXPECT_EQ(pdfItem1->getItemValue(FTDistribution2DItem::P_OMEGA_X).toDouble(), clength_x);
    EXPECT_EQ(pdfItem1->getItemValue(FTDistribution2DItem::P_OMEGA_Y).toDouble(), clength_y);
    EXPECT_EQ(pdfItem1->getItemValue(FTDistribution2DItem::P_GAMMA).toDouble(), gamma);

    SessionItem* pdfItem2 = item.getGroupItem(InterferenceFunction2DParaCrystalItem::P_PDF2);
    EXPECT_EQ(pdfItem2->modelType(), "FTDistribution2DGauss");
    EXPECT_EQ(pdfItem2->getItemValue(FTDistribution2DItem::P_OMEGA_X).toDouble(), clength_x);
    EXPECT_EQ(pdfItem2->getItemValue(FTDistribution2DItem::P_OMEGA_Y).toDouble(), clength_y);
    EXPECT_EQ(pdfItem2->getItemValue(FTDistribution2DItem::P_GAMMA).toDouble(), gamma);

    // to domain
    auto ifun = item.createInterferenceFunction();
    std::unique_ptr<InterferenceFunction2DParaCrystal> domain(
        dynamic_cast<InterferenceFunction2DParaCrystal*>(ifun->clone()));
    EXPECT_EQ(domain->integrationOverXi(), orig.integrationOverXi());
    EXPECT_EQ(domain->domainSizes(), orig.domainSizes());
    EXPECT_EQ(domain->dampingLength(), orig.dampingLength());
    EXPECT_EQ(domain->lattice().length1(), orig.lattice().length1());
    EXPECT_EQ(domain->lattice().length2(), orig.lattice().length2());
    EXPECT_EQ(domain->lattice().latticeAngle(), orig.lattice().latticeAngle());
    EXPECT_EQ(domain->lattice().rotationAngle(), orig.lattice().rotationAngle());
}

TEST_F(TestParaCrystalItems, test_Inference2DRotationAngleToggle)
{
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem("MultiLayer");
    SessionItem* layer = model.insertNewItem("Layer", multilayer->index());
    SessionItem* layout = model.insertNewItem("ParticleLayout", layer->index());

    SessionItem* interference = model.insertNewItem("Interference2DParaCrystal", layout->index(),
                                                    -1, ParticleLayoutItem::T_INTERFERENCE);

    // rotation (xi) should be disabled if integration is on
    interference->setItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION, true);

    SessionItem* angleItem =
        interference->getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)
            ->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE);

    EXPECT_FALSE(angleItem->isEnabled());

    // rotation (xi) should be enabled if integration is off
    interference->setItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION, false);

    angleItem = interference->getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)
                    ->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE);

    EXPECT_TRUE(angleItem->isEnabled());
}
