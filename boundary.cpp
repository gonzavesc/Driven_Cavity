#include <iostream>
#include <vector>
#include <fstream>
#include "positions.hpp"
#include "import.hpp"
#include "velocity.hpp"
#include "boundary.hpp"

void set_boundary(std::vector<Velocity>& V, Pressure& P)
{
    int filx, colx, filp, colp, i, j;
    filx = V[0].get_V().size();
    colx= V[0].get_V()[0].size();
    i = filx - 1;
    for (j = 0; j < colx; j++)
    {
        V[0].set_V(i,j,1);
    }
    filp = P.get_P().size();
    colp = P.get_P()[0].size();
    for (j = 0; j < colp; j++)
    {
        P.set_P(0, j, P.get_P(1 , j));
        P.set_P(filp-1,j,P.get_P(filp - 2,j));
    }
    for (i = 0; i < filp; i++)
    {
        P.set_P(i,0,P.get_P(i,1));
        P.set_P(i,colp-1,P.get_P(i,colp - 2));
    }
}