#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
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
    Xvel.set_Vp(mesh, Xvel);
    Velocity Yvel(mesh.get_m() + 2, mesh.get_n() + 1);
    Yvel.set_Vp(mesh, Yvel);
    Pressure P(mesh.get_m() + 1, mesh.get_n() + 1);
    std::vector<Velocity> V;
    V.push_back(Xvel); V.push_back(Yvel);
    set_boundary(V, P);
    V[0].set_Vp(mesh, V[0]); V[1].set_Vp(mesh, V[1]);
    return 0;

}
