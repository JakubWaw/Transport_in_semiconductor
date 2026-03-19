#include <vector>
#include <algorithm>

#include "evolution.h"
#include "class.h"
#include "distribution.h"

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
double draw_new_time(ScatteringType type) // function to draw new time to scattering event based on type of scattering
{
    switch(type)
    {
        case ScatteringType::Acoustic:
            return Poisson(1e-6); //draw_acoustic_time();

        case ScatteringType::Optical:
            return Poisson(1e-6); //draw_optical_time();

        case ScatteringType::Impurity:
            return Poisson(1e-6); //draw_impurity_time();
    }

    return 0.0;
}
bool compare_time(const ScatteringEvent& a, const ScatteringEvent& b) // function to compare scattering events based on time to event, used for sorting
{
    return a.event_time < b.event_time;
}

struct vec3d CalcMeanDrift(double Temp, struct vec3d Efield, struct material Mat)
{
	int N = 1000; //Ilosc czastek w sumulacji
	std::vector <vec3d> Drifts;
	Drifts.resize(N);
	
	double MaxTime = 1e-3; //ms

	for (int i = 0; i < N; i++)
	{
		//Inicjalizaje wektorow
		double Time = 0;
		vec3d r = vec3d(0, 0, 0); //position of particle

		vec3d k = Boltzmannk(Temp, Mat); // quasi-momentum of particle, randomly drawn from Boltzmann distribution for given temperature and material

		std::vector<ScatteringEvent> events; //vector to store scattering events and their times, will be updated after each scattering event
		events.push_back(ScatteringEvent(ScatteringType::Acoustic, Poisson(1e-6))); 
		events.push_back(ScatteringEvent(ScatteringType::Optical, Poisson(1e-6))); //docelowo tutaj losujemy 3 rozne czasy dla 
		events.push_back(ScatteringEvent(ScatteringType::Impurity, Poisson(1e-6))); //3 rozproszen, ale na razie niech bedzie jedno dla uproszczenia

		while (Time < MaxTime)
		{
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

			// 🔴 UPDATE k (równanie ruchu)
			vec3d dk = vec3d(0, 0, 0);
			k.x = k_old.x + (-e / hbar) * Efield.x * dt;
			k.y = k_old.y + (-e / hbar) * Efield.y * dt;
			k.z = k_old.z + (-e / hbar) * Efield.z * dt;
			// 🔵 UPDATE r (prędkość z k)
			vec3d v = vec3d(0, 0, 0); //velocity of particle, calculated from quasi-momentum k using effective mass approximation and parabolic dispersion relation
			v.x = hbar * k.x / Mat.mx;
			v.y = hbar * k.y / Mat.my;
			v.z = hbar * k.z / Mat.mz;
			r.x = r.x + (hbar / Mat.mx) * k_old.x * dt + (-e / (2.0 * Mat.mx)) * Efield.x * dt * dt;
			r.y = r.y + (hbar / Mat.my) * k_old.y * dt + (-e / (2.0 * Mat.my)) * Efield.y * dt * dt;
			r.z = r.z + (hbar / Mat.mz) * k_old.z * dt + (-e / (2.0 * Mat.mz)) * Efield.z * dt * dt;
			//new time on the clock
			Time = t_next;
			// wykonanie rozproszenia
			// k = k + perform_scattering(event_type); //fuction to write that will update quasi-momentum k based on type of scattering
			// będzie trzeba przełdować dodawanie w tej funkcji bo k jest wektorem a perform_scattering będzie zwracać wektor, więc trzeba będzie zdefiniować operator + dla wektorów
			// time of next scattering event of the same type
			double new_time = Time + draw_new_time(type);
			// update time to next scattering event of the same type
			it->event_time = new_time;
		}

		Drifts[i] = r;
	}

	//Dodanie do siebie wszystkich dryfow
	vec3d SumDrifts(0, 0, 0);
	for (int i = 0; i < Drifts.size(); i++)
	{
		SumDrifts.x += Drifts[i].x;
		SumDrifts.y += Drifts[i].y;
		SumDrifts.z += Drifts[i].z;
	}

	//Obliczenie sredniego dryfu
	vec3d MeanDrift(0, 0, 0);
	MeanDrift.x = SumDrifts.x / N;
	MeanDrift.y = SumDrifts.y / N;
	MeanDrift.z = SumDrifts.z / N;

	return MeanDrift;
}