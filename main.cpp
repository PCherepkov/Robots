/* Property of Cherepkov Petr
 * FILE: 'main.cpp'
 * LAST UPDATE: 10.02.2023
 */

#include "def.h"
#include "main.h"

anim ani;

int main(int argc, char* argv[]) {  
  if (!glfwInit())
    return 1;

  SetWindow(1920, 1080, false);

  ani.cam.SetPos(vec3(0, 2, 2));
  ani.cam.SetAt(vec3(0));

  ani.exit = false;

  while (!ani.exit) {
    Render(ani.window);

    glfwSwapBuffers(ani.window);
    glfwPollEvents();
  }

  return 0;
}

/* END OF 'main.cpp' FILE */
