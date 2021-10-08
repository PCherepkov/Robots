/* Property of Cherepkov Petr
 * FILE: 'render.cpp'
 * LAST UPDATE: 08.10.2021
 */

/* rendering functions */

#include "render.h"
#include "../utils/utils.h"

#define BEGIN glPushMatrix(); {
#define END   } glPopMatrix();

void Render(void) {
  vec3
    pos = ani.cam.GetPos(),
    at = ani.cam.GetAt(),
    up = ani.cam.GetUp();

  /* test scene */
  topo smth;
  smth.descr = GL_TRIANGLE_STRIP;

  smth.verts.push_back({ vec3(-1, 0, -1), vec3(0), vec3(0, 1, 0), vec3(1, 0, 0) });
  smth.verts.push_back({ vec3(1, 0, -1), vec3(0), vec3(0, 1, 0), vec3(1, 0.25, 0.25) });
  smth.verts.push_back({ vec3(-1, 0, 1), vec3(0), vec3(0, 1, 0), vec3(0.25, 0.25, 0.25) });
  smth.verts.push_back({ vec3(1, 0, 1), vec3(0), vec3(0, 1, 0), vec3(0.25, 0.25, 0.25) });

  BEGIN
    gluLookAt(pos[0], pos[1], pos[2], at[0], at[1], at[2], 0, 1, 0);
    smth.Draw();
  END

  /* debug output */
  BEGIN
  {
    gluLookAt(pos[0], pos[1], pos[2], at[0], at[1], at[2], 0, 1, 0);
    glMatrixMode(GL_PROJECTION);
    BEGIN
      int w = ani.w, h = ani.h, x = w - 90, y = h - 10;

      glLoadIdentity();
      char buf[32];
      sprintf_s(buf, 32, "%s%f", "fps: ", ani.fps);
      glDisable(GL_LIGHTING);
      Output(x, y, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, buf);
      glEnable(GL_LIGHTING);
    END
    glMatrixMode(GL_MODELVIEW);
  }
  END
}

/* END OF 'render.cpp' FILE */
