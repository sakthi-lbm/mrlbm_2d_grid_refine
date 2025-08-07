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

    h_fMom.iscopied = nullptr;
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

#ifdef GRID_REFINE
inline void allocate_host_memory_refine(nodeVar &hc_Mom, nodeVar &hf_Mom)
{
    // Coarse grid memory allocation
    hc_Mom.rho = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_COARSE));
    hc_Mom.ux = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_COARSE));
    hc_Mom.uy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_COARSE));
    hc_Mom.mxx = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_COARSE));
    hc_Mom.myy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_COARSE));
    hc_Mom.mxy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_COARSE));
    hc_Mom.nodeType = static_cast<unsigned int *>(std::malloc(MEM_SIZE_NODETYPE_COARSE));
    hc_Mom.iscopied = static_cast<unsigned int *>(std::malloc(MEM_SIZE_NODETYPE_COARSE));

    hc_Mom.f_in = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_Q_COARSE));
    hc_Mom.f_out = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_Q_COARSE));

    // Coarse grid memory allocation
    hf_Mom.rho = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_FINE));
    hf_Mom.ux = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_FINE));
    hf_Mom.uy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_FINE));
    hf_Mom.mxx = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_FINE));
    hf_Mom.myy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_FINE));
    hf_Mom.mxy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_FINE));
    hf_Mom.nodeType = static_cast<unsigned int *>(std::malloc(MEM_SIZE_NODETYPE_FINE));
    hf_Mom.iscopied = static_cast<unsigned int *>(std::malloc(MEM_SIZE_NODETYPE_COARSE));

    hf_Mom.f_in = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_Q_FINE));
    hf_Mom.f_out = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_Q_FINE));
}

// Free host memory
inline void free_host_memory_refine(nodeVar &hc_Mom, nodeVar &hf_Mom)
{
    std::free(hc_Mom.rho);
    std::free(hc_Mom.ux);
    std::free(hc_Mom.uy);
    std::free(hc_Mom.mxx);
    std::free(hc_Mom.myy);
    std::free(hc_Mom.mxy);
    std::free(hc_Mom.nodeType);
    std::free(hc_Mom.f_in);
    std::free(hc_Mom.f_out);

    std::free(hf_Mom.rho);
    std::free(hf_Mom.ux);
    std::free(hf_Mom.uy);
    std::free(hf_Mom.mxx);
    std::free(hf_Mom.myy);
    std::free(hf_Mom.mxy);
    std::free(hf_Mom.nodeType);
    std::free(hf_Mom.f_in);
    std::free(hf_Mom.f_out);
}
#endif

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

inline void initialize_domain_grid(nodeVar hc_Mom, nodeVar hf_Mom)
{
    for (size_t x = 0; x < NX_COARSE; x++)
    {
        for (size_t y = 0; y < NY_COARSE; y++)
        {
            // boundary_definitions(nodeType, x, y);
            hc_Mom.nodeType[IDX(x, y)] = boundary_definitions_coarse(x, y);

            dfloat rho_var, ux_var, uy_var;
            dfloat mxx, myy, mxy;
            initialize_moments(&rho_var, &ux_var, &uy_var, &mxx, &myy, &mxy);
            hc_Mom.rho[IDX(x, y)] = rho_var - RHO_0;
            hc_Mom.ux[IDX(x, y)] = ux_var;
            hc_Mom.uy[IDX(x, y)] = uy_var;
            hc_Mom.mxx[IDX(x, y)] = mxx;
            hc_Mom.myy[IDX(x, y)] = myy;
            hc_Mom.mxx[IDX(x, y)] = mxy;

            dfloat pop[Q];
            pop_reconstruction(rho_var, ux_var, uy_var, mxx, myy, mxy, pop);
            for (size_t q = 0; q < Q; q++)
            {
                hc_Mom.f_in[FIDX(x, y, q)] = pop[q];
            }
        }
    }

    //FINE GRID
    for (size_t x = 0; x < NX_FINE; x++)
    {
        for (size_t y = 0; y < NY_FINE; y++)
        {
            // boundary_definitions(nodeType, x, y);
            hf_Mom.nodeType[IDX(x, y)] = boundary_definitions_fine(x, y);

            dfloat rho_var, ux_var, uy_var;
            dfloat mxx, myy, mxy;
            initialize_moments(&rho_var, &ux_var, &uy_var, &mxx, &myy, &mxy);
            hf_Mom.rho[IDX(x, y)] = rho_var - RHO_0;
            hf_Mom.ux[IDX(x, y)] = ux_var;
            hf_Mom.uy[IDX(x, y)] = uy_var;
            hf_Mom.mxx[IDX(x, y)] = mxx;
            hf_Mom.myy[IDX(x, y)] = myy;
            hf_Mom.mxx[IDX(x, y)] = mxy;

            dfloat pop[Q];
            pop_reconstruction(rho_var, ux_var, uy_var, mxx, myy, mxy, pop);
            for (size_t q = 0; q < Q; q++)
            {
                hf_Mom.f_in[FIDX(x, y, q)] = pop[q];
            }
        }
    }
}

#endif