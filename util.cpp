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
    m = -1e7; 
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
    m = -1e7;
    for (int i = 0; i < Ny; i++)
    {    
        m = std::max(M[i], m);
    }
    return m;   
}

std::vector<int> get_maxpos(const std::vector<std::vector<double>>& M)
{
    int Nx, Ny;
    double Val(0);
    std::vector<int> pos;
    pos.resize(2,0);
    Ny = M.size(); Nx = M[0].size();
    for (int i = 0; i < Ny; i++)
    {
        for (int j = 0; j < Nx; j++)
        {
            if (M[i][j] > Val)
            {
                pos[0] = i;
                pos[1] = j;
                Val = M[i][j];
            }
        }
    }
    return pos;
}

double get_min(const std::vector<std::vector<double>>& M)
{
    double m;
    int Ny,Nx;
    Ny = M.size(); Nx = M[0].size();
    m = 1e7; 
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
    m = 1e7;
    for (int i = 1; i < Ny - 1; i++)
    {    
        m = std::min(M[i], m);
    }
    return m;   
}

std::vector<std::vector<double>> substract(std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B)
{
    std::vector<std::vector<double>> C;
    int Nx, Ny;
    Nx = A[0].size(); Ny = A.size();
    C.resize(Ny, std::vector<double>(Nx));
    for (int i = 0; i < Ny; i++)
    {
        for (int j = 0; j < Nx; j++)
        {
            C[i][j] = std::abs(A[i][j] - B[i][j]);
        }
    }
    return C;
}

