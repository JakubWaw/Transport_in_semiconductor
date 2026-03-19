// external libraries
#include <iostream>
#include <vector>

// project headers
#include "class.h"
#include "scattering.h"
#include "dossier.h"
#include "evolution.h"
#include "distribution.h"
#include "bandstruct.h"


int main()
{

	material Si = material(0.98*m0, 0.98*m0, 0.19*m0, pow(10,-13.5), pow(10,-12.5), pow(10,-10), 1.2*10e16);
	double Ek_Si = Ek(vec3d(10e10, 10e10, 10e10), Si);

	std::cout<< Ek_Si;

	return 0;

}

