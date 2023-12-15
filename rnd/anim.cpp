/* Property of Cherepkov Petr
 * FILE: 'anim.cpp'
 * LAST UPDATE: 15.12.2023
 */

/* animation system functions */

#include "anim.h"
#include "object.h"

anim::anim() {
	w = h = 0;
	is_wire_frame = is_fullscreen = exit = false;
	window = nullptr;
}

anim::~anim() {
	for (auto obj : objs) delete obj;
	for (auto& m : mtls) delete m.second;
	for (auto& L : lights) delete L;
}

void anim::Response(GLFWwindow* window, int key, int scancode, int action, int mods) {
	keyboard::Response(window, key, scancode, action, mods);
}

void anim::Response(const int& newx, const int& newy) {
	mouse::Response(newx, newy);
}

void anim::AddLight(lights::light* L) {
	int i = 0, sum = 0;
	for (; i < lights.size(); i++)
		if (lights[i]->type == L->type)
			sum += 1;
	L->ind = sum;
	lights.push_back(L);
}

void anim::AddObj(object* obj) {
	if (obj->shd == nullptr)
		SetShader(obj);
	objs.push_back(obj);
}

void anim::AddPrim(object* obj, prim* pr) {
	if (obj->shd == nullptr)
		SetShader(pr);
	else
		SetShader(pr, *obj->shd);
	if (pr->textures.empty())
		SetTexture(pr);
	if (pr->material == nullptr)
		SetMaterial(pr, "default");
	obj->prs.push_back(pr);
}

void anim::SetShader(prim* pr, const string& name) {
	map<string, shader>::iterator it = shaders.find(name);
	if (it == shaders.end())
		shaders[name] = shader(name);
	pr->shd = &shaders[name];
}

void anim::ForceShader(object* obj, const string& name) {
	for (auto pr : obj->prs)
		pr->shd = &shaders[name];

	for (auto child : obj->children)
		ForceShader(child, name);
}

void anim::SetShader(object* obj, const string& name) {
	map<string, shader>::iterator it = shaders.find(name);
	if (it == shaders.end())
		shaders[name] = shader(name);
	obj->shd = &shaders[name];
	ForceShader(obj, name);
}

void anim::SetShader(prim* pr, shader& shd) {
	auto it = shaders.begin();
	for (; it != shaders.end(); it++)
		if (it->second == shd)
			break;
	if (it == shaders.end())
		shaders[shd.path] = shd;
	pr->shd = &shaders[shd.path];
}

void anim::SetTexture(prim* pr, const string& name, const int& ind) {
	map<string, tex>::iterator it = texes.find(name);
	if (it == texes.end() && name == "")
		texes[name] = tex();
	else if (it == texes.end())
		texes[name] = tex(name);
	if (ind == -1 && pr->textures.size() < MAX_TEXTURES)
		pr->textures.push_back(&texes[name]);
	else if (ind > -1 && ind < pr->textures.size())
		pr->textures[ind] = &texes[name];
}

void anim::SetMaterial(prim* pr, const string& name) {
	map<string, mtl*>::iterator it = mtls.find(name);
	if (it == mtls.end() && name == "")
		mtls[name] = new mtl();
	else if (it == mtls.end())
		mtls[name] = new mtl(name);
	pr->material = mtls[name];
}

void anim::SetMaterial(prim* pr, mtl* src) {
	if (src->name == "")
		src->name = string("~") + to_string(mtls.size());
	map<string, mtl*>::iterator it = mtls.find(src->name);
	if (it == mtls.end())
		mtls[src->name] = src;
	pr->material = src;
}

void anim::AddTex(tex& texture) {
	if (texes.find(texture.name) != texes.end())
		return;
	texes[texture.name] = texture;
}

void anim::ForceTex(tex& texture) {
	texes[texture.name] = texture;
}

bool anim::IsTexByName(string& name) {
	return texes.find(name) != texes.end();
}

bool anim::IsTexByPath(const string& path) {
	for (auto it = texes.begin(); it != texes.end(); it++)
		if (it->second.path == path)
			return true;
	return false;
}

/* END OF 'anim.cpp' FILE */
