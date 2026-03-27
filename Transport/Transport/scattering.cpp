#include <cstdlib>
#include <math.h>
#include <iostream>
#include <random>

#include "scattering.h"
#include "class.h"
#include "bandstruct.h"
#include "distribution.h"


struct vec3d ScatterAcousticPhonon(vec3d k, material Mat, std::mt19937& gen)
{
	double E = Ek(k, Mat);

	double Ep = E;

	vec3d kp = RandKFromE(Ep, Mat, gen);

	return kp;
}

struct vec3d ScatterOpticalPhonon(vec3d k, material Mat, std::mt19937& gen)
{
	double E = Ek(k, Mat);

	double nw = 1.0 / (exp((hbar * Mat.omega_0) / (kB * Mat.T)) - 1.0);//obsadzenie fononow optycznych
	
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	double U = dist(gen); // w [0,1]

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

	vec3d kp = RandKFromE(Ep, Mat, gen);

	//To do debugu
	//std::cout << "q: " << kp.x - k.x << " " << kp.y - k.y << " " << kp.y - k.y << std::endl;

	return kp;
}

struct vec3d ScatterIon(vec3d k, material Mat, std::mt19937& gen)
{
	double E = Ek(k, Mat);

	double Ep = E;

	//wylosowanie q z rozkladu za pomoca metody odrzutu
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	double a, f_q;
	vec3d q;
	vec3d kp;
	do
	{
		kp = RandKFromE(Ep, Mat, gen);

		double V = dist(gen); // w [0,1]
		a = V * 1.0 / (Mat.Q_s * Mat.Q_s); //0-fqmax

		q = kp + (k*(-1));

		f_q = 1.0 / (q * q + Mat.Q_s * Mat.Q_s);
		

	} while (a > f_q);

	//To do debugu
	//std::cout << "q: " << kp.x - k.x << " " << kp.y - k.y << " " << kp.y - k.y << std::endl;
	return kp;
}