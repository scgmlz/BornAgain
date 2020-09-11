#ifndef BORNAGAIN_TESTS_UNITTESTS_GUI_TESTSESSIONITEMCONTROLLERHELPER_H
#define BORNAGAIN_TESTS_UNITTESTS_GUI_TESTSESSIONITEMCONTROLLERHELPER_H

#include <QObject>
class SessionItem;
class SessionItemController;

//! Helper classes for TestSessionItemController unit tests.
//! Should be in separate header to avoid interference of Qt moc and google test macros.

//! Helper class to test object behaviour after their death.

class TestListener
{
public:
    TestListener();
    void clear();
    int m_onItemDestroyedCount;
    int m_onPropertyChangeCount;
    int m_onWidgetDestroyed;
};

//! Helper class to test SessionItemController usage in widget context.

class TestObject : public QObject
{
    Q_OBJECT
public:
    TestObject(TestListener* listener);
    ~TestObject();

    void setItem(SessionItem* item);
    void onSubscribe();

    SessionItem* currentItem();

    void onUnsubscribe();

    void setVisible(bool isVisible);

    TestListener* m_listener;
    SessionItemController* m_controller;
    bool m_is_subscribed;
};

#endif // BORNAGAIN_TESTS_UNITTESTS_GUI_TESTSESSIONITEMCONTROLLERHELPER_H
