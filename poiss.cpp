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
Poisson::Poisson(const double& a)
{
    err = a;
}
void Poisson::set_P(Pressure& P, std::vector<std::vector<double>>& up, std::vector<std::vector<double>>& vp, positions& mesh, const double& deltat)
{
    double rms,p,prev, bp, Ae, Aw, An, As,ae,aw,an,as;
    rms = err * 10;
    int Nx, Ny;
    Nx = P.get_P()[0].size(); Ny = P.get_P().size(); 
    Ae = mesh.get_Dypu()[0] + mesh.get_Dypd()[1];
    Aw = Ae;
    An = mesh.get_Dxpr()[0] + mesh.get_Dxpl()[1];
    As = An;
    ae = Ae / (mesh.get_Dxpr()[0] + mesh.get_Dxpl()[1]); aw = ae;
    an = An / (mesh.get_Dypu()[0] + mesh.get_Dypd()[1]); as = an;
    std::cout << Ae << " " << mesh.get_Dxpr()[0] + mesh.get_Dxpl()[1] << " " << Ae/deltat << std::endl;
    while (rms > err)
    {
        rms = 0;
        for (int i = 1; i < Ny - 1; i++)
        {
            for (int j = 1; j < Nx - 1; j++)
            {
                prev = P.get_P(i,j);
                p = P.get_P(i,j + 1) * ae + P.get_P(i, j - 1) * aw + P.get_P(i + 1, j) * an + P.get_P(i - 1, j) * as;
                bp = 1.0 / deltat * (up[i - 1][j] * Ae - up[i - 1][j - 1] * Aw + vp[i][j - 1] * An - vp[i - 1][j - 1] * As);
                P.set_P(i,j, (p - bp) / (ae+aw+as+an)); 
                rms = std::max(rms, std::abs(prev - P.get_P(i,j)));
                std::cout << bp << std::endl;
            }
        }
        //std::cout << rms << std::endl;
    }
}

void Poisson::set_V(Pressure& P, positions& mesh, std::vector<Velocity>& V, std::vector<std::vector<double>>& up, std::vector<std::vector<double>>& vp, const double& deltat)
{
    int Nx, Ny, i, j;
    double a;
    Nx = V[0].get_V()[0].size(); Ny = V[0].get_V().size();
    for (i = 1; i < Ny - 1; i++)
    {
        for (j = 1; j < Nx - 1; j++)
        {
            a = up[i - 1][j - 1] - deltat * (P.get_P(i, j)-P.get_P(i, j - 1)) / (mesh.get_Dxpl()[j] + mesh.get_Dxpr()[j - 1]);
            V[0].set_V(i,j,a);
        }
    }
    Nx = V[1].get_V()[0].size(); Ny = V[1].get_V().size();
    for (i = 1; i < Ny - 1; i++)
    {
        for (j = 1; j < Nx - 1; j++)
        {
            a = vp[i - 1][j - 1] - deltat * (P.get_P(i, j)-P.get_P(i - 1, j)) / (mesh.get_Dypd()[i] + mesh.get_Dypu()[i - 1]);
            V[1].set_V(i,j,a);
        }
    }
}