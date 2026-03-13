#include <cstdlib>
#include <math.h>

#include "distribution.h"
#include "class.h"


double Poisson(double tau)
{
	//This function returns time of next event with constant probability gamma = 1/tau
	double U = double((rand() % 1000))/1000.0;
	return -log(U) / tau;
}

vec2d UniAngles()
{
	double U = double((rand() % 1000)) / 1000.0;
	double V = double((rand() % 1000)) / 1000.0;

	double psi = acos(1 - 2 * U);
	double phi = 2 * PI * V;
	return vec2d(psi, phi);
}

double Boltzmann(double T)
{
	double U = double((rand() % 1000)) / 1000.0;
	double E = -kB * T * log(U);
}