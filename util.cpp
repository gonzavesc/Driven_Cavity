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

double get_max(const std::vector<std::vector<double>>& M)
{
    double m;
    int Ny,Nx;
    Ny = M.size(); Nx = M[0].size();
    m = M[0][0]; 
    for (int i = 0; i < Ny; i++)
    {
        for (int j = 0; j < Nx; j++)
        {
            m = std::max(M[i][j], m);
        }
    }
    return m;   
}

double get_max(const std::vector<double>& M)
{
    double m;
    int Ny;
    Ny = M.size();
    m = M[0];
    for (int i = 0; i < Ny; i++)
    {    
        m = std::max(M[i], m);
    }
    return m;   
}

double get_min(const std::vector<std::vector<double>>& M)
{
    double m;
    int Ny,Nx;
    Ny = M.size(); Nx = M[0].size();
    m = M[0][0]; 
    for (int i = 0; i < Ny; i++)
    {
        for (int j = 0; j < Nx; j++)
        {
            m = std::min(M[i][j], m);
        }
    }
    return m;   
}

double get_min(const std::vector<double>& M)
{
    double m;
    int Ny;
    Ny = M.size();
    m = M[0];
    for (int i = 1; i < Ny - 1; i++)
    {    
        m = std::min(M[i], m);
    }
    return m;   
}

double get_deltatc(std::vector<Velocity>& Vv, positions& mesh)
{
    double Dtc, M, N;
    std::vector <std::vector<double>> Vm;
    Vm = vel_module(Vv); M = get_max(Vm);
    N = get_min(mesh.get_Dxpr());
    Dtc = 0.35 * N / M;
    return Dtc;
}
double get_deltatd(const double& Re, positions& mesh)
{
    double Dtd, N;
    N = get_min(mesh.get_Dxpr());
    Dtd = 0.2 * Re * N;
    return Dtd;
}
void copy_matrix(std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B)
{
    int Nx, Ny;
    Nx = B[0].size(); Ny = B.size();
    A.resize(Ny, std::vector<double>(Nx));
    for (int i = 0; i < Ny; i++)
    {
        for(int j = 0; j < Nx; j++)
        {
            A[i][j] = B[i][j];
        }
    }
}

std::vector<std::vector<double>> get_Ru(std::vector<Velocity>& V, positions& mesh, const double& Re)
{
    std::vector<std::vector<double>> R;
    double Vol, Ue, Uw, Vn, Vs, Ae, Aw, An, As;
    double aux1, aux2;
    int Nx, Ny;
    Nx=V[0].get_V()[0].size(); Ny=V[0].get_V().size();
    R.resize(Ny - 2, std::vector<double>(Nx - 2) );
    for (int i = 0; i < Ny - 2; i++)
    {
        for (int j = 0; j < Nx - 2; j++)
        {
            Vol = (mesh.get_Dxur()[j + 1] + mesh.get_Dxul()[j + 1]) * (mesh.get_Dypu()[i + 1] + mesh.get_Dypd()[i +1]);
            Ae = mesh.get_Dypu()[i + 1] + mesh.get_Dypd()[i +1];
            Aw = Ae;
            An = mesh.get_Dxur()[j + 1] + mesh.get_Dxul()[j + 1];
            As = An;
            Ue = (V[0].get_V(i + 1, j + 2) + V[0].get_V(i + 1, j + 1)) / 2;
            Uw = (V[0].get_V(i + 1, j + 1) + V[0].get_V(i + 1, j)) / 2;
            Vn = (V[1].get_V(i + 2, j) * mesh.get_Dxul()[j + 1] + V[1].get_V(i + 2, j + 1) * mesh.get_Dxur()[j + 1]) / (mesh.get_Dxur()[j + 1] + mesh.get_Dxul()[j + 1]);
            Vs = (V[1].get_V(i + 1, j) * mesh.get_Dxul()[j + 1] + V[1].get_V(i + 1, j + 1) * mesh.get_Dxur()[j + 1]) / (mesh.get_Dxur()[j + 1] + mesh.get_Dxul()[j + 1]);
            aux1 = Ue * V[0].get_Vp(i + 1, j + 1) * Ae - Uw * V[0].get_Vp(i + 1, j) * Aw + Vn * V[0].get_Vpc(i + 1, j) * An - Vs * V[0].get_Vpc(i, j) * As;
            aux2 = (V[0].get_V(i + 1, j + 2) - V[0].get_V(i + 1, j + 1)) / (mesh.get_Dxur()[j + 1] + mesh.get_Dxul()[j + 2]) * Ae 
                    - (V[0].get_V(i + 1, j + 1) - V[0].get_V(i + 1, j)) / (mesh.get_Dxur()[j] + mesh.get_Dxul()[j + 1]) * Aw
                    + (V[0].get_V(i + 2,j + 1) - V[0].get_V(i + 1, j + 1)) / (mesh.get_Dypu()[i + 1] + mesh.get_Dypd()[i + 2]) * An
                    - (V[0].get_V(i + 1, j + 1) - V[0].get_V(i, j + 1)) / (mesh.get_Dypu()[i] + mesh.get_Dypd()[i + 1]) * As;
            R[i][j] = (-aux1 + aux2 / Re) / Vol;

        }
    }
    return R;   
}


