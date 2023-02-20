/* Property of Cherepkov Petr
 * FILE: 'textures.cpp'
 * LAST UPDATE: 20.02.2023
 */

#define STB_IMAGE_IMPLEMENTATION
#include "../../utils/stb_image.h"

#include "textures.h"

tex::tex() {
	name = "DEFAULT";

	glGenTextures(1, &code);
	glBindTexture(GL_TEXTURE_2D, code);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = new uchar[4 * 3];
	data[0] = 255, data[1] = 100, data[2] = 0;
	data[3] = 0, data[4] = 30, data[5] = 255;
	data[6] = 255, data[7] = 100, data[8] = 0;
	data[9] = 0, data[10] = 30, data[11] = 255;

	width = height = 2;
	noc = 3;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	delete data;
}

tex::tex(const string& path) {
	glGenTextures(1, &code);
	glBindTexture(GL_TEXTURE_2D, code);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(path.c_str(), &width, &height, &noc, 0);
	if (data && noc == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else if (noc == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		cout << "Failed to load texture" << endl;
	
	// TODO: move to a destructor???
	stbi_image_free(data);
}

/* END OF 'textures.cpp' FILE */
