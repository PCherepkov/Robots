/* Property of Cherepkov Petr
 * FILE: 'main.cpp'
 * LAST UPDATE: 08.10.2021
 */

#include "def.h"
#include "main.h"

anim ani;

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Robots");

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutReshapeFunc(Reshape);
  glutIdleFunc(Idle);
  glutMouseFunc(Mouse);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);

  ani.cam.SetPos(vec3(0, 2, 2));
  ani.cam.SetAt(vec3(0));

  glutMainLoop();

  return 0;
}

/* END OF 'main.cpp' FILE */
