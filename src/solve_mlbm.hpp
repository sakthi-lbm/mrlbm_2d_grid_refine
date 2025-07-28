#ifndef SOLVE_MLBM_HPP
#define SOLVE_MLBM_HPP

#include<iostream>

#include "var.hpp"
#include "global_struct.hpp"
#include COLREC
#include CASE_BOUNDARY

void MomCollisionStreaming(nodeVar h_fMom);
void calculate_moments(nodeVar h_fMom);

#endif