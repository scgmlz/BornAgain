#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "Tests/GTestWrapper/google_test.h"
#include <memory>

using SessionItemUtils::ParentRow;

//! Test Widget which logs calling activity of ModelMapper
class Widget
{
public:
    Widget()
        : m_onPropertyChangeCount(0), m_onChildPropertyChangeCount(0), m_onParentChangeCount(0),
          m_onChildrenChangeCount(0), m_onSiblingsChangeCount(0), m_onAboutToRemoveChild(0)
    {
    }

    void clear()
    {
        m_onPropertyChangeCount = 0;
        m_onChildPropertyChangeCount = 0;
        m_onParentChangeCount = 0;
        m_onChildrenChangeCount = 0;
        m_onSiblingsChangeCount = 0;
        m_onAboutToRemoveChild = 0;
        m_reported_items.clear();
        m_reported_names.clear();
    }

    void subscribe(ModelMapper* mapper, bool with_subscription = false)
    {
        clear();

        void* caller = (with_subscription ? this : 0);

        mapper->setOnPropertyChange([this](QString name) { onPropertyChange(name); }, caller);

        mapper->setOnChildPropertyChange(
            [this](SessionItem* item, QString name) { onChildPropertyChange(item, name); }, caller);

        mapper->setOnParentChange([this](SessionItem* parent) { onParentChange(parent); }, caller);

        mapper->setOnChildrenChange([this](SessionItem*) { onChildrenChange(); }, caller);

        mapper->setOnSiblingsChange([this]() { onSiblingsChange(); }, caller);

        mapper->setOnAboutToRemoveChild([this](SessionItem* item) { onAboutToRemoveChild(item); },
                                        caller);
    }

    void onPropertyChange(const QString& name)
    {
        m_reported_names.append(name);
        m_onPropertyChangeCount++;
    }

    void onChildPropertyChange(SessionItem* item, const QString& name)
    {
        m_reported_items.append(item);
        m_reported_names.append(name);
        m_onChildPropertyChangeCount++;
    }

    void onParentChange(SessionItem* item)
    {
        m_reported_items.append(item);
        m_onParentChangeCount++;
    }

    void onChildrenChange() { m_onChildrenChangeCount++; }

    void onSiblingsChange() { m_onSiblingsChangeCount++; }

    void unsubscribe(ModelMapper* mapper) { mapper->unsubscribe(this); }

    void onAboutToRemoveChild(SessionItem* item)
    {
        m_reported_items.append(item);
        m_onAboutToRemoveChild++;
    }

    int m_onPropertyChangeCount;
    int m_onChildPropertyChangeCount;
    int m_onParentChangeCount;
    int m_onChildrenChangeCount;
    int m_onSiblingsChangeCount;
    int m_onAboutToRemoveChild;
    QList<SessionItem*> m_reported_items;
    QStringList m_reported_names;
};

class TestMapperForItem : public ::testing::Test
{
public:
    TestMapperForItem() : m_mapped_item(0) {}
    ~TestMapperForItem();

    void setItem(SessionItem* item, Widget* widget = 0, bool with_subscription = false)
    {
        m_mapped_item = item;
        m_mapper.reset(new ModelMapper);
        m_mapper->setItem(item);
        if (widget)
            widget->subscribe(m_mapper.get(), with_subscription);
    }

    SessionItem* m_mapped_item;
    std::unique_ptr<ModelMapper> m_mapper;
};

TestMapperForItem::~TestMapperForItem() = default;

TEST_F(TestMapperForItem, test_initialCondition)
{
    Widget w;
    EXPECT_EQ(w.m_onPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onChildPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onParentChangeCount, 0);
    EXPECT_EQ(w.m_onChildrenChangeCount, 0);
    EXPECT_EQ(w.m_onSiblingsChangeCount, 0);
    EXPECT_TRUE(w.m_reported_items.isEmpty());
    EXPECT_TRUE(w.m_reported_names.isEmpty());
    EXPECT_TRUE(m_mapped_item == nullptr);
    EXPECT_TRUE(!m_mapper);
}

