/* Property of Cherepkov Petr
 * FILE: 'render.h'
 * LAST UPDATE: 10.10.2021
 */

#pragma once

 /* common header file for rendering */

#include "topology/topology.h"
#include "anim.h"
#include "gl_funcs.h"
#include "prim.h"
#include "shd/shaders.h"

void RenderInit(GLFWwindow* window);
void Render(GLFWwindow* window);

 /* END OF 'render.h' FILE */
