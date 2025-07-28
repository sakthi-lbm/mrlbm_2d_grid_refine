#ifndef MAIN_HPP
#define MAIN_HPP

#include "var.hpp"
#include "global_struct.hpp"
#include "initialize_lbm.hpp"
#include "solve_mlbm.hpp"
#include "file_utils.hpp"
#include "save_data.hpp"

// Allocate host memory
inline void allocate_host_memory(nodeVar &h_fMom)
{
    h_fMom.rho = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    h_fMom.ux = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    h_fMom.uy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    h_fMom.mxx = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    h_fMom.myy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    h_fMom.mxy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    h_fMom.nodeType = static_cast<unsigned int *>(std::malloc(MEM_SIZE_NODETYPE));

    h_fMom.f_in = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_Q));
    h_fMom.f_out = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_Q));
}

// Free host memory
inline void free_host_memory(nodeVar &h_fMom)
{
    std::free(h_fMom.rho);
    std::free(h_fMom.ux);
    std::free(h_fMom.uy);
    std::free(h_fMom.mxx);
    std::free(h_fMom.myy);
    std::free(h_fMom.mxy);
    std::free(h_fMom.nodeType);
    std::free(h_fMom.f_in);
    std::free(h_fMom.f_out);
}

inline void initialize_domain(nodeVar h_fMom)
{
    for (size_t x = 0; x < NX; x++)
    {
        for (size_t y = 0; y < NY; y++)
        {
            // boundary_definitions(nodeType, x, y);
            h_fMom.nodeType[IDX(x, y)] = boundary_definitions(x, y);

            dfloat rho_var, ux_var, uy_var;
            dfloat mxx, myy, mxy;
            initialize_moments(&rho_var, &ux_var, &uy_var, &mxx, &myy, &mxy);
            h_fMom.rho[IDX(x, y)] = rho_var - RHO_0;
            h_fMom.ux[IDX(x, y)] = ux_var;
            h_fMom.uy[IDX(x, y)] = uy_var;
            h_fMom.mxx[IDX(x, y)] = mxx;
            h_fMom.myy[IDX(x, y)] = myy;
            h_fMom.mxx[IDX(x, y)] = mxy;

            dfloat pop[Q];
            pop_reconstruction(rho_var, ux_var, uy_var, mxx, myy, mxy, pop);
            for (size_t q = 0; q < Q; q++)
            {
                h_fMom.f_in[FIDX(x, y, q)] = pop[q];
            }
        }
    }
}

#endif