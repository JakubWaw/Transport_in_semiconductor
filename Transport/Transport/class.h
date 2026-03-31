#pragma once

#include <iostream>
#include <vector>
#include <cmath>

//Uzywajmy w kodzie jednostek SI, bez jakis eV czy innych udziwnien bo potem sie wszystko pierdoli
#define PI 3.14159265359
#define kB 1.380649e-23
#define m0 9.10938356e-31
#define hbar 1.054571817e-34
#define delta_k 10e12
#define e 1.602176634e-19

using namespace std;

struct material
{
	double mx;
	double my;
	double mz;
	double tau_op;
	double tau_ac;
	double tau_ion;
	double N_d;
	double T;
	double omega_0;
	double Q_s;

	material(double mx, double my, double mz, double tau_op, double tau_ac, double tau_ion, double N_d, double T, double omega_0, double Q_s)
		: mx(mx), my(my), mz(mz), tau_op(tau_op), tau_ac(tau_ac), tau_ion(tau_ion), N_d(N_d), T(T), omega_0(omega_0), Q_s(Q_s)  {}

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
	//overload addition operator for vec3d
	vec3d operator+(const vec3d& other) const
	{
		return vec3d(x + other.x, y + other.y, z + other.z);
	}
	//multiplication by scalar
	vec3d operator*(double scalar) const
	{
		return vec3d(x * scalar, y * scalar, z * scalar);
	}
	//multiplication by scalar
	vec3d operator/(double scalar) const
	{
		return vec3d(x / scalar, y / scalar, z / scalar);
	}
	//scalar product
	double operator*(const vec3d& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	friend std::ostream& operator<<(std::ostream& os, const vec3d& v)
	{
		os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}
};


struct TrajectoryPoint
{
    double time;
    vec3d r;   // pozycja
    vec3d k;   // quasi-momentum

    TrajectoryPoint(double t, const vec3d& pos, const vec3d& mom)
        : time(t), r(pos), k(mom) {}
};

struct ParticleTrajectory
{
    int particle_id;
    std::vector<TrajectoryPoint> points;

    ParticleTrajectory(int id = -1) : particle_id(id) {}
};

