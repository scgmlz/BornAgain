#include "Param/Base/IParametricComponent.h"
#include "Tests/GTestWrapper/google_test.h"
#include <stdexcept>

class IParametricComponentTest : public ::testing::Test {
protected:
    IParametricComponent m_initial_object;

    class ParameterizedObject : public IParametricComponent {
    public:
        ParameterizedObject() : m_real_par1(0), m_real_par2(0) {
            setName("Parameterized");
            registerParameter("par1", &m_real_par1);
            registerParameter("par2", &m_real_par2);
        }
        double m_real_par1;
        double m_real_par2;
    };
    ParameterizedObject m_parameterized;
};

// TODO enable tests

TEST_F(IParametricComponentTest, InitialState) {
    /* TEMPORARILY DISABLED getParameterPool()
    EXPECT_EQ( size_t(0), m_initial_object.getParameterPool()->size() );
    IParametricComponent obj2(m_initial_object);
    EXPECT_EQ( size_t(0), obj2.getParameterPool()->size() );
    */
}

TEST_F(IParametricComponentTest, DealingWithPool) {
    /* TEMPORARILY DISABLED getParameterPool()
    EXPECT_EQ( size_t(2), m_parameterized.getParameterPool()->size());
    IParametricComponentTest::ParameterizedObject obj2 = m_parameterized;
    EXPECT_EQ( size_t(0), obj2.getParameterPool()->size());
    ParameterPool *pool = m_parameterized.createParameterTree();
    //POOL_2('/Parameterized/par1':0 '/Parameterized/par2':0 )
    //std::cout << *pool << std::endl;
    pool->getParameter("/Parameterized/par1").setValue(1.0);
    pool->getParameter("/Parameterized/par2").setValue(2.0);
    EXPECT_EQ( double(1.0), m_parameterized.m_real_par1);
    EXPECT_EQ( double(2.0), m_parameterized.m_real_par2);
    */
}

TEST_F(IParametricComponentTest, SetParameterValue) {
    //    m_parameterized.m_real_par1 = 1.0;
    //    m_parameterized.m_real_par2 = 2.0;
    //    m_parameterized.setParameterValue("par1", 3.0);
    //    m_parameterized.setParameterValue("par2", 4.0);
    //    EXPECT_EQ( double(3.0), m_parameterized.m_real_par1);
    //    EXPECT_EQ( double(4.0), m_parameterized.m_real_par2);
    //    ASSERT_THROW( m_parameterized.setParameterValue("NotExistingParameterName", 4.0),
    //                  std::runtime_error );
    //    m_parameterized.setParameterValue("*par*", 5.0);
    //    EXPECT_EQ( double(5.0), m_parameterized.m_real_par1);
    //    EXPECT_EQ( double(5.0), m_parameterized.m_real_par2);
    //    m_parameterized.setParameterValue("/Parameterized/par1", 7.0);
    //    EXPECT_EQ( double(7.0), m_parameterized.m_real_par1);
    //    EXPECT_EQ( double(5.0), m_parameterized.m_real_par2);
    /* TEMPORARILY DISABLED getParameterPool()
    m_parameterized.clearParameterPool();
    EXPECT_EQ( 0.0, m_parameterized.getParameterPool()->size());
    */
}
