#ifndef INDEX_HPP
#define INDEX_HPP

#include "var.hpp"

inline int IDX(int x, int y)
{
    return x + (y * NX);
}

inline int FIDX(int x, int y, int q)
{
    return (q * NX * NY) + x + (y * NX);
}

#endif