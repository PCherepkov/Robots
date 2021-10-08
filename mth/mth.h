/* Property of Cherepkov Petr
 * FILE: 'mth.h'
 * LAST UPDATE: 07.10.2021
 */

#pragma once

/* maths handling functions */

#include <Windows.h>
typedef double dbl;

#define PI 3.1415926535897932384626433832795

class vec3 {
private:
	dbl x, y, z;

public:
	vec3() : x(0), y(0), z(0) {
	}

	vec3(dbl x1, dbl y1, dbl z1) : x(x1), y(y1), z(z1) {
	}

	vec3(dbl a) : x(a), y(a), z(a) {
	}

	~vec3() {
	}

	dbl Length2(void) const {
		return x * x + y * y + z * z;
	}

	dbl operator[](int i) const {
		return *(&x + i);
	}

	dbl operator&(vec3 v2) const {
		return x * v2.x + y * v2.y + z * v2.z;
	}

	vec3 operator%(vec3 v2) const {
		return vec3(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x);
	}

	vec3 operator+(vec3 v2) const {
		return vec3(x + v2.x, y + v2.y, z + v2.z);
	}

	vec3 operator-(vec3 v2) const {
		return vec3(x - v2.x, y - v2.y, z - v2.z);
	}

	vec3 operator-(void) const {
		return vec3(-x, -y, -z);
	}

	vec3 operator*(vec3 v2) const {
		return vec3(x * v2.x, y * v2.y, z * v2.z);
	}

	vec3 operator*(dbl a) const {
		return vec3(x * a, y * a, z * a);
	}

	vec3 operator/(vec3 v2) const {
		return vec3(x / v2.x, y / v2.y, z / v2.z);
	}

	vec3 operator/(dbl a) const {
		return vec3(x / a, y / a, z / a);
	}

	dbl operator!(void) const {
		return sqrt(x * x + y * y + z * z);
	}

	vec3 operator*=(dbl a) {
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	vec3 operator/=(dbl a) {
		x /= a;
		y /= a;
		z /= a;
		return *this;
	}

	vec3 operator*=(vec3 a) {
		x *= a.x;
		y *= a.y;
		z *= a.z;
		return *this;
	}

	vec3 operator/=(vec3 a) {
		x /= a.x;
		y /= a.y;
		z /= a.z;
		return *this;
	}

	vec3 operator+=(vec3 a) {
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}

	vec3 operator-=(vec3 a) {
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}

	vec3 Normalizing(void) const
	{
		dbl k = 1 / sqrt(Length2());
		vec3 v = *this * k;
		return v;
	}

	vec3 Normalize(void)
	{
		dbl k = 1 / sqrt(Length2());
		*this = *this * k;
		return *this;
	}
};

/* END OF 'mth.h' FILE */
