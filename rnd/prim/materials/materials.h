/* Property of Cherepkov Petr
 * FILE: 'materials.h'
 * LAST UPDATE: 09.12.2023
 */

#pragma once

#include "../../../def.h"

class mtl {
public:
	vec3 ka, kd, ks;
	flt ph;
	string name;

	mtl();
	mtl(const string& s);
	mtl(vec3 a, vec3 d, vec3 s, flt p);
};

/* END OF 'materials.h' FILE */
