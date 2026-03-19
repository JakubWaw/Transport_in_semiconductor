#include "bandstruct.h"
#include "class.h"

double Ek(vec3d k, material Mat) // parabola na początek, h jeszcze podać 
{
	double Ek = hbar*hbar*((k.x)*(k.x)/(2*Mat.mx)+(k.y)*(k.y)/(2*Mat.my)+(k.z)*(k.z)/(2*Mat.mz));
	return Ek;
}

double gradEk_anal(vec3d k, material Mat)
{
	double gradEk = hbar*hbar*((k.x)/(Mat.mx)+(k.y)/(Mat.my)+(k.z)/(Mat.mz));
	return gradEk;
}

double gradEk_Ek_num(vec3d k, material Mat)
{
	double gradEk = ((hbar*hbar*((k.x+delta_k)*(k.x+delta_k)/(2*Mat.mx)+(k.y+delta_k)*(k.y+delta_k)/(2*Mat.my)+(k.z+delta_k)*(k.z+delta_k)
	/(2*Mat.mz)))-(hbar*hbar*((k.x-delta_k)*(k.x-delta_k)/(2*Mat.mx)+(k.y-delta_k)*(k.y-delta_k)/(2*Mat.my)+(k.z-delta_k)*(k.z-delta_k)
	/(2*Mat.mz))))/(2*delta_k);

	return gradEk;
}

