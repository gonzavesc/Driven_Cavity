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
std::vector<std::vector<double>> Pressure::get_P()
{
    return P;
}