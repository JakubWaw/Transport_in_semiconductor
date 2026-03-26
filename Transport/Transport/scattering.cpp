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
	//std::cout << "q: " << kp.x - k.x << " " << kp.y - k.y << " " << kp.y - k.y << std::endl;
	return kp;
}

struct vec3d ScatterOpticalPhonon(vec3d k, material Mat)
{
	double E = Ek(k, Mat);

	double nw = 1.0 / (exp((hbar * Mat.omega_0) / (kB * Mat.T)) - 1.0);//obsadzenie fononow optycznych
	
	double U = double((rand() % 1000)) / 1000.0;

	//wylosuj czy emisja czy absobcja
	bool emmit = 0;
	if (U > (nw) / (2.0 * nw + 1.0))
		emmit = 1;
	

	double Ep;
	if (emmit == 1)
	{
		
		Ep = E - Mat.omega_0 * hbar;
		if (Ep < 0) //jesli za malo energii nie rozpraszaj
			return k;
	}
	else
	{
		Ep = E + Mat.omega_0 * hbar;
	}

	vec3d kp = RandKFromE(Ep, Mat);

	//To do debugu
	//std::cout << "q: " << kp.x - k.x << " " << kp.y - k.y << " " << kp.y - k.y << std::endl;

	return kp;
}

struct vec3d ScatterIon(vec3d k, material Mat)
{
	double E = Ek(k, Mat);

	double Ep = E;

	//przejscie do przestrzeni przeskalowanej do sfery
	vec3d ks = vec3d(k.x / sqrt(Mat.mx / m0), k.y / sqrt(Mat.my / m0), k.z / sqrt(Mat.mz / m0));

	//wylosowanie q z rozkladu za pomoca metody odrzutu
	double a, f_q;
	vec3d q, qs;
	vec3d kp, ksp;
	do
	{
		ksp = RandKFromE(Ep, Mat);
		//std::cout << "k: " << k.x << " " << k.y << " " << k.y << std::endl;
		//std::cout << "ks: " << ks.x << " " << ks.y << " " << ks.y << std::endl;
		//std::cout << "ksp: " << ksp.x << " " << ksp.y << " " << ksp.y << std::endl;

		double V = double(rand()) / RAND_MAX;

		qs = ksp + (ks*(-1));
		q = vec3d(qs.x * sqrt(Mat.mx / m0), qs.y * sqrt(Mat.my / m0), qs.z * sqrt(Mat.mz / m0));

		f_q = 1.0 / (q * q + Mat.Q_s * Mat.Q_s);
		a = V * 1.0 / (Mat.Q_s * Mat.Q_s);

	} while (a <= f_q);

	//przeskalowanie na wszelki
	//ksp = ksp * (sqrt(ks*ks) / sqrt(ksp*ksp));
	kp = vec3d(ksp.x * sqrt(Mat.mx / m0), ksp.y * sqrt(Mat.my / m0), ksp.z * sqrt(Mat.mz / m0));

	//To do debugu
	//std::cout << "q: " << kp.x - k.x << " " << kp.y - k.y << " " << kp.y - k.y << std::endl;
	return kp;
}