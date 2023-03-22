/* Property of Cherepkov Petr
 * FILE: 'textures.h'
 * LAST UPDATE: 20.02.2023
 */

#pragma once

#include "../../def.h"

class tex {
public:
	uint code; // opengl code
	string name;
	int width, height, noc; // width, height and number of channels
	uchar* data;            // image data

	tex();
	tex(const string& path);

	~tex() {}
};

 /* END OF 'textures.h' FILE */