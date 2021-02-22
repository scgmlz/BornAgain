#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QSignalSpy>

Q_DECLARE_METATYPE(const InstrumentItem*)

class TestInstrumentModel : public ::testing::Test {
};

//! Checks that LinkInstrumentManager listens instrument model.

TEST_F(TestInstrumentModel, test_instrumentAddedRemoved)
{
    InstrumentModel instrumentModel;

    QSignalSpy spy(&instrumentModel, SIGNAL(instrumentAddedOrRemoved()));

    // populating instrument model
    auto instrument = instrumentModel.insertItem<GISASInstrumentItem>();

    // checking that a signal was emitted about the new instrument
    EXPECT_EQ(spy.count(), 1);

    // removing instrument
    instrumentModel.removeRow(0);
    EXPECT_EQ(spy.count(), 2);
}

//! Test whether instrumentNameChanged will be emitted as expected
TEST_F(TestInstrumentModel, test_instrumentNameChanged)
{
    qRegisterMetaType<const InstrumentItem*>();
    InstrumentModel instrumentModel;

    // populating instrument model
    auto instrument1 = instrumentModel.insertItem<GISASInstrumentItem>();
    auto instrument2 = instrumentModel.insertItem<SpecularInstrumentItem>();

    QSignalSpy spy(&instrumentModel, SIGNAL(instrumentNameChanged(const InstrumentItem*)));
    ASSERT_TRUE(spy.isValid());

    // change name of instrument 1
    instrument1->setName("A");
    ASSERT_EQ(spy.count(), 1);
    const InstrumentItem* instr = qvariant_cast<const InstrumentItem*>(spy.at(0).at(0));
    EXPECT_EQ(instr, instrument1);

    // no signal when changing other properties, e.g. id
    instrument1->setId("xxxxx");
    EXPECT_EQ(spy.count(), 1);

    // change name of instrument 2
    instrument2->setName("B");
    ASSERT_EQ(spy.count(), 2);
    instr = qvariant_cast<const InstrumentItem*>(spy.at(1).at(0));
    EXPECT_EQ(instr, instrument2);

    // Add another instrument
    auto instrument3 = instrumentModel.insertItem<OffSpecularInstrumentItem>();

    // Change instrument2
    instrument2->setName("BB");
    ASSERT_EQ(spy.count(), 3);
    instr = qvariant_cast<const InstrumentItem*>(spy.at(2).at(0));
    EXPECT_EQ(instr, instrument2);

    // Change instrument3
    instrument3->setName("C");
    ASSERT_EQ(spy.count(), 4);
    instr = qvariant_cast<const InstrumentItem*>(spy.at(3).at(0));
    EXPECT_EQ(instr, instrument3);
}
