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

vec3d CalcMeanDrift(double Temp, double Efield, material Mat)
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
			//new time on the clock
			Time = it->event_time;
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