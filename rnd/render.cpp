/* Property of Cherepkov Petr
 * FILE: 'render.cpp'
 * LAST UPDATE: 20.02.2023
 */

/* rendering functions */

#include "render.h"
#include "../utils/utils.h"

#define BEGIN glPushMatrix(); {
#define END   } glPopMatrix();

void RenderInit(GLFWwindow* window) {
    vector<vertex> v;
    vector<uint> i;
    // topo::sphere<vertex>(v, i, 1, 30, 30);
    topo::grid<vertex>(v, i, 10, 10, 4, 4);
    prim* smth = new prim(v, i);
    
    mat4 model = mat4(1.0f);
    model = rotate(model, radians(45.0f * 0), vec3(1, 0, 0));
    
    mat4 view = mat4(1.0f);
    view = translate(view, vec3(0.0f, -0.5f, -2.0f));
    
    mat4 projection = mat4(1.0f);
    projection = perspective(radians(90.0f), (float)ani.w / (float)ani.h, 0.01f, 1000.0f);
    
    smth->projection = projection;
    smth->view = view;
    smth->model = model;
    
    ani.SetTexture(smth, "src/wall.jpg");

    ani.AddPrim(smth);
}

void Render(GLFWwindow* window) {
    glClearColor(0.17, 0.1603, 0.209, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (ani.is_wire_frame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    vector<prim*> prs;
    ani.GetPrims(&prs);
    for (auto pr : prs) {
        pr->view = ani.cam.GetView();
        pr->Draw();
    }

    ani.UpdateTimer(ani.is_pause);
    FlyingWASD();
    
    ani.dx = ani.dy = 0;

    /* debug output */
#if 0
      int w = ani.w, h = ani.h, x = w - 90, y = h - 10;

      glLoadIdentity();
      char buf[32];
      sprintf_s(buf, 32, "%s%f", "fps: ", ani.fps);
      glDisable(GL_LIGHTING);
      Output(x, y, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, buf);
      sprintf_s(buf, 32, "%s%d%s%d", "x: ", (int)ani.x, " y: ", (int)ani.y);
      Output(x, y - 10, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, buf);
#endif
}

/* END OF 'render.cpp' FILE */
