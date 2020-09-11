#include "Core/Lattice/Lattice2D.h"
#include "Tests/GTestWrapper/google_test.h"

class Lattice2DTest : public ::testing::Test
{
};

TEST_F(Lattice2DTest, basicLattice)
{
    const double length1(1.0), length2(2.0), angle(3.0), rotangle(0.7);
    BasicLattice lattice(length1, length2, angle, rotangle);
    EXPECT_EQ(lattice.length1(), length1);
    EXPECT_EQ(lattice.length2(), length2);
    EXPECT_EQ(lattice.latticeAngle(), angle);
    EXPECT_EQ(lattice.rotationAngle(), rotangle);

    const double new_value(42.0);

    lattice.setParameterValue("LatticeLength1", new_value);
    EXPECT_EQ(lattice.length1(), new_value);
    lattice.setParameterValue("LatticeLength2", new_value);
    EXPECT_EQ(lattice.length2(), new_value);
    lattice.setParameterValue("Alpha", new_value);
    EXPECT_EQ(lattice.latticeAngle(), new_value);
    lattice.setParameterValue("Xi", new_value);
    EXPECT_EQ(lattice.rotationAngle(), new_value);
}

TEST_F(Lattice2DTest, basicLatticeClone)
{
    const double length1(1.0), length2(2.0), angle(3.0), xi(4.0);
    BasicLattice lattice(length1, length2, angle, xi);

    std::unique_ptr<Lattice2D> clone(lattice.clone());
    EXPECT_EQ(clone->length1(), length1);
    EXPECT_EQ(clone->length2(), length2);
    EXPECT_EQ(clone->latticeAngle(), angle);
    EXPECT_EQ(clone->rotationAngle(), xi);
}

TEST_F(Lattice2DTest, squareLatticeClone)
{
    const double length(1.0), xi(4.0);
    SquareLattice lattice(length, xi);

    std::unique_ptr<Lattice2D> clone(lattice.clone());
    EXPECT_EQ(clone->length1(), length);
    EXPECT_EQ(clone->length2(), length);
    EXPECT_DOUBLE_EQ(clone->latticeAngle(), M_PI / 2.0);
    EXPECT_EQ(clone->rotationAngle(), xi);

    // registered parameters of clone
    const double new_value(42.0);
    clone->setParameterValue("LatticeLength", new_value);
    EXPECT_EQ(clone->length1(), new_value);
    EXPECT_EQ(clone->length2(), new_value);
    clone->setParameterValue("Xi", new_value);
    EXPECT_EQ(clone->rotationAngle(), new_value);
}

TEST_F(Lattice2DTest, hexagonalLatticeClone)
{
    const double length(1.0), xi(4.0);
    HexagonalLattice lattice(length, xi);

    std::unique_ptr<Lattice2D> clone(lattice.clone());
    EXPECT_EQ(clone->length1(), length);
    EXPECT_EQ(clone->length2(), length);
    EXPECT_DOUBLE_EQ(clone->latticeAngle(), 2. * M_PI / 3.0);
    EXPECT_EQ(clone->rotationAngle(), xi);

    // registered parameters of clone
    const double new_value(42.0);
    clone->setParameterValue("LatticeLength", new_value);
    EXPECT_EQ(clone->length1(), new_value);
    EXPECT_EQ(clone->length2(), new_value);
    clone->setParameterValue("Xi", new_value);
    EXPECT_EQ(clone->rotationAngle(), new_value);
}

TEST_F(Lattice2DTest, onChange)
{
    class Parent : public INode
    {
    public:
        Parent() : m_changed(false) {}
        void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
        virtual void onChange() { m_changed = true; }
        bool m_changed;
    };

    Parent parent;
    const double length1(1.0), length2(2.0), angle(3.0), xi(4.0);
    BasicLattice lattice(length1, length2, angle, xi);

    parent.registerChild(&lattice);
    EXPECT_FALSE(parent.m_changed);
    lattice.setParameterValue("LatticeLength1", 42.0);
    EXPECT_TRUE(parent.m_changed);
}
