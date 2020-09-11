#include "Core/Export/OrderedMap.h"
#include "Tests/GTestWrapper/google_test.h"

class OrderedMapTest : public ::testing::Test
{
};

TEST_F(OrderedMapTest, OrderedMapInsert)
{
    OrderedMap<int, std::string> omap;
    EXPECT_EQ(size_t(0), omap.size());

    std::vector<int> keys = {3, 2, 1};
    std::vector<std::string> values = {"aaa", "bbb", "ccc"};

    omap.insert(keys[0], values[0]);
    omap.insert(keys[1], values[1]);
    omap.insert(keys[2], values[2]);
    EXPECT_EQ(size_t(3), omap.size());

    // check that <key,value> are stored in the order of insertion and that there is no sorting
    // along key as in normal map
    size_t npos(0);
    for (OrderedMap<int, std::string>::const_iterator it = omap.begin(); it != omap.end(); ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    omap.clear();
    EXPECT_EQ(size_t(0), omap.size());
}

TEST_F(OrderedMapTest, OrderedMapErase)
{
    OrderedMap<std::string, double> omap;

    std::vector<std::string> keys = {"ccc", "bbb", "aaa"};
    std::vector<double> values = {2.0, 1.0, 3.0};

    omap.insert(keys[0], values[0]);
    omap.insert(keys[1], values[1]);
    omap.insert(keys[2], values[2]);

    int npos(0);
    for (OrderedMap<std::string, double>::const_iterator it = omap.begin(); it != omap.end();
         ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    EXPECT_EQ(size_t(3), omap.size());

    EXPECT_EQ(omap.erase("ddd"), size_t(0));
    EXPECT_EQ(size_t(3), omap.size());

    EXPECT_EQ(omap.erase("bbb"), size_t(1));
    EXPECT_EQ(size_t(2), omap.size());

    keys = {"ccc", "aaa"};
    values = {2.0, 3.0};
    npos = 0;
    for (OrderedMap<std::string, double>::const_iterator it = omap.begin(); it != omap.end();
         ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    EXPECT_EQ(omap.erase("ccc"), size_t(1));
    EXPECT_EQ(omap.erase("aaa"), size_t(1));
    EXPECT_EQ(size_t(0), omap.size());

    omap.insert("ddd", 99.0);
    EXPECT_EQ(size_t(1), omap.size());
}

TEST_F(OrderedMapTest, OrderedMapGetValue)
{
    OrderedMap<const std::string*, std::string*> omap;

    std::unique_ptr<std::string> key1(new std::string("key1"));
    std::unique_ptr<std::string> key2(new std::string("key2"));
    std::unique_ptr<std::string> key3(new std::string("key3"));
    std::unique_ptr<std::string> val1(new std::string("val1"));
    std::unique_ptr<std::string> val2(new std::string("val2"));
    std::unique_ptr<std::string> val3(new std::string("val3"));

    omap.insert(key1.get(), val1.get());
    omap.insert(key2.get(), val2.get());
    omap.insert(key3.get(), val3.get());

    EXPECT_EQ(omap.value(key1.get()), val1.get());
    EXPECT_EQ(omap.value(key2.get()), val2.get());
    EXPECT_EQ(omap.value(key3.get()), val3.get());
}

TEST_F(OrderedMapTest, OrderedMapFind)
{
    OrderedMap<const std::string*, std::string> omap;

    std::unique_ptr<std::string> n1(new std::string("named1"));
    std::unique_ptr<std::string> n2(new std::string("named2"));
    std::unique_ptr<std::string> n3(new std::string("named3"));
    std::unique_ptr<std::string> n4(new std::string("named4"));

    omap.insert(n1.get(), "aaa");
    omap.insert(n2.get(), "bbb");
    omap.insert(n3.get(), "ccc");
    EXPECT_EQ(size_t(3), omap.size());

    EXPECT_EQ(omap.find(n1.get())->first, n1.get());
    EXPECT_EQ(omap.find(n1.get())->second, "aaa");

    EXPECT_EQ(omap.find(n2.get())->first, n2.get());
    EXPECT_EQ(omap.find(n2.get())->second, "bbb");

    EXPECT_EQ(omap.find(n3.get())->first, n3.get());
    EXPECT_EQ(omap.find(n3.get())->second, "ccc");

    EXPECT_EQ(omap.find(n4.get()), omap.end());
}

TEST_F(OrderedMapTest, OrderedMapReInsert)
{
    std::unique_ptr<std::string> P_n1(new std::string("named1"));
    std::unique_ptr<std::string> P_n2(new std::string("named2"));
    std::unique_ptr<std::string> P_n3(new std::string("named3"));

    OrderedMap<std::string*, double> omap;
    omap.insert(P_n1.get(), 1.0);
    omap.insert(P_n2.get(), 2.0);
    omap.insert(P_n3.get(), 3.0);
    EXPECT_EQ(omap.size(), size_t(3));

    omap.insert(P_n2.get(), 99.0);
    EXPECT_EQ(omap.size(), size_t(3));
    EXPECT_EQ(omap.value(P_n2.get()), 99.0);
}
