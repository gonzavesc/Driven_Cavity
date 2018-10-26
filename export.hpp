#include <iostream>
#include <vector>
#include <fstream>
#include "positions.hpp"
#include "import.hpp"
#include "velocity.hpp"
#include "boundary.hpp"

#ifndef INCLUDE_EXP
#define INCLUDE_EXP
void exportarMatriu(const std::vector<std::vector<double>>& phi);
#endif