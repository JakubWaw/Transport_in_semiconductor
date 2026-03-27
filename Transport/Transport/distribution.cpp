#include <cstdlib>
#include <math.h>
#include <random>

#include "distribution.h"
#include "class.h"


double Poisson(double tau, std::mt19937& gen)
{
	//This function returns time of next event with constant probability gamma = 1/tau
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	double U; 
	do {
		U = dist(gen);
	} while (U < 0.001); //jak za male to czas sie robi w chuj duzy

	return -log(U) * tau;
}

struct vec2d UniAngles(std::mt19937& gen)
{
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	double U = dist(gen); // w [0,1]
	double V = dist(gen); // w [0,1]

	double psi = acos(1 - 2 * U);
	double phi = 2 * PI * V;
	return vec2d(psi, phi);
}

struct vec3d RandKFromE(double E, material Mat, std::mt19937& gen)
{
	vec2d Angles = UniAngles(gen);
	double psi = Angles.x;
	double phi = Angles.y;

	double q1 = sqrt(2 * E / (hbar * hbar));

	vec3d q2 = vec3d(q1 * sin(psi) * cos(phi), q1 * sin(psi) * sin(phi), q1 * cos(psi));
	vec3d k = vec3d(q2.x * sqrt(Mat.mx), q2.y * sqrt(Mat.my), q2.z * sqrt(Mat.mz));

	return k;
}

double uniform01(std::mt19937& gen)
{
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	double U = dist(gen);
    return U; // unika 0 i 1
}

double normal01(std::mt19937& gen)
{
    // Box-Muller
    double u1 = uniform01(gen);
    double u2 = uniform01(gen);
    return sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);
}

vec3d Boltzmannk(material Mat, std::mt19937& gen)
{
    double zx = normal01(gen);
    double zy = normal01(gen);
    double zz = normal01(gen);

    double sx = sqrt(Mat.mx * kB * Mat.T) / hbar;
    double sy = sqrt(Mat.my * kB * Mat.T) / hbar;
    double sz = sqrt(Mat.mz * kB * Mat.T) / hbar;

    return vec3d(sx * zx, sy * zy, sz * zz);
}