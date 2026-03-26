#include <cstdlib>
#include <math.h>
#include <iostream>

#include "scattering.h"
#include "class.h"
#include "bandstruct.h"
#include "distribution.h"


struct vec3d ScatterAcousticPhonon(vec3d k, material Mat)
{
	double E = Ek(k, Mat);

	double Ep = E;

	vec3d kp = RandKFromE(Ep, Mat);


	//To do debugu
	std::cout << "q: " << kp.x - k.x << " " << kp.y - k.y << " " << kp.y - k.y << std::endl;
	return kp;
}

struct vec3d ScatterOpticalPhonon(vec3d k, material Mat)
{
	double E = Ek(k, Mat);

	double nw = 1.0 / (exp((hbar * Mat.omega_0) / (kB * Mat.T)) - 1.0);//obsadzenie fononow optycznych

	double U = double((rand() % 1000)) / 1000.0;

	//wylosuj czy emisja czy absobcja
	bool emmit = 0;
	if (U > (nw + 1.0) / (2.0 * nw + 1))
		emmit = 1;
	

	double Ep;
	if (emmit == 1)
	{
		Ep = E - Mat.omega_0 * hbar;
	}
	else
	{
		Ep = E + Mat.omega_0 * hbar;
	}

	vec3d kp = RandKFromE(Ep, Mat);

	//To do debugu
	std::cout << "q: " << kp.x - k.x << " " << kp.y - k.y << " " << kp.y - k.y << std::endl;

	return kp;
}

struct vec3d ScatterIon(vec3d k, material Mat)
{
	double E = Ek(k, Mat);

	double Ep = E;

	//przejscie do przestrzeni przeskalowanej do sfery
	vec3d ks = vec3d(k.x / sqrt(Mat.mx), k.y / sqrt(Mat.my), k.z / sqrt(Mat.mz));

	//wylosowanie q z rozkladu za pomoca metody odrzutu
	double a, f_q;
	vec3d q, qs;
	vec3d kp, ksp;
	do
	{
		ksp = RandKFromE(Ep, Mat);

		double V = double((rand() % 1000)) / 1000.0;

		qs = ksp + (ks*(-1));
		q = vec3d(qs.x * sqrt(Mat.mx), qs.y * sqrt(Mat.my), qs.z * sqrt(Mat.mz));

		f_q = 1.0 / (q * q + Mat.Q_s * Mat.Q_s);
		a = V * 1.0 / (Mat.Q_s * Mat.Q_s);

	} while (a <= f_q);

	//przeskalowanie na wszelki
	//ksp = ksp * (sqrt(ks*ks) / sqrt(ksp*ksp));
	kp = vec3d(ksp.x * sqrt(Mat.mx), ksp.y * sqrt(Mat.my), ksp.z * sqrt(Mat.mz));

	//To do debugu
	std::cout << "q: " << kp.x - k.x << " " << kp.y - k.y << " " << kp.y - k.y << std::endl;
	return kp;
}