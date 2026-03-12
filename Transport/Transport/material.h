#pragma once

struct material
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

