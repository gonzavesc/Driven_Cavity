#include <iostream>
#include <fstream>
#include <vector>
#include "import.hpp"
#include "positions.hpp"

positions::positions(const double& a)
{
    int n;
    dx = a;
    n = 1 / dx;
    for (int j = 0; j <= n; j++)
    {
        Xp.push_back(j * dx);
    }
}