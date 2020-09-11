#include "GUI/coregui/Models/BeamDistributionItem.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/DistributionItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/RotationItems.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/TransformationItem.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "Tests/GTestWrapper/google_test.h"

class TestTranslations : public ::testing::Test
{
};

TEST_F(TestTranslations, test_TranslatePosition)
{
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem("MultiLayer");
    SessionItem* layer = model.insertNewItem("Layer", multilayer->index());
    SessionItem* layout = model.insertNewItem("ParticleLayout", layer->index());
    SessionItem* particle = model.insertNewItem("Particle", layout->index());

    SessionItem* positionItem = particle->getItem(ParticleItem::P_POSITION);
    SessionItem* xItem = positionItem->getItem(VectorItem::P_X);

    EXPECT_EQ(ModelPath::itemPathTranslation(*xItem, multilayer->parent()),
              "MultiLayer/Layer/ParticleLayout/Particle/PositionX");
}

TEST_F(TestTranslations, test_TranslateRotation)
{
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem("MultiLayer");
    SessionItem* layer = model.insertNewItem("Layer", multilayer->index());
    SessionItem* layout = model.insertNewItem("ParticleLayout", layer->index());
    SessionItem* particle = model.insertNewItem("Particle", layout->index());

    SessionItem* transformation =
        model.insertNewItem("Rotation", particle->index(), -1, ParticleItem::T_TRANSFORMATION);

    SessionItem* rotationItem =
        transformation->setGroupProperty(TransformationItem::P_ROT, "XRotation");

    SessionItem* angleItem = rotationItem->getItem(XRotationItem::P_ANGLE);
    EXPECT_EQ(ModelPath::itemPathTranslation(*angleItem, multilayer->parent()),
              "MultiLayer/Layer/ParticleLayout/Particle/XRotation/Angle");
}

TEST_F(TestTranslations, test_BeamDistributionNone)
{
    SampleModel model;
    SessionItem* instrument = model.insertNewItem("GISASInstrument");
    SessionItem* beam = instrument->getItem(Instrument2DItem::P_BEAM);

    SessionItem* wavelength = beam->getItem(BeamItem::P_WAVELENGTH);

    SessionItem* distr = wavelength->getGroupItem(BeamDistributionItem::P_DISTRIBUTION);
    EXPECT_EQ(distr->modelType(), "DistributionNone");
    SessionItem* value = distr->getItem(DistributionNoneItem::P_MEAN);

    EXPECT_EQ(ModelPath::itemPathTranslation(*value, instrument->parent()),
              "Instrument/Beam/Wavelength");

    SessionItem* inclinationAngle = beam->getItem(BeamItem::P_INCLINATION_ANGLE);
    distr = inclinationAngle->getGroupItem(BeamDistributionItem::P_DISTRIBUTION);
    value = distr->getItem(DistributionNoneItem::P_MEAN);

    EXPECT_EQ(ModelPath::itemPathTranslation(*value, instrument->parent()),
              "Instrument/Beam/InclinationAngle");
}
