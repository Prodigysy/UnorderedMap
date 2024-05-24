#include <gtest/gtest.h>
#include <UnorderedMap/UnorderedMap.h>


TEST(UnorderedMap, Methods1) {
    UnorderedMap<int, std::string> map(10);

    map.insert(1, "One");
    map.insert(1, "OneOne");
    map.insert(2, "Two");
    map.insert(2, "TwoTwo");
    map.insert(2, "TwoTwoTwo");
    map.insert(3, "Three");
    map.insert(4, "Four");
    map.insert(5, "Five");
    map.insert(25, "TwentyFive");
    map.insert(28, "TwentyEight");

    map.print();

    auto map2(map);
    map2.print();

    auto map3 = map;
    map3.print();
    
    UnorderedMap<int, std::string> map4(10,0,10,0,15);
    map4.print();
    
}

TEST(UnorderedMap, Methods2) {
    UnorderedMap<int, std::string> map(10);

    map.insert(1, "One");
    map.insert(1, "OneOne");
    map.insert(2, "Two");
    map.insert(2, "TwoTwo");
    map.insert(2, "TwoTwoTwo");
    map.insert(5, "Five");
    
    auto item = map.search(2);
    ASSERT_TRUE(*item == "Two");

    map.insert_or_assign(12, "Twelve");
    ASSERT_TRUE(map.search(12));

    map.insert_or_assign(2, "TwoTwoTwo");
    auto item2 = map.search(2);
    ASSERT_TRUE(*item2 == "TwoTwoTwo");

    
}

TEST(UnorderedMap, Methods3) {
    UnorderedMap<int, std::string> map(10);

    map.insert(1, "One");
    map.insert(1, "OneOne");
    map.insert(2, "Two");
    map.insert(2, "TwoTwo");
    map.insert(2, "TwoTwoTwo");
    map.insert(5, "Five");

    map.erase(1);
    map.erase(1);
    ASSERT_FALSE(map.search(1));

    ASSERT_TRUE(map.count(2) == 3);

    ASSERT_TRUE(map.contains("Five") == 1);
    ASSERT_TRUE(map.contains("Six") == 0);
}

TEST(UnorderedMap, Task) {
    ASSERT_TRUE(romanToDecimal("LXXV") == 75);
    ASSERT_TRUE(romanToDecimal("XCIX") == 99);
    ASSERT_TRUE(romanToDecimal("DXLIX") == 549);
    ASSERT_TRUE(romanToDecimal("MCMLXXVI") == 1976);
}