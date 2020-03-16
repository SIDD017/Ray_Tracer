#pragma once
#ifndef RANDOMH
#define RANDOMH

#include <cstdlib>

inline double random_double()
{
	return rand() / (RAND_MAX + 1.0);
}

Vec3 random_in_unit_sphere() {
    Vec3 p;
    do {
        p = 2.0 * Vec3(random_double(), random_double(), random_double()) - Vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}
#endif