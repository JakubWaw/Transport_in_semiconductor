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
struct vec3d CalcMeanDrift(double Temp, struct vec3d Efield, struct material Mat, int N, double MaxTime)
{	
	
	std::vector <vec3d> Drifts;
	Drifts.resize(N);
	
	//double MaxTime = pow(10, -9); //1ns

	double Prog_Size = 0.1;
	int Progress = 0;

	//omp_set_num_threads(6);
	#pragma omp parallel
	{
		//tutaj jest zaladowanie kazdego watku przed petla
		//stworzenie dobrego generatora liczb losowych 0-1
		std::random_device rd;
		std::mt19937 gen(rd() + omp_get_thread_num());

		#pragma omp for
		for (int i = 0; i < N; i++)
		{
			Progress++;
			if (Progress % int(N * Prog_Size) == 0)
				cout << "Progress " << double(Progress) / N * 100.0 << "%" << endl;
			//Inicjalizaje wektorow
			double Time = 0;
			vec3d r = vec3d(0, 0, 0); //position of particle

			vec3d k = Boltzmannk(Mat, gen); // quasi-momentum of particle, randomly drawn from Boltzmann distribution for given temperature and material

			//std::cout << "k: " << k << std::endl;

			std::vector<ScatteringEvent> events; //vector to store scattering events and their times, will be updated after each scattering event
			events.push_back(ScatteringEvent(ScatteringType::Acoustic, Poisson(Mat.tau_ac, gen)));
			events.push_back(ScatteringEvent(ScatteringType::Optical, Poisson(Mat.tau_op, gen))); //docelowo tutaj losujemy 3 rozne czasy dla 
			events.push_back(ScatteringEvent(ScatteringType::Impurity, Poisson(Mat.tau_ion, gen))); //3 rozproszen, ale na razie niech bedzie jedno dla uproszczenia
			while (Time < MaxTime)
			{
				//std:: cout << "Time: " << Time << " s, k: (" << k.x << ", " << k.y << ", " << k.z << ")" << std::endl;
				// ta funkcja trochę zmieniła swoją strukture wzgledem poczaatkowego pomysłu bo usuwanie elementów w wektorze
				// jest dość problematyczne, więc zamiast tego po prostu aktualizuje czas do nastepnego rozproszenia danego typu,
				// a potem wybieram to rozproszenie które nastąpi najprędzej

				// choice of scattering event with the shortest time to event

				// w kolejnej linicje powastał taki potworek, ale chodzi o to że funkcja min zwraca indeks w wektorze a nie obiekt 
				// na miejscu tego indesku, więc potem odwołuje się do tego obiektu za pomoca iteratora "->" a nie "." tak jak 
				// w przypadku obiektu a nie indeksu
				std::vector<ScatteringEvent>::iterator it = std::min_element(
					events.begin(),
					events.end(),
					[](const ScatteringEvent& a, const ScatteringEvent& b)
					{
						return a.event_time < b.event_time;
					}
				);
				// type of scattering event
				ScatteringType type = it->type;

				// time to next scattering event
				double t_next = it->event_time;
				double dt = t_next - Time;
				// zapamiętaj stare k!
				vec3d k_old = k;

				// UPDATE k
				k = k_old + Efield * (-e / hbar) * dt;
				// UPDATE r 
				double rx_push = k_old.x * (hbar / Mat.mx) * dt + Efield.x * (-e / (2.0 * Mat.mx)) * dt * dt;
				double ry_push = k_old.y * (hbar / Mat.my) * dt + Efield.y * (-e / (2.0 * Mat.my)) * dt * dt;
				double rz_push = k_old.z * (hbar / Mat.mz) * dt + Efield.z * (-e / (2.0 * Mat.mz)) * dt * dt;
				r = r + vec3d(rx_push, ry_push, rz_push); //klasyczna aktualizacja pozycji, ale z uwzglednieniem przyspieszenia elektrycznego
				//cout << k_old * (hbar / Mat.mx) * dt << endl;
				//cout << Efield * (-e / (2.0 * Mat.mx)) * dt * dt << endl;
				//new time on the clock
				Time = t_next;
				// wykonanie rozproszenia
				k = perform_scattering(type, k, Mat, gen); //fuction to write that will update quasi-momentum k based on type of scattering
				// time of next scattering event of the same type
				double new_time = Time + draw_new_time(type, Mat, gen); //function to write that will draw new time to scattering event based on type of scattering
				// update time to next scattering event of the same type
				it->event_time = new_time;
				//std::cout << "New time: " << new_time << std::endl;
				//std::cout << "Time: " << Time << " s, Scattering type: " << static_cast<int>(type) << ", k: (" << k.x << ", " << k.y << ", " << k.z << ")" << std::endl;
			}

			Drifts[i] = r;
		}
	}

	//Dodanie do siebie wszystkich dryfow
	vec3d SumDrifts(0, 0, 0);
	for (int i = 0; i < Drifts.size(); i++)
	{
		//cout << Drifts[i] << endl;
		SumDrifts = SumDrifts + Drifts[i];
	}

	//Obliczenie sredniego dryfu
	vec3d MeanDrift(0, 0, 0);
	MeanDrift.x = SumDrifts.x / N;
	MeanDrift.y = SumDrifts.y / N;
	MeanDrift.z = SumDrifts.z / N;

	return MeanDrift;
}