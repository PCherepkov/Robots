/* Property of Cherepkov Petr
 * FILE: 'main.cpp'
 * LAST UPDATE: 10.10.2021
 */

#include "def.h"
#include "main.h"

anim ani;

int main(int argc, char* argv[]) {
  if (!glfwInit())
    return 1;

  GLFWwindow* window = glfwCreateWindow(800, 800, "Robots", NULL, NULL);
  if (window == NULL)
    return 2;

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    return 3;

  glfwSetFramebufferSizeCallback(window, Reshape);

  ani.cam.SetPos(vec3(0, 2, 2));
  ani.cam.SetAt(vec3(0));

  RenderInit(window);
  while (!glfwWindowShouldClose(window)) {
    Input(window);

    Render(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

/* END OF 'main.cpp' FILE */
