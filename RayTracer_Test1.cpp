#include "Ray.h"
#include "float.h"
#include "Hittable_list.h"
#include "Sphere.h"
#include "Camera.h"
#include "Random.h"
#include "Material.h"
#include <iostream>


Vec3 color(const Ray& r, Hittable *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		Ray scattered;
		Vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return Vec3(0, 0, 0);
		}
	}
	else {
		Vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

Hittable* random_scene()
{
	int n = 500;
	Hittable** list = new Hittable * [n + 1];
	list[0] = new Sphere(Vec3(0, -1000, 0), 1000, new lambertian(Vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -8; a < 8; a++)
	{
		for (int b = -8; b < 8; b++)
		{
			float choose_mat = random_double();
			Vec3 center(a + 8.0 * random_double(), 0.2, b + 8.0 * random_double());
			if ((center - Vec3(4, 0, 2.0)).length() > 0.9)
			{
				if (choose_mat < 0.8)
				{
					list[i++] = new Sphere(center, 0.2, new lambertian(Vec3(random_double() * random_double(), random_double() * random_double(), random_double() * random_double())));
				}
				else if (choose_mat < 0.95)
				{
					list[i++] = new Sphere(center, 0.2, new metal(Vec3(0.5 * (1 + random_double()), 0.5 * (1 + random_double()), 0.5 * (1 + random_double())), 0.5 * random_double()));
				}
				else
				{
					list[i++] = new Sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new Sphere(Vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0, new lambertian(Vec3(0.4, 0.2, 0.1)));
	list[i++] = new Sphere(Vec3(4, 1, 0), 1.0, new metal(Vec3(0.7, 0.6, 0.5), 0.0));

	return new Hittable_list(list, i);
}

int main()
{
	int nx = 640;
	int ny = 360;
	int ns = 32;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	Vec3 lower_left_corner(-2.0,-1.0,-1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);

	/*Hittable* list[5];
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new lambertian(Vec3(0.1,0.2,1)));
	list[1] = new Sphere(Vec3(0, -100.5, -1), 100, new lambertian(Vec3(0.8,0.8,0.0)));
	list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new metal(Vec3(0.8, 0.6, 0.2), 0.0));
	list[3] = new Sphere(Vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new Sphere(Vec3(-1, 0, -1), -0.49, new dielectric(1.5));
	Hittable* world = new Hittable_list(list, 5);*/

	Hittable *world = random_scene();

	Vec3 lookfrom(13, 2, 3);
	Vec3 lookat(0, 0, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;
	Camera cam(lookfrom, lookat, Vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + random_double()) / float(nx);
				float v = float(j + random_double()) / float(ny);
				Ray r = cam.get_ray(u, v);
				col += color(r, world,0);
			}
			col /= float(ns);
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib= int(255.99 * col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}