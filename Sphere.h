#ifndef SPHEREH
#define SPHEREH

#include "Hittable.h"
#include "Random.h"

class Sphere : public Hittable
{
public:
	Sphere() {}
	Sphere(Vec3 cen, float r, Material *m) : center(cen), radius(r), mat_ptr(m){};
	Vec3 center;
	float radius;
	Material* mat_ptr;
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const;
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const 
{
	Vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;     //Redundant 2's omitted
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp<t_max && temp>t_min)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp<t_max && temp>t_min)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

#endif
