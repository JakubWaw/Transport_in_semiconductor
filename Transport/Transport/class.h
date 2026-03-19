#pragma once

//Uzywajmy w kodzie jednostek SI, bez jakis eV czy innych udziwnien bo potem sie wszystko pierdoli
#define PI 3.14159265359
#define kB 1.380649e-23
#define m0 9.10938356e-31
#define hbar 1.054571817e-34
#define delta_k 10e12
#define e 1.602176634e-19

struct material
{
	double mx;
	double my;
	double mz;
	double tau_op;
	double tau_ac;
	double tau_ion;
	double N_d;

	material(double mx, double my, double mz, double tau_op, double tau_ac, double tau_ion, double N_d)
		: mx(mx), my(my), mz(mz), tau_op(tau_op), tau_ac(tau_ac), tau_ion(tau_ion), N_d(N_d) {
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

	vec3d()
		: x(0), y(0), z(0) {
	}
};

