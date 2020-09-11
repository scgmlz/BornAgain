#include "GUI/coregui/Views/CommonWidgets/UpdateTimer.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QSignalSpy>

class TestUpdateTimer : public ::testing::Test
{
};

TEST_F(TestUpdateTimer, test_updateTimerShort)
{
    const int timer_interval(100);
    UpdateTimer timer(timer_interval);

    QSignalSpy spy(&timer, SIGNAL(timeToUpdate()));

    for (int i = 0; i < 10; ++i)
        timer.scheduleUpdate();

    // Checks that after time bigger than timer interval, we have a valid signal
    EXPECT_TRUE(spy.wait(timer_interval * 3));
    EXPECT_EQ(spy.count(), 1);

    // once again
    timer.scheduleUpdate();
    EXPECT_TRUE(spy.wait(timer_interval * 3));
    EXPECT_EQ(spy.count(), 2);

    /* The following test is disabled because it occasionally fails on Travis
        // Checks that after time smaller than timer interval, we have no signals
        for (int i = 0; i < 10; ++i)
            timer.scheduleUpdate();

        EXPECT_FALSE(spy.wait(timer_interval / 2));
        EXPECT_EQ(spy.count(), 2);
    */
}
