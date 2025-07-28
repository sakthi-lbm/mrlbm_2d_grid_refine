#include <iostream>

#include "initialize_lbm.hpp"

void initialize_moments(dfloat *rho, dfloat *ux, dfloat *uy, dfloat *mxx, dfloat *myy, dfloat *mxy)
{
    *rho = RHO_0;
    *ux = UX_0;
    *uy = UY_0;

    dfloat pop_eq[Q];
    for (size_t i = 0; i < Q; i++)
    {
        dfloat Hxx = cx[i] * cx[i] - cs2;
        dfloat Hyy = cy[i] * cy[i] - cs2;
        dfloat Hxy = cx[i] * cy[i];
        pop_eq[i] = w[i] * (*rho) * (1.0 + 3.0 * ((*ux) * cx[i] + (*uy) * cy[i]) + 4.5 * ((*ux) * (*ux) * Hxx + (*uy) * (*uy) * Hyy) + 9 * (*ux) * (*uy) * Hxy);
    }
    dfloat inv_rho = 1.0 / (*rho);
    *mxx = (pop_eq[1] + pop_eq[3] + pop_eq[5] + pop_eq[6] + pop_eq[7] + pop_eq[8]) * inv_rho - cs2;
    *myy = (pop_eq[2] + pop_eq[4] + pop_eq[5] + pop_eq[6] + pop_eq[7] + pop_eq[8]) * inv_rho - cs2;
    *mxy = (pop_eq[5] - pop_eq[6] + pop_eq[7] - pop_eq[8]) * inv_rho;
}

