#ifndef MACSCOUNTER_H
#define MACSCOUNTER_H

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>

class MacsCounter
{
public:
    MacsCounter();
    std::unordered_map<std::string, int> getMacsCount(const std::string &filePath);
    std::vector<std::pair<std::string, int>> orderMacs(const std::unordered_map<std::string, int> &unorderedMacs);

private:
    // bool inKwords(const std::string &);
    std::unordered_set<std::string> kwords;
};

#endif // MACSCOUNTER_H
