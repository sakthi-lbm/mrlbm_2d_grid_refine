#ifndef SAVE_DATA_HPP
#define SAVE_DATA_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream> // std::cout, std::fixed
#include <iomanip>  // std::setprecision

#include "var.hpp"
#include "global_struct.hpp"

void write_grid();

void write_solution(nodeVar h_fMom, size_t iter);






#endif