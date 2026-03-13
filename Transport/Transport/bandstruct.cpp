#include "bandstruct.h"
#include "class.h"

double Ek(vec3d k, material Mat) // parabola na początek, h jeszcze podać 
{
	double Ek = hbar*hbar*((k.x)*(k.x)/(2*Mat.meff_l)+(k.y)*(k.y)/(2*Mat.meff_l)+(k.z)*(k.z)/(2*Mat.meff_t));
	return Ek;
}

double gradEk_anal(vec3d k, material Mat)
{
	double gradEk = hbar*hbar*((k.x)/(Mat.meff_l)+(k.y)/(Mat.meff_l)+(k.z)/(Mat.meff_t));
	return gradEk;
}

double gradEk_Ek_num(vec3d k, material Mat)
{
	double gradEk = ((hbar*hbar*((k.x+delta_k)*(k.x+delta_k)/(2*Mat.meff_l)+(k.y+delta_k)*(k.y+delta_k)/(2*Mat.meff_l)+(k.z+delta_k)*(k.z+delta_k)
	/(2*Mat.meff_t)))-(hbar*hbar*((k.x-delta_k)*(k.x-delta_k)/(2*Mat.meff_l)+(k.y-delta_k)*(k.y-delta_k)/(2*Mat.meff_l)+(k.z-delta_k)*(k.z-delta_k)
	/(2*Mat.meff_t))))/(2*delta_k);

	return gradEk;
}

