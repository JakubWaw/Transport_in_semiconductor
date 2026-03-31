#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <omp.h>

#include "evolution.h"
#include "class.h"
#include "distribution.h"
#include "scattering.h"

using namespace std;

//additional functions for inside loop
enum class ScatteringType { // numbering of scattering types
    Acoustic,
    Optical,
    Impurity
};
struct ScatteringEvent { // structure to store information about scattering events
    ScatteringType type;
    double event_time;
	ScatteringEvent(ScatteringType type, double time_to_event) : type(type), event_time(time_to_event) {}
};
double draw_new_time(ScatteringType type, material Mat, std::mt19937& gen) // function to draw new time to scattering event based on type of scattering
{
    switch(type)
    {
        case ScatteringType::Acoustic:
            return Poisson(Mat.tau_ac, gen); //draw_acoustic_time();

        case ScatteringType::Optical:
            return Poisson(Mat.tau_op, gen); //draw_optical_time();

        case ScatteringType::Impurity:
            return Poisson(Mat.tau_ion, gen); //draw_impurity_time();
    }

    return 0.0;
}
struct vec3d perform_scattering(ScatteringType type, vec3d k, material Mat, std::mt19937& gen) // function to update quasi-momentum k based on type of scattering
{
	vec3d new_k(0, 0, 0);
	switch(type)
	{
		case ScatteringType::Acoustic:
			new_k = ScatterAcousticPhonon(k, Mat, gen);
			break;

		case ScatteringType::Optical:
			new_k = ScatterOpticalPhonon(k, Mat, gen);
			break;

		case ScatteringType::Impurity:
			new_k = ScatterIon(k, Mat, gen);
			break;
	}
	return new_k;
}
struct vec3d CalcMeanDrift(
    double Temp,
    struct vec3d Efield,
    struct material Mat,
    int N,
    double MaxTime,
    std::vector<ParticleTrajectory>* trajectories,
    int trajectories_to_store
)
{

    std::vector<vec3d> Drifts;
    Drifts.resize(N);

    if (trajectories != nullptr)
    {
        int nsave = std::min(N, trajectories_to_store);
        trajectories->clear();
        trajectories->resize(nsave);
        for (int i = 0; i < nsave; i++)
        {
            (*trajectories)[i].particle_id = i;
        }
    }

    double Prog_Size = 0.1;
    int Progress = 0;

    #pragma omp parallel
    {
        std::random_device rd;
        std::mt19937 gen(rd() + omp_get_thread_num());

        #pragma omp for
        for (int i = 0; i < N; i++)
        {
            // Progress++;
            // if (Progress % int(N * Prog_Size) == 0)
            //     cout << "Progress " << double(Progress) / N * 100.0 << "%" << endl;


            double Time = 0.0;
            vec3d r = vec3d(0, 0, 0);
            vec3d k = Boltzmannk(Mat, gen);

            bool store_this_trajectory =
                (trajectories != nullptr) && (i < (int)trajectories->size());

            if (store_this_trajectory)
            {
                (*trajectories)[i].points.emplace_back(Time, r, k);
            }

            std::vector<ScatteringEvent> events;
            events.push_back(ScatteringEvent(ScatteringType::Acoustic, Poisson(Mat.tau_ac, gen)));
            events.push_back(ScatteringEvent(ScatteringType::Optical, Poisson(Mat.tau_op, gen)));
            events.push_back(ScatteringEvent(ScatteringType::Impurity, Poisson(Mat.tau_ion, gen)));

            while (Time < MaxTime)
            {
                std::vector<ScatteringEvent>::iterator it = std::min_element(
                    events.begin(),
                    events.end(),
                    [](const ScatteringEvent& a, const ScatteringEvent& b)
                    {
                        return a.event_time < b.event_time;
                    }
                );

                ScatteringType type = it->type;
                double t_next = it->event_time;
                double dt = t_next - Time;

                vec3d k_old = k;

                k = k_old + Efield * (-e / hbar) * dt;

                double rx_push = k_old.x * (hbar / Mat.mx) * dt + Efield.x * (-e / (2.0 * Mat.mx)) * dt * dt;
                double ry_push = k_old.y * (hbar / Mat.my) * dt + Efield.y * (-e / (2.0 * Mat.my)) * dt * dt;
                double rz_push = k_old.z * (hbar / Mat.mz) * dt + Efield.z * (-e / (2.0 * Mat.mz)) * dt * dt;

                r = r + vec3d(rx_push, ry_push, rz_push);
                Time = t_next;

                if (store_this_trajectory)
                {
                    // stan przed rozproszeniem
                    (*trajectories)[i].points.emplace_back(Time, r, k);
                }

                k = perform_scattering(type, k, Mat, gen);

                if (store_this_trajectory)
                {
                    // stan po rozproszeniu
                    (*trajectories)[i].points.emplace_back(Time, r, k);
                }

                double new_time = Time + draw_new_time(type, Mat, gen);
                it->event_time = new_time;
            }

            Drifts[i] = r;
        }
    }

    

    vec3d SumDrifts(0, 0, 0);
    for (int i = 0; i < Drifts.size(); i++)
    {
        SumDrifts = SumDrifts + Drifts[i];
    }

    vec3d MeanDrift(0, 0, 0);
    MeanDrift.x = SumDrifts.x / N;
    MeanDrift.y = SumDrifts.y / N;
    MeanDrift.z = SumDrifts.z / N;

    return MeanDrift;
}