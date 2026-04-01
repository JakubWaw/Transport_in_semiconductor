// external libraries
#include <iostream>
#include <vector>

// project headers
#include "class.h"
#include "scattering.h"
#include "dossier.h"
#include "evolution.h"
#include "distribution.h"
#include "bandstruct.h"


int main()
{
	double Tau_Si_Ac = pow(10, -12.5);
	double Tau_Si_Op = pow(10, -13.5);
	double Tau_Si_Ion = pow(10, -10);
	double Q_s_Si = pow(10, 8); // 1/10nm
	double Omega0_Si = 15.6 * pow(10, 12) * 2.0 * PI;
	double Temp0_Si = 200;
	double Nd_Si = 1.2 * 10e16;
	material Si = material(0.98 * m0, 0.98 * m0, 0.19 * m0, Tau_Si_Op, Tau_Si_Ac, Tau_Si_Ion, Nd_Si, Temp0_Si, Omega0_Si, Q_s_Si); //dla normalnego Q_s cos wolno sie liczy

	//Si.T = 20;
	//std::cout << 1.0 / (exp((hbar * Si.omega_0) / (kB * Si.T)) - 1.0) << std::endl;


	double MaxTime = pow(10, -9);
	double N = 3;
	vec3d Si_200K_Ee5 = CalcMeanDrift(200, vec3d(1e+1, 0, 0), Si, N, MaxTime); //1e+5
	std::cout << "Mean drift for Si at 200K and E = 1e2 V/m: " << Si_200K_Ee5 / MaxTime << std::endl;

	// trajectories to store for visualization
	int trajectories_to_store = 3;

	std::vector<ParticleTrajectory> trajectories;
	CalcMeanDrift(200, vec3d(1e+5, 0, 0), Si, N, MaxTime, &trajectories, trajectories_to_store);

	//std::vector<ParticleTrajectory> trajectories2;
	//CalcMeanDrift(200, vec3d(1e+5, 0, 0), Si, N, MaxTime, &trajectories2, trajectories_to_store);

	SaveTrajectoriesToSeparateFiles(trajectories,  "traj", Si);
	//SaveTrajectoriesToSeparateFiles(trajectories2, "C:\\Users\\kwaw1\\Desktop\\studia\\semestr8\\traj2_", Si);

	// convergence test for number of particles
	// std::vector<double> N_values = {100, 500, 1000, 5000, 10000, 50000, 100000};
	// std::vector<vec3d> drifts;
	// for (double N : N_values)
	// {
	// 	std::cout << "Calculating drift for N = " << N << " particles..." << std::endl;
	// 	vec3d drift = CalcMeanDrift(200, vec3d(1e+5, 0, 0), Si, N, MaxTime);
	// 	drifts.push_back(drift);
	// }
	// save_to_file(drifts, N_values, "drift_convergence_particles.csv");

	// // convergence test for MaxTime
	// std::vector<double> MaxTime_values = {pow(10, -10),pow(10, -9.5), pow(10, -9), pow(10, -8.5), pow(10, -8), pow(10, -7.5), pow(10, -7)};
	// std::vector<vec3d> drifts_time;
	// for (double MaxTime : MaxTime_values)
	// {
	// 	std::cout << "Calculating drift for MaxTime = " << MaxTime << " s..." << std::endl;
	// 	vec3d drift = CalcMeanDrift(200, vec3d(0, 0, 0), Si, N, MaxTime);
	// 	drifts_time.push_back(drift);
	// }
	// save_to_file(drifts_time, MaxTime_values, "drift_convergence_time.csv");


	return 0;

}

