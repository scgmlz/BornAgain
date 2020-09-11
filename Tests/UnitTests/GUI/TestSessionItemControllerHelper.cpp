#include "Tests/UnitTests/GUI/TestSessionItemControllerHelper.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/CommonWidgets/SessionItemController.h"

TestListener::TestListener()
    : m_onItemDestroyedCount(0), m_onPropertyChangeCount(0), m_onWidgetDestroyed(0)
{
}

void TestListener::clear()
{
    m_onItemDestroyedCount = 0;
    m_onPropertyChangeCount = 0;
    m_onWidgetDestroyed = 0;
}

TestObject::TestObject(TestListener* listener)
    : m_listener(listener), m_controller(new SessionItemController(this)), m_is_subscribed(false)
{
    m_controller->setSubscribeCallback([this]() { onSubscribe(); });
    m_controller->setUnsubscribeCallback([this]() { onUnsubscribe(); });
}

TestObject::~TestObject()
{
    m_listener->m_onWidgetDestroyed++;
}

void TestObject::setItem(SessionItem* item)
{
    m_controller->setItem(item);
}

void TestObject::onSubscribe()
{
    m_is_subscribed = true;
    currentItem()->mapper()->setOnPropertyChange(
        [this](const QString&) { m_listener->m_onPropertyChangeCount++; }, this);

    currentItem()->mapper()->setOnItemDestroy(
        [this](SessionItem*) { m_listener->m_onItemDestroyedCount++; }, this);
}

SessionItem* TestObject::currentItem()
{
    return m_controller->currentItem();
}

void TestObject::onUnsubscribe()
{
    m_is_subscribed = false;
}

void TestObject::setVisible(bool isVisible)
{
    if (isVisible)
        m_controller->subscribe();
    else
        m_controller->unsubscribe();
}
