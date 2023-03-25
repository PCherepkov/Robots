/* Property of Cherepkov Petr
 * FILE: 'anim.h'
 * LAST UPDATE: 25.03.2023
 */

#pragma once

/* animation class file */

#include "../utils/timer.h"
#include "object.h"
#include "lighting/lighting.h"
#include "../mth/camera.h"
#include "../ui/controls.h"

class anim;

extern anim ani;

class anim : public timer, public keyboard, public mouse {
	vector<object*> objs;
	vector<lights::light*> lights;
	map<string, shader> shaders;
	map<string, tex> texes;
	map<string, mtl*> mtls;
public:
	GLFWwindow* window;
	int w, h;
	camera cam;
	bool is_wire_frame, is_fullscreen, exit;

	anim() {
		w = h = 0;
		is_wire_frame = is_fullscreen = exit = false;
		window = nullptr;
	}

	~anim() {
		for (auto obj : objs) delete obj;
		for (auto& m : mtls) delete m.second;
		for (auto& L : lights) delete L;
	}

	void Response(GLFWwindow* window, int key, int scancode, int action, int mods) {
		keyboard::Response(window, key, scancode, action, mods);
	}

	void Response(const int& newx, const int& newy) {
		mouse::Response(newx, newy);
	}

	shader* GetShd(const string& path) {
		return &shaders[path];
	}

	void GetObjs(vector<object*>* ptr) {
		*ptr = objs;
	}

	void AddLight(lights::light* L) {
		int i = 0, sum = 0;
		for (; i < lights.size(); i++)
			if (lights[i]->type == L->type)
				sum += 1;
		L->ind = sum;
		lights.push_back(L);
	}

	void AddObj(object* obj) {
		if (obj->shd == nullptr)
			SetShader(obj);
		for (auto pr : obj->prs) AddPrim(obj, pr);
		objs.push_back(obj);
	}

	void AddPrim(object* obj, prim* pr) {
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

	static anim& GetRef(void) {
		return ani;
	}

	void SetShader(prim* pr, const string& name="rnd/prim/shd/DEFAULT/") {
		map<string, shader>::iterator it = shaders.find(name);
		if (it == shaders.end())
			shaders[name] = shader(name);
		pr->shd = &shaders[name];
	}

	void SetShader(object* obj, const string& name = "rnd/prim/shd/DEFAULT/") {
		map<string, shader>::iterator it = shaders.find(name);
		if (it == shaders.end())
			shaders[name] = shader(name);
		obj->shd = &shaders[name];
	}

	void SetShader(prim* pr, shader& shd) {
		auto it = shaders.begin();
		for (; it != shaders.end(); it++)
			if (it->second == shd)
				break;
		if (it == shaders.end())
			shaders[shd.path] = shd;
		pr->shd = &shaders[shd.path];
	}

	void SetTexture(prim* pr, const string& name="", const int& ind=-1) {
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

	void SetMaterial(prim* pr, const string& name) {
		map<string, mtl*>::iterator it = mtls.find(name);
		if (it == mtls.end() && name == "")
			mtls[name] = new mtl();
		else if (it == mtls.end())
			mtls[name] = new mtl(name);
		pr->material = mtls[name];
	}

	void SetMaterial(prim* pr, mtl* src) {
		if (src->name == "")
			src->name = string("~") + to_string(mtls.size());
		map<string, mtl*>::iterator it = mtls.find(src->name);
		if (it == mtls.end())
			mtls[src->name] = src;
		pr->material = src;
	}
};

/* END OF 'anim.h' FILE */
