#include <fstream>
#include <iostream>

#include "macscounter.h"

MacsCounter::MacsCounter() {
    kwords = {"SA", "TA", "RA", "DA"};
    // std::vector<std::string> kwords {"SA", "TA", "RA", "DA"};
}

std::unordered_map<std::string, int> MacsCounter::getMacsCount(const std::string &filePath) {
    std::string line;
    std::ifstream frames_file(filePath);
    std::unordered_map<std::string, int> macsCount;
    if (frames_file.is_open()) {
        while (std::getline(frames_file, line)) {
            size_t delim = line.find(',');
            while (delim != std::string::npos) {
                std::string cur_key = line.substr(delim + 1, 2);
                if (kwords.find(cur_key) != kwords.end()) {
                    std::string mac = line.substr(line.find('=', delim + 1) + 1, 17);
                    if (macsCount.find(mac) == macsCount.end()) {
                        macsCount[mac] = 0;
                    }
                    macsCount[mac] += 1;
                }
                delim = line.find(',', delim + 1);
            }
        }
        frames_file.close();
    } else {
        throw std::runtime_error("Could not open file");
    }
    return macsCount;
}

std::vector<std::pair<std::string, int>> MacsCounter::orderMacs(const std::unordered_map<std::string, int> &unorderedMacs) {
    std::multimap<int, std::string> res_map;
    for (auto it=unorderedMacs.begin(); it!=unorderedMacs.end(); it++) {
        res_map.insert({it->second, it->first});
    }

    std::vector<std::pair<std::string, int>> res_vector;
    for (auto it=res_map.rbegin(); it!=res_map.rend(); it++) {
        res_vector.push_back(std::pair<std::string, int> (it->second, it->first));
    }

    return res_vector;
}

// bool MacsCounter::inKwords(const std::string &string_to_find) {
//     std::vector<std::string> kwords {"SA", "TA", "RA", "DA"};
//     return find(kwords.begin(), kwords.end(), string_to_find) != kwords.end();
// }
