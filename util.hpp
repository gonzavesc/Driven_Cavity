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
std::vector<int> get_maxpos(const std::vector<std::vector<double>>& M);
double get_max(const std::vector<double>& M);
double get_min(const std::vector<std::vector<double>>& M);
double get_min(const std::vector<double>& M);
double get_deltatc(std::vector<Velocity>& Vv, positions& mesh);
double get_deltatd(const double& Re, positions& mesh);
std::vector<std::vector<double>> substract(std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B);
std::vector<std::vector<double>> get_Ru(std::vector<Velocity>& V, positions& mesh, const double& Re);
std::vector<std::vector<double>> get_Rv(std::vector<Velocity>& V, positions& mesh, const double& Re);
std::vector<std::vector<double>> get_up(std::vector<Velocity>& V, std::vector<std::vector<double>>& Rnu, std::vector<std::vector<double>>& Rpu, const double& deltat);
std::vector<std::vector<double>> get_vp(std::vector<Velocity>& V, std::vector<std::vector<double>>& Rnv, std::vector<std::vector<double>>& Rpv, const double& deltat);
#endif