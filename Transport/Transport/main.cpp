// external libraries
#include <iostream>


//Uzywajmy w kodzie jednostek SI, bez jakis eV czy innych udziwnien bo potem sie wszystko pierdoli

double m0 = 9.10938356e-31; // kg
struct Si
{
	double meff_l = 0.98*m0;
	double meff_t = 0.19*m0;
	double tau_op = 1;
	double tau_ac = 1;
	double tau_ion = 1;
	double N_d = 1;

	Si(double meff_l, double meff_t, double tau_op, double tau_ac, double tau_ion, double N_d)
		: meff_l(meff_l), meff_t(meff_t), tau_op(tau_op), tau_ac(tau_ac), tau_ion(tau_ion), N_d(N_d) {}
};

struct material //Do Kuby - tutaj zrobilem to jak ma wygladac taka struktura, w main dopiero do tych zmiennych sie wpisze rzeczy, potem mozna normalnie taki obiekt przesylac do funkcji i dziala git nie tylko dla si
{
	double meff_l;
	double meff_t;
	double tau_op;
	double tau_ac;
	double tau_ion;
	double N_d;

	material(double meff_l, double meff_t, double tau_op, double tau_ac, double tau_ion, double N_d)
		: meff_l(meff_l), meff_t(meff_t), tau_op(tau_op), tau_ac(tau_ac), tau_ion(tau_ion), N_d(N_d) {
	}
};

// project headers
#include "scattering.h"
#include "dossier.h"
#include "evolution.h"
#include "distribution.h"


int main()
{
	return 0;
}

