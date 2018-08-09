#include "InterferenceFunctionItems.h"
#include "ParticleLayoutItem.h"
#include "SampleModel.h"
#include "SessionItemUtils.h"
#include "Lattice2DItems.h"
#include "MathConstants.h"
#include "google_test.h"

class TestParticleLayoutItem : public ::testing::Test
{
public:
    ~TestParticleLayoutItem();
};

TestParticleLayoutItem::~TestParticleLayoutItem() = default;

using namespace SessionItemUtils;

//! Checks enabled/disabled status of TotalSurfaceDensity when adding interference function items.

TEST_F(TestParticleLayoutItem, densityAppearance)
{
    SampleModel model;
    auto layout
        = dynamic_cast<ParticleLayoutItem*>(model.insertNewItem(Constants::ParticleLayoutType));

    // empty layout should have TotalDensity enabled
    EXPECT_TRUE(layout->getItem(ParticleLayoutItem::P_TOTAL_DENSITY)->isEnabled());

    // adding radial paracrystal shouldn't change it
    auto interference
        = model.insertNewItem(Constants::InterferenceFunctionRadialParaCrystalType,
                              model.indexOfItem(layout), -1, ParticleLayoutItem::T_INTERFERENCE);
    EXPECT_TRUE(layout->getItem(ParticleLayoutItem::T_INTERFERENCE) == interference);
    EXPECT_TRUE(layout->getItem(ParticleLayoutItem::P_TOTAL_DENSITY)->isEnabled());

    // removing paracrystal, TotalDensity still enabled
    layout->takeRow(ParentRow(*interference));
    EXPECT_TRUE(layout->getItem(ParticleLayoutItem::T_INTERFERENCE) == nullptr);
    EXPECT_TRUE(layout->getItem(ParticleLayoutItem::P_TOTAL_DENSITY)->isEnabled());
    delete interference;

    // adding 2d interference, TotalDensity should be disabled
    interference
        = model.insertNewItem(Constants::InterferenceFunction2DLatticeType,
                              model.indexOfItem(layout), -1, ParticleLayoutItem::T_INTERFERENCE);
    EXPECT_FALSE(layout->getItem(ParticleLayoutItem::P_TOTAL_DENSITY)->isEnabled());

    // removing 2D interference, TotalIntensity should be reenabled
    layout->takeRow(ParentRow(*interference));
    delete interference;
    EXPECT_TRUE(layout->getItem(ParticleLayoutItem::T_INTERFERENCE) == nullptr);
    EXPECT_TRUE(layout->getItem(ParticleLayoutItem::P_TOTAL_DENSITY)->isEnabled());
}

//! Checks the value of TotalSurfaceDensity in ParticleLayout
//! a) on interference function attachment
//! b) on lattice parameter adjustments

TEST_F(TestParticleLayoutItem, densityValue)
{
    SampleModel model;
    auto layout
        = dynamic_cast<ParticleLayoutItem*>(model.insertNewItem(Constants::ParticleLayoutType));

    // empty layout should have TotalDensity 0.01
    EXPECT_EQ(layout->getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).toDouble(), 0.01);

    // adding 2d interference with default hexagonal lattice
    auto interference
        = model.insertNewItem(Constants::InterferenceFunction2DLatticeType,
                              model.indexOfItem(layout), -1, ParticleLayoutItem::T_INTERFERENCE);

    auto& hexItem = interference->groupItem<Lattice2DItem>(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
    EXPECT_EQ(hexItem.modelType(), Constants::HexagonalLatticeType);
    double length = hexItem.getItemValue(HexagonalLatticeItem::P_LATTICE_LENGTH).toDouble();
    double expectedDensity = 1./(length*length*std::sin(M_TWOPI/3.0));
    EXPECT_DOUBLE_EQ(1.0/hexItem.unitCellArea(), expectedDensity);
    EXPECT_DOUBLE_EQ(layout->getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).toDouble(), expectedDensity);

    // changing hexagonal lattice length
    length = 100.0;
    hexItem.setItemValue(HexagonalLatticeItem::P_LATTICE_LENGTH, length);
    expectedDensity = 1./(length*length*std::sin(M_TWOPI/3.0));
    EXPECT_DOUBLE_EQ(layout->getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).toDouble(), expectedDensity);

    // changing lattice type to square and checking new surface density
    interference->setGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE, Constants::SquareLatticeType);
    auto& squareItem = interference->groupItem<Lattice2DItem>(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
    EXPECT_EQ(squareItem.modelType(), Constants::SquareLatticeType);
    length = squareItem.getItemValue(SquareLatticeItem::P_LATTICE_LENGTH).toDouble();
    expectedDensity = 1./(length*length);
    EXPECT_DOUBLE_EQ(1.0/squareItem.unitCellArea(), expectedDensity);
    EXPECT_DOUBLE_EQ(layout->getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).toDouble(), expectedDensity);

    // changing square lattice length
    length = 200.0;
    squareItem.setItemValue(SquareLatticeItem::P_LATTICE_LENGTH, length);
    expectedDensity = 1./(length*length);
    EXPECT_DOUBLE_EQ(layout->getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).toDouble(), expectedDensity);

    // removing interference function, density should remain the same
    // (we could return density of ParticleLayout to initial value 1,
    // but probably it's not necessary)
    layout->takeRow(ParentRow(*interference));
    delete interference;
    EXPECT_DOUBLE_EQ(layout->getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).toDouble(), expectedDensity);
}
