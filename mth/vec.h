/* Property of Cherepkov Petr
 * FILE: 'vec.h'
 * LAST UPDATE: 09.10.2021
 */

#pragma once
#include "matr.h"

class vec3 {
private:
	dbl x, y, z;

public:
	vec3() : x(0), y(0), z(0) {
	}

	vec3(const dbl& x1, const dbl& y1, const dbl& z1) : x(x1), y(y1), z(z1) {
	}

	vec3(const dbl& a) : x(a), y(a), z(a) {
	}

	~vec3() {
	}

	dbl Length2(void) const {
		return x * x + y * y + z * z;
	}

	dbl operator[](int i) const {
		return *(&x + i);
	}

	dbl operator&(const vec3& v2) const {
		return x * v2.x + y * v2.y + z * v2.z;
	}

	vec3 operator%(const vec3& v2) const {
		return vec3(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x);
	}

	dbl operator!(void) const {
		return sqrt(x * x + y * y + z * z);
	}

	vec3 operator*(const dbl& a) const {
		return vec3(x * a, y * a, z * a);
	}

	vec3 operator*(const vec3& v2) const {
		return vec3(x * v2.x, y * v2.y, z * v2.z);
	}

	vec3 operator*(const matr& m) const {
		dbl w = x * m.a[0][3] + y * m.a[1][3] + z * m.a[2][3] + m.a[3][3];
		return vec3((x * m.a[0][0] + y * m.a[1][0] + z * m.a[2][0] + m.a[3][0]) / w,
								(x * m.a[0][1] + y * m.a[1][1] + z * m.a[2][1] + m.a[3][1]) / w,
								(x * m.a[0][2] + y * m.a[1][2] + z * m.a[2][2] + m.a[3][2]) / w);
	}

	vec3 operator*=(const vec3& a) {
		x *= a.x;
		y *= a.y;
		z *= a.z;
		return *this;
	}

	vec3 operator*=(const dbl& a) {
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	vec3 operator/(const vec3& v2) const {
		return vec3(x / v2.x, y / v2.y, z / v2.z);
	}

	vec3 operator/(const dbl& a) const {
		return vec3(x / a, y / a, z / a);
	}

	vec3 operator/=(const dbl& a) {
		x /= a;
		y /= a;
		z /= a;
		return *this;
	}

	vec3 operator/=(const vec3& a) {
		x /= a.x;
		y /= a.y;
		z /= a.z;
		return *this;
	}

	vec3 operator+(const vec3& v2) const {
		return vec3(x + v2.x, y + v2.y, z + v2.z);
	}

	vec3 operator+=(const vec3& a) {
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}

	vec3 operator-(const vec3& v2) const {
		return vec3(x - v2.x, y - v2.y, z - v2.z);
	}

	vec3 operator-(void) const {
		return vec3(-x, -y, -z);
	}

	vec3 operator-=(const vec3& a) {
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}

	vec3 Normalizing(void) const {
		dbl k = 1 / sqrt(Length2());
		vec3 v = *this * k;
		return v;
	}

	vec3 Normalize(void) {
		dbl k = 1 / sqrt(Length2());
		*this = *this * k;
		return *this;
	}

	static matr Rotate(const dbl& angle, const vec3& dir) {
		vec3 v = dir.Normalizing();
		dbl x = D2R(angle), si = sin(x), co = cos(x);

		return matr(
			co + v.x * v.x * (1 - co), v.x * v.y * (1 - co) + v.z * si, v.x * v.z * (1 - co) - v.y * si, 0,
			v.y * v.x * (1 - co) - v.z * si, co + v.y * v.y * (1 - co), v.y * v.z * (1 - co) + v.x * si, 0,
			v.z * v.x * (1 - co) + v.y * si, v.z * v.y * (1 - co) - v.x * si, co + v.z * v.z * (1 - co), 0,
			0, 0, 0, 1
		);
	}

	static matr Scale(const vec3& v) {
		return matr(
			v.x, 0, 0, 0,
			0, v.y, 0, 0,
			0, 0, v.z, 0,
			0, 0, 0, 1
		);
	}

	static matr Translate(const vec3& v) {
		return matr(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			v.x, v.y, v.z, 1
		);
	}

	friend matr;
};

 /* END OF 'vec.h' FILE */