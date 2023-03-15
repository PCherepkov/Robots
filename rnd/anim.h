/* Property of Cherepkov Petr
 * FILE: 'anim.h'
 * LAST UPDATE: 15.03.2023
 */

#pragma once

/* animation class file */

#include "../utils/timer.h"
#include "prim.h"
#include "../mth/camera.h"
#include "../ui/controls.h"

class anim;

extern anim ani;

class anim : public timer, public keyboard, public mouse {
	vector<prim*> prims;
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
		for (auto pr : prims) delete pr;
		for (auto& m : mtls) delete m.second;
	}

	void Response(GLFWwindow* window, int key, int scancode, int action, int mods) {
		keyboard::Response(window, key, scancode, action, mods);
	}

	void Response(const int& newx, const int& newy) {
		mouse::Response(newx, newy);
	}

	void GetPrims(vector<prim*>* prs) {
		*prs = prims;
	}

	void AddPrim(prim* pr) {
		if (pr->shd == nullptr)
			SetShader(pr);
		if (pr->textures.empty())
			SetTexture(pr);
		if (pr->material == nullptr)
			SetMaterial(pr, "default");
		prims.push_back(pr);
	}

	static anim& GetRef(void) {
		return ani;
	}

	void SetShader(prim* pr, const string& name="rnd/shd/DEFAULT/") {
		map<string, shader>::iterator it = shaders.find(name);
		if (it == shaders.end())
			shaders[name] = shader(name);
		pr->shd = &shaders[name];
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
