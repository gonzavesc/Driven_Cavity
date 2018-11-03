#include <iostream>
#include <vector>
#include <fstream>
#include "positions.hpp"
#include "import.hpp"
#include "velocity.hpp"

#ifndef INCLUDE_BND
#define INCLUDE_BND

void set_boundary(std::vector<Velocity>& V, Pressure& P);
void set_boundary(std::vector<std::vector<double>>& up, std::vector<std::vector<double>>& vp);
#endif