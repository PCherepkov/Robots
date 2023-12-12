/* Property of Cherepkov Petr
 * FILE: 'materials.cpp'
 * LAST UPDATE: 09.12.2023
 */

#include "materials.h"

mtl::mtl() : ka(0.1), kd(0.1), ks(0), ph(1), name("DEFAULT") {}

mtl::mtl(const string& s) : ka(0.1), kd(0.1), ks(0), ph(0.1), name(s) {}

mtl::mtl(vec3 a, vec3 d, vec3 s, flt p) : ka(a), kd(d), ks(s), ph(p), name("") {}

/* END OF 'materials.cpp' FILE */
