#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "positions.hpp"
#include "import.hpp"
#include "velocity.hpp"
#include "boundary.hpp"
#include "export.hpp"

#ifndef INCLUDE_UTIL
#define INCLUDE_UTIL
void copy_matrix(std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B);
double get_max(const std::vector<std::vector<double>>& M);
double get_max(const std::vector<double>& M);
double get_min(const std::vector<std::vector<double>>& M);
double get_min(const std::vector<double>& M);
double get_deltatc(std::vector<Velocity>& Vv, positions& mesh);
double get_deltatd(const double& Re, positions& mesh);
std::vector<std::vector<double>> get_Ru(std::vector<Velocity>& V, positions& mesh, const double& Re);

#endif