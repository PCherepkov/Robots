/* Property of Cherepkov Petr
 * FILE: 'controls.cpp'
 * LAST UPDATE: 08.10.2021
 */

/* control functions */
#include "../def.h"
#include "../rnd/anim.h"
#include "controls.h"

#if 0
void Head(void) {
  // glutSetCursor(GLUT_CURSOR_NONE);

  if (ani.x != ani.w / 2) {
    glutWarpPointer(ani.w / 2, ani.y);
    ani.Response(ani.w / 2, ani.y);
  }
  if (ani.y != ani.h / 2) {
    glutWarpPointer(ani.x, ani.h / 2);
    ani.Response(ani.x, ani.h / 2);
  }

  vec3 at = ani.cam.GetAt(), pos = ani.cam.GetPos();
  if (ani.dx != 0 && ani.w != 0 && true) {
    vec3 new_at = (at - pos) * matr::RotateY(ani.dx * 180 / (dbl)ani.w) + pos;
    ani.cam.SetAt(new_at);
  }
  if (ani.dy != 0 && ani.dy * 2 < ani.h && ani.h != 0 && true) {
    vec3 new_at = (at - pos) * matr::RotateX(ani.dy * 180 / (dbl)ani.h) + pos;
    ani.cam.SetAt(new_at);
  }

  return;
}
#endif

void FlyingWASD(void) {
  vec3
    at = ani.cam.GetAt(),
    pos = ani.cam.GetPos(),
    right = ani.cam.GetRight(),
    dir = ani.cam.GetDir(),
    up = ani.cam.GetUp();

  if (ani.keys['W'] || ani.keys['w']) {
    ani.cam.SetAt(at + dir / ani.fps);
    ani.cam.SetPos(pos + dir / ani.fps);
  }

  if (ani.keys['S'] || ani.keys['s']) {
    ani.cam.SetAt(at - dir / ani.fps);
    ani.cam.SetPos(pos - dir / ani.fps);
  }

  if (ani.keys['D'] || ani.keys['d']) {
    ani.cam.SetAt(at + right / ani.fps);
    ani.cam.SetPos(pos + right / ani.fps);
  }

  if (ani.keys['A'] || ani.keys['a']) {
    ani.cam.SetAt(at - right / ani.fps);
    ani.cam.SetPos(pos - right / ani.fps);
  }

  if (ani.keys[VK_SHIFT]) {
    ani.cam.SetAt(at - up / ani.fps);
    ani.cam.SetPos(pos - up / ani.fps);
  }

  if (ani.keys[VK_SPACE]) {
    ani.cam.SetAt(at + up / ani.fps);
    ani.cam.SetPos(pos + up / ani.fps);
  }

  // Head();
  return;
}

/* END OF 'controls.cpp' FILE */
