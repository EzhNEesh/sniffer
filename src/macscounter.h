#ifndef MACSCOUNTER_H
#define MACSCOUNTER_H

#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <map>

class MacsCounter
{
public:
    MacsCounter();
    std::unordered_map<std::string, int> getMacsCount(const std::string &);
    std::multimap<int, std::string> orderMacs(const std::unordered_map<std::string, int> &);

private:
    bool in_kwords(const std::string &);
};

#endif // MACSCOUNTER_H
