#include <iostream>
#include <vector>
#include <fstream>
#include "positions.hpp"
#include "import.hpp"
#include "velocity.hpp"
#include "boundary.hpp"
#include "export.hpp"
int main()
{
    std::vector<double> v;    

    v = readfiledat();
    positions mesh(v[0], v[1]);
    Velocity Xvel(mesh.get_m() + 1, mesh.get_n() + 2);
    Velocity Yvel(mesh.get_m() + 2, mesh.get_n() +1);
    Pressure P(mesh.get_m() + 1, mesh.get_n() + 1);
    std::vector<Velocity> V;
    V.push_back(Xvel); V.push_back(Yvel);
    set_boundary(V, P);
    exportarMatriu(V[0].get_V());
    return 0;

}
