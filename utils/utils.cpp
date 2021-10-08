/* Property of Cherepkov Petr
 * FILE: 'utils.cpp'
 * LAST UPDATE: 07.10.2021
 */

 /* other utils functions */

#include "../def.h"
#include "../rnd/render.h"
#include "utils.h"

void Output(int x, int y, dbl r, dbl g, dbl b, void* font, const char* string) {
  dbl w = ani.w, h = ani.h;
  vec3
    dir = ani.cam.GetDir(), right = ani.cam.GetRight(), pos = ani.cam.GetPos(),
    up = ani.cam.GetUp(),
    res = pos + right * (0.5 - x / w) * 2 + up * (y / h - 0.5) * 2;

  glColor3d(r, g, b);
  glRasterPos3d(res[0], res[1], res[2]);
  int len = (int)strlen(string);
  for (int i = 0; i < len; i++)
    glutBitmapCharacter(font, string[i]);
}

/* END OF 'utils.cpp' FILE */
