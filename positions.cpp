#include <iostream>
#include <fstream>
#include <vector>
#include "import.hpp"
#include "positions.hpp"

positions::positions(const double& a, const double& b)
{
    int n,m;
    double j;
    dx = a;
    dy = b;

    n = 1 / dx;
    m = 1/ dy;
    Xu.push_back(0); Xp.push_back(0);
    Yv.push_back(0); Yp.push_back(0);
    for (j = 0; j < n; j++)
    {
        Xp.push_back(j * dx);
        Xu.push_back((j + 0.5) * dx);
        
    }
    Xp.push_back(n * dx); Xu.push_back(n * dx);
    for (j = 0; j < m; j++)
    {
        Yp.push_back(j * dy);
        Yv.push_back((j + 0.5) * dy);
    }
    Xp.push_back(m * dy); Xu.push_back(m * dy);
}
std::vector <double> positions::get_Xu()
{
    return Xu;
}

std::vector <double> positions::get_Yv()
{
    return Yv;
}
std::vector <double> positions::get_Yp()
{
    return Yp;
}
std::vector <double> positions::get_Xp()
{
    return Xp;
}