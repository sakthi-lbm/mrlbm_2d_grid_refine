#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <string>
#include "var.hpp"

inline void create_output_directory()
{
#if defined(_WIN32)
    std::string strPath;
    strPath = PATH_FILES;
    strPath += "\\\\"; // adds "\\"
    strPath += ID_SIM;
    std::string cmd = "md ";
    cmd += strPath;
    system(cmd.c_str());
    return;
#endif // !_WIN32

#if defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    std::string strPath;
    strPath = PATH_FILES;
    strPath += "/";
    strPath += ID_SIM;
    strPath += "/";
    strPath += "plots";
    std::string cmd = "mkdir -p ";
    cmd += strPath;
    const int i = system(cmd.c_str());
    static_cast<void>(i);
    return;

#endif
    printf("I don't know how to setup folders for your operational system :(\n");
    return;
}

inline void calculate_mlups(timestep &tstart, timestep &tend, int steps, dfloat &mlups)
{
    tend = std::chrono::high_resolution_clock::now();
    double step_time = std::chrono::duration<double>(tend - tstart).count();
    if (step_time > 0.0)
        mlups = (NUM_NODES * steps / 1e6) / step_time;
    else
        mlups = 0.0;

    tstart = std::chrono::high_resolution_clock::now();
}

#endif