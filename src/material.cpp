/*
#include"material.h"

bool lambertian::scatter(const ray& r_in, const hit_record& rec, vector3& attenuation, ray& scattered) const
{
	vector3 target = rec.p + rec.normal + random_in_unit_sphere();
	scattered = ray(rec.p, target - rec.p);
	attenuation = albedo;
	return true;
}

bool metal::scatter(const ray& r_in, const hit_record& rec, vector3& attenuation, ray& scattered) const
{
	vector3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	scattered = ray(rec.p, reflected);
	attenuation = albedo;
	return(dot(scattered.direction(), rec.normal) > 0);
}*/