#include <cstdlib>
#include <math.h>

#include "scattering.h"
#include "class.h"
#include "bandstruct.h"
#include "distribution.h"


struct vec3d ScatterAcousticPhonon(vec3d k, material Mat)
{
	double E = Ek(k, Mat);

	double Ep = E;

	vec3d kp = RandKFromE(Ep, Mat);

	return kp;
}

struct vec3d ScatterOpticalPhonon(vec3d k, material Mat)
{
	double E = Ek(k, Mat);

	//wylosuj czy emisja czy absobcja
	bool emmit = 0;

	double Ep;
	if (emmit == 1)
	{
		Ep = E - Mat.omega0 * hbar;
	}
	else
	{
		Ep = E + Mat.omega0 * hbar;
	}

	vec3d kp = RandKFromE(Ep, Mat);

	return kp;
}

struct vec3d ScatterIon(vec3d k, material Mat)
{
	double E = Ek(k, Mat);

	double Ep = E;



	double U = double((rand() % 1000)) / 1000.0;
	double V = double((rand() % 1000)) / 1000.0;

	double cos_psi = 1.0 - (2.0 * (1.0 - U)) / (1.0 + U * ((4.0 * k * k) / (Mat.qs * Mat.qs)));
	double phi = V * 2.0 * PI;

	double sin_psi = sqrt(1 - cos_psi * cos_psi);

	double q1 = sqrt(2 * Ep / (hbar * hbar));

	double ux = k.x / (k * k);
	double uy = k.y / (k * k);
	double uz = k.z / (k * k);

	double ax = 0;
	double ay = 0;
	double az = 1;

	double vx = ay * uz - az * uy;
	double vy = az * ux - ax * uz;
	double vz = ax * uy - ay * ux;

	double wx = uy * vz - uz * vy;
	double wy = uz * vx - ux * vz;
	double wz = ux * vy - uy * vx;

	double uxp = cos_psi * ux + sin_psi * cos(phi) * vx + sin_psi * sin(phi) * wx;
	double uyp = cos_psi * uy + sin_psi * cos(phi) * vy + sin_psi * sin(phi) * wy;
	double uzp = cos_psi * uz + sin_psi * cos(phi) * vz + sin_psi * sin(phi) * wz;



	vec3d q2 = vec3d(q1 * uxp, q1 * uyp, q1 * uzp);
	vec3d kp = vec3d(q2.x * Mat.mx, q2.y * Mat.my, q2.z * Mat.mz);

	return kp;
}