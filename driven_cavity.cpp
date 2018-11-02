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
    std::vector <std::vector<double>> Rpu, Rnu, Rpv, Rnv, up, vp, Vm;
    double Re,deltatc, deltatd, deltat, runtime, total_time(0),M(0);
    int n(0);
    v = readfiledat();
    Re = v[2];
    runtime = v[4];
    Poisson poiss(v[3]);
    positions mesh(v[0], v[1]);
    Velocity Xvel(mesh.get_m() + 1, mesh.get_n() + 2);
    Velocity Yvel(mesh.get_m() + 2, mesh.get_n() + 1);
    Pressure P(mesh.get_m() + 1, mesh.get_n() + 1);
    std::vector<Velocity> V;
    V.push_back(Xvel); V.push_back(Yvel);
    V[0].set_Vp(mesh, V[0]); V[1].set_Vp(mesh, V[1]);
    V[0].set_Vpc(mesh, V); V[1].set_Vpc(mesh, V);
    Rpu = get_Ru(V, mesh, Re);
    Rpv = get_Rv(V, mesh, Re);
    set_boundary(V, P);
    V[0].set_Vp(mesh, V[0]); V[1].set_Vp(mesh, V[1]);
    V[0].set_Vpc(mesh, V); V[1].set_Vpc(mesh, V);
    deltatc = get_deltatc(V, mesh);
    deltatd = get_deltatd(Re, mesh);
    deltat = std::min(deltatd,deltatc);
    deltat = deltat;
    Rnu = get_Ru(V, mesh, Re);
    Rnv = get_Rv(V, mesh, Re);

    up = get_up(V, Rnu, Rpu, deltat);
    vp = get_vp(V, Rnv, Rpv, deltat);
    poiss.set_P(P, up, vp, mesh,  deltat);
    poiss.set_V(P, mesh, V, up, vp, deltat);
    set_boundary(V, P);
    copy_matrix(Rpu, Rnu);
    copy_matrix(Rpv, Rnv);
    total_time+=deltat;
    //while(total_time < runtime)
    std::cout << deltat << std::endl;
    while(n < 0)
    {
        std::cout << "Hey loop" << std::endl;
        n+=1;
        Vm = vel_module(V); M = get_max(Vm);
        std::cout<< "1 " << M << std::endl;
        V[0].set_Vp(mesh, V[0]); V[1].set_Vp(mesh, V[1]);
        V[0].set_Vpc(mesh, V); V[1].set_Vpc(mesh, V);
        Vm = vel_module(V); M = get_max(Vm);
        std::cout <<"2 " << M << std::endl;
        deltatc = get_deltatc(V, mesh);
        deltatd = get_deltatd(Re, mesh);
        Rnu = get_Ru(V, mesh, Re);
        Rnv = get_Rv(V, mesh, Re);
        Vm = vel_module(V); M = get_max(Vm);
        std::cout <<"3 " << M << std::endl;
        up = get_up(V, Rnu, Rpu, deltat);
        vp = get_vp(V,Rnv,Rpv,deltat);
        Vm = vel_module(V); M = get_max(Vm);
        std::cout <<"4 " << M << std::endl;
        poiss.set_P(P, up, vp, mesh,  deltat);
        poiss.set_V(P, mesh, V, up, vp, deltat);
        Vm = vel_module(V); M = get_max(Vm);
        std::cout <<"5 " << M << std::endl;
        set_boundary(V, P);
        Vm = vel_module(V); M = get_max(Vm);
        std::cout <<"6 " << M << std::endl;
        copy_matrix(Rpu, Rnu);
        copy_matrix(Rpv, Rnv);
        total_time+=deltat;
        Vm = vel_module(V); M = get_max(Vm);
        std::cout << total_time / runtime * 100 << " " << deltat << " " << n << std::endl;
    }
    V[0].set_Vp(mesh, V[0]); V[1].set_Vp(mesh, V[1]);
    V[0].set_Vpc(mesh, V); V[1].set_Vpc(mesh, V);
    char name0[] = "vel_x.out";
    char name2[] = "vel_y.out";
    char name3[] = "vel_xp.out";
    char name4[] = "vel_yp.out";
    char name5[] = "Pressure.out";
    exportarMatriu(V[0].get_V(),name0);
    exportarMatriu(V[1].get_V(),name2);
    exportarMatriu(V[0].get_Vp(),name3);
    exportarMatriu(V[1].get_Vp(),name4);
    exportarMatriu(P.get_P(), name5);
    std::cout << "End!" << std::endl;
    return 0;
}
