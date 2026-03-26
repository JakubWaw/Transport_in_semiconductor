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
	srand(time(NULL));

	material Si = material(0.98 * m0, 0.98 * m0, 0.19 * m0, pow(10, -13.5), pow(10, -12.5), pow(10, -10), 1.2 * 10e16, 200, 15.6 * pow(10, 12), 0);
	double Ek_Si = Ek(vec3d(10e10, 10e10, 10e10), Si);

	//std::cout<< Ek_Si;
	//std::cout << Poisson(Si.tau_ac) << std::endl;
	//std::cout << Boltzmannk(Si).x << " " << Boltzmannk(Si).y << " " << Boltzmannk(Si).z << std::endl;
	vec3d Si_200K_Ee5 = CalcMeanDrift(200, vec3d(0, 0, 0), Si, 2);
	std::cout << "Mean drift for Si at 200K and E = 1e5 V/m: " << Si_200K_Ee5.x << " " << Si_200K_Ee5.y << " " << Si_200K_Ee5.z << std::endl;

	// tempartaura
	// mat SI.t_op = 

	// std::cout <<1e10<< std::endl;

	// ScatterIon(vec3d(1e10, 0, 0), Si);
	// ScatterIon(vec3d(1e10, 0, 0), Si);
	// ScatterIon(vec3d(1e10, 0, 0), Si);
	// ScatterIon(vec3d(1e10, 0, 0), Si);

	// std::cout << std::endl;
	// ScatterAcousticPhonon(vec3d(1e10, 0, 0), Si);
	// ScatterAcousticPhonon(vec3d(1e10, 0, 0), Si);
	// ScatterAcousticPhonon(vec3d(1e10, 0, 0), Si);
	// ScatterAcousticPhonon(vec3d(1e10, 0, 0), Si);

	return 0;

}

