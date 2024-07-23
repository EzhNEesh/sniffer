#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>

#include "macscounter.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        return 1;
    }
    MacsCounter macsCounter;
    unordered_map<string, int> macsCount = macsCounter.getMacsCount(argv[1]);
    multimap<int, string> res_out = macsCounter.orderMacs(macsCount);
    for (auto it=res_out.begin(); it!=res_out.end();it++) {
        cout << it->second << ' ' << it->first << endl;
    }
    return 0;
}
