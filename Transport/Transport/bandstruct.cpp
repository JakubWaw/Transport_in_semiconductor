#include "bandstruct.h"
#include "class.h"

double Ek(vec3d k, material Mat) // parabola na początek, h jeszcze podać 
{
	Ek = h*h((k.x)*(k.x)/(2*meff_l)+(k.y)(k.y)/(2*meff_l)+(k.z)(k.z)/(2*meff_t)
	return Ek;
}