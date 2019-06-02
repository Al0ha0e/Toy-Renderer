#include"helper.h"

#include"helper.h"
#include<random>

std::uniform_real_distribution<float> urd(0, 1);
std::default_random_engine dre;

vector3 random_in_unit_sphere()
{
	vector3 p;
	do
	{
		p = 2.0*vector3(urd(dre), urd(dre), urd(dre)) - vector3(1, 1, 1);
	} while (p.length2() >= 1.0);
	return p;
}


vector3 reflect(const vector3& v, const vector3& n)
{
	return v - 2 * dot(v, n)*n;
}

bool refract(const vector3& v, const vector3& n, float ni_over_nt, vector3& refracted)
{
	vector3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt*(1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	return false;
}

float schlick(float cosine, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}
