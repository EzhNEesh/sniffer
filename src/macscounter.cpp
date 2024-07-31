#include <fstream>
#include <iostream>

#include "macscounter.h"

MacsCounter::MacsCounter(const char &_delim, const char &_keyDelim, const char &_assignment) {
    kwords = {"SA", "TA", "RA", "DA"};
    delim = _delim;
    keyDelim = _keyDelim;
    assignment = _assignment;
}

std::unordered_map<std::string, int> MacsCounter::getMacsCount(const std::string &filePath) {
    std::string line;
    std::ifstream framesFile(filePath);
    std::unordered_map<std::string, int> macsCount;
    if (framesFile.is_open()) {
        while (std::getline(framesFile, line)) {
            std::vector<std::string> foundedMacs;
            try {
                foundedMacs = parseString(line);
            } catch (std::out_of_range &excp) {
                framesFile.close();
                throw excp;
            }

            for (auto &mac : foundedMacs) {
                if (macsCount.find(mac) == macsCount.end()) {
                    macsCount[mac] = 0;
                }
                macsCount[mac] += 1;
            }
        }
        framesFile.close();
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

std::vector<std::string> MacsCounter::parseString(const std::string &line) {
    std::vector<std::string> foundedMacs;
    size_t delimPos = line.find(delim);
    while (delimPos != std::string::npos) {
        size_t assignmentPos = line.find(assignment, delimPos + 1);
        if (assignmentPos == std::string::npos) {
            throw std::out_of_range("Invalid data in line: " + line);
        }
        std::string curKey = line.substr(delimPos + 1, assignmentPos - delimPos - 1);
        if (checkKey(curKey)) {
            std::string mac = line.substr(assignmentPos + 1, 17);
            if (mac.size() != 17) {
                throw std::out_of_range("Invalid mac data in line: " + line);
            }
            foundedMacs.push_back(mac);
        }
        delimPos = line.find(',', delimPos + 1);
    }
    return foundedMacs;
}

bool MacsCounter::checkKey(const std::string &key) {
    if (key.size() < 2) {
        throw std::out_of_range("Invalid data");
    }
    if (key.size() > 2) {
        size_t keyDelimPos = key.find(keyDelim);
        if (keyDelimPos == std::string::npos) {
            return false;
        }
        if (kwords.find(key.substr(0, keyDelimPos)) != kwords.end() || kwords.find(key.substr(keyDelimPos + 1)) != kwords.end()) {
            return true;
        }
        return false;
    } else if (kwords.find(key) != kwords.end()) {
        return true;
    } else {
        return false;
    }
}
