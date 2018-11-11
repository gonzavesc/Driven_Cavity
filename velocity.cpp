#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
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
double Velocity::get_V(const int& i, const int& j)
{
    return V[i][j];
    
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
    if (Nxv < Nx)
    {
        for(i = 0; i < Ny; i++)
        {
            for (j = 1; j < Nx - 1; j++)
            {
                ve = Vv.get_V(i,j);
                vw = Vv.get_V(i, j - 1);
                if(vw + ve >= 0)
                {
                    Vp[i][j] = vw;
                }
                else
                {
                    Vp[i][j] = ve;
                }
            }
            j = 0;
            Vp[i][j] = Vv.get_V(i,j);
            j = Nx - 1;
            Vp[i][j] = Vv.get_V(i,j - 1);
        }
    }
    else
    {
        for(j = 0; j < Nx; j++)
        {
            for (i = 1; i < Ny - 1; i++)
            {
                ve = Vv.get_V(i,j);
                vw = Vv.get_V(i - 1,j);
                if(vw + ve >= 0)
                {
                    Vp[i][j] = vw;
                }
                else
                {
                    Vp[i][j] = ve;
                }
            }
            i = 0; Vp[i][j] = Vv.get_V(i,j);
            i = Ny - 1; Vp[i][j] = Vv.get_V(i - 1,j); 
        }   
        
    }
}

void Velocity::set_Vpc(positions& mesh, Velocity& V ,std::vector<Velocity>& Vv)
{
    int Nx, Ny, Nxv, i, j;
    double ve;
    Nx = mesh.get_Xp().size();
    Ny = mesh.get_Yp().size();
    Nxv = V.get_V()[0].size();
    Vpc.resize(Ny - 1, std::vector<double>(Nx - 1));
    if (Nxv < Nx)
    {
        
        for (j = 0; j < Nx - 1; j++)
        {
            for (i = 1; i < Ny - 2; i++)
            {
                ve = (Vv[1].get_V(i,j) + Vv[1].get_V(i, j + 1));
                if (ve >= 0)
                {
                    Vpc[i][j] = Vv[0].get_V(i, j);
                }
                else
                {
                    Vpc[i][j] = Vv[0].get_V(i + 1, j);
                }
            }
            i = 0;
            Vpc[i][j] = Vv[0].get_V(i, j);
            i = Ny - 2;
            Vpc[i][j] = Vv[0].get_V(i + 1, j);
        }
    }
    else
    {
        for (i = 0; i < Ny - 1; i++)
        {
            for (j = 1; j < Nx - 2; j++)
            {
                ve = (Vv[0].get_V(i, j) + Vv[0].get_V(i + 1, j));
                if ( ve >= 0)
                {
                    Vpc[i][j] = Vv[1].get_V(i, j);
                }
                else
                {
                    Vpc[i][j] = Vv[1].get_V(i, j + 1);
                }
            }
            j = 0;
            Vpc[i][j] = Vv[1].get_V(i, j);
            j = Nx - 2;
            Vpc[i][j] = Vv[1].get_V(i, j + 1);
        }

    }
}
std::vector<std::vector<double>> Velocity::get_Vp()
{
    return Vp;
}

double Velocity::get_Vp(const int& i, const int& j)
{
    return Vp[i][j];
}

std::vector<std::vector<double>> Velocity::get_Vpc()
{
    return Vpc;
}

double Velocity::get_Vpc(const int& i, const int& j)
{
    return Vpc[i][j];
}

std::vector<std::vector<double>> vel_module(std::vector<Velocity>& Vv)
{
    int Nx,Ny, i, j;
    std::vector<std::vector<double>> Vmag;
    Ny = Vv[0].get_Vp().size(); Nx = Vv[0].get_Vp()[0].size();
    Vmag.resize(Ny, std::vector<double> (Nx));
    for (i = 0; i < Ny; i++)
    {
        for (j = 0; j < Nx; j++)
        {
            Vmag[i][j] = sqrt( Vv[0].get_Vp()[i][j] * Vv[0].get_Vp()[i][j] + Vv[1].get_Vp()[i][j] * Vv[1].get_Vp()[i][j] );
        }
    }
    return Vmag;
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