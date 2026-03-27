#pragma once

#include <random>

#include "class.h"

struct vec3d ScatterAcousticPhonon(vec3d k, material Mat, std::mt19937& gen);
struct vec3d ScatterOpticalPhonon(vec3d k, material Mat, std::mt19937& gen);
struct vec3d ScatterIon(vec3d k, material Mat, std::mt19937& gen);

