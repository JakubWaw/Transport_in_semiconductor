#pragma once

#include <random>

#include "class.h"

double Poisson(double tau, std::mt19937& gen);

struct vec2d UniAngles(std::mt19937& gen);

struct vec3d RandKFromE(double E, material Mat, std::mt19937& gen);

struct vec3d Boltzmannk(material Mat, std::mt19937& gen);


