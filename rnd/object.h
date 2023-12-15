/* Property of Cherepkov Petr
 * FILE: 'object.h'
 * LAST UPDATE: 15.12.2021
 */

#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./prim/prim.h"

class object {
	mat4 model;
public:
	vector<prim*> prs;
	vector<object*> children;
	shader* shd;
	mat4 projection, view;

	inline mat4 GetModel(void) { return model; }
	void SetModel(const mat4& m);
	void ApplyModel(const mat4& m);
	void ApplyShader(const string& path);
	void ApplyShader(shader& shd);

	bool Load(const string &path);

	void Draw(void);

	object() { shd = nullptr; }
	~object() { for (auto pr : prs) delete pr; }
};

/* END OF 'object.h' FILE */