double get_deltatc(std::vector<Velocity>& Vv, positions& mesh)
{
    double Dtc, M, N, NN;
    std::vector <std::vector<double>> Vm;
    Vm = vel_module(Vv); M = get_max(Vm);
    N = get_min(mesh.get_Dxpr());
    NN = get_min(mesh.get_Dypu());
    N = std::min(NN,N);
    Dtc = 0.35 * N / M;
    return Dtc;
}
double get_deltatd(const double& Re, positions& mesh)
{
    double Dtd, N,NN;
    N = get_min(mesh.get_Dxpr());
    NN = get_min(mesh.get_Dypu());
    N = std::min(NN,N);
    Dtd = 0.2 * Re * N * N;
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
    R.resize(Ny - 2, std::vector<double>(Nx) );
    for (int i = 0; i < Ny - 2; i++)
    {
        for (int j = 1; j < Nx - 1; j++)
        {
            Vol = (mesh.get_Dxur()[j] + mesh.get_Dxul()[j]) * (mesh.get_Dypu()[i + 1] + mesh.get_Dypd()[i + 1]);
            Ue = (V[0].get_V(i + 1, j + 1) + V[0].get_V(i + 1, j)) / 2.0;
            Uw = (V[0].get_V(i + 1, j) + V[0].get_V(i + 1, j - 1)) / 2.0;
            Vn = (V[1].get_V(i + 1, j) * mesh.get_Dxul()[j] + V[1].get_V(i + 1, j + 1) * mesh.get_Dxur()[j]) / (mesh.get_Dxul()[j] + mesh.get_Dxur()[j]);
            Vs = (V[1].get_V(i, j) * mesh.get_Dxul()[j] + V[1].get_V(i, j + 1) * mesh.get_Dxur()[j]) / (mesh.get_Dxul()[j] + mesh.get_Dxur()[j]);
            Ae = mesh.get_Dypu()[i + 1] + mesh.get_Dypd()[i + 1];
            Aw = mesh.get_Dypu()[i + 1] + mesh.get_Dypd()[i + 1];
            As = mesh.get_Dxul()[j] + mesh.get_Dxur()[j];
            An = As;
            aux1 = Ue * V[0].get_Vp(i + 1, j + 1) * Ae - Uw * V[0].get_Vp(i + 1, j) * Aw + Vn * V[0].get_Vpc(i + 1, j) * An - As * Vs * V[0].get_Vpc(i, j);
            aux2 = (V[0].get_V(i + 1, j + 1) - V[0].get_V(i + 1, j)) / (mesh.get_Dxur()[j] + mesh.get_Dxul()[j + 1]) * Ae
                    - (V[0].get_V(i + 1, j) - V[0].get_V(i + 1, j - 1)) / (mesh.get_Dxur()[j - 1] + mesh.get_Dxul()[j]) * Aw
                    + (V[0].get_V(i + 2, j) - V[0].get_V(i + 1, j)) / (mesh.get_Dypu()[i + 1] + mesh.get_Dypd()[i + 2]) * An
                    - (V[0].get_V(i + 1, j) - V[0].get_V(i, j)) / (mesh.get_Dypu()[i] + mesh.get_Dypd()[i + 1]) * As;
            
            R[i][j] = (-aux1 + aux2 / Re ) / Vol;
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
    R.resize(Ny, std::vector<double>(Nx - 2) );
    for (int j = 0; j < Nx - 2; j++)
    {
        for (int i = 1; i < Ny - 1; i++)
        {
            Vol = ( mesh.get_Dxpr()[j + 1] + mesh.get_Dxpl()[j + 1] ) * (mesh.get_Dyvu()[i] + mesh.get_Dyvd()[i]);
            Ue = (V[0].get_V(i, j + 1) * mesh.get_Dyvd()[i] + V[0].get_V(i + 1, j + 1) * mesh.get_Dyvu()[i]) / (mesh.get_Dyvd()[i] + mesh.get_Dyvu()[i]);
            Uw = (V[0].get_V(i, j) * mesh.get_Dyvd()[i] + V[0].get_V(i + 1, j) * mesh.get_Dyvu()[i]) / (mesh.get_Dyvd()[i] + mesh.get_Dyvu()[i]);            
            Ae = (mesh.get_Dyvu()[i] + mesh.get_Dyvd()[i]);
            Aw = (mesh.get_Dyvu()[i] + mesh.get_Dyvd()[i]);

            Vs = (V[1].get_V(i, j + 1) + V[1].get_V(i - 1, j + 1)) / 2.0;
            As = (mesh.get_Dxpl()[j + 1] + mesh.get_Dxpr()[j + 1]);

            An = (mesh.get_Dxpl()[j + 1] + mesh.get_Dxpr()[j + 1]);
            Vn = (V[1].get_V(i + 1, j + 1) + V[1].get_V(i, j + 1)) / 2.0;
            
            aux1 = Ue * V[1].get_Vpc(i, j + 1) * Ae - Uw * V[1].get_Vpc(i, j) * Aw + Vn * V[1].get_Vp(i + 1, j + 1) * An - Vs * V[1].get_Vp(i, j + 1) * As;
            aux2 = (V[1].get_V(i, j + 2) - V[1].get_V(i, j + 1)) / (mesh.get_Dxpr()[j + 1] + mesh.get_Dxpl()[j + 2]) * Ae
                    - (V[1].get_V(i, j + 1) - V[1].get_V(i, j)) / (mesh.get_Dxpr()[j] + mesh.get_Dxpl()[j + 1]) * Aw
                    + (V[1].get_V(i + 1, j + 1) - V[1].get_V(i, j + 1)) / (mesh.get_Dyvu()[i] + mesh.get_Dyvd()[i + 1]) * An
                    - (V[1].get_V(i, j + 1) - V[1].get_V(i - 1, j + 1)) / (mesh.get_Dyvu()[i - 1] + mesh.get_Dyvd()[i]) * As;
            R[i][j] = (-aux1 + aux2 / Re ) / Vol;
            
        }
    }
    return R;   
}

std::vector<std::vector<double>> get_up(std::vector<Velocity>& V, std::vector<std::vector<double>>& Rnu, std::vector<std::vector<double>>& Rpu, const double& deltat)
{
    std::vector<std::vector<double>> up;
    int Nx, Ny;
    Nx=V[0].get_V()[0].size(); Ny=V[0].get_V().size();
    up.resize(Ny - 2, std::vector<double>(Nx));
    for (int i = 0; i < Ny - 2; i++)
    {
        for (int j = 1; j < Nx - 1; j++)
        {
            up[i][j] = V[0].get_V(i + 1, j) + deltat * ( 3.0 / 2.0 * Rnu[i][j] - 1.0 / 2.0 * Rpu[i][j]);

        }
    }
    return up;
}

std::vector<std::vector<double>> get_vp(std::vector<Velocity>& V, std::vector<std::vector<double>>& Rnv, std::vector<std::vector<double>>& Rpv, const double& deltat)
{
    std::vector<std::vector<double>> vp;
    int Nx, Ny;
    Nx=V[1].get_V()[0].size(); Ny=V[1].get_V().size();
    vp.resize(Ny, std::vector<double>(Nx - 2));
    for (int i = 1; i < Ny - 1; i++)
    {
        for (int j = 0; j < Nx - 2; j++)
        {
            vp[i][j] = V[1].get_V(i, j + 1) + deltat * ( 3.0 / 2.0 * Rnv[i][j] - 1.0 / 2.0 * Rpv[i][j]);

            
        }
    }
    return vp;
}