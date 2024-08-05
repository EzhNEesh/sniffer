#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <map>
#include <iostream>
#include <fstream>

#include "macscounter.h"
#include "macscounter.cpp"

struct MacsCounterTest : testing::Test {
    MacsCounter *macsCounter;
    std::multimap<int, std::string> orderedMacsCountMap;
    std::unordered_map<std::string, int> macsCountExc;
    std::vector<std::pair<std::string, int>> orderedMacsExc;

    void SetUp() {
        macsCounter = new MacsCounter();

        std::fstream file("../orderedMacs.txt");
        std::string line;
        if (file.is_open()) {
            while (std::getline(file, line)) {
                size_t spacePos = line.find(' ');
                orderedMacsCountMap.insert({std::stoi(line.substr(spacePos)), line.substr(0, spacePos)});
            }
        }

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

MATCHER(orderedMacsEq, "") {
    return std::get<0>(arg) == std::get<1>(arg);
}

TEST_F(MacsCounterTest, OrderMacs_Test) {
    std::vector<std::pair<std::string, int>> orderedMacs = macsCounter->orderMacs(macsCountExc);
    std::vector<int> macsKeys;
    for (auto &it : orderedMacs) {
        macsKeys.push_back(it.second);
    }
    std::vector<int> macsKeysExc;
    for (auto &it : orderedMacsExc) {
        macsKeysExc.push_back(it.second);
    }

    EXPECT_THAT(orderedMacs, testing::UnorderedPointwise(orderedMacsEq(), orderedMacsExc));
    EXPECT_THAT(macsKeys, testing::ElementsAreArray(macsKeysExc));
}
