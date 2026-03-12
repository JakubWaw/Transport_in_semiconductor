#include <cstdlib>
#include <math.h>

#include "distribution.h"


double Poisson(double tau)
{
	//This function returns time of next event with constant probability gamma = 1/tau
	double U = double((rand() % 1000))/1000.0;
	return -log(U) / tau;
}