#ifndef MACSCOUNTER_H
#define MACSCOUNTER_H

#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>

class MacsCounter
{
public:
    MacsCounter();
    std::unordered_map<std::string, int> getMacsCount(const std::string &);
    std::vector<std::pair<std::string, int>> orderMacs(const std::unordered_map<std::string, int> &);

private:
    bool inKwords(const std::string &);
};

#endif // MACSCOUNTER_H
