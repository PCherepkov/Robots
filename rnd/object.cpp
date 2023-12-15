/* Property of Cherepkov Petr
 * FILE: 'object.cpp'
 * LAST UPDATE: 15.12.2021
 */

#include "object.h"
#include "anim.h"
#include "topology/topology.h"


vector<tex> LoadTexes(aiMaterial* material, aiTextureType type, string name, const string& path) {
	vector<tex> texes;
	uint n = ani.NumOfTexes();

	for (uint i = 0; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i, &str);
		bool loaded = ani.IsTexByPath(path + str.C_Str());

		if (!loaded) {
			tex texture(path + str.C_Str());
			texture.type = name;
			texture.name = to_string(n + i);
			ani.ForceTex(texture);
			texes.push_back(texture);
		}
	}

	return texes;
}

void ProcessMesh(object* obj, aiMesh *mesh, const aiScene *scene, const string& path) {
	vector<vertex> verts;
	vector<uint> inds;
	vector<tex> texes;

	for (uint i = 0; i < mesh->mNumVertices; i++) {
		vertex v;

		v.p.x = mesh->mVertices[i].x;
		v.p.y = mesh->mVertices[i].y;
		v.p.z = mesh->mVertices[i].z;

		v.n.x = mesh->mNormals[i].x;
		v.n.y = mesh->mNormals[i].y;
		v.n.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0]) {
			v.t.x = mesh->mTextureCoords[0][i].x;
			v.t.y = mesh->mTextureCoords[0][i].y;
		}
		else
			v.t = vec2(0.0f, 0.0f);

		verts.push_back(v);
	}

	for (uint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (uint j = 0; j < face.mNumIndices; j++)
			inds.push_back(face.mIndices[j]);
	}

	vector<tex> diffuse, specular, normals;
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		diffuse = LoadTexes(material, aiTextureType_DIFFUSE, "texture_diffuse", path);
		texes.insert(texes.end(), diffuse.begin(), diffuse.end());
		specular = LoadTexes(material, aiTextureType_SPECULAR, "texture_specular", path);
		texes.insert(texes.end(), specular.begin(), specular.end());
		normals = LoadTexes(material, aiTextureType_NORMALS, "texture_normals", path);
		texes.insert(texes.end(), specular.begin(), specular.end());
	}

	prim *pr = new prim(verts, inds);
	pr->prim_type = GL_TRIANGLES;
	pr->model = mat4(1.0f);
	ani.AddPrim(obj, pr);
	for (auto t : texes)
		ani.SetTexture(pr, t.name);
}

void ProcessNode(object* obj, aiNode* node, const aiScene* scene, const string& path) {
	ani.AddObj(obj);

	for (uint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(obj, mesh, scene, path);
	}

	for (uint i = 0; i < node->mNumChildren; i++) {
		object* child = new object();
		obj->children.push_back(child);
		ProcessNode(child, node->mChildren[i], scene, path);
	}
}

bool object::Load(const string &path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return false;
	}

	ProcessNode(this, scene->mRootNode, scene, path.substr(0, path.find_last_of('/') + 1));
	return true;
}

void object::Draw(void) {
	shd->ApplyVP(view, projection);
	for (auto pr : prs) {
		pr->Draw();
	}
}

void object::SetModel(const mat4& m) {
	for (auto pr : prs) pr->model = m;
	for (auto child : children) child->SetModel(m);
	model = m;
}

void object::ApplyModel(const mat4& m) {
	for (auto pr : prs) pr->model *= m;
	for (auto child : children) child->ApplyModel(m);
	model *= m;
}

/* END OF 'object.h' FILE */
