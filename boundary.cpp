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
    for (i = 0; i < filx; i++)
    {
        V[0].set_V(i,0,0);
        V[0].set_V(i,colx - 1,0);
    }
    i = filx - 1;
    for (j = 0; j < colx; j++)
    {
        V[0].set_V(i,j,1);
        V[0].set_V(0,j,0);
    }
    filx = V[1].get_V().size();
    colx= V[1].get_V()[0].size();

    for (j = 0; j < colx; j++)
    {
        V[1].set_V(0,j,0);
        V[1].set_V(filx -1,j,0);
    }
    for (i = 0; i < filx; i++)
    {
        V[1].set_V(i,0,0);
        V[1].set_V(i,colx - 1,0);
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

