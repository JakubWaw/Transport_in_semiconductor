#pragma once

#include "class.h"

struct vec3d CalcMeanDrift(double Temp, struct vec3d Efield, struct material Mat, int N, double MaxTime, std::vector<ParticleTrajectory>* trajectories = nullptr, int trajectories_to_store = 0);

