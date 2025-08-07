#ifndef VAR_HPP
#define VAR_HPP
#include <cmath>
#include <chrono>

typedef float dfloat;
typedef std::chrono::high_resolution_clock::time_point timestep;

#define STR_IMPL(x) #x
#define STR(x) STR_IMPL(x)

#define BC_PROBLEM ldc
#define REG_ORDER second_order

#define CASE_DIRECTORY cases
#define COLREC_DIRECTORY colrec
#define CASE_CONSTANTS STR(CASE_DIRECTORY/BC_PROBLEM/constants.hpp)
#define CASE_CONSTANTS_GRID STR(CASE_DIRECTORY/BC_PROBLEM/constants_grid.hpp)
#define CASE_OUTPUTS STR(CASE_DIRECTORY/BC_PROBLEM/outputs.hpp)
#define COLREC STR(COLREC_DIRECTORY/REG_ORDER/collision_and_reconstruction.hpp)
#define CASE_BOUNDARY STR(CASE_DIRECTORY/BC_PROBLEM/boundaries.hpp)
#define CASE_BOUNDARY_GRID STR(CASE_DIRECTORY/BC_PROBLEM/boundaries_grid.hpp)

#include CASE_CONSTANTS
#include CASE_CONSTANTS_GRID
#include CASE_OUTPUTS

#include "index.hpp"
#include "definitions.hpp"
#include "nodeTypeMap.hpp"


#endif