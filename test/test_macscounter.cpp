#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <map>
#include <iostream>

#include "../src/macscounter.h"
#include "../src/macscounter.cpp"

struct MacsCounterTest : testing::Test {
    MacsCounter *macsCounter;
    std::unordered_map<std::string, int> macsCountExc;
    std::multimap<int, std::string> orderedMacsExc;

    void SetUp() {
        macsCounter = new MacsCounter();

        macsCountExc["c8:7f:54:28:74:ac"] = 3;
        macsCountExc["80:b6:55:60:6f:58"] = 4;
        macsCountExc["70:c9:32:1b:54:e2"] = 13;
        macsCountExc["52:ff:20:52:16:9a"] = 14;
        macsCountExc["ff:ff:ff:ff:ff:ff"] = 98;
        macsCountExc["4a:5f:99:ae:ea:99"] = 98;
        macsCountExc["6e:52:4e:5f:f9:eb"] = 107;
        macsCountExc["84:c5:a6:07:38:66"] = 124;
        macsCountExc["b8:69:f4:7a:a5:93"] = 136;
        macsCountExc["34:1c:f0:d2:78:5a"] = 5307;
        macsCountExc["34:1c:f0:d3:40:a2"] = 5812;
        macsCountExc["00:0c:29:65:08:ee"] = 7740;
        macsCountExc["b8:69:f4:7a:a5:ac"] = 15235;

        orderedMacsExc.insert({3, "c8:7f:54:28:74:ac"});
        orderedMacsExc.insert({4, "80:b6:55:60:6f:58"});
        orderedMacsExc.insert({13, "70:c9:32:1b:54:e2"});
        orderedMacsExc.insert({14, "52:ff:20:52:16:9a"});
        orderedMacsExc.insert({98, "ff:ff:ff:ff:ff:ff"});
        orderedMacsExc.insert({98, "4a:5f:99:ae:ea:99"});
        orderedMacsExc.insert({107, "6e:52:4e:5f:f9:eb"});
        orderedMacsExc.insert({124, "84:c5:a6:07:38:66"});
        orderedMacsExc.insert({136, "b8:69:f4:7a:a5:93"});
        orderedMacsExc.insert({5307, "34:1c:f0:d2:78:5a"});
        orderedMacsExc.insert({5812, "34:1c:f0:d3:40:a2"});
        orderedMacsExc.insert({7740, "00:0c:29:65:08:ee"});
        orderedMacsExc.insert({15235, "b8:69:f4:7a:a5:ac"});
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
    std::multimap<int, std::string> orderedMacs = macsCounter->orderMacs(macsCountExc);

    ASSERT_EQ(orderedMacs, orderedMacsExc);
}
