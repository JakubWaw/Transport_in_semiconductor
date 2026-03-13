#pragma once

#include "class.h"

double Ek(vec3d k, material Mat);

double gradEk_anal(vec3d k, material Mat);

double gradEk_Ek_num(vec3d k, material Mat);
