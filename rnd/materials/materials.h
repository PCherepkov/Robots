/* Property of Cherepkov Petr
 * FILE: 'materials.h'
 * LAST UPDATE: 15.03.2023
 */

#pragma once

#include "../../def.h"

class mtl {
public:
	vec3 ka, kd, ks;
	flt ph;
	string name;

	mtl() : ka(0.1), kd(0.1), ks(0.1), ph(1), name("DEFAULT") {}
	mtl(const string &s) : ka(0.1), kd(0.1), ks(0.1), ph(0.1), name(s) {}
	mtl(vec3 a, vec3 d, vec3 s, flt p) : ka(a), kd(d), ks(s), ph(p), name("") {}
};

/* END OF 'materials.h' FILE */
