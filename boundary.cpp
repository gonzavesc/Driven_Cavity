#include <iostream>
#include <vector>
#include <fstream>
#include "positions.hpp"
#include "import.hpp"
#include "velocity.hpp"
#include "boundary.hpp"

void set_boundary(std::vector<Velocity>& V, Pressure& P)
{
    int filx, colx, i, j;
    filx = V[0].get_V().size();
    colx= V[0].get_V()[0].size();
    i = filx - 1;
    for (j = 0; j < colx; j++)
    {
        V[0].set_V(i,j,1);
    }
}