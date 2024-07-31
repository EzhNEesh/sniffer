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
    MacsCounter(const char &_delim = ',', const char &_keyDelim = '/', const char &_assignment='=');
    std::unordered_map<std::string, int> getMacsCount(const std::string &filePath);
    std::vector<std::pair<std::string, int>> orderMacs(const std::unordered_map<std::string, int> &unorderedMacs);

private:
    std::unordered_set<std::string> kwords;
    std::vector<std::string> parseString(const std::string &line);
    bool checkKey(const std::string &key);
    char delim;
    char keyDelim;
    char assignment;
};

#endif // MACSCOUNTER_H
