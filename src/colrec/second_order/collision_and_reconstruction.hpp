#ifndef COLLISION_AND_RECONSTRUCTION_HPP
#define COLLISION_AND_RECONSTRUCTION_HPP

#include <iostream>

#include "../../var.hpp"

inline void mom_collision(dfloat ux, dfloat uy, dfloat *mxx, dfloat *myy, dfloat *mxy)
{
    const dfloat omegaVar = OMEGA;
    const dfloat omega_m1 = 1.0 - omegaVar;

    *mxx = omega_m1 * (*mxx) + omegaVar * ux * ux;
    *myy = omega_m1 * (*myy) + omegaVar * uy * uy;
    *mxy = omega_m1 * (*mxy) + omegaVar * ux * uy;
}

inline void pop_reconstruction(dfloat rho, dfloat ux, dfloat uy, dfloat mxx, dfloat myy, dfloat mxy, dfloat (& pop)[Q])
{

    rho = (rho)*F_M_0_SCALE;
    ux = ux * F_M_I_SCALE;
    uy = uy * F_M_I_SCALE;
    mxx = mxx * F_M_II_SCALE;
    myy = myy * F_M_II_SCALE;
    mxy = mxy * F_M_IJ_SCALE;

    dfloat pics2 = 1 - cs2 * (mxx + myy);

    dfloat multiplyTerm = W0 * (rho);
    pop[0] = multiplyTerm * (pics2);

    multiplyTerm = W1 * (rho);
    pop[1] = multiplyTerm * (pics2 + ux + mxx);
    pop[2] = multiplyTerm * (pics2 + uy + myy);
    pop[3] = multiplyTerm * (pics2 - ux + mxx);
    pop[4] = multiplyTerm * (pics2 - uy + myy);

    multiplyTerm = W2 * (rho);
    pop[5] = multiplyTerm * (pics2 + ux + uy + mxx + myy + mxy);
    pop[6] = multiplyTerm * (pics2 - ux + uy + mxx + myy - mxy);
    pop[7] = multiplyTerm * (pics2 - ux - uy + mxx + myy + mxy);
    pop[8] = multiplyTerm * (pics2 + ux - uy + mxx + myy - mxy);
}

#endif