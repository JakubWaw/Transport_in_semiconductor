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

	material Si = material(0.98 * m0, 0.98 * m0, 0.19 * m0, pow(10, -13.5), pow(10, -12.5), pow(10, -10), 1.2 * 10e16, 200, 15.6 * pow(10, 12), 1e1);
	double Ek_Si = Ek(vec3d(10e10, 10e10, 10e10), Si);

	//std::cout<< Ek_Si;

	vec3d Si_200K_Ee5 = CalcMeanDrift(200, vec3d(1e5, 0, 0), Si, 10);


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

