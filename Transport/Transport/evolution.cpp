#include <vector>
#include <algorithm>
#include <iostream>

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
double draw_new_time(ScatteringType type, material Mat) // function to draw new time to scattering event based on type of scattering
{
    switch(type)
    {
        case ScatteringType::Acoustic:
            return Poisson(Mat.tau_ac); //draw_acoustic_time();

        case ScatteringType::Optical:
            return Poisson(Mat.tau_op); //draw_optical_time();

        case ScatteringType::Impurity:
            return Poisson(Mat.tau_ion); //draw_impurity_time();
    }

    return 0.0;
}
struct vec3d perform_scattering(ScatteringType type, vec3d k, material Mat) // function to update quasi-momentum k based on type of scattering
{
	vec3d new_k(0, 0, 0);
	switch(type)
	{
		case ScatteringType::Acoustic:
			new_k = ScatterAcousticPhonon(k, Mat);
			break;

		case ScatteringType::Optical:
			new_k = ScatterOpticalPhonon(k, Mat);
			break;

		case ScatteringType::Impurity:
			new_k = ScatterIon(k, Mat);
			break;
	}
	return new_k;
}
struct vec3d CalcMeanDrift(double Temp, struct vec3d Efield, struct material Mat, int N)
{	
	
	std::vector <vec3d> Drifts;
	Drifts.resize(N);
	
	double MaxTime = pow(10, -6); //1us

	for (int i = 0; i < N; i++)
	{
		//Inicjalizaje wektorow
		double Time = 0;
		vec3d r = vec3d(0, 0, 0); //position of particle

		vec3d k = Boltzmannk(Mat); // quasi-momentum of particle, randomly drawn from Boltzmann distribution for given temperature and material

		std::vector<ScatteringEvent> events; //vector to store scattering events and their times, will be updated after each scattering event
		events.push_back(ScatteringEvent(ScatteringType::Acoustic, Poisson(Mat.tau_ac))); 
		events.push_back(ScatteringEvent(ScatteringType::Optical, Poisson(Mat.tau_op))); //docelowo tutaj losujemy 3 rozne czasy dla 
		events.push_back(ScatteringEvent(ScatteringType::Impurity, Poisson(Mat.tau_ion))); //3 rozproszen, ale na razie niech bedzie jedno dla uproszczenia
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
			k = k_old +  Efield * (-e/hbar)* dt ; 
			// UPDATE r 
			r = r + k_old * (hbar / Mat.mx) * dt + Efield * (-e / (2.0 * Mat.mx)) * dt * dt; //klasyczna aktualizacja pozycji, ale z uwzglednieniem przyspieszenia elektrycznego
			//new time on the clock
			Time = t_next;
			// wykonanie rozproszenia
			k = perform_scattering(type,k,Mat); //fuction to write that will update quasi-momentum k based on type of scattering
			// time of next scattering event of the same type
			double new_time = Time + draw_new_time(type, Mat); //function to write that will draw new time to scattering event based on type of scattering
			// update time to next scattering event of the same type
			it->event_time = new_time;
			std::cout << "New time: " << new_time << std::endl;
			//std::cout << "Time: " << Time << " s, Scattering type: " << static_cast<int>(type) << ", k: (" << k.x << ", " << k.y << ", " << k.z << ")" << std::endl;
		}

		Drifts[i] = r;
	}

	//Dodanie do siebie wszystkich dryfow
	vec3d SumDrifts(0, 0, 0);
	for (int i = 0; i < Drifts.size(); i++)
	{
		SumDrifts = SumDrifts + Drifts[i];
	}

	//Obliczenie sredniego dryfu
	vec3d MeanDrift(0, 0, 0);
	MeanDrift.x = SumDrifts.x / N;
	MeanDrift.y = SumDrifts.y / N;
	MeanDrift.z = SumDrifts.z / N;

	return MeanDrift;
}