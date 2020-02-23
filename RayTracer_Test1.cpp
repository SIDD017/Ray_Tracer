//#include "Vec3.h"
#include "Ray.h"
#include <iostream>

float hit_sphere(const Vec3& center, float radius, Ray r)
{
	Vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - (radius * radius);
	float discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return -1.0;
	else
		return (-b - sqrt(discriminant)) / (2 * a);
}

Vec3 color(const Ray& r)
{
	float t = hit_sphere(Vec3(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		Vec3 N = unit_vector(r.point_at_parameter(t) - Vec3(0, 0, -1));
		return 0.5 * Vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	Vec3 unit_direction = unit_vector(r.direction());
	t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main()
{
	int nx = 1280;
	int ny = 720;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	Vec3 lower_left_corner(-2.0,-1.0,-1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			Vec3 col = color(r);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib= int(255.99 * col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}





/*int main() {
	int nx = 640;
	int ny = 360;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	for (int j = ny - 1; j >= 0; j--) 
	{
		for (int i = 0; i < nx; i++) 
		{
			Vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}*/