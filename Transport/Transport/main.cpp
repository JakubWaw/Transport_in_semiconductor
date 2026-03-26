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

	

	double Tau_Si_Ac = pow(10, -12.5);
	double Tau_Si_Op = pow(10, -13.5);
	double Tau_Si_Ion = pow(10, -10);
	material Si = material(0.98 * m0, 0.98 * m0, 0.19 * m0, Tau_Si_Op, Tau_Si_Ac, Tau_Si_Ion, 1.2 * 10e16, 200, 15.6 * pow(10, 12) * 2.0 * PI, 0); //dla normalnego Q_s cos wolno sie liczy

	//Si.T = 20;
	//std::cout << 1.0 / (exp((hbar * Si.omega_0) / (kB * Si.T)) - 1.0) << std::endl;

	//std::cout << Si.tau_ac << " " << Si.tau_op << " " << Si.tau_ion << std::endl;
	//std::cout<< Ek_Si;
	//std::cout << Poisson(Si.tau_ac) << std::endl;
	//std::cout << Boltzmannk(Si).x << " " << Boltzmannk(Si).y << " " << Boltzmannk(Si).z << std::endl;
	double MaxTime = pow(10, -9);
	vec3d Si_200K_Ee5 = CalcMeanDrift(200, vec3d(0, 0, 0), Si, 1000, MaxTime); //1e+5
	//std::cout << "Mean drift for Si at 200K and E = 1e7 V/m: " << Si_200K_Ee5.x << " " << Si_200K_Ee5.y << " " << Si_200K_Ee5.z << std::endl;
	std::cout << "Mean drift for Si at 200K and E = 1e2 V/m: " << Si_200K_Ee5 / MaxTime << std::endl;

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

