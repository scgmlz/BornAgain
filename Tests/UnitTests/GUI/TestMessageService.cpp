#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/GUIMessage.h"
#include "GUI/coregui/utils/MessageService.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QObject>
#include <QString>

namespace
{
const QString senderName1("senderName1");
const QString senderName2("senderName2");

const QString messageType1("messageType1");
const QString description1("description1");

const QString messageType2("messageType2");
const QString description2("description2");

const QString messageType3("messageType3");
const QString description3("description3");
} // namespace

class TestMessageService : public ::testing::Test
{
public:
    class Sender : public QObject
    {
    public:
        Sender(const QString& name) { setObjectName(name); }
    };
};

TEST_F(TestMessageService, guiMessage)
{
    GUIMessage message(senderName1, messageType1, description1);

    EXPECT_EQ(message.senderName(), senderName1);
    EXPECT_EQ(message.messageType(), messageType1);
    EXPECT_EQ(message.messageDescription(), description1);
}

TEST_F(TestMessageService, initialState)
{
    MessageService svc;
    EXPECT_TRUE(svc.messages().isEmpty());
}

TEST_F(TestMessageService, sendMessage)
{
    MessageService svc;
    Sender sender(senderName1);

    // sending 3 messages
    svc.send_message(&sender, messageType1, description1);
    svc.send_message(&sender, messageType1, description1);
    svc.send_message(&sender, messageType2, description2);

    EXPECT_EQ(svc.messages().size(), 3);
    EXPECT_EQ(svc.messages().at(0)->senderName(), senderName1);
    EXPECT_EQ(svc.messages().at(1)->senderName(), senderName1);
    EXPECT_EQ(svc.messages().at(2)->senderName(), senderName1);
    EXPECT_EQ(svc.messages().at(0)->messageType(), messageType1);
    EXPECT_EQ(svc.messages().at(1)->messageType(), messageType1);
    EXPECT_EQ(svc.messages().at(2)->messageType(), messageType2);
    EXPECT_EQ(svc.messages().at(0)->messageDescription(), description1);
    EXPECT_EQ(svc.messages().at(1)->messageDescription(), description1);
    EXPECT_EQ(svc.messages().at(2)->messageDescription(), description2);

    // checking sender list
    EXPECT_EQ(svc.senderList().size(), 1);
}

TEST_F(TestMessageService, twoSenders)
{
    MessageService svc;
    Sender sender1(senderName1);
    Sender sender2(senderName2);

    // sending 3 messages
    svc.send_message(&sender1, messageType1, description1);
    svc.send_message(&sender1, messageType1, description1);
    svc.send_message(&sender2, messageType2, description2);

    EXPECT_EQ(svc.messages().size(), 3);
    EXPECT_EQ(svc.messages().at(0)->senderName(), senderName1);
    EXPECT_EQ(svc.messages().at(1)->senderName(), senderName1);
    EXPECT_EQ(svc.messages().at(2)->senderName(), senderName2);
    EXPECT_EQ(svc.messages().at(0)->messageType(), messageType1);
    EXPECT_EQ(svc.messages().at(1)->messageType(), messageType1);
    EXPECT_EQ(svc.messages().at(2)->messageType(), messageType2);
    EXPECT_EQ(svc.messages().at(0)->messageDescription(), description1);
    EXPECT_EQ(svc.messages().at(1)->messageDescription(), description1);
    EXPECT_EQ(svc.messages().at(2)->messageDescription(), description2);

    // checking sender list
    EXPECT_EQ(svc.senderList().size(), 2);
    EXPECT_TRUE(svc.senderList().contains(senderName1));
    EXPECT_TRUE(svc.senderList().contains(senderName2));
}

TEST_F(TestMessageService, messageCount)
{
    MessageService svc;
    Sender sender1(senderName1);
    Sender sender2(senderName2);

    // sending messages
    svc.send_message(&sender1, messageType1, description1);
    svc.send_message(&sender1, messageType2, description2);
    svc.send_message(&sender1, messageType1, description1);
    svc.send_message(&sender2, messageType2, description2);
    svc.send_message(&sender1, messageType3, description3);

    EXPECT_EQ(svc.messageCount(&sender1), 4);
    EXPECT_EQ(svc.messageCount(&sender2), 1);

    EXPECT_EQ(svc.messageCount(&sender1, messageType1), 2);
    EXPECT_EQ(svc.messageCount(&sender1, messageType3), 1);
    EXPECT_EQ(svc.messageCount(&sender2, messageType2), 1);
    EXPECT_EQ(svc.messageCount(&sender2, messageType3), 0);
    EXPECT_EQ(svc.messageCount(&sender1, messageType3), 1);

    Sender sender3("sender3");
    EXPECT_EQ(svc.messageCount(&sender3), 0);
}

TEST_F(TestMessageService, warningAndErrorCount)
{
    MessageService svc;
    Sender sender1(senderName1);
    Sender sender2(senderName2);

    // sending messages
    svc.send_warning(&sender1, description1);
    svc.send_warning(&sender1, description2);
    svc.send_error(&sender1, description1);
    svc.send_error(&sender2, description2);
    svc.send_warning(&sender1, description3);

    EXPECT_EQ(svc.errorCount(&sender1), 1);
    EXPECT_EQ(svc.errorCount(&sender2), 1);
    EXPECT_EQ(svc.errorCount(), 2);

    EXPECT_EQ(svc.warningCount(&sender1), 3);
    EXPECT_EQ(svc.warningCount(&sender2), 0);
    EXPECT_EQ(svc.warningCount(), 3);
}
