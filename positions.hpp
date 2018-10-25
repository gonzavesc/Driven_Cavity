#include <iostream>
#include <fstream>
#include <vector>
#include "import.hpp"

#ifndef INCLUDE_POS
#define INCLUDE_POS
class positions{
    private:
        double dx,dy;
        std::vector<double> Xp, Yp, Xu, Yv, Dxpr, Dxpl, Dypu, Dypd, Dxur, Dxul;
    public:
        positions(const double& a, const double& b);
        std::vector<double> get_Xp();
        std::vector<double> get_Yp();
        std::vector<double> get_Yv();
        std::vector<double> get_Xu();

};

#endif