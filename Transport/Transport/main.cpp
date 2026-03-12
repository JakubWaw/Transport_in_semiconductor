// external libraries
#include <iostream>


// project headers
#include "scattering.h"
#include "dossier.h"
#include "evolution.h"
#include "distribution.h"


struct Si
{
	double meff_l = 1;
	double meff_t = 1;
	double tau_op = 1;
	double tau_ac = 1;
	double tau_ion = 1;
	double N_d = 1;

	Si(double meff_l, double meff_t, double tau_op, double tau_ac, double tau_ion, double N_d)
		: meff_l(meff_l), meff_t(meff_t), tau_op(tau_op), tau_ac(tau_ac), tau_ion(tau_ion), N_d(N_d) {}
};


int main()
{
	return 0;
}

