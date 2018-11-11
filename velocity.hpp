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
        std::vector<std::vector<double>> Vp;
        std::vector<std::vector<double>> Vpc;
    public:
        Velocity(const int& row, const int& col);        
        void set_Vp(positions& mesh, Velocity& Vv);
        void set_Vpc(positions& mesh, Velocity& V ,std::vector<Velocity>& Vv);
        void set_V(const int& i, const int& j, const double& u);
        std::vector<std::vector<double>> get_Vp();
        double get_Vp(const int& i, const int& j);
        std::vector<std::vector<double>> get_V();
        double get_V(const int& i, const int& j);
        std::vector<std::vector<double>> get_Vpc();
        double get_Vpc(const int& i, const int& j);
};
class Pressure{
    private:
        std::vector<std::vector<double>> P;
    public:
        Pressure(const int& row, const int& col);
        std::vector<std::vector<double>> get_P();
        double get_P(const int& i, const int& j);
        void set_P(const int&i, const int& j, const double p);
};

std::vector<std::vector<double>> vel_module(std::vector<Velocity>& Vv);
#endif