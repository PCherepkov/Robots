/* Property of Cherepkov Petr
 * FILE: 'render.cpp'
 * LAST UPDATE: 10.02.2023
 */

/* rendering functions */

#include "render.h"
#include "../utils/utils.h"

#define BEGIN glPushMatrix(); {
#define END   } glPopMatrix();

void RenderInit(GLFWwindow* window) {
  prim smth(std::vector<vertex>({
    { vec3(-1, -1, 0), vec3(0), vec3(0, 1, 0), vec3(1, 0, 0) },
    { vec3(-1, 1, 0), vec3(0), vec3(0, 1, 0), vec3(1, 1, 0) },
    { vec3(1, 1, 0), vec3(0), vec3(0, 1, 0), vec3(0, 0, 1) },
    { vec3(1, -1, 0), vec3(0), vec3(0, 1, 0), vec3(1, 0, 1) },
    }), std::vector<uint>({0, 1, 3, 2}));

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, -1.0f, -3.0f));

  glm::mat4 projection = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(60.0f), (float)ani.w / (float)ani.h, 0.1f, 1000.0f);
  
  smth.projection = projection;
  smth.view = view;
  smth.model = model;
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
  vec3
      pos = ani.cam.GetPos(),
      at = ani.cam.GetAt(),
      up = ani.cam.GetUp();
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
