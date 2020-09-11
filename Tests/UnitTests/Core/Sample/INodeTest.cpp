#include "Core/Parametrization/INode.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Parametrization/NodeUtils.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include "Tests/GTestWrapper/google_test.h"
#include <memory>

namespace
{
const std::string test_class_name = "TestClass";
const std::string another_test_class_name = "AnotherTestClass";
const double test_par1_value(1.0);
} // namespace

class INodeTest : public ::testing::Test
{
public:
    class TestClass : public INode
    {
    public:
        TestClass(const std::string& name = test_class_name, double value = test_par1_value)
            : m_parameter1(value)
        {
            setName(name);
            registerParameter("par1", &m_parameter1);
        }

        virtual ~TestClass()
        {
            for (auto child : m_nodes)
                delete child;
        }
        void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

        void appendChild(INode* node)
        {
            m_nodes.push_back(node);
            registerChild(node);
        }

        virtual std::vector<const INode*> getChildren() const
        {
            return {m_nodes.begin(), m_nodes.end()};
        }

        std::vector<INode*> m_nodes;
        double m_parameter1;
    };
};

TEST_F(INodeTest, initialState)
{
    INodeTest::TestClass node;
    EXPECT_EQ(node.getChildren().size(), 0u);
    EXPECT_EQ(node.parent(), nullptr);
}

TEST_F(INodeTest, appendChild)
{
    INodeTest::TestClass node;

    INodeTest::TestClass* child0 = new INodeTest::TestClass();

    // inserting single child
    node.appendChild(child0);

    // accessing vector of children
    auto children = node.getChildren();
    EXPECT_EQ(children.size(), 1u);
    EXPECT_TRUE(std::find(children.begin(), children.end(), child0) != children.end());
}

//! Checks change of parentship on insert/detach.

TEST_F(INodeTest, parentship)
{
    INodeTest::TestClass node;
    EXPECT_EQ(node.parent(), nullptr);

    INodeTest::TestClass* child = new INodeTest::TestClass();
    node.appendChild(child);
    EXPECT_EQ(child->parent(), &node);
}

//! Checks the display name.

TEST_F(INodeTest, displayName)
{
    INodeTest::TestClass node;

    // Adding first child and checking its displayName
    INodeTest::TestClass* child0 = new INodeTest::TestClass();
    node.appendChild(child0);
    EXPECT_EQ(child0->displayName(), test_class_name);

    // Adding second child with same name and checking change in displayName
    INodeTest::TestClass* child1 = new INodeTest::TestClass();
    node.appendChild(child1);
    EXPECT_EQ(child0->displayName(), test_class_name + "0");
    EXPECT_EQ(child1->displayName(), test_class_name + "1");

    // Adding second child with another name and checking
    INodeTest::TestClass* child2 = new INodeTest::TestClass(another_test_class_name);
    node.appendChild(child2);
    EXPECT_EQ(child2->displayName(), another_test_class_name);
}

//! Checking the path of the node, which is a path composed of node's displayName and
//! the displayName of parent.

TEST_F(INodeTest, nodePath)
{
    INodeTest::TestClass root("root");
    EXPECT_EQ(NodeUtils::nodePath(root), "/root");

    // adding first child
    INodeTest::TestClass* child0 = new INodeTest::TestClass("child");
    root.appendChild(child0);
    EXPECT_EQ(NodeUtils::nodePath(*child0), "/root/child");

    // adding second child with the same name
    INodeTest::TestClass* child1 = new INodeTest::TestClass("child");
    root.appendChild(child1);
    EXPECT_EQ(NodeUtils::nodePath(*child0), "/root/child0");
    EXPECT_EQ(NodeUtils::nodePath(*child1), "/root/child1");

    // adding grandchild
    INodeTest::TestClass* grandchild = new INodeTest::TestClass("grandchild");
    child0->appendChild(grandchild);
    EXPECT_EQ(NodeUtils::nodePath(*grandchild), "/root/child0/grandchild");

    // Now check path of grandchild wrt it's direct parent
    EXPECT_EQ(NodeUtils::nodePath(*grandchild, child0), "/grandchild");

    // Check if exception is thrown when grandchild doesn't belong to child's branch
    EXPECT_THROW(NodeUtils::nodePath(*grandchild, child1), Exceptions::RuntimeErrorException);
}

//! Checking parameter tree for INode structure.

TEST_F(INodeTest, createParameterTree)
{
    INodeTest::TestClass root("root");

    std::unique_ptr<ParameterPool> pool(root.createParameterTree());
    EXPECT_EQ(pool->size(), 1u);
    EXPECT_EQ(pool->parameter("/root/par1")->value(), test_par1_value);

    // adding first child
    INodeTest::TestClass* child0 = new INodeTest::TestClass("child", 99.0);
    root.appendChild(child0);
    pool.reset(root.createParameterTree());

    EXPECT_EQ(pool->size(), 2u);
    EXPECT_EQ(pool->parameter("/root/par1")->value(), test_par1_value);
    EXPECT_EQ(pool->parameter("/root/child/par1")->value(), 99.0);
}

//! Checking parameter tree for INode structure (for one of children).

TEST_F(INodeTest, createChildParameterTree)
{
    INodeTest::TestClass root("root");
    INodeTest::TestClass* child = new INodeTest::TestClass("child", 1.0);
    root.appendChild(child);

    INodeTest::TestClass* grand = new INodeTest::TestClass("grand", 2.0);
    child->appendChild(grand);

    INodeTest::TestClass* grandgrand = new INodeTest::TestClass("grandgrand", 3.0);
    grand->appendChild(grandgrand);

    std::unique_ptr<ParameterPool> pool(grand->createParameterTree());
    EXPECT_EQ(pool->size(), 2u);
    EXPECT_EQ(pool->parameter("/grand/par1")->value(), 2.0);
    EXPECT_EQ(pool->parameter("/grand/grandgrand/par1")->value(), 3.0);
}
