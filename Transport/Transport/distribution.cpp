#include <cstdlib>
#include <math.h>

#include "distribution.h"
#include "class.h"


double Poisson(double tau)
{
	//This function returns time of next event with constant probability gamma = 1/tau
	double U = double((rand() % 1000))/1000.0;
	return -log(U) * tau;
}

struct vec2d UniAngles()
{
	double U = double((rand() % 1000)) / 1000.0;
	double V = double((rand() % 1000)) / 1000.0;

	double psi = acos(1 - 2 * U);
	double phi = 2 * PI * V;
	return vec2d(psi, phi);
}

double BoltzmannE(double T)
{
	//Funkcja ta nie uwzglednia zmiennej DOS w funkcji E
	double U = double((rand() % 1000)) / 1000.0;
	double E = -kB * T * log(U);
	return E;
}

struct vec3d RandKFromE(double E, material Mat)
{
	vec2d Angles = UniAngles();
	double psi = Angles.x;
	double phi = Angles.y;

	double q1 = sqrt(2 * E / (hbar * hbar));

	vec3d q2 = vec3d(q1 * sin(psi) * cos(phi), q1 * sin(psi) * sin(phi), q1 * cos(psi));
	vec3d k = vec3d(q2.x * sqrt(Mat.mx), q2.y * sqrt(Mat.my), q2.z * sqrt(Mat.mz));

	return k;
}

struct vec3d Boltzmannk(double T, material Mat)
{
	//Funkcja ta losuje od razu k, wiec uwzglednia DOS
	double U = double((rand() % 1000)) / 1000.0;
	double V = double((rand() % 1000)) / 1000.0;
	double Y = double((rand() % 1000)) / 1000.0;

	vec3d q = vec3d(U * kB * T / (hbar * hbar), U * kB * T / (hbar * hbar), U * kB * T / (hbar * hbar));

	vec3d k = vec3d(q.x*sqrt(Mat.mx), q.y * sqrt(Mat.my), q.z * sqrt(Mat.mz));

	return k;
}

double uniform01()
{
    return (rand() + 1.0) / (RAND_MAX + 2.0); // unika 0 i 1
}

double normal01()
{
    // Box-Muller
    double u1 = uniform01();
    double u2 = uniform01();
    return sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);
}

vec3d Boltzmannk(material Mat)
{
    double zx = normal01();
    double zy = normal01();
    double zz = normal01();

    double sx = sqrt(Mat.mx * kB * Mat.T) / hbar;
    double sy = sqrt(Mat.my * kB * Mat.T) / hbar;
    double sz = sqrt(Mat.mz * kB * Mat.T) / hbar;

    return vec3d(sx * zx, sy * zy, sz * zz);
}