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
        void set_V(const int& i, const int& j, const double& u);
};
class Pressure{
    private:
        std::vector<std::vector<double>> P;
    public:
        Pressure(const int& row, const int& col);
        std::vector<std::vector<double>> get_P();
};
#endif