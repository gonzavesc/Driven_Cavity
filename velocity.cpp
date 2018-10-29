#include <iostream>
#include <vector>
#include <fstream>
#include "positions.hpp"
#include "import.hpp"
#include "velocity.hpp"

Velocity::Velocity (const int& row, const int& col)
{
    V.resize(row, std::vector<double>(col));
    for (int i = 0; i < row; i++ )
    {
        for (int j = 0; j < col; j++)
        {
            V[i][j] = 0;
        }
    }
}
std::vector<std::vector<double>> Velocity::get_V()
{
    return V;
}
void Velocity::set_V(const int& i, const int& j, const double& u)
{
    V[i][j] = u;
}
void Velocity::set_Vp(positions& mesh, Velocity& Vv)
{
    int Nx, Ny, Nxv, i, j;
    double vw, ve;
    Nx = mesh.get_Xp().size();
    Ny = mesh.get_Yp().size();
    Nxv = Vv.get_V()[0].size();
    Vp.resize(Ny, std::vector<double>(Nx));
    if (Nxv > Nx)
    {
        for(i = 0; i < Ny; i++)
        {
            for (j = 1; j < Nx - 1; j++)
            {
                ve = Vv.get_V()[i][j+1];
                vw = Vv.get_V()[i][j];
                if(vw + ve >= 0)
                {
                    Vp[i][j] = vw;
                }
                else
                {
                    Vp[i][j] = ve;
                }
            }
            j = 0; Vp[i][j] = Vv.get_V()[i][j];
            j = Nx -1; Vp[i][j] = Vv.get_V()[i][j];
        }   

    }
    else
    {
        for(j = 0; j < Nx; j++)
        {
            for (i = 1; i < Ny - 1; i++)
            {
                ve = Vv.get_V()[i+1][j];
                vw = Vv.get_V()[i][j];
                if(vw + ve >= 0)
                {
                    Vp[i][j] = vw;
                }
                else
                {
                    Vp[i][j] = ve;
                }
            }
            i = 0; Vp[i][j] = Vv.get_V()[i][j];
            i = Ny - 1; Vp[i][j] = Vv.get_V()[i][j]; 
        }   
    }
}
std::vector<std::vector<double>> Velocity::get_Vp()
{
    return Vp;
}
Pressure::Pressure(const int& row, const int& col)
{
    P.resize(row, std::vector<double>(col));
    for (int i = 0; i < row; i++ )
    {
        for (int j = 0; j < col; j++)
        {
            P[i][j] = 0;
        }
    }
}
double Pressure::get_P(const int& i, const int& j)
{
    return P[i][j];
}
void Pressure::set_P(const int& i,const int& j, const double p)
{
    P[i][j] = p;
}
std::vector<std::vector<double>> Pressure::get_P()
{
    return P;
}