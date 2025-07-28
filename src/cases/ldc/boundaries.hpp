#ifndef BOUNDARIES_HPP
#define BOUNDARIES_HPP

#include "../../var.hpp"

inline unsigned int boundary_definitions(const size_t x, const size_t y)
{
    if (x == 0 && y == 0)
    {
#ifdef WITH_CORNERS
        return SOUTH_WEST;
#else
        return SOUTH;
#endif
    }
    else if (x == 0 && y == (NY - 1))
    {
#ifdef WITH_CORNERS
        return NORTH_WEST;
#else
        return NORTH;
#endif
    }
    else if (x == (NX - 1) && y == 0)
    {
#ifdef WITH_CORNERS
        return SOUTH_EAST;
#else
        return SOUTH;
#endif
    }
    else if (x == (NX - 1) && y == (NY - 1))
    {
#ifdef WITH_CORNERS
        return NORTH_EAST;
#else
        return NORTH;
#endif
    }
    else if (x == 0)
    {
        return WEST;
    }
    else if (x == (NX - 1))
    {
        return EAST;
    }
    else if (y == 0)
    {
        return SOUTH;
    }
    else if (y == (NY - 1))
    {
        return NORTH;
    }
    else
    {
        return BULK;
    }
}

inline void boundary_condition(unsigned int nodeType, dfloat (&pop)[Q], dfloat *rhoVar, dfloat *ux, dfloat *uy, dfloat *mxx, dfloat *myy, dfloat *mxy)
{
    switch (nodeType)
    {
    case NORTH:
    {
        const dfloat rhoI = pop[0] + pop[1] + pop[2] + pop[3] + pop[5] + pop[6];
        const dfloat inv_rhoI = 1.0 / rhoI;
        const dfloat mxxI = (pop[1] + pop[3] + pop[5] + pop[6]) * inv_rhoI - cs2;
        const dfloat myyI = (pop[2] + pop[5] + pop[6]) * inv_rhoI - cs2;
        const dfloat mxyI = (pop[5] - pop[6]) * inv_rhoI;

        *ux = U0;
        *uy = 0.0;

        *rhoVar = 3.0 * rhoI * (4.0 - 3.0 * (OMEGA - 1.0) * myyI) / (9.0 + OMEGA);

        *mxx = 6.0 * rhoI * mxxI / (5.0 * (*rhoVar));
        *myy = (9.0 * rhoI * myyI + (*rhoVar)) / (6.0 * (*rhoVar));
        *mxy = (6.0 * rhoI * mxyI - U0 * (*rhoVar)) / (3.0 * (*rhoVar));

        break;
    }
    case SOUTH:
    {
        const dfloat rhoI = pop[0] + pop[1] + pop[3] + pop[4] + pop[7] + pop[8];
        const dfloat inv_rhoI = 1.0 / rhoI;
        const dfloat mxxI = (pop[1] + pop[3] + pop[7] + pop[8]) * inv_rhoI - cs2;
        const dfloat myyI = (pop[4] + pop[7] + pop[8]) * inv_rhoI - cs2;
        const dfloat mxyI = (pop[7] - pop[8]) * inv_rhoI;

        *ux = 0.0;
        *uy = 0.0;

        *rhoVar = 3.0 * rhoI * (4.0 - 3.0 * (OMEGA - 1.0) * myyI) / (9.0 + OMEGA);

        *mxx = 6.0 * rhoI * mxxI / (5.0 * (*rhoVar));
        *myy = (*rhoVar + 9.0 * rhoI * myyI) / (6.0 * (*rhoVar));
        *mxy = 2.0 * rhoI * mxyI / (*rhoVar);

        break;
    }
    case WEST:
    {
        const dfloat rhoI = pop[0] + pop[2] + pop[3] + pop[4] + pop[6] + pop[7];
        const dfloat inv_rhoI = 1.0 / rhoI;
        const dfloat mxxI = (pop[3] + pop[6] + pop[7]) * inv_rhoI - cs2;
        const dfloat myyI = (pop[2] + pop[4] + pop[6] + pop[7]) * inv_rhoI - cs2;
        const dfloat mxyI = (pop[7] - pop[6]) * inv_rhoI;

        *ux = 0.0;
        *uy = 0.0;

        *rhoVar = 3.0 * rhoI * (4.0 - 3.0 * (OMEGA - 1.0) * mxxI) / (9.0 + OMEGA);

        *mxx = (9.0 * rhoI * mxxI + (*rhoVar)) / (6.0 * (*rhoVar));
        *myy = (6.0 * rhoI * myyI) / (5.0 * (*rhoVar));
        *mxy = 2.0 * rhoI * mxyI / (*rhoVar);

        break;
    }
    case EAST:
    {
        const dfloat rhoI = pop[0] + pop[1] + pop[2] + pop[4] + pop[5] + pop[8];
        const dfloat inv_rhoI = 1.0 / rhoI;
        const dfloat mxxI = (pop[1] + pop[5] + pop[8]) * inv_rhoI - cs2;
        const dfloat myyI = (pop[2] + pop[4] + pop[5] + pop[8]) * inv_rhoI - cs2;
        const dfloat mxyI = (pop[5] - pop[8]) * inv_rhoI;

        *ux = 0.0;
        *uy = 0.0;

        *rhoVar = 3.0 * rhoI * (4.0 - 3.0 * (OMEGA - 1.0) * mxxI) / (9.0 + OMEGA);

        *mxx = (9.0 * rhoI * mxxI + (*rhoVar)) / (6.0 * (*rhoVar));
        *myy = (6.0 * rhoI * myyI) / (5.0 * (*rhoVar));
        *mxy = 2.0 * rhoI * mxyI / (*rhoVar);

        break;
    }
    case SOUTH_WEST:
    {
        const dfloat rhoI = pop[0] + pop[3] + pop[4] + pop[7];
        const dfloat inv_rhoI = 1.0 / rhoI;
        const dfloat mxxI = (pop[3] + pop[7]) * inv_rhoI - cs2;
        const dfloat myyI = (pop[4] + pop[7]) * inv_rhoI - cs2;
        const dfloat mxyI = pop[7] * inv_rhoI;

        *ux = 0.0;
        *uy = 0.0;

        *rhoVar = -12.0 * rhoI * (-3.0 - 3.0 * myyI + 3.0 * (OMEGA - 1.0) * mxxI - 7.0 * (OMEGA - 1.0) * mxyI + 3.0 * OMEGA * myyI) / (16.0 + 9.0 * OMEGA);

        *mxx = 2.0 * (9.0 * rhoI * mxxI - 6.0 * mxyI * rhoI + (*rhoVar)) / (9.0 * (*rhoVar));
        *myy = -2.0 * (6.0 * rhoI * mxyI - 9.0 * myyI * rhoI - (*rhoVar)) / (9.0 * (*rhoVar));
        *mxy = -(18.0 * rhoI * mxxI - 132.0 * mxyI * rhoI + 18.0 * rhoI * myyI + 7.0 * (*rhoVar)) / (27.0 * (*rhoVar));

        break;
    }
    case SOUTH_EAST:
    {
        const dfloat rhoI = pop[0] + pop[1] + pop[4] + pop[8];
        const dfloat inv_rhoI = 1.0 / rhoI;
        const dfloat mxxI = (pop[1] + pop[8]) * inv_rhoI - cs2;
        const dfloat myyI = (pop[4] + pop[8]) * inv_rhoI - cs2;
        const dfloat mxyI = -pop[8] * inv_rhoI;

        *ux = 0.0;
        *uy = 0.0;

        *rhoVar = -12.0 * rhoI * (-3.0 - 3.0 * myyI + 3.0 * (OMEGA - 1.0) * mxxI + 7.0 * (OMEGA - 1.0) * mxyI + 3.0 * OMEGA * myyI) / (16.0 + 9.0 * OMEGA);

        *mxx = 2.0 * (9.0 * rhoI * mxxI + 6.0 * mxyI * rhoI + (*rhoVar)) / (9.0 * (*rhoVar));
        *myy = 2.0 * (6.0 * rhoI * mxyI + 9.0 * myyI * rhoI + (*rhoVar)) / (9.0 * (*rhoVar));
        *mxy = -(-18.0 * rhoI * mxxI - 132.0 * mxyI * rhoI - 18.0 * rhoI * myyI - 7.0 * (*rhoVar)) / (27.0 * (*rhoVar));

        break;
    }
    case NORTH_WEST:
    {
        const dfloat rhoI = pop[0] + pop[2] + pop[3] + pop[6];
        const dfloat inv_rhoI = 1.0 / rhoI;
        const dfloat mxxI = (pop[3] + pop[6]) * inv_rhoI - cs2;
        const dfloat myyI = (pop[2] + pop[6]) * inv_rhoI - cs2;
        const dfloat mxyI = -pop[6] * inv_rhoI;

        *ux = U0;
        *uy = 0.0;

        *rhoVar = 12.0 * rhoI * (-3.0 - 3.0 * myyI + 3.0 * (OMEGA - 1.0) * mxxI + 7.0 * (OMEGA - 1.0) * mxyI + 3.0 * OMEGA * myyI) / (-2.0 * (8.0 + 7.0 * U0) + OMEGA * (-9.0 - U0 + 15.0 * U0 * U0));

        *mxx = 2.0 * (9.0 * rhoI * mxxI + 6.0 * mxyI * rhoI + (*rhoVar) + 2.0 * U0 * (*rhoVar)) / (9.0 * (*rhoVar));
        *myy = -2.0 * (-6.0 * rhoI * mxyI - 9.0 * myyI * rhoI - (*rhoVar) + U0 * (*rhoVar)) / (9.0 * (*rhoVar));
        *mxy = -(-18.0 * rhoI * mxxI - 132.0 * mxyI * rhoI - 18.0 * rhoI * myyI - 7.0 * (*rhoVar) + 7.0 * U0 * (*rhoVar)) / (27.0 * (*rhoVar));

        break;
    }
    case NORTH_EAST:
    {
        const dfloat rhoI = pop[0] + pop[1] + pop[2] + pop[5];
        const dfloat inv_rhoI = 1.0 / rhoI;
        const dfloat mxxI = (pop[1] + pop[5]) * inv_rhoI - cs2;
        const dfloat myyI = (pop[2] + pop[5]) * inv_rhoI - cs2;
        const dfloat mxyI = pop[5] * inv_rhoI;

        *ux = U0;
        *uy = 0.0;

        *rhoVar = 12.0 * rhoI * (-3.0 - 3.0 * myyI + 3.0 * (OMEGA - 1.0) * mxxI - 7.0 * (OMEGA - 1.0) * mxyI + 3.0 * OMEGA * myyI) / (2.0 * (-8.0 + 7.0 * U0) + OMEGA * (-9.0 + U0 + 15.0 * U0 * U0));

        *mxx = -2.0 * (-9.0 * rhoI * mxxI + 6.0 * mxyI * rhoI - (*rhoVar) + 2.0 * U0 * (*rhoVar)) / (9.0 * (*rhoVar));
        *myy = 2.0 * (-6.0 * rhoI * mxyI + 9.0 * myyI * rhoI + (*rhoVar) + U0 * (*rhoVar)) / (9.0 * (*rhoVar));
        *mxy = -(18.0 * rhoI * mxxI - 132.0 * mxyI * rhoI + 18.0 * rhoI * myyI + 7.0 * (*rhoVar) + 7.0 * U0 * (*rhoVar)) / (27.0 * (*rhoVar));

        break;
    }

    default:
        break;
    }
}

#endif
