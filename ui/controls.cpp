/* Property of Cherepkov Petr
 * FILE: 'controls.cpp'
 * LAST UPDATE: 15.02.2023
 */

/* control functions */
#include "../def.h"
#include "../rnd/anim.h"
#include "controls.h"

#if 1
void Head(void) {
    // glutSetCursor(GLUT_CURSOR_NONE);
#if 0    
    if (ani.x != ani.w / 2) {
        glutWarpPointer(ani.w / 2, ani.y);
        ani.Response(ani.w / 2, ani.y);
    }
    if (ani.y != ani.h / 2) {
        glutWarpPointer(ani.x, ani.h / 2);
        ani.Response(ani.x, ani.h / 2);
    }
#endif
    
    vec3 at = ani.cam.GetAt(), pos = ani.cam.GetPos();
    if (ani.dx != 0 && ani.w != 0) {
        vec3 new_at = translate(mat4(1.0f), pos) * rotate(mat4(1.0f), radians(-(flt)ani.dx * 180 / ani.w), ani.cam.GetUp()) * vec4(at - pos, 1.0);
        ani.cam.SetAt(new_at);
		at = new_at;
    }
    if (ani.dy != 0 && ani.h != 0) {
        flt angle = -(flt)ani.dy * 180 / ani.h, elev = ani.cam.GetElev(),
            new_angle = elev - angle;
        if (new_angle > PI * 0.99)
            angle = elev - PI * 0.99;
        else if (new_angle < PI * 0.01)
            angle = elev - PI * 0.01;
        vec3 new_at = translate(mat4(1.0f), pos) * rotate(mat4(1.0f), radians(angle), ani.cam.GetRight()) * vec4(at - pos, 1.0);
        flt co = dot(normalize(new_at), vec3(0, 1, 0));
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
  flt speed = 8.f * ani.delta_time;

  if (ani.keys['W'] || ani.keys['w']) {
    ani.cam.SetAt(at + dir * speed);
    ani.cam.SetPos(pos + dir * speed);
    at = ani.cam.GetAt();
    pos = ani.cam.GetPos();
  }

  if (ani.keys['S'] || ani.keys['s']) {
    ani.cam.SetAt(at - dir * speed);
    ani.cam.SetPos(pos - dir * speed);
    at = ani.cam.GetAt();
    pos = ani.cam.GetPos();
  }

  if (ani.keys['D'] || ani.keys['d']) {
    ani.cam.SetAt(at + right * speed);
    ani.cam.SetPos(pos + right * speed);
    at = ani.cam.GetAt();
    pos = ani.cam.GetPos();
  }

  if (ani.keys['A'] || ani.keys['a']) {
    ani.cam.SetAt(at - right * speed);
    ani.cam.SetPos(pos - right * speed);
    at = ani.cam.GetAt();
    pos = ani.cam.GetPos();
  }

  if (ani.keys[GLFW_KEY_LEFT_SHIFT]) {
    ani.cam.SetAt(at - up * speed);
    ani.cam.SetPos(pos - up * speed);
    at = ani.cam.GetAt();
    pos = ani.cam.GetPos();
  }

  if (ani.keys[GLFW_KEY_SPACE]) {
    ani.cam.SetAt(at + up * speed);
    ani.cam.SetPos(pos + up * speed);
  }

  // Head();
  return;
}

/* END OF 'controls.cpp' FILE */
