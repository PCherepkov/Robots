/* Property of Cherepkov Petr
 * FILE: 'gl_funcs.h'
 * LAST UPDATE: 15.02.2023
 */

#pragma once

/* header file for glut handling functions */

#include "../def.h"

void Reshape(GLFWwindow* window, int w, int h);
void KeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseInput(GLFWwindow* window, double xpos, double ypos);
void MouseButtonsInput(GLFWwindow* window, int button, int action, int mods);
void MouseScrollInput(GLFWwindow* window, double xoffset, double yoffset);
void SetWindow(int w, int h, bool is_full_screen);

 /* END OF 'gl_funcs.h' FILE */
