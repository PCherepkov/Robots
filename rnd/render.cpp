/* Property of Cherepkov Petr
 * FILE: 'render.cpp'
 * LAST UPDATE: 19.10.2021
 */

/* rendering functions */

#include "render.h"
#include "../utils/utils.h"

#define BEGIN glPushMatrix(); {
#define END   } glPopMatrix();

void RenderInit(GLFWwindow* window) {
  vec3
    pos = ani.cam.GetPos(),
    at = ani.cam.GetAt(),
    up = ani.cam.GetUp();

  prim smth(std::vector<vertex>({
    { vec3(-1, -1, 0), vec3(0), vec3(0, 1, 0), vec3(0.8) },
    { vec3(-1, 1, 0), vec3(0), vec3(0, 1, 0), vec3(1, 0, 0) },
    { vec3(1, 1, 0), vec3(0), vec3(0, 1, 0), vec3(0.8) },
    { vec3(1, -1, 0), vec3(0), vec3(0, 1, 0), vec3(0.5, 0.25, 0.25) },
    }), std::vector<uint>({0, 1, 3, 2}));

  ani.AddPrim(smth);
}

void Render(GLFWwindow* window) {
  glClearColor(0.17, 0.1603, 0.209, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (anim::GetRef().is_wire_frame)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  std::vector<prim> prs;
  ani.GetPrims(&prs);
  for (auto pr : prs) {
    pr.Draw();
  }

  /* debug output */
#if 0
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
      sprintf_s(buf, 32, "%s%d%s%d", "x: ", ani.x, " y: ", ani.y);
      Output(x, y - 10, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, buf);
      glEnable(GL_LIGHTING);
    END
    glMatrixMode(GL_MODELVIEW);
  }
    END
#endif
}

/* END OF 'render.cpp' FILE */
