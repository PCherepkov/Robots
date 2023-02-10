/* Property of Cherepkov Petr
 * FILE: 'def.h'
 * LAST UPDATE: 10.02.2023
 */

#pragma once

#include <cstdio>
#include <ctime>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
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

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char byte;
typedef double dbl;
typedef float flt;

#define MAX_TEXTURES 10

/* END OF 'def.h' FILE */
