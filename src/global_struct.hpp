#ifndef GLOBAL_STRUCT_HPP
#define GLOBAL_STRUCT_HPP

#include "var.hpp"

struct nodeVar
{
    unsigned int *nodeType;
    dfloat *rho;
    dfloat *ux;
    dfloat *uy;
    dfloat *mxx;
    dfloat *myy;
    dfloat *mxy;
    dfloat *f_in;
    dfloat *f_out;
};


#endif