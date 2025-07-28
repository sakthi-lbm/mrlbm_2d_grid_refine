#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include "var.hpp"

constexpr dfloat PI = 3.14159265358979323846;

// Lattice Velocity sets
constexpr unsigned char Q = 9;
constexpr dfloat W0 = 4.0 / 9.0;
constexpr dfloat W1 = 1.0 / 9.0;
constexpr dfloat W2 = 1.0 / 36.0;

constexpr dfloat w[Q] = {W0,
                         W1, W1, W1, W1,
                         W2, W2, W2, W2};

constexpr dfloat as2 = 3.0;
constexpr dfloat cs2 = 1.0 / 3.0;

constexpr dfloat cx[Q] = {0, 1, 0, -1, 0, 1, -1, -1, 1};
constexpr dfloat cy[Q] = {0, 0, 1, 0, -1, 1, 1, -1, -1};

constexpr dfloat F_M_0_SCALE = 1.0;
constexpr dfloat F_M_I_SCALE = as2;
constexpr dfloat F_M_II_SCALE = as2 * as2 / 2;
constexpr dfloat F_M_IJ_SCALE = as2 * as2;

const size_t NUM_NODES = NX * NY;
const size_t NUM_NODES_Q = NUM_NODES * Q;

const size_t MEM_SIZE_NODES = sizeof(dfloat) * NUM_NODES;
const size_t MEM_SIZE_NODETYPE = sizeof(unsigned int) * NUM_NODES;
const size_t MEM_SIZE_NODES_Q = sizeof(dfloat) * NUM_NODES_Q;

#endif