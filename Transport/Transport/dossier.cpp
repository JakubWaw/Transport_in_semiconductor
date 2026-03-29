#include "dossier.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "class.h"


void save_to_file(std::vector<vec3d> drifts, std::vector<double> N_values, std::string filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << "N, Drift_x, Drift_y, Drift_z\n";
        for (size_t i = 0; i < N_values.size(); ++i)
        {
            file << N_values[i] << ", " << drifts[i].x << ", " << drifts[i].y << ", " << drifts[i].z << "\n";
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}