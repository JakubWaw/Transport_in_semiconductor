#pragma once

#include "class.h"

double Poisson(double tau);

struct vec2d UniAngles();

double BoltzmannE(double T);

struct vec3d RandKFromE(double E, material Mat);

struct vec3d Boltzmannk(double T, material Mat);


