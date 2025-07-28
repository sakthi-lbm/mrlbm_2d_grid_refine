#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include<iostream>
#include "../../var.hpp"

constexpr dfloat delx = 1.0;
constexpr dfloat dely = 1.0;
constexpr int N = 64;
constexpr int NX = N;
constexpr int NY = N;

constexpr dfloat RE = 5000;
constexpr dfloat RHO_0 = 1.0;
constexpr dfloat UX_0 = 0.0;
constexpr dfloat UY_0 = 0.0;
constexpr dfloat U0 = 0.1;
constexpr dfloat NU = U0 * (NX - 1) / RE;
constexpr dfloat TAU = 0.5 + 3.0 * NU;
constexpr dfloat OMEGA = 1.0 / TAU;

constexpr int MAX_ITER  = 100000;
constexpr int MACR_SAVE = 10000;
constexpr int RESTART_SAVE = 10000;

// #define WITH_CORNERS









#endif