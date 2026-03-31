#include "dossier.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "class.h"


void save_to_file(std::vector<vec3d> drifts, std::vector<double> N_values, std::string filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << "N, Drift_x, Drift_y, Drift_z\n";
        for (size_t i = 0; i < N_values.size(); ++i)
        {
            file << N_values[i] << "     " << drifts[i].x << "     " << drifts[i].y << "     " << drifts[i].z << "\n";
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}
void SaveTrajectoriesToSeparateFiles(const std::vector<ParticleTrajectory>& trajectories,
                                     const std::string& prefix)
{
    std::cout << "Saving trajectories, count = " << trajectories.size() << std::endl;

    for (const auto& traj : trajectories)
    {
        std::string filename = prefix + std::to_string(traj.particle_id) + ".csv";
        std::cout << "Trying to save: " << filename
                  << " | points = " << traj.points.size()
                  << " | particle_id = " << traj.particle_id << std::endl;

        std::ofstream out(filename);

        if (!out.is_open())
        {
            std::cerr << "Error: cannot open file " << filename << std::endl;
            continue;
        }

        out << std::scientific << std::setprecision(10);
        out << "point_id,time,r_x,r_y,r_z,k_x,k_y,k_z\n";

        for (std::size_t j = 0; j < traj.points.size(); ++j)
        {
            const auto& p = traj.points[j];

            out << j << ","
                << p.time << ","
                << p.r.x << ","
                << p.r.y << ","
                << p.r.z << ","
                << p.k.x << ","
                << p.k.y << ","
                << p.k.z << ","
                << p.k.x*p.k.x + p.k.y*p.k.y + p.k.z*p.k.z << "\n";
        }

        out.close();
        std::cout << "Saved: " << filename << std::endl;
    }
}