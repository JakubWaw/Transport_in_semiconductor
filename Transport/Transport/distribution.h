#pragma once

#include "class.h"

double Poisson(double tau);

vec2d UniAngles();

double BoltzmannE(double T);

vec3d RandKFromE(double E, material Mat);

vec3d Boltzmannk(double T, material Mat);


