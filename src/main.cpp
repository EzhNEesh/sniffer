#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>

#include "macscounter.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "The count of arguments must be two\n";
        return 1;
    }
    MacsCounter macsCounter;
    std::unordered_map<std::string, int> macsCount;

    try {
        macsCount = macsCounter.getMacsCount(argv[1]);
    } catch (std::runtime_error &excp) {
        std::cout << excp.what() << std::endl;
        return 1;
    }

    std::vector<std::pair<std::string, int>> res_out = macsCounter.orderMacs(macsCount);
    for (auto it=res_out.begin(); it!=res_out.end(); it++) {
        std::cout << it->first << ' ' << it->second << std::endl;
    }
    return 0;
}
