#include "google_test.h"
#include <QString>
#include <QCoreApplication>
#include <QAbstractItemModel>
#include "Comparators.h"

#include "TestComboProperty.h"
#include "TestComponentProxyModel.h"
#include "TestComponentUtils.h"
#include "TestDataItems.h"
#include "TestDataItemViews.h"
#include "TestDetectorItems.h"
#include "TestExternalProperty.h"
#include "TestFitParameterModel.h"
#include "TestFormFactorItems.h"
#include "TestFTDistributionItems.h"
#include "TestGroupItem.h"
#include "TestGUICoreObjectCorrespondence.h"
#include "TestGUIHelpers.h"
#include "TestLayerItems.h"
#include "TestLayerRoughnessItems.h"
#include "TestLinkInstrument.h"
#include "TestMapperCases.h"
#include "TestMapperForItem.h"
#include "TestMaterialModel.h"
#include "TestMaterialPropertyController.h"
#include "TestModelUtils.h"
#include "TestOutputDataIOService.h"
#include "TestParaCrystalItems.h"
#include "TestParameterTreeUtils.h"
#include "TestParticleCoreShell.h"
#include "TestParticleDistributionItem.h"
#include "TestParticleItem.h"
#include "TestProjectDocument.h"
#include "TestProjectUtils.h"
#include "TestPropertyRepeater.h"
#include "TestProxyModelStrategy.h"
#include "TestRealSpaceBuilderUtils.h"
#include "TestSaveService.h"
#include "TestSessionItemController.h"
#include "TestSessionItem.h"
#include "TestSessionItemUtils.h"
#include "TestSessionModel.h"
#include "TestSessionXML.h"
#include "TestTranslations.h"
#include "TestUpdateTimer.h"
#include "TestSessionItemData.h"
#include "TestSessionItemTags.h"
#include "TestMessageService.h"
#include "TestParticleLayoutItem.h"
#include "TestAxesItems.h"
#include "TestMultiLayerItem.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    Comparators::registerComparators();
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("LayoutChangeHint");

    ::testing::InitGoogleTest(&argc, argv);

    // run all google tests
    return RUN_ALL_TESTS();
}
