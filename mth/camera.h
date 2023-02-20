/* Property of Cherepkov Petr
 * FILE: 'camera.h'
 * LAST UPDATE: 20.02.2023
 */

#pragma once

/* camera and controls classes */

#include <map>
#include "..\def.h"

class keyboard
{
public:
	map<int, bool>
		keys,
		keys_old,
		keys_click;

	void Response(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		bool tmp = keys[key];

		if (action == GLFW_PRESS) {
			keys[key] = 1;
			keys_click[key] = 1;
		}
		if (action == GLFW_REPEAT)
			keys[key] = 1;
		if (action == GLFW_RELEASE)
			keys[key] = 0;
		if (action == GLFW_REPEAT || action == GLFW_RELEASE)
			keys_click[key] = 0;

		keys_old[key] = tmp;
	}

	keyboard(void) {
		for (int i = 0; i < 1024; i++) {
			keys[i] = false;
			keys_old[i] = false;
			keys_click[i] = false;
		}
	};
};

class mouse {
public:
	dbl x, y, dx, dy;
	int buttons[3];
	dbl scrollX, scrollY;

	mouse() {
		x = y = dx = dy = 0;
		buttons[0] = buttons[1] = buttons[2] = 0;
		scrollX = scrollY = 0;
	}

	~mouse() {
	}

	void Response(dbl newx, dbl newy) {
		dx = newx - x;
		dy = newy - y;
		x = newx;
		y = newy;
	}
};

class camera {
private:
	vec3 pos, at, up, right;
	dbl elev_angle;
public:
	camera() {
		pos = vec3(0, 0, 1);
		at = vec3(0);
		up = vec3(0, 1, 0);
		right = vec3(1, 0, 0);
	}

	~camera() {
	}

	dbl GetElev(void) {
		elev_angle = acos(dot(normalize(at - pos), vec3(0, 1, 0)));
		return elev_angle;
	}

	void SetPos(vec3 Loc) {
		pos = Loc;
		right = normalize(cross((at - pos), vec3(0, 1, 0)));
		up = normalize(cross(right, (at - pos)));
	}

	vec3 GetPos(void) {
		return pos;
	}

	void SetAt(vec3 Look) {
		at = pos + normalize(Look - pos);
		right = normalize(cross((at - pos), vec3(0, 1, 0)));
		up = normalize(cross(right, (at - pos)));
	}

	vec3 GetAt(void) {
		return at;
	}

	vec3 GetRight(void) {
		return right;
	}

	vec3 GetUp(void) {
		return up;
	}

	vec3 GetDir(void) {
		return normalize(at - pos);
	}

	mat4 GetView(void) {
		return lookAt(pos, at, up);
	}
};

/* END OF 'camera.h' FILE */