TEST_F(TestMapperForItem, test_onPropertyChange)
{
    Widget w;
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem("MultiLayer");
    SessionItem* layer = model.insertNewItem("Layer", model.indexOfItem(multilayer));

    // Mapper is looking on child; set property of child
    setItem(layer, &w);
    EXPECT_TRUE(m_mapped_item == layer);

    layer->setItemValue(LayerItem::P_THICKNESS, 1.0);
    EXPECT_EQ(w.m_onPropertyChangeCount, 1);
    EXPECT_EQ(w.m_onChildPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onParentChangeCount, 0);
    EXPECT_EQ(w.m_onChildrenChangeCount, 0);
    EXPECT_EQ(w.m_onSiblingsChangeCount, 0);
    EXPECT_TRUE(w.m_reported_items.isEmpty());
    EXPECT_TRUE((w.m_reported_names.size() == 1)
                && (w.m_reported_names[0] == LayerItem::P_THICKNESS));

    // Mapper is looking on child; set property of parent;
    setItem(layer, &w);
    EXPECT_TRUE(m_mapped_item == layer);
    multilayer->setItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH, 1.0);
    EXPECT_EQ(w.m_onPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onChildPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onParentChangeCount, 0);
    EXPECT_EQ(w.m_onChildrenChangeCount, 0);
    EXPECT_EQ(w.m_onSiblingsChangeCount, 0);
    EXPECT_TRUE(w.m_reported_items.isEmpty());
    EXPECT_TRUE(w.m_reported_names.isEmpty());

    // Mapper is looking on parent; set property of child;
    setItem(multilayer, &w);
    EXPECT_TRUE(m_mapped_item == multilayer);
    layer->setItemValue(LayerItem::P_THICKNESS, 2.0);
    EXPECT_EQ(w.m_onPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onChildPropertyChangeCount, 1);
    EXPECT_EQ(w.m_onParentChangeCount, 0);
    EXPECT_EQ(w.m_onChildrenChangeCount, 0);
    EXPECT_EQ(w.m_onSiblingsChangeCount, 0);
    EXPECT_TRUE((w.m_reported_items.size() == 1) && (w.m_reported_items[0] == layer));
    EXPECT_TRUE((w.m_reported_names.size() == 1)
                && (w.m_reported_names[0] == LayerItem::P_THICKNESS));

    // Mapper is looking on parent; set property of parent;
    setItem(multilayer, &w);
    EXPECT_TRUE(m_mapped_item == multilayer);
    multilayer->setItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH, 2.0);
    EXPECT_EQ(w.m_onPropertyChangeCount, 1);
    EXPECT_EQ(w.m_onChildPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onParentChangeCount, 0);
    EXPECT_EQ(w.m_onChildrenChangeCount, 0);
    EXPECT_EQ(w.m_onSiblingsChangeCount, 0);
    EXPECT_TRUE(w.m_reported_items.isEmpty());
    EXPECT_TRUE((w.m_reported_names.size() == 1)
                && (w.m_reported_names[0] == MultiLayerItem::P_CROSS_CORR_LENGTH));
}

TEST_F(TestMapperForItem, test_onParentChange)
{
    Widget w;
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem("MultiLayer");
    SessionItem* layer = model.insertNewItem("Layer", model.indexOfItem(multilayer));

    // Mapper is looking on child; changing child's parent
    setItem(layer, &w);
    EXPECT_TRUE(m_mapped_item == layer);
    delete multilayer->takeRow(ParentRow(*layer));

    EXPECT_EQ(w.m_onPropertyChangeCount, 2); // Layer updates its property appearance, see LayerItem
    EXPECT_EQ(w.m_onChildPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onParentChangeCount, 1);
    EXPECT_EQ(w.m_onChildrenChangeCount, 0);
}

TEST_F(TestMapperForItem, test_onChildrenChange)
{
    Widget w;
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem("MultiLayer");

    // Mapper is looking on parent; adding new child to parent
    setItem(multilayer, &w);
    EXPECT_TRUE(m_mapped_item == multilayer);
    model.insertNewItem("Layer", model.indexOfItem(multilayer));

    EXPECT_EQ(w.m_onPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onChildPropertyChangeCount, 2);
    EXPECT_EQ(w.m_onParentChangeCount, 0);
    EXPECT_EQ(w.m_onChildrenChangeCount, 1);
    EXPECT_EQ(w.m_onSiblingsChangeCount, 0);
    EXPECT_EQ(w.m_reported_items.size(), 2);
    EXPECT_EQ(w.m_reported_names.size(), 2);
}

