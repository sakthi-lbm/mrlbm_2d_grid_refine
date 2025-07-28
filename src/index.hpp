#ifndef INDEX_HPP
#define INDEX_HPP

#include "var.hpp"

#define IDX(x, y) (x + y * NX)
#define FIDX(x, y, q) ((q * NX * NY) + x + (y * NX))


#endif