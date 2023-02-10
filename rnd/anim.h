/* Property of Cherepkov Petr
 * FILE: 'anim.h'
 * LAST UPDATE: 10.02.2023
 */

#pragma once

/* animation class file */

#include "../utils/timer.h"
#include "prim.h"
#include "../mth/camera.h"

class anim;

extern anim ani;

class anim : public camera, public timer, public keyboard, public mouse {
	std::vector<prim> prims;
public:
	GLFWwindow* window;
	int w, h;
	camera cam;
	bool is_wire_frame, is_fullscreen, exit;

	anim() {
		window = nullptr;
	}

	~anim() {
	}

	void Response(GLFWwindow* window, int key, int scancode, int action, int mods) {
		keyboard::Response(window, key, scancode, action, mods);
	}

	void Response(const int& newx, const int& newy) {
		mouse::Response(newx, newy);
	}

	void GetPrims(std::vector<prim>* prs) {
		*prs = prims;
	}

	void AddPrim(const prim& pr) {
		prims.push_back(pr);
	}

	static anim& GetRef(void) {
		return ani;
	}
};

 /* END OF 'anim.h' FILE */
