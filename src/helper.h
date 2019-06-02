#pragma once

#include"vector.h"
#include<random>

extern std::uniform_real_distribution<float> urd;
extern std::default_random_engine dre;

vector3 random_in_unit_sphere();

vector3 reflect(const vector3& v, const vector3& n);

bool refract(const vector3& v, const vector3& n, float ni_over_nt, vector3& refracted);

float schlick(float cosine, float ref_idx);
