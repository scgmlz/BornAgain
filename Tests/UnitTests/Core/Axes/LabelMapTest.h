#ifndef LABELMAPTEST_H
#define LABELMAPTEST_H

#include "SampleLabelHandler.h"
#include "INamed.h"
#include <map>
#include <iostream>
#include <memory>

class LabelMapTest : public ::testing::Test
{
protected:
    LabelMapTest(){}
    virtual ~LabelMapTest(){}
};

TEST_F(LabelMapTest, LabelMapInsert)
{
    LabelMap<int> omap;
    EXPECT_EQ( size_t(0), omap.size());

    std::vector<int> keys = {3, 2, 1};
    std::vector<std::string> values = {"aaa", "bbb", "ccc"};

    omap.insert(keys[0], values[0]);
    omap.insert(keys[1], values[1]);
    omap.insert(keys[2], values[2]);
    EXPECT_EQ( size_t(3), omap.size());

    // check that <key,value> are stored in the order of insertion and that there is no sorting
    // along key as in normal map
    int npos(0);
    for(LabelMap<int>::const_iterator it = omap.begin(); it!= omap.end(); ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    omap.clear();
    EXPECT_EQ( size_t(0), omap.size());
}

TEST_F(LabelMapTest, LabelMapErase)
{
    LabelMap<std::string> omap;

    std::vector<std::string> keys = {"ccc", "bbb", "aaa"};
    std::vector<std::string> values = {"2.0", "1.0", "3.0"};

    omap.insert(keys[0], values[0]);
    omap.insert(keys[1], values[1]);
    omap.insert(keys[2], values[2]);

    int npos(0);
    for(LabelMap<std::string>::const_iterator it = omap.begin(); it!= omap.end(); ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    EXPECT_EQ(size_t(3), omap.size());

    omap.erase("ddd");
    EXPECT_EQ(size_t(3), omap.size());

    omap.erase("bbb");
    EXPECT_EQ(size_t(2), omap.size());

    keys = {"ccc", "aaa"};
    values = {"2.0", "3.0"};
    npos = 0;
    for(LabelMap<std::string>::const_iterator it = omap.begin(); it!= omap.end(); ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    omap.erase("ccc");
    omap.erase("aaa");
    EXPECT_EQ(size_t(0), omap.size());

    omap.insert("ddd", "99.0");
    EXPECT_EQ(size_t(1), omap.size());
}

TEST_F(LabelMapTest, LabelMapGetValue)
{
    LabelMap<const INamed*> omap;

    INamed *key1 = new INamed("key1");
    INamed *key2 = new INamed("key2");
    INamed *key3 = new INamed("key3");
    std::string val1 = "val1";
    std::string val2 = "val2";
    std::string val3 = "val3";

    omap.insert(key1, val1);
    omap.insert(key2, val2);
    omap.insert(key3, val3);

    EXPECT_EQ(omap.value(key1), val1);
    EXPECT_EQ(omap.value(key2), val2);
    EXPECT_EQ(omap.value(key3), val3);

    delete key1; delete key2; delete key3;
}

TEST_F(LabelMapTest, LabelMapFind)
{
    LabelMap<const INamed*> omap;

    INamed *n1 = new INamed("named1");
    INamed *n2 = new INamed("named2");
    INamed *n3 = new INamed("named3");
    INamed *n4 = new INamed("named4");

    omap.insert(n1, "aaa");
    omap.insert(n2, "bbb");
    omap.insert(n3, "ccc");
    EXPECT_EQ( size_t(3), omap.size());

    EXPECT_EQ(omap.find(n1)->first, n1);
    EXPECT_EQ(omap.find(n1)->first->getName(), "named1");
    EXPECT_EQ(omap.find(n1)->second, std::string("aaa"));

    EXPECT_EQ(omap.find(n2)->first, n2);
    EXPECT_EQ(omap.find(n2)->first->getName(), "named2");
    EXPECT_EQ(omap.find(n2)->second, std::string("bbb"));

    EXPECT_EQ(omap.find(n3)->first, n3);
    EXPECT_EQ(omap.find(n3)->first->getName(), "named3");
    EXPECT_EQ(omap.find(n3)->second, std::string("ccc"));

    EXPECT_EQ(omap.find(n4), omap.end());

    delete n1; delete n2; delete n3; delete n4;
}

TEST_F(LabelMapTest, LabelMapReInsert)
{
    std::unique_ptr<INamed> P_n1(new INamed("named1"));
    std::unique_ptr<INamed> P_n2(new INamed("named2"));
    std::unique_ptr<INamed> P_n3(new INamed("named3"));

    LabelMap<INamed *> omap;
    omap.insert(P_n1.get(), "1.0");
    omap.insert(P_n2.get(), "2.0");
    omap.insert(P_n3.get(), "3.0");
    EXPECT_EQ(omap.size(), size_t(3));

    omap.insert(P_n2.get(), "99.0");
    EXPECT_EQ(omap.size(), size_t(3));
    EXPECT_EQ(omap.value(P_n2.get()), "99.0");
}

#endif // LABELMAPTEST_H
