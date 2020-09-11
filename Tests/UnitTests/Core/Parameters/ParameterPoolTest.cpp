#include "Core/Parametrization/ParameterPool.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Parametrization/RealParameter.h"
#include "Tests/GTestWrapper/google_test.h"

class ParameterPoolTest : public ::testing::Test
{
};

TEST_F(ParameterPoolTest, initialState)
{
    ParameterPool pool;
    EXPECT_EQ(pool.size(), 0u);
    EXPECT_EQ(pool.parameterNames().size(), 0u);
}

TEST_F(ParameterPoolTest, addParameter)
{
    double par1(1.0), par2(2.0);
    ParameterPool pool;
    RealParameter* rp1 = new RealParameter("rp1", &par1);
    RealParameter* rp2 = new RealParameter("rp2", &par2);

    EXPECT_EQ(&pool.addParameter(rp1), rp1);
    EXPECT_EQ(&pool.addParameter(rp2), rp2);
    EXPECT_EQ(pool.size(), 2u);

    // attempt to add same parameter twice
    EXPECT_THROW(pool.addParameter(rp1), Exceptions::RuntimeErrorException);

    // getting parameters
    EXPECT_EQ(pool.parameter("rp1"), rp1);
    EXPECT_EQ(pool.parameter("rp2"), rp2);

    // getting non-existing parameters
    EXPECT_EQ(pool.parameter("rp3"), nullptr);

    // vector of parameter names
    std::vector<std::string> names{"rp1", "rp2"};
    EXPECT_EQ(pool.parameterNames(), names);

    // cleaning the pool
    pool.clear();
    EXPECT_EQ(pool.size(), 0u);
}

TEST_F(ParameterPoolTest, matchedParameters)
{
    double par1(1.0), par2(2.0), par3(3.0);
    ParameterPool pool;
    RealParameter* rp1 = new RealParameter("par1", &par1);
    RealParameter* rp2 = new RealParameter("xxx", &par2);
    RealParameter* rp3 = new RealParameter("par3", &par3);

    pool.addParameter(rp1);
    pool.addParameter(rp2);
    pool.addParameter(rp3);

    auto matched = pool.getMatchedParameters("*par*");
    EXPECT_EQ(matched.size(), 2u);
    EXPECT_EQ(matched.at(0), rp1);
    EXPECT_EQ(matched.at(1), rp3);

    // unique match
    EXPECT_EQ(rp2, pool.getUniqueMatch("*xxx*"));
    EXPECT_THROW(pool.getUniqueMatch("*par*"), Exceptions::RuntimeErrorException);
}

TEST_F(ParameterPoolTest, setValue)
{
    double par1(1.0), par2(2.0), par3(3.0);
    ParameterPool pool;

    pool.addParameter(new RealParameter("par1", &par1));
    pool.addParameter(new RealParameter("xxx", &par2));
    pool.addParameter(new RealParameter("par3", &par3));

    // set single parameter value
    pool.setParameterValue("par1", 10.0);
    EXPECT_EQ(par1, 10.0);
    EXPECT_THROW(pool.setParameterValue("non-existing", 10.0), Exceptions::RuntimeErrorException);

    // set matched parameter values
    EXPECT_EQ(pool.setMatchedParametersValue("*par*", 99.0), 2);
    EXPECT_EQ(par1, 99.0);
    EXPECT_EQ(par3, 99.0);
    EXPECT_THROW(pool.setMatchedParametersValue("*non-existing*", 10.0),
                 Exceptions::RuntimeErrorException);

    // set unique match value
    pool.setUniqueMatchValue("*xxx*", 88.0);
    EXPECT_EQ(par2, 88.0);
    EXPECT_THROW(pool.setUniqueMatchValue("*non-existing*", 10.0),
                 Exceptions::RuntimeErrorException);
}

TEST_F(ParameterPoolTest, clone)
{
    double par1(1.0), par2(2.0), par3(3.0);
    ParameterPool* pool = new ParameterPool;
    pool->addParameter(new RealParameter("par1", &par1));
    pool->addParameter(new RealParameter("xxx", &par2));
    pool->addParameter(new RealParameter("par3", &par3));

    std::unique_ptr<ParameterPool> clone(pool->clone());

    // deleting original, and checking that clone points to the same parameters
    delete pool;

    EXPECT_EQ(clone->size(), 3u);
    EXPECT_EQ(double(1.0), clone->parameter("par1")->value());
    EXPECT_EQ(double(2.0), clone->parameter("xxx")->value());
    EXPECT_EQ(double(3.0), clone->parameter("par3")->value());
}

TEST_F(ParameterPoolTest, copyToExternalPool)
{
    double par1(1.0), par2(2.0);
    ParameterPool* pool = new ParameterPool;
    pool->addParameter(new RealParameter("par1", &par1));
    pool->addParameter(new RealParameter("par2", &par2));

    double par3(3.0);
    ParameterPool externalPool;
    externalPool.addParameter(new RealParameter("par3", &par3));

    pool->copyToExternalPool("prefix/", &externalPool);
    delete pool;

    EXPECT_EQ(externalPool.size(), 3u);
    EXPECT_EQ(double(1.0), externalPool.parameter("prefix/par1")->value());
    EXPECT_EQ(double(2.0), externalPool.parameter("prefix/par2")->value());
    EXPECT_EQ(double(3.0), externalPool.parameter("par3")->value());

    std::vector<std::string> names{"par3", "prefix/par1", "prefix/par2"};
    EXPECT_EQ(externalPool.parameterNames(), names);
}

TEST_F(ParameterPoolTest, removeParameter)
{
    double par1(1.0), par2(2.0);
    ParameterPool pool;
    pool.addParameter(new RealParameter("par1", &par1));
    pool.addParameter(new RealParameter("par2", &par2));
    EXPECT_EQ(pool.size(), 2u);

    EXPECT_FALSE(pool.parameter("par1") == nullptr);
    pool.removeParameter("par1");
    EXPECT_EQ(pool.size(), 1u);
    EXPECT_TRUE(pool.parameter("par1") == nullptr);
}
