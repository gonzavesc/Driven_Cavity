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