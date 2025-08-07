#ifndef CONSTANTS_GRID_HPP
#define CONSTANTS_GRID_HPP

#include "constants.hpp"

#ifdef GRID_REFINE
constexpr int GRID_RATIO = 2;
constexpr int PATCH = 2;
constexpr int GRID_OVERLAP = 1;

constexpr int NX_COARSE_TOTAL = NX;
constexpr int NY_COARSE_TOTAL = NY;
constexpr int NX_FINE_TOTAL = GRID_RATIO * NX - 1;
constexpr int NY_FINE_TOTAL = GRID_RATIO * NY - 1;

constexpr int XSPLIT = NX_COARSE_TOTAL - PATCH;

// Coarse grid size
constexpr int NX_COARSE = XSPLIT + GRID_OVERLAP;
constexpr int NY_COARSE = NY_COARSE_TOTAL;
// Fine grid size
constexpr int NX_FINE = GRID_RATIO * PATCH + 1;
constexpr int NY_FINE = NY_FINE_TOTAL;

// Grid coordinate limits
constexpr int XC_START = 1;
constexpr int XC_END = NX_COARSE;
constexpr int YC_START = 1;
constexpr int YC_END = NY;

constexpr dfloat NU_COARSE = U0 * (NX_COARSE_TOTAL - 1) / RE;
constexpr dfloat TAU_COARSE = 0.5 + 3.0 * NU_COARSE;
constexpr dfloat OMEGA_COARSE = 1.0 / TAU_COARSE;

constexpr dfloat NU_FINE = U0 * (NX_FINE_TOTAL - 1) / RE;
constexpr dfloat TAU_FINE = 0.5 + 3.0 * NU_FINE;
constexpr dfloat OMEGA_FINE = 1.0 / TAU_FINE;

#endif



#endif