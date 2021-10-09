/* Property of Cherepkov Petr
 * FILE: 'def.h'
 * LAST UPDATE: 09.10.2021
 */

#pragma once

#include <cstdio>
#include <ctime>
#include <iostream>
#include <string.h>
#include <stdio.h>

#pragma comment(lib, "legacy_stdio_definitions.lib")

// #include <glut.h>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char byte;

#define MAX_TEXTURES 10

#include "mth/mth.h"
#include "mth/camera.h"

/* END OF 'def.h' FILE */
