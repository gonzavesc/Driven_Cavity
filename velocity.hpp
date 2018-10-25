#include <iostream>
#include <vector>
#include <fstream>
#include "positions.hpp"
#include "import.hpp"

#ifndef INCLUDE_VEL
#define INCLUDE_VEL
class Velocity{
    private:
        std::vector<std::vector<double>> V;
    public:
        Velocity(const int& row, const int& col);
        std::vector<std::vector<double>> get_V();
};

#endif