#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "positions.hpp"
#include "import.hpp"
#include "velocity.hpp"
#include "boundary.hpp"
#include "export.hpp"
#include "util.hpp"
#ifndef INCLUDE_POIS
#define INCLUDE_POIS
class Poisson {
    private:
        double err;
    public:
        Poisson(const double& a);
        void set_P(Pressure& P, std::vector<std::vector<double>>& up, std::vector<std::vector<double>>& vp, positions& mesh, const double& deltat);
        void set_V(Pressure& P, positions& mesh, std::vector<Velocity>& V, std::vector<std::vector<double>>& up, std::vector<std::vector<double>>& vp, const double& deltat); 
};


#endif