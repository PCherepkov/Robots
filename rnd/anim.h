/* Property of Cherepkov Petr
 * FILE: 'anim.h'
 * LAST UPDATE: 07.10.2021
 */

#pragma once

/* animation class file */

#include "../utils/timer.h"

class anim : public camera, public timer, public keyboard, public mouse {
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

	void Response(int newx, int newy) {
		mouse::Response(newx, newy);
	}
};

extern anim ani;

 /* END OF 'anim.h' FILE */
