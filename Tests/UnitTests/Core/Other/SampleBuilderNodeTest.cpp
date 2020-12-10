#include "Sample/SampleBuilderEngine/SampleBuilderNode.h"
#include "Param/Base/ParameterPool.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/SampleBuilderEngine/ISampleBuilder.h"
#include "Tests/GTestWrapper/google_test.h"
#include <iostream>
#include <memory>
#include <stdexcept>

#define EXPECT_ASSERT_TRIGGERED(condition) EXPECT_THROW((condition), std::runtime_error)

class SampleBuilderNodeTest : public ::testing::Test {
public:
    //! Returns test multilayer.
    static std::unique_ptr<MultiLayer> testMultiLayer(double length) {
        std::unique_ptr<MultiLayer> result(new MultiLayer);
        result->setCrossCorrLength(length); // used to check following cloning
        return result;
    }

    //! Test sample builder
    class TestBuilder : public ISampleBuilder {
    public:
        explicit TestBuilder(double length = 42.0) : m_length(length) {
            setName("TestBuilder");
            registerParameter("length", &m_length);
        }

        MultiLayer* buildSample() const { return testMultiLayer(m_length).release(); }
        double m_length;
    };
};

//! Checks children and pool parameters.

TEST_F(SampleBuilderNodeTest, builderParameters) {
    SampleBuilderNode builderNode;

    // initial state
    EXPECT_EQ(builderNode.parent(), nullptr);
    EXPECT_EQ(builderNode.getChildren().size(), 0u);
    EXPECT_EQ(builderNode.parameterPool()->size(), 0u);
    EXPECT_EQ(bool(builderNode), false);

    // setting builder
    std::shared_ptr<ISampleBuilder> builder(new SampleBuilderNodeTest::TestBuilder(33.0));
    builderNode.setSBN(builder);
    EXPECT_EQ(bool(builderNode), true);

    // checks that still no children
    EXPECT_EQ(builderNode.parent(), nullptr);
    EXPECT_EQ(builderNode.getChildren().size(), 0u);

    // checks that  node has same parameters/name as sample builder
    EXPECT_EQ(builder.use_count(), 2);
    ASSERT_EQ(builderNode.parameterPool()->parameterNames().size(), 1u);
    EXPECT_EQ(builderNode.parameterPool()->parameterNames()[0], "length");

    // checks sample creation
    EXPECT_EQ(builderNode.createMultiLayer()->crossCorrLength(), 33.0);

    // reset node to initial state
    builderNode.reset();
    EXPECT_EQ(builder.use_count(), 1);
    EXPECT_EQ(builderNode.parameterPool()->size(), 0u);
    EXPECT_ASSERT_TRIGGERED(builderNode.createMultiLayer());
}

//! Checks assignment operator.

TEST_F(SampleBuilderNodeTest, assignmentOperator) {
    SampleBuilderNode builderNode;
    std::shared_ptr<ISampleBuilder> builder(new SampleBuilderNodeTest::TestBuilder(33.0));
    builderNode.setSBN(builder);

    // checking assignment
    SampleBuilderNode node2;
    node2 = builderNode;
    EXPECT_EQ(builder.use_count(), 3);
}
