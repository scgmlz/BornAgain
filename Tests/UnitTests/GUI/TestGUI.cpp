#include <QtTest>
#include <QString>
#include <QCoreApplication>
#include "TestMapperCases.h"
#include "TestFormFactorItems.h"
#include "TestFTDistributionItems.h"
#include "TestParameterizedItem.h"
#include "TestParticleItem.h"
#include "TestLayerRoughnessItems.h"
#include "TestParaCrystalItems.h"
#include "TestSessionModel.h"
#include "TestSessionItem.h"
#include "TestGUICoreObjectCorrespondence.h"
#include "TestMapperForItem.h"
#include "TestParticleDistributionItem.h"
#include "TestGUIHelpers.h"
#include "TestFitParameterModel.h"
#include "TestMaterialModel.h"
#include "TestComboProperty.h"
#include "TestTranslations.h"
#include "TestGroupProperty.h"
#include "TestParameterTreeUtils.h"
#include "TestDetectorItems.h"
#include "TestLinkInstrument.h"
#include "TestUpdateTimer.h"
#include "TestProjectDocument.h"
#include "TestSaveService.h"
#include "TestOutputDataIOService.h"
#include "TestIntensityDataItem.h"
#include "TestProjectUtils.h"
#include "TestParticleCoreShell.h"
#include "TestPropertyRepeater.h"
#include "TestSessionItemController.h"
#include "TestModelUtils.h"
#include "TestComponentProxyModel.h"
#include "TestProxyModelStrategy.h"
#include "TestSessionItemUtils.h"
#include <memory>

class GUITestFactory {
public:
    using create_t = std::function<QObject*()>;

    template<typename T> void add() {
        creators.push_back([](){return new T();});
    }

    int runAll(int argc, char** argv)
    {
        int result(0);
        for(auto f : creators) {
            std::unique_ptr<QObject> obj(f());
            result +=  QTest::qExec(obj.get(), argc, argv);
        }
        return result;
    }

private:
    std::vector<create_t> creators;
};

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    QMetaType::registerComparators<ComboProperty>();

    GUITestFactory tests;

//    tests.add<TestFormFactorItems>();
//    tests.add<TestFTDistributionItems>();
//    tests.add<TestParameterizedItem>();
//    tests.add<TestParticleItem>();
//    tests.add<TestLayerRoughnessItems>();
//    tests.add<TestParaCrystalItems>();
//    tests.add<TestSessionModel>();
//    tests.add<TestGUICoreObjectCorrespondence>();
//    tests.add<TestSessionItem>();
//    tests.add<TestMapperCases>();
//    tests.add<TestMapperForItem>();
//    tests.add<TestGUIHelpers>();
//    tests.add<TestFitParameterModel>();
//    tests.add<TestMaterialModel>();
//    tests.add<TestComboProperty>();
//    tests.add<TestTranslations>();
//    tests.add<TestGroupProperty>();
//    tests.add<TestParticleDistributionItem>();
//    tests.add<TestParameterTreeUtils>();
//    tests.add<TestDetectorItems>();
//    tests.add<TestLinkInstrument>();
//    tests.add<TestUpdateTimer>();
//    tests.add<TestProjectDocument>();
//    tests.add<TestSaveService>();
//    tests.add<TestOutputDataIOService>();
//    tests.add<TestIntensityDataItem>();
//    tests.add<TestProjectUtils>();
//    tests.add<TestParticleCoreShell>();
//    tests.add<TestPropertyRepeater>();
//    tests.add<TestSessionItemController>();
    tests.add<TestModelUtils>();
    tests.add<TestComponentProxyModel>();
    tests.add<TestProxyModelStrategy>();
    tests.add<TestSessionItemUtils>();

    return tests.runAll(argc, argv);
}
