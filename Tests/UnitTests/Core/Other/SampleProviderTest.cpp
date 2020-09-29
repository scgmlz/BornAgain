#include "Core/SampleBuilderEngine/SampleProvider.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/SampleBuilderEngine/ISampleBuilder.h"
#include "Tests/GTestWrapper/google_test.h"
#include <memory>

class SampleProviderTest : public ::testing::Test
{
public:
    //! Returns test multilayer.
    static std::unique_ptr<MultiLayer> testMultiLayer(double length)
    {
        std::unique_ptr<MultiLayer> result(new MultiLayer);
        result->setCrossCorrLength(length); // used to check following cloning
        return result;
    }

    //! Test class playing the role of SampleContainer's parent
    class TestSimulation : public INode
    {
    public:
        TestSimulation()
        {
            setName("TestSimulation");
            registerChild(&m_provider);
        }

        TestSimulation(const TestSimulation& other) : INode(), m_provider(other.m_provider)
        {
            setName("TestSimulation");
            registerChild(&m_provider);
        }

        void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

        std::vector<const INode*> getChildren() const { return m_provider.getChildren(); }

        void setContainer(const SampleProvider& provider) { m_provider = provider; }
        SampleProvider m_provider;
    };

    //! Test sample builder
    class TestBuilder : public ISampleBuilder
    {
    public:
        explicit TestBuilder(double length = 42.0) : m_length(length)
        {
            setName("TestBuilder");
            registerParameter("length", &m_length);
        }

        MultiLayer* buildSample() const { return testMultiLayer(m_length).release(); }
        double m_length;
    };
};

//! Test initial state,  assignment operator.

TEST_F(SampleProviderTest, initialState)
{
    SampleProvider provider;
    EXPECT_EQ(provider.sample(), nullptr);
    EXPECT_EQ(provider.getChildren().size(), 0u);

    // setting the sample
    provider.setSample(*SampleProviderTest::testMultiLayer(42.0));
    EXPECT_EQ(provider.sample()->crossCorrLength(), 42.0);
    EXPECT_EQ(provider.sample()->parent(), nullptr);

    // checking assignment operator
    SampleProvider provider2;
    provider2 = provider;
    EXPECT_EQ(provider2.sample()->crossCorrLength(), 42.0);
    EXPECT_EQ(provider2.sample()->parent(), nullptr);
}

//! Testing sample builder assignment.

TEST_F(SampleProviderTest, sampleBuilder)
{
    // Setting sample first
    SampleProvider provider;
    provider.setSample(*SampleProviderTest::testMultiLayer(42.0));

    // Setting sample builder, original sample should gone.
    std::shared_ptr<ISampleBuilder> builder(new SampleProviderTest::TestBuilder(33.0));
    EXPECT_EQ(builder.use_count(), 1);
    provider.setSampleBuilder(builder);
    EXPECT_EQ(builder.use_count(), 2);
    EXPECT_EQ(provider.sample(), nullptr);

    // Updating sample and checking if it is generated by sample builder
    provider.updateSample();
    EXPECT_EQ(provider.sample()->crossCorrLength(), 33.0);

    // Copying container, sample_builder should be copied, but not the sample
    SampleProvider provider2;
    provider2 = provider;
    EXPECT_EQ(provider2.sample(), nullptr);
    EXPECT_EQ(builder.use_count(), 3);

    // updating sample in second container
    provider2.updateSample();
    EXPECT_EQ(provider2.sample()->crossCorrLength(), 33.0);

    // setting new sample, builder should go
    provider2.setSample(*SampleProviderTest::testMultiLayer(42.0));
    EXPECT_EQ(builder.use_count(), 2);
    EXPECT_EQ(provider2.sample()->crossCorrLength(), 42.0);
}

//! Test parentship of container and sample in simulation context.

TEST_F(SampleProviderTest, sampleInSimulationContext)
{
    SampleProviderTest::TestSimulation sim;
    SampleProvider& provider = sim.m_provider;
    provider.setSample(*SampleProviderTest::testMultiLayer(42.0));

    // parent of container and parent of sample should be the same
    EXPECT_EQ(provider.parent(), &sim);
    EXPECT_EQ(provider.sample()->parent(), &sim);

    // children of container
    ASSERT_EQ(provider.getChildren().size(), 1u);
    EXPECT_EQ(provider.getChildren()[0], provider.sample());

    EXPECT_FALSE(sim.treeToString().empty());
    EXPECT_FALSE(sim.parametersToString().empty());

    // creating second simulation via copy-construction
    SampleProviderTest::TestSimulation sim2(sim);
    SampleProvider& provider2 = sim2.m_provider;

    // check that parent has changed for new container and its sample
    EXPECT_EQ(provider2.parent(), &sim2);
    EXPECT_EQ(provider2.sample()->parent(), &sim2);
    EXPECT_EQ(provider2.sample()->crossCorrLength(), 42.0);

    // checking parameter pool
    std::unique_ptr<ParameterPool> pool(sim2.createParameterTree());
    ASSERT_EQ(pool->size(), 4u);
    EXPECT_TRUE(pool->parameter("/TestSimulation/MultiLayer/CrossCorrelationLength") != nullptr);
}

//! Test parentship of container and builder in simulation context.

TEST_F(SampleProviderTest, builderInSimulationContext)
{
    SampleProviderTest::TestSimulation sim;
    SampleProvider& provider = sim.m_provider;

    std::shared_ptr<ISampleBuilder> builder(new SampleProviderTest::TestBuilder(33.0));
    provider.setSampleBuilder(builder);
    provider.updateSample();

    // provider's sample should not have neither parent nor children
    EXPECT_EQ(provider.sample()->parent(), nullptr);
    ASSERT_EQ(provider.getChildren().size(), 1u);

    EXPECT_FALSE(sim.treeToString().empty());
    EXPECT_FALSE(sim.parametersToString().empty());

    // creating second simulation via  copy-construction
    SampleProviderTest::TestSimulation sim2(sim);

    // checking parameter pool
    std::unique_ptr<ParameterPool> pool(sim2.createParameterTree());
    ASSERT_EQ(pool->size(), 1u);
    EXPECT_EQ(pool->parameter("/TestSimulation/TestBuilder/length")->value(), 33.0);
}
