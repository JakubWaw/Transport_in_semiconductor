// external libraries
#include <iostream>


//Uzywajmy w kodzie jednostek SI, bez jakis eV czy innych udziwnien bo potem sie wszystko pierdoli

double m0 = 9.10938356e-31; // kg


// project headers
#include "class.h"
#include "scattering.h"
#include "dossier.h"
#include "evolution.h"
#include "distribution.h"
#include "bandstruct.h"


int main()
{

	material Si = material(0.98*m0, 0.19*m0, 10e-12, 10e-20, 10e-14, 10e-15);
	double Ek_Si = Ek(vec3d(10e10, 10e10, 10e10), Si);

	std::cout<< Ek_Si;

	return 0;

}

