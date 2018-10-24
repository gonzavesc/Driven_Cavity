#include <iostream>
#include <fstream>
#include <vector>
#include "import.hpp"
#include "positions.hpp"

positions::positions(const double& a, const doulbe& b)
{
    int n;
    dx = a;
    dy = b;

    n = 1 / dx;
    m = 1/ dy;
    Xu.push_back(0);
    for (int j = 0; j < n; j++)
    {
        Xp.push_back(j * dx);
        Xu.push_back((j + 1/2) * dx);
    }
    Xp.push_back(n * dx); Xu.push_back(n * dx);
    for (j = 0; j < m; j++)
    {
        Yp.push_back(j * dx);
        Yv.push_back((j + 1/2) * dx);
    }
    Xp.push_back(m * dx); Xu.push_back(m * dx);
}
