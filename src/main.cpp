#include<fstream>
#include"sphere.h"
#include"hitablelist.h"
#include"camera.h"
#include<float.h>
#include<random>
#include"helper.h"
#include"material.h"


vector3 color(const ray& r,hitable *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		ray scattered;
		vector3 attenuation;
		if(depth<50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else { return vector3(0, 0, 0); }
;	}
	else
	{
		vector3 unit_dir = unit_vector(r.direction());
		float t = 0.5*(unit_dir.y() + 1.0);
		return (1.0 - t)*vector3(1.0, 1.0, 1.0) + t * vector3(0.5, 0.7, 1.0);
	}
}

extern std::uniform_real_distribution<float> urd;
extern std::default_random_engine dre;

hitable *random_scene()
{
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vector3(0, -1000, 0), 1000, new lambertian(vector3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = urd(dre);
			vector3 center(a + 0.9*urd(dre), 0.2, b + 0.9*urd(dre));
			if ((center - vector3(4, 0.2, 0)).length() > 0.9)
			{
				if(choose_mat<0.8)
				{
					list[i++] = new sphere(center, 0.2, new lambertian(vector3(urd(dre)*urd(dre), urd(dre)*urd(dre), urd(dre)*urd(dre))));
				}
				else if (choose_mat < 0.95)
				{
					list[i++] = new sphere(center, 0.2, new metal(vector3(0.5*(1 + urd(dre)), 0.5*(1 + urd(dre)), 0.5*(1 + urd(dre))), 0.5*urd(dre)));
				}
				else
				{
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vector3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vector3(-4, 1, 0), 1.0, new lambertian(vector3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vector3(4, 1, 0), 1.0, new metal(vector3(0.7, 0.6, 0.5), 0.0));
	return new hitable_list(list, i);
}

int main()
{
	int nx = 1200, ny = 800,ns = 10;
	std::ofstream result("result.ppm");
	result << "P3\n" << nx << " " << ny << "\n255\n";
	/*
	hitable *list[4];
	list[0] = new sphere(vector3(0, 0, -1), 0.5,new lambertian(vector3(0.1,0.2,0.5)));
	list[1] = new sphere(vector3(0, -100.5, -1), 100, new lambertian(vector3(0.8,0.8,0.0)));
	list[2] = new sphere(vector3(1, 0, -1), 0.5, new metal(vector3(0.8, 0.6, 0.2),0.0));
	list[3] = new sphere(vector3(-1, 0, -1), 0.5, new dielectric(1.5));
	//list[4] = new sphere(vector3(-1, 0, -1), -0.45, new dielectric(1.5));
	hitable *world = new hitable_list(list, 4);
	*/
	hitable *world = random_scene();
	camera cam(vector3(13,2,3),vector3(0,0,0),vector3(0,1,0),20,float(nx)/float(ny));
	for (int j = ny - 1; j>=0; --j)
	{
		for (int i = 0; i < nx; i++)
		{
			vector3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + urd(dre)) / float(nx);
				float v = float(j + urd(dre)) / float(ny);
				ray r = cam.get_ray(u, v);
				vector3 p = r.point_at_parameter(2.0);
				col += color(r, world,0);
			}
			col /= float(ns);
			col = vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			result << int(col.r() * 255.99) << " " << int(col.g() * 255.99) << " " << int(col.b() * 255.99) << "\n";
		}
	}
	return 0;
}