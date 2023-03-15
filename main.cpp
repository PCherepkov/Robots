/* Property of Cherepkov Petr
 * FILE: 'main.cpp'
 * LAST UPDATE: 20.02.2023
 */


#include "def.h"

#include "main.h"

anim ani;

int main(int argc, char* argv[]) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

    if (!glfwInit())
      return 1;
    
    SetWindow(1920, 1080, false);
    
    ani.cam.SetPos(vec3(6, 2, 1));
    ani.cam.SetAt(vec3(0));
    
    ani.exit = false;
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glPointSize(5);
    while (!ani.exit) {
        Render(ani.window);
      
        glfwSwapBuffers(ani.window);
        glfwPollEvents();
    }
    
    return 0;
}

/* END OF 'main.cpp' FILE */
