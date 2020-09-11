#include "Core/Fitting/FitObserver.h"
#include "Tests/GTestWrapper/google_test.h"

class FitObserverTest : public ::testing::Test
{
public:
    class TestHelper
    {
    public:
        TestHelper() : m_ncalls(0), m_data(42) {}
        int m_ncalls;
        int m_data;
    };
};

//! Checks that single observer is called on every iteration.

TEST_F(FitObserverTest, oneObserverOneEveryIteration)
{
    TestHelper helper;
    FitObserver<TestHelper> observer;

    // adding function representing observer callback
    int ncalls(0), data(0);
    std::function<void(const TestHelper&)> fun = [&](const TestHelper& helper) {
        ncalls++;
        data = helper.m_data;
    };
    observer.addObserver(1, fun);

    // calling observer once
    EXPECT_EQ(ncalls, 0);
    observer.notify(helper);
    EXPECT_EQ(ncalls, 1);
    EXPECT_EQ(data, 42);

    // calling observer few times
    for (int i = 0; i < 10; ++i)
        observer.notify(helper);

    // it should be called on every iteration
    EXPECT_EQ(ncalls, 11);
}

//! Checks that single observer called every 2-nd iteration.

TEST_F(FitObserverTest, oneObserverEverySecondIteration)
{
    TestHelper helper;
    FitObserver<TestHelper> observer;

    int ncalls(0);
    std::function<void(const TestHelper&)> fun = [&](const TestHelper&) { ncalls++; };
    observer.addObserver(2, fun);

    EXPECT_EQ(ncalls, 0);
    for (int i = 0; i < 11; ++i)
        observer.notify(helper);

    EXPECT_EQ(ncalls, 6);
}

//! Checks that two observers are called: one every 10-th iteration, another every 20-th.

TEST_F(FitObserverTest, twoObservers)
{
    TestHelper helper;
    FitObserver<TestHelper> observer;

    // Creating two functions representing observers callbacks.
    int ncalls1(0), ncalls2(0);
    std::function<void(const TestHelper&)> fun1 = [&](const TestHelper& helper) {
        ncalls1++;
        (void)helper;
    };

    std::function<void(const TestHelper&)> fun2 = [&](const TestHelper& helper) {
        ncalls2++;
        (void)helper;
    };

    // adding callbacks to the observer
    observer.addObserver(10, fun1);
    observer.addObserver(20, fun2);

    // calling observer 100 times and checking corresponding number of callbacks calls
    for (int i = 0; i < 101; ++i)
        observer.notify(helper);

    EXPECT_EQ(ncalls1, 11);
    EXPECT_EQ(ncalls2, 6);

    // checks forced notification
    observer.notify_all(helper);
    EXPECT_EQ(ncalls1, 12);
    EXPECT_EQ(ncalls2, 7);
}
