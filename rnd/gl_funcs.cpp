/* Property of Cherepkov Petr
 * FILE: 'gl_funcs.cpp'
 * LAST UPDATE: 03.11.2021
 */

/* common glut handling functions */

#include "render.h"
#include "../def.h"
#include "../utils/utils.h"
#include "../ui/controls.h"

void SetWindow(int w, int h, bool is_full_screen) {
  if (ani.window != nullptr)
    glfwDestroyWindow(ani.window);

  if (is_full_screen)
    ani.window = glfwCreateWindow(w, h, "Robots", glfwGetPrimaryMonitor(), NULL);
  else
    ani.window = glfwCreateWindow(w, h, "Robots", NULL, NULL);

  if (ani.window == nullptr)
    return;

  glfwMakeContextCurrent(ani.window);
  glfwSetFramebufferSizeCallback(ani.window, Reshape);
  glfwSetKeyCallback(ani.window, Input);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    return;

  RenderInit(ani.window);
}


void Reshape(GLFWwindow* window, int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // gluPerspective(60, 1.0 * w / h, 0.1, 1000);
  glMatrixMode(GL_MODELVIEW);

  ani.w = w;
  ani.h = h;
}


void Input(GLFWwindow* window, int key, int scancode, int action, int mods) {
  ani.Response(window, key, scancode, action, mods);
  if (ani.keys_click[GLFW_KEY_ESCAPE]) {
    glfwDestroyWindow(ani.window);
    glfwTerminate();
    ani.exit = true;
  }
  if (ani.keys_click[GLFW_KEY_P])
    ani.is_pause = !ani.is_pause;
  if (ani.keys_click[GLFW_KEY_TAB])
    ani.is_wire_frame = !ani.is_wire_frame;
  if (ani.keys_click[GLFW_KEY_F5]) {
    ani.is_fullscreen = !ani.is_fullscreen;
    if (ani.is_fullscreen)
      SetWindow(1920, 1080, ani.is_fullscreen);
    else
      SetWindow(800, 800, ani.is_fullscreen);
  }
}


#if 0
void Display(void) {
  glClearColor(0.17, 0.1603, 0.209, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Render();

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

void Keyboard(uchar key, int x, int y) {
  ani.Response();
  if (key == VK_ESCAPE) {
    exit(0);
  }
  if (key == 'P' || key == 'p') {
    ani.is_pause = !ani.is_pause;
  }
  if (key == VK_TAB) {
    ani.is_wire_frame = !ani.is_wire_frame;
  }
}


void Idle(void) {
  ani.UpdateTimer();
  ani.Response();
  FlyingWASD();
}

void Mouse(int button, int state, int x, int y) {
  ani.state = state;
  ani.button = button;
  ani.Response(x, y);
  Head();
}

void PassiveMotion(int x, int y) {
  ani.Response(x, y);
  Head();
}

void Motion(int x, int y) {
  ani.Response(x, y);
  Head();
}
#endif

 /* END OF 'gl_funcs.cpp' FILE */
