/* Property of Cherepkov Petr
 * FILE: 'object.cpp'
 * LAST UPDATE: 08.12.2021
 */

#include "object.h"
#include "anim.h"

void ProcessMesh(object* obj, aiMesh *mesh, const aiScene *scene) {
	vector<vertex> verts;
	vector<uint> inds;

	for (uint i = 0; i < mesh->mNumVertices; i++) {
		vertex v;
		verts.push_back(v);
	}

	prim *pr = new prim(verts, inds);
	ani.AddPrim(obj, pr);
}

void ProcessNode(object* obj, aiNode* node, const aiScene* scene) {
	for (uint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(obj, mesh, scene);
	}

	for (uint i = 0; i < node->mNumChildren; i++)
		ProcessNode(obj, node->mChildren[i], scene);
}

bool object::Load(string &path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		return false;

	ProcessNode(this, scene->mRootNode, scene);
	return true;
}

void object::Draw(void) {
	shd->ApplyVP(view, projection);
	for (auto pr : prs) {
		pr->Draw();
	}
}

/* END OF 'object.h' FILE */
