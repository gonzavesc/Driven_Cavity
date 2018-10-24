#include <iostream>
#include <fstream>
#include <vector>
#include "import.hpp"

#ifndef INCLUDE_POS
#define INCLUDE_POS
class positions{
    private:
        double dx;
        std::vector<double> Xp, Yp, Xu;
    public:
        positions(const double& a);
        std::vector<double> get_Xp();
        std::vector<double> get_Yp();
        std::vector<double> get_Yu();

};

#endif