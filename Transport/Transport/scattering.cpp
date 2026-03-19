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
		Ep = E - Mat.omega0;
	}
	else
	{
		Ep = E + Mat.omega0;
	}

	vec3d kp = RandKFromE(Ep, Mat);

	return kp;
}

struct vec3d ScatterIon(vec3d k, material Mat)
{
	double E = Ek(k, Mat);

	double Ep = E;



	//vec3d kp = RandKFromE(Ep, Mat);

	return kp;
}