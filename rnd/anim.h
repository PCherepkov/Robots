/* Property of Cherepkov Petr
 * FILE: 'anim.h'
 * LAST UPDATE: 20.02.2023
 */

#pragma once

/* animation class file */

#include "../utils/timer.h"
#include "prim.h"
#include "../mth/camera.h"
#include "../ui/controls.h"

class anim;

extern anim ani;

class anim : public camera, public timer, public keyboard, public mouse {
	vector<prim*> prims;
	map<string, shader> shaders;
	map<string, tex> texes;
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
		if (pr->texture == nullptr)
			SetTexture(pr);
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

	void SetTexture(prim* pr, const string& name="") {
		map<string, tex>::iterator it = texes.find(name);
		if (it == texes.end() && name == "")
			texes[name] = tex();
		else if (it == texes.end())
			texes[name] = tex(name);
		pr->texture = &texes[name];
	}
};

 /* END OF 'anim.h' FILE */
