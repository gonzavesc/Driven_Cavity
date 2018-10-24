#include <iostream>
#include <vector>
#include <fstream>
#include "positions.hpp"
#include "import.hpp"

int main()
{
    std::vector<double> v;    

    v = readfiledat();
    positions mesh(v[0], v[1]);
    return 0;
}
