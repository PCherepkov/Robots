/* Property of Cherepkov Petr
 * FILE: 'camera.h'
 * LAST UPDATE: 18.10.2021
 */

#pragma once

/* camera and controls classes */

#include "mth.h"
#include <map>

class keyboard
{
public:
	std::map<int, bool>
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
		if (action == GLFW_RELEASE)
			keys[key] = 0;
		if (action == GLFW_REPEAT || action == GLFW_RELEASE)
			keys_click[key] = 0;

		keys_old[key] = tmp;
	}

	keyboard(VOID) {
		keys.insert(std::pair<int, bool>(32, 0));
		keys_old.insert(std::pair<int, bool>(32, 0));
		keys_click.insert(std::pair<int, bool>(32, 0));
		keys.insert(std::pair<int, bool>(39, 0));
		keys_old.insert(std::pair<int, bool>(39, 0));
		keys_click.insert(std::pair<int, bool>(39, 0));
		for (int i = 44; i < 58; i++)
			keys.insert(std::pair<int, bool>(i, 0)), keys_old.insert(std::pair<int, bool>(i, 0)), keys_click.insert(std::pair<int, bool>(i, 0));
		keys.insert(std::pair<int, bool>(59, 0));
		keys_old.insert(std::pair<int, bool>(59, 0));
		keys_click.insert(std::pair<int, bool>(59, 0));
		keys.insert(std::pair<int, bool>(61, 0));
		keys_old.insert(std::pair<int, bool>(61, 0));
		keys_click.insert(std::pair<int, bool>(61, 0));
		for (int i = 65; i < 94; i++)
			keys.insert(std::pair<int, bool>(i, 0)), keys_old.insert(std::pair<int, bool>(i, 0)), keys_click.insert(std::pair<int, bool>(i, 0));
		keys.insert(std::pair<int, bool>(96, 0));
		keys_old.insert(std::pair<int, bool>(96, 0));
		keys_click.insert(std::pair<int, bool>(96, 0));
		keys.insert(std::pair<int, bool>(161, 0));
		keys_old.insert(std::pair<int, bool>(161, 0));
		keys_click.insert(std::pair<int, bool>(161, 0));
		keys.insert(std::pair<int, bool>(162, 0));
		keys_old.insert(std::pair<int, bool>(162, 0));
		keys_click.insert(std::pair<int, bool>(162, 0));
		for (int i = 256; i < 270; i++)
			keys.insert(std::pair<int, bool>(i, 0)), keys_old.insert(std::pair<int, bool>(i, 0)), keys_click.insert(std::pair<int, bool>(i, 0));
		for (int i = 280; i < 285; i++)
			keys.insert(std::pair<int, bool>(i, 0)), keys_old.insert(std::pair<int, bool>(i, 0)), keys_click.insert(std::pair<int, bool>(i, 0));
		for (int i = 290; i < 315; i++)
			keys.insert(std::pair<int, bool>(i, 0)), keys_old.insert(std::pair<int, bool>(i, 0)), keys_click.insert(std::pair<int, bool>(i, 0));
		for (int i = 320; i < 337; i++)
			keys.insert(std::pair<int, bool>(i, 0)), keys_old.insert(std::pair<int, bool>(i, 0)), keys_click.insert(std::pair<int, bool>(i, 0));
		for (int i = 340; i < 349; i++)
			keys.insert(std::pair<int, bool>(i, 0)), keys_old.insert(std::pair<int, bool>(i, 0)), keys_click.insert(std::pair<int, bool>(i, 0));
	}
};

class mouse {
public:
	int x, y, dx, dy;
	int button, state;

	mouse() : x(-1), y(-1) {
	}

	~mouse() {
	}

	void Response(int newx, int newy) {
		dx = newx - x;
		dy = newy - y;
		x = newx;
		y = newy;
	}
};

class camera {
private:
	vec3 pos, at, up, right;
	dbl elev_angle, rot_angle;
	dbl dist;
public:
	camera() {
	}

	~camera() {
	}

	void SetDist(dbl new_dist) {
		dist = new_dist;
	}

	dbl GetDist(void) {
		return dist;
	}

	void SetRot(dbl new_rot) {
		rot_angle = new_rot;
	}

	dbl GetRot(void) {
		return rot_angle;
	}

	void SetElev(dbl new_elev) {
		if (new_elev < 0.99 * PI && new_elev > 0.01) {
			elev_angle = new_elev;
		}
	}

	dbl GetElev(void) {
		return elev_angle;
	}

	void SetPos(vec3 Loc) {
		pos = Loc;
		right = ((at - pos) % vec3(0, 1, 0)).Normalizing();
		up = (right % (at - pos)).Normalizing();
	}

	vec3 GetPos(void) {
		return pos;
	}

	void SetAt(vec3 Look) {
		at = Look;
		right = ((at - pos) % vec3(0, 1, 0)).Normalizing();
		up = (right % (at - pos)).Normalizing();
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
		return (at - pos).Normalizing();
	}
};

/* END OF 'camera.h' FILE */
