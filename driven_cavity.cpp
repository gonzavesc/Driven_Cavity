#include <iostream>
#include <vector>
#include <sstream>
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
    double k(0.01);
    v = readfiledat();
    Re = v[2];
    runtime = v[4];
    Poisson poiss(v[3]);
    positions mesh(v[0], v[1]);
    
    Velocity Xvel(mesh.get_m() + 2, mesh.get_n() + 1);
    Velocity Yvel(mesh.get_m() + 1, mesh.get_n() + 2);
    
    Pressure P(mesh.get_m() + 2, mesh.get_n() + 2);
    std::vector<Velocity> V;
    
    V.push_back(Xvel); V.push_back(Yvel); 
    //V[1].set_V(2,2,2); V[0].set_V(2,2,-3);
    V[0].set_Vp(mesh, V[0]);  V[1].set_Vp(mesh, V[1]);
    V[0].set_Vpc(mesh, V);  V[1].set_Vpc(mesh, V);
    Rpu = get_Ru(V, mesh, Re);
    Rpv = get_Rv(V, mesh, Re);

    set_boundary(V, P);
    V[0].set_Vp(mesh, V[0]); V[1].set_Vp(mesh, V[1]);
    V[0].set_Vpc(mesh, V); V[1].set_Vpc(mesh, V);
    deltatc = get_deltatc(V, mesh);
    deltatd = get_deltatd(Re, mesh);
    std::cout << "deltatd= " << deltatd << " deltatc= " << deltatc << std::endl;
    deltat = std::min(deltatd,deltatc);
    deltat = deltat;    
    Rnu = get_Ru(V, mesh, Re);
    Rnv = get_Rv(V, mesh, Re);
    up = get_up(V, Rnu, Rpu, deltat);
    vp = get_vp(V, Rnv, Rpv, deltat);
    set_boundary(up, vp);
    poiss.set_P(P, up, vp, mesh,  deltat);    
    poiss.set_V(P, mesh, V, up, vp, deltat);
    std::string save = "";
    total_time += deltat;
    while(total_time < runtime)
    {
        n+=1;
        V[0].set_Vp(mesh, V[0]); V[1].set_Vp(mesh, V[1]);
        V[0].set_Vpc(mesh, V); V[1].set_Vpc(mesh, V);
        copy_matrix(Rpu, Rnu); copy_matrix(Rpv, Rnv); 
        deltatc = get_deltatc(V, mesh);
        deltatd = get_deltatd(Re, mesh);
        deltat = std::min(deltatd,deltatc);
        Rnu = get_Ru(V, mesh, Re);
        Rnv = get_Rv(V, mesh, Re);
        up = get_up(V, Rnu, Rpu, deltat);
        vp = get_vp(V, Rnv, Rpv, deltat);
        set_boundary(up, vp);
        poiss.set_P(P, up, vp, mesh,  deltat);    
        poiss.set_V(P, mesh, V, up, vp, deltat);
        total_time += deltat;
        std::cout << total_time << " " << deltat << std::endl;
        if (total_time > k * runtime)
        {
            k+= 0.01;
            std::ostringstream strs;
            strs << total_time;
            save ="vel_x" + strs.str() + ".out";
            exportarMatriu(V[0].get_V(),save.c_str());
        }
    }




    char name0[] = "vel_x.out";
    char name2[] = "vel_y.out";
    char name3[] = "vel_xp.out";
    char name4[] = "vel_yp.out";
    char name5[] = "Pressure.out";
    char name6[] = "up.out";
    char name7[] = "vp.out";
    char name8[] = "Rnu.out";
    exportarMatriu(V[0].get_V(),name0);
    exportarMatriu(V[1].get_V(),name2);
    exportarMatriu(V[0].get_Vp(),name3);
    exportarMatriu(V[1].get_Vp(),name4);
    exportarMatriu(P.get_P(), name5);
    exportarMatriu(up, name6);
    exportarMatriu(vp, name7);
    exportarMatriu(Rnu, name8);
    std::cout << "End!" << std::endl;
    return 0;
}