std::vector<std::vector<double>> get_Rv(std::vector<Velocity>& V, positions& mesh, const double& Re)
{
    std::vector<std::vector<double>> R;
    double Vol, Ue, Uw, Vn, Vs, Ae, Aw, An, As;
    double aux1, aux2;
    int Nx, Ny;
    Nx=V[1].get_V()[1].size(); Ny=V[1].get_V().size();
    R.resize(Ny - 2, std::vector<double>(Nx - 2) );
    for (int i = 0; i < Ny - 2; i++)
    {
        for (int j = 0; j < Nx - 2; j++)
        {
            Vol = (mesh.get_Dxpr()[j + 1] + mesh.get_Dxpl()[j + 1]) * (mesh.get_Dyvu()[i + 1] + mesh.get_Dyvd()[i +1]);
            Ae = mesh.get_Dyvu()[i + 1] + mesh.get_Dyvd()[i +1];
            Aw = Ae;
            An = mesh.get_Dxpr()[j + 1] + mesh.get_Dxpl()[j + 1];
            As = An;
            Ue = (V[0].get_V(i + 1, j + 2) * mesh.get_Dyvu()[i + 1] + V[0].get_V(i, j + 2) * mesh.get_Dyvd()[i + 1]) / (mesh.get_Dyvu()[i + 1] + mesh.get_Dyvd()[i + 1]);
            Uw = (V[0].get_V(i + 1, j + 1) * mesh.get_Dyvu()[i + 1] + V[0].get_V(i, j + 1) * mesh.get_Dyvd()[i + 1]) / (mesh.get_Dyvu()[i + 1] + mesh.get_Dyvd()[i + 1]);
            Vn = (V[1].get_V(i + 1, j + 1) + V[1].get_V(i + 2, j + 1)) / (2);
            Vs = (V[1].get_V(i + 1, j + 1) + V[1].get_V(i, j + 1)) / (2);
            aux1 = Ue * V[1].get_Vpc(i, j + 1) * Ae - Uw * V[1].get_Vpc(i, j) * Aw + Vn * V[1].get_Vp(i + 1, j + 1) * An - Vs * V[1].get_Vp(i, j + 1) * As;
            aux2 = (V[1].get_V(i + 1, j + 2) - V[1].get_V(i + 1, j + 1)) / (mesh.get_Dxpr()[j + 1] + mesh.get_Dxpl()[j + 2]) * Ae 
                    - (V[1].get_V(i + 1, j + 1) - V[1].get_V(i + 1, j)) / (mesh.get_Dxpr()[j] + mesh.get_Dxpl()[j + 1]) * Aw
                    + (V[1].get_V(i + 2,j + 1) - V[1].get_V(i + 1, j + 1)) / (mesh.get_Dyvu()[i + 1] + mesh.get_Dyvd()[i + 2]) * An
                    - (V[1].get_V(i + 1, j + 1) - V[1].get_V(i, j + 1)) / (mesh.get_Dyvu()[i] + mesh.get_Dyvd()[i + 1]) * As;
            R[i][j] = (-aux1 + aux2 / Re) / Vol;

        }
    }
    return R;   
}

std::vector<std::vector<double>> get_up(std::vector<Velocity>& V, std::vector<std::vector<double>>& Rnu, std::vector<std::vector<double>>& Rpu, const double& deltat)
{
    std::vector<std::vector<double>> up;
    int Nx, Ny;
    Nx=V[0].get_V()[0].size(); Ny=V[0].get_V().size();
    up.resize(Ny - 2, std::vector<double>(Nx - 2));
    for (int i = 0; i < Ny - 2; i++)
    {
        for (int j = 0; j < Nx -2; j++)
        {
            up[i][j] = V[0].get_V(i + 1, j + 1) + deltat * ( 3 / 2 * Rnu[i][j] - 1 / 2 * Rpu[i][j]);
        }
    }
    return up;
}

std::vector<std::vector<double>> get_vp(std::vector<Velocity>& V, std::vector<std::vector<double>>& Rnv, std::vector<std::vector<double>>& Rpv, const double& deltat)
{
    std::vector<std::vector<double>> vp;
    int Nx, Ny;
    Nx=V[1].get_V()[0].size(); Ny=V[1].get_V().size();
    vp.resize(Ny - 2, std::vector<double>(Nx - 2));
    for (int i = 0; i < Ny - 2; i++)
    {
        for (int j = 0; j < Nx -2; j++)
        {
            vp[i][j] = V[1].get_V(i + 1, j + 1) + deltat * ( 3 / 2 * Rnv[i][j] - 1 / 2 * Rpv[i][j]);
        }
    }
    return vp;
}