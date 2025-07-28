#include <iostream>
#include "solve_mlbm.hpp"

void calculate_moments(nodeVar h_fMom)
{

    for (size_t x = 0; x < NX; x++)
    {
        for (size_t y = 0; y < NY; y++)
        {
            dfloat rhoVar = 0;
            dfloat uxVar = 0;
            dfloat uyVar = 0;
            dfloat mxxVar = 0;
            dfloat myyVar = 0;
            dfloat mxyVar = 0;
            dfloat pop[Q];
            const unsigned int node = h_fMom.nodeType[IDX(x, y)];
            for (size_t q = 0; q < Q; q++)
            {
                pop[q] = h_fMom.f_in[FIDX(x, y, q)];
            }

            if (node != BULK)
            {
                boundary_condition(node, pop, &rhoVar, &uxVar, &uyVar, &mxxVar, &myyVar, &mxyVar);
                h_fMom.rho[IDX(x, y)] = rhoVar - RHO_0;
                h_fMom.ux[IDX(x, y)] = uxVar;
                h_fMom.uy[IDX(x, y)] = uyVar;
                h_fMom.mxx[IDX(x, y)] = mxxVar;
                h_fMom.myy[IDX(x, y)] = myyVar;
                h_fMom.mxy[IDX(x, y)] = mxyVar;

                // std::cout << x << " " << y << " " << rhoVar << " " << uxVar << " " << uyVar << std::endl;
            }

            else
            {
                const dfloat pop0 = h_fMom.f_in[FIDX(x, y, 0)];
                const dfloat pop1 = h_fMom.f_in[FIDX(x, y, 1)];
                const dfloat pop2 = h_fMom.f_in[FIDX(x, y, 2)];
                const dfloat pop3 = h_fMom.f_in[FIDX(x, y, 3)];
                const dfloat pop4 = h_fMom.f_in[FIDX(x, y, 4)];
                const dfloat pop5 = h_fMom.f_in[FIDX(x, y, 5)];
                const dfloat pop6 = h_fMom.f_in[FIDX(x, y, 6)];
                const dfloat pop7 = h_fMom.f_in[FIDX(x, y, 7)];
                const dfloat pop8 = h_fMom.f_in[FIDX(x, y, 8)];

                rhoVar = pop0 + pop1 + pop2 + pop3 + pop4 + pop5 + pop6 + pop7 + pop8;
                dfloat invRho = 1.0 / rhoVar;

                uxVar = (pop1 - pop3 + pop5 - pop6 - pop7 + pop8) * invRho;
                uyVar = (pop2 - pop4 + pop5 + pop6 - pop7 - pop8) * invRho;

                mxxVar = (pop1 + pop3 + pop5 + pop6 + pop7 + pop8) * invRho - cs2;
                myyVar = (pop2 + pop4 + pop5 + pop6 + pop7 + pop8) * invRho - cs2;
                mxyVar = (pop5 - pop6 + pop7 - pop8) * invRho;

                h_fMom.rho[IDX(x, y)] = rhoVar - RHO_0;
                h_fMom.ux[IDX(x, y)] = uxVar;
                h_fMom.uy[IDX(x, y)] = uyVar;
                h_fMom.mxx[IDX(x, y)] = mxxVar;
                h_fMom.myy[IDX(x, y)] = myyVar;
                h_fMom.mxy[IDX(x, y)] = mxyVar;
            }
        }
    }
}

void MomCollisionStreaming(nodeVar h_fMom)
{
    for (size_t x = 0; x < NX; x++)
    {
        for (size_t y = 0; y < NY; y++)
        {
            dfloat rho_var = RHO_0 + h_fMom.rho[IDX(x, y)];
            dfloat ux_var = h_fMom.ux[IDX(x, y)];
            dfloat uy_var = h_fMom.uy[IDX(x, y)];
            dfloat mxx = h_fMom.mxx[IDX(x, y)];
            dfloat myy = h_fMom.myy[IDX(x, y)];
            dfloat mxy = h_fMom.mxy[IDX(x, y)];

            mom_collision(ux_var, uy_var, &mxx, &myy, &mxy);

            h_fMom.mxx[IDX(x, y)] = mxx;
            h_fMom.myy[IDX(x, y)] = myy;
            h_fMom.mxy[IDX(x, y)] = mxy;

            dfloat pop[Q];
            pop_reconstruction(rho_var, ux_var, uy_var, mxx, myy, mxy, pop);
            for (size_t q = 0; q < Q; q++)
            {
                h_fMom.f_out[FIDX(x, y, q)] = pop[q];
            }
        }
    }

    // Streaming
    for (size_t x = 0; x < NX; x++)
    {
        for (size_t y = 0; y < NY; y++)
        {
            int xm1 = (x - 1 + NX) % NX;
            int xp1 = (x + 1) % NX;
            int ym1 = (y - 1 + NY) % NY;
            int yp1 = (y + 1) % NY;

            h_fMom.f_in[FIDX(x, y, 0)] = h_fMom.f_out[FIDX(x, y, 0)];
            h_fMom.f_in[FIDX(x, y, 1)] = h_fMom.f_out[FIDX(xm1, y, 1)];
            h_fMom.f_in[FIDX(x, y, 2)] = h_fMom.f_out[FIDX(x, ym1, 2)];
            h_fMom.f_in[FIDX(x, y, 3)] = h_fMom.f_out[FIDX(xp1, y, 3)];
            h_fMom.f_in[FIDX(x, y, 4)] = h_fMom.f_out[FIDX(x, yp1, 4)];
            h_fMom.f_in[FIDX(x, y, 5)] = h_fMom.f_out[FIDX(xm1, ym1, 5)];
            h_fMom.f_in[FIDX(x, y, 6)] = h_fMom.f_out[FIDX(xp1, ym1, 6)];
            h_fMom.f_in[FIDX(x, y, 7)] = h_fMom.f_out[FIDX(xp1, yp1, 7)];
            h_fMom.f_in[FIDX(x, y, 8)] = h_fMom.f_out[FIDX(xm1, yp1, 8)];
        }
    }
}