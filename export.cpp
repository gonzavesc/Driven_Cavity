#include <iostream>
#include <vector>
#include <fstream>
#include "positions.hpp"
#include "import.hpp"
#include "velocity.hpp"
#include "boundary.hpp"
#include "export.hpp"

void exportarMatriu(const std::vector<std::vector<double>>& phi)
{
    int i, jj, Nx, Ny;
    std::ofstream output;
    output.precision(17);
    output.open("Matrix.dat");
    Ny = phi.size() - 1;
    Nx = phi[0].size() - 1;
    for (i = 0; i <= Ny; i++)
    {
        for (jj = 0; jj <= Nx - 1; jj++)
        {
             output << phi[i][jj] << ", " ;
        }
        output << std::scientific << phi[i][Nx] << std::endl;
    }
    output.close();
}