#include <iostream>
#include <vector>
#include <fstream>
#include "positions.hpp"
#include "import.hpp"
#include "velocity.hpp"

#ifndef INCLUDE_BND
#define INCLUDE_BND

void set_boundary(std::vector<Velocity>& V, Pressure& P);
double get_max(const std::vector<std::vector<double>>& M);
double get_max(const std::vector<double>& M);
double get_min(const std::vector<std::vector<double>>& M);
double get_min(const std::vector<double>& M);
#endif