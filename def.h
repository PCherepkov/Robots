/* Property of Cherepkov Petr
 * FILE: 'def.h'
 * LAST UPDATE: 12.12.2023
 */

#pragma once

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG_ // _DEBUG ('new' redefinition conflicts with assimp)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <cstdio>
#include <chrono>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <Windows.h>

#pragma comment(lib, "legacy_stdio_definitions.lib")

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class anim;

extern anim ani;

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char byte;
typedef double dbl;
typedef float flt;

#define PI 3.14159265358979323846

#define MAX_TEXTURES 8 // 32

/* END OF 'def.h' FILE */
