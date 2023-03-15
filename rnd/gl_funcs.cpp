/* Property of Cherepkov Petr
 * FILE: 'gl_funcs.cpp'
 * LAST UPDATE: 15.03.2023
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
  glfwSetKeyCallback(ani.window, KeyboardInput);
  glfwSetCursorPosCallback(ani.window, MouseInput);
  glfwSetMouseButtonCallback(ani.window, MouseButtonsInput);
  glfwSetScrollCallback(ani.window, MouseScrollInput);
  glfwSetInputMode(ani.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    return;

  ani.w = w, ani.h = h;
  glfwGetCursorPos(ani.window, &ani.x, &ani.y);
  RenderInit(ani.window);
}


void Reshape(GLFWwindow* window, int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);

  ani.w = w;
  ani.h = h;
}


void MouseScrollInput(GLFWwindow* window, double xoffset, double yoffset) {
	ani.scrollX = xoffset;
	ani.scrollY = yoffset;
}


void MouseButtonsInput(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        ani.buttons[button] = 1;
    if (action == GLFW_RELEASE)
        ani.buttons[button] = 0;
}


void MouseInput(GLFWwindow* window, double xpos, double ypos) {
	ani.Response(xpos, ypos);
}


void KeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
      // SetWindow(2560, 1600, ani.is_fullscreen);
    else
      SetWindow(800, 800, ani.is_fullscreen);
  }
}

/* END OF 'gl_funcs.cpp' FILE */
