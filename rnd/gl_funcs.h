/* Property of Cherepkov Petr
 * FILE: 'gl_funcs.h'
 * LAST UPDATE: 07.10.2021
 */

#pragma once

/* header file for glut handling functions */

#include "../def.h"

void Display(void);
void Idle(void);
void Reshape(int w, int h);
void Keyboard(uchar key, int x, int y);
void Mouse(int button, int state, int x, int y);

 /* END OF 'gl_funcs.h' FILE */
