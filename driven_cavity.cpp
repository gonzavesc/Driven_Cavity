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
#include "poiss.hpp"
int main()
{
    std::vector<double> v;    
    std::vector <std::vector<double>> Vm, Rpu, Rnu, Rpv, Rnv, up, vp;
    double Re,deltatc, deltatd, deltat;
    v = readfiledat();
    Re = v[2];
    Poisson poiss(v[3]);
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
    V[0].set_Vpc(mesh, V); V[1].set_Vpc(mesh, V);
    deltatc = get_deltatc(V, mesh);
    deltatd = get_deltatd(Re, mesh);
    deltat = std::min(deltatd,deltatc);

    Rnu = get_Ru(V, mesh, Re);
    Rnv = get_Rv(V, mesh, Re);
    copy_matrix(Rpu, Rnu);
    copy_matrix(Rpv, Rnv);
    up = get_up(V, Rnu, Rpu, deltat);
    vp = get_vp(V,Rnv,Rpv,deltat);
    poiss.set_P(P, up, vp, mesh,  deltat);
    return 0;

}
