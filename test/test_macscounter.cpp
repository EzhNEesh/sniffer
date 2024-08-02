#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <map>
#include <iostream>

#include "macscounter.h"
#include "macscounter.cpp"

struct MacsCounterTest : testing::Test {
    MacsCounter *macsCounter;
    std::multimap<int, std::string> orderedMacsCountMap;
    std::unordered_map<std::string, int> macsCountExc;
    std::vector<std::pair<std::string, int>> orderedMacsExc;

    void SetUp() {
        macsCounter = new MacsCounter();

        orderedMacsCountMap.insert({3, "c8:7f:54:28:74:ac"});
        orderedMacsCountMap.insert({4, "80:b6:55:60:6f:58"});
        orderedMacsCountMap.insert({13, "70:c9:32:1b:54:e2"});
        orderedMacsCountMap.insert({14, "52:ff:20:52:16:9a"});
        orderedMacsCountMap.insert({98, "ff:ff:ff:ff:ff:ff"});
        orderedMacsCountMap.insert({98, "4a:5f:99:ae:ea:99"});
        orderedMacsCountMap.insert({107, "6e:52:4e:5f:f9:eb"});
        orderedMacsCountMap.insert({124, "84:c5:a6:07:38:66"});
        orderedMacsCountMap.insert({136, "b8:69:f4:7a:a5:93"});
        orderedMacsCountMap.insert({5307, "34:1c:f0:d2:78:5a"});
        orderedMacsCountMap.insert({5812, "34:1c:f0:d3:40:a2"});
        orderedMacsCountMap.insert({7740, "00:0c:29:65:08:ee"});
        orderedMacsCountMap.insert({15235, "b8:69:f4:7a:a5:ac"});

        for (auto it = orderedMacsCountMap.rbegin(); it != orderedMacsCountMap.rend(); it++) {
            macsCountExc[it->second] = it->first;
            orderedMacsExc.push_back(std::pair<std::string, int> (it->second, it->first));
        }
    }
    void TearDown() {
        delete macsCounter;
    }
};

TEST_F(MacsCounterTest, GetMacsCount_Test) {
    std::unordered_map<std::string, int> macsCount = macsCounter->getMacsCount("../frames_parser.log");

    ASSERT_THAT(macsCount, testing::UnorderedElementsAreArray(macsCountExc));
}

TEST_F(MacsCounterTest, OrderMacs_Test) {
    std::vector<std::pair<std::string, int>> orderedMacs = macsCounter->orderMacs(macsCountExc);

    ASSERT_EQ(orderedMacs, orderedMacsExc);
}
