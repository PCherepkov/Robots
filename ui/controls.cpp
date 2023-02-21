/* Property of Cherepkov Petr
 * FILE: 'controls.cpp'
 * LAST UPDATE: 21.02.2023
 */

/* control functions */
#include "../def.h"
#include "../rnd/anim.h"
#include "controls.h"


void Head(void) {
    vec3 at = ani.cam.GetAt(), pos = ani.cam.GetPos();
    if (ani.dx != 0 && ani.w != 0) {
        vec3 new_at = translate(mat4(1.0f), pos) * rotate(mat4(1.0f), radians(-(flt)ani.dx * 180 / ani.w), ani.cam.GetUp()) * vec4(at - pos, 1.0);
        ani.cam.SetAt(new_at);
		at = new_at;
    }
    if (ani.dy != 0 && ani.h != 0) {
        flt angle = radians(-(flt)ani.dy * 180 / ani.h), pitch = ani.cam.GetPitch(),
            new_angle = pitch - angle;
        if (new_angle > PI * 0.99)
            return;
        else if (new_angle < PI * 0.01)
            return;
        vec3 new_at = translate(mat4(1.0f), pos) * rotate(mat4(1.0f), angle, ani.cam.GetRight()) * vec4(at - pos, 1.0);
		ani.cam.SetAt(new_at);
    }
    return;
}


void FlyingWASD(void) {
    vec3
      at = ani.cam.GetAt(),
      pos = ani.cam.GetPos(),
      right = ani.cam.GetRight(),
      dir = ani.cam.GetDir(),
      up = ani.cam.GetUp();
    flt speed = 8.f * ani.delta_time;

    vec3 move =
        dir * (speed * (ani.keys['W'] || ani.keys['w'])) - 
        dir * (speed * (ani.keys['S'] || ani.keys['s'])) +
        right * (speed * (ani.keys['D'] || ani.keys['d'])) -
        right * (speed * (ani.keys['A'] || ani.keys['a'])) +
        up * (speed * (ani.keys[GLFW_KEY_SPACE])) -
        up * (speed * (ani.keys[GLFW_KEY_LEFT_SHIFT]));
    ani.cam.SetAt(at + move);
    ani.cam.SetPos(pos + move);

    Head();
    return;
}

/* END OF 'controls.cpp' FILE */
