/* Property of Cherepkov Petr
 * FILE: 'anim.h'
 * LAST UPDATE: 12.10.2021
 */

#pragma once

/* animation class file */

#include "../utils/timer.h"
#include "prim.h"

class anim;

extern anim ani;

class anim : public camera, public timer, public keyboard, public mouse {
	std::vector<prim> prims;
public:
	int w, h;
	camera cam;
	bool is_wire_frame;

	anim() {
	}

	~anim() {
	}

	void Response(void) {
		keyboard::Response();
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