TEST_F(TestMapperForItem, test_onSiblingsChange)
{
    Widget w;
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem("MultiLayer");
    SessionItem* layer = model.insertNewItem("Layer", model.indexOfItem(multilayer));

    // Mapper is looking on child; adding another child to parent
    setItem(layer, &w);
    EXPECT_TRUE(m_mapped_item == layer);
    SessionItem* layer2 = model.insertNewItem("Layer", model.indexOfItem(multilayer));
    Q_UNUSED(layer2);

    EXPECT_EQ(w.m_onPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onChildPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onParentChangeCount, 0);
    EXPECT_EQ(w.m_onChildrenChangeCount, 0);
    EXPECT_EQ(w.m_onSiblingsChangeCount, 1);
    EXPECT_TRUE(w.m_reported_items.isEmpty());
    EXPECT_TRUE(w.m_reported_names.isEmpty());

    delete multilayer->takeItem(1, MultiLayerItem::T_LAYERS);
    EXPECT_EQ(w.m_onSiblingsChangeCount, 2);
}

TEST_F(TestMapperForItem, test_Subscription)
{
    Widget w;
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem("MultiLayer");
    SessionItem* layer = model.insertNewItem("Layer", model.indexOfItem(multilayer));

    // Mapper is looking on child; set property of child
    setItem(layer, &w, true);
    EXPECT_TRUE(m_mapped_item == layer);
    layer->setItemValue(LayerItem::P_THICKNESS, 1.0);
    EXPECT_EQ(w.m_onPropertyChangeCount, 1);
    EXPECT_EQ(w.m_onChildPropertyChangeCount, 0);
    EXPECT_EQ(w.m_onParentChangeCount, 0);
    EXPECT_EQ(w.m_onChildrenChangeCount, 0);
    EXPECT_EQ(w.m_onSiblingsChangeCount, 0);
    EXPECT_TRUE(w.m_reported_items.isEmpty());
    EXPECT_TRUE((w.m_reported_names.size() == 1)
                && (w.m_reported_names[0] == LayerItem::P_THICKNESS));

    layer->setItemValue(LayerItem::P_THICKNESS, 2.0);
    EXPECT_EQ(w.m_onPropertyChangeCount, 2);

    // unsubscribe widget and check that it doesn't react on item value change
    w.unsubscribe(m_mapper.get());
    layer->setItemValue(LayerItem::P_THICKNESS, 3.0);
    EXPECT_EQ(w.m_onPropertyChangeCount, 2);
}

TEST_F(TestMapperForItem, test_TwoWidgetsSubscription)
{
    Widget w1, w2;
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem("MultiLayer");
    SessionItem* layer = model.insertNewItem("Layer", model.indexOfItem(multilayer));

    // Mapper is looking on child; set property of child
    setItem(layer);
    w1.subscribe(m_mapper.get(), true);
    w2.subscribe(m_mapper.get(), true);
    EXPECT_EQ(w1.m_onPropertyChangeCount, 0);
    EXPECT_EQ(w2.m_onPropertyChangeCount, 0);

    layer->setItemValue(LayerItem::P_THICKNESS, 1.0);
    EXPECT_EQ(w1.m_onPropertyChangeCount, 1);
    EXPECT_EQ(w2.m_onPropertyChangeCount, 1);

    w1.unsubscribe(m_mapper.get());
    layer->setItemValue(LayerItem::P_THICKNESS, 2.0);
    EXPECT_EQ(w1.m_onPropertyChangeCount, 1);
    EXPECT_EQ(w2.m_onPropertyChangeCount, 2);
}

TEST_F(TestMapperForItem, test_AboutToRemoveChild)
{
    Widget w;
    SampleModel model;
    SessionItem* container = model.insertNewItem("ProjectionContainer");

    SessionItem* line = model.insertNewItem("HorizontalLineMask", container->index());

    setItem(container, &w);
    EXPECT_EQ(w.m_onAboutToRemoveChild, 0);
    EXPECT_EQ(w.m_reported_items.size(), 0);

    delete line->parent()->takeRow(line->parent()->rowOfChild(line));
    EXPECT_EQ(w.m_onAboutToRemoveChild, 1);
    EXPECT_EQ(w.m_reported_items.size(), 1);
    EXPECT_EQ(w.m_reported_items.back(), line);
}
