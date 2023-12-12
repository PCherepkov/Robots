/* Property of Cherepkov Petr
 * FILE: 'object.h'
 * LAST UPDATE: 08.12.2021
 */

#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./prim/prim.h"

class object {
public:
	mat4 projection, view, model;
	vector<prim*> prs;
	shader* shd;

	bool Load(string &path);

	void Draw(void);

	object() { shd = nullptr; }
	~object() { for (auto pr : prs) delete pr; }
};

/* END OF 'object.h' FILE */
