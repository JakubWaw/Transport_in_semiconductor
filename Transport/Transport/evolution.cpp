#include <vector>

#include "evolution.h"
#include "class.h"
#include "distribution.h"

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
		vec3d r = vec3d(0, 0, 0);

		double En0 = BoltzmannE(Temp);
		vec3d k = RandKFromE(En0, Mat);

		std::vector<double> times; //Czasy do kolejnych rozproszen
		times.push_back(Poisson(1e-6)); //srednio us

		while (Time < MaxTime)
		{
			//Znajdz najmniejszy czas

			//Zrob ewolucje do tego czasu, rozprosz oraz zaktualizuj time
			//zaktualizuj czasy innych rozproszen (odejmij od nich tyle ile minelo)
			//wylosuj czas rozproszenia wykonanego
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