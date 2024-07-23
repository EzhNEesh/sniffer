#include "macscounter.h"

MacsCounter::MacsCounter() {}

std::unordered_map<std::string, int> MacsCounter::getMacsCount(const std::string &filePath) {
    std::string line;
    std::ifstream frames_file(filePath);
    std::unordered_map<std::string, int> macsCount;
    if (frames_file.is_open()) {
        while (std::getline(frames_file, line)) {
            size_t delim = line.find(',');
            while (delim != std::string::npos) {
                std::string cur_key = line.substr(delim + 1, 2);
                if (this->in_kwords(cur_key)) {
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
    }
    return macsCount;
}

std::multimap<int, std::string> MacsCounter::orderMacs(const std::unordered_map<std::string, int> &unorderedMacs) {
    std::multimap<int, std::string> res;
    for (auto it=unorderedMacs.begin(); it!=unorderedMacs.end(); it++) {
        res.insert({it->second, it->first});
    }
    return res;
}

bool MacsCounter::in_kwords(const std::string &string_to_find) {
    std::vector<std::string> kwords {"SA", "TA", "RA", "BSSID", "DA"};
    return find(kwords.begin(), kwords.end(), string_to_find) != kwords.end();
}
