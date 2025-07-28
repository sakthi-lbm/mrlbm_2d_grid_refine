#include <iostream>

#include "main.hpp"

int main()
{
    create_output_directory();
    
    nodeVar h_fMom;

    timestep sim_start_time = std::chrono::high_resolution_clock::now();
    timestep start_time = std::chrono::high_resolution_clock::now();
    timestep end_time;
    dfloat mlups;

    allocate_host_memory(h_fMom);

    // Domain Initialization: Moments and population
    initialize_domain(h_fMom);
    write_grid();

    for (size_t iter = 0; iter <= MAX_ITER; iter++)
    {
        calculate_moments(h_fMom);
        //  std::cout << iter << " " << h_fMom[MIDX(1,NX-1,M_UX_INDEX)] << std::endl;

        MomCollisionStreaming(h_fMom);
        // std::cout << iter << " " << f_in[FIDX(5, 5, 8)] << std::endl;

        if (iter % MACR_SAVE == 0)
        {
            write_solution(h_fMom, iter);
            calculate_mlups(start_time, end_time, MACR_SAVE, mlups);
            printf("\n---------------------- (%zu/%d) %.2f%% ----------------------\n", iter, MAX_ITER, static_cast<float>(iter) / static_cast<float>(MAX_ITER) * 100.0f);
            std::cout << "MLUPS: " << mlups << std::endl;
        }
    }
    calculate_mlups(sim_start_time, end_time, MAX_ITER, mlups);
    std::cout << "GLOBAL MLUPS: " << mlups << std::endl;
    free_host_memory(h_fMom);
    return 0;
}