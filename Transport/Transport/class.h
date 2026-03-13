#pragma once

#define PI 3.14159265359
#define kB 1.380649e-23
#define m0 9.10938356e-31

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

struct vec2d
{
	double x;
	double y;

	vec2d(double x, double y)
		: x(x), y(y) {
	}
};

struct vec3d
{
	double x;
	double y;
	double z;

	vec3d(double x, double y, double z)
		: x(x), y(y), z(z) {
	}
};

