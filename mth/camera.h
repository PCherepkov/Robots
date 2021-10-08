/* Property of Cherepkov Petr
 * FILE: 'camera.h'
 * LAST UPDATE: 07.10.2021
 */

#pragma once

/* camera and controls classes */

#include "mth.h"

class keyboard
{
public:
	byte
		Keys[256],
		KeysOld[256],
		KeysClick[256];

	void Response(void)
	{
		bool flag = false;
		GetKeyboardState(Keys);

		for (int i = 0; i < 256; i++) {
			if ((Keys[i] >> 7) != 0) {
				flag = true;
			}
		}

		for (int i = 0; i < 256; i++) {
			Keys[i] = (Keys[i] >> 7);
			KeysClick[i] = Keys[i] && KeysOld[i];
		}

		memcpy(KeysOld, Keys, 256 * flag);
	}

	keyboard(VOID) {
		GetKeyboardState(Keys);
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
		right = ((pos - at) % vec3(0, 1, 0)).Normalizing();
		up = (right % (pos - at)).Normalizing();
	}

	vec3 GetPos(void) {
		return pos;
	}

	void SetAt(vec3 Look) {
		at = Look;
		right = ((pos - at) % vec3(0, 1, 0)).Normalizing();
		up = (right % (pos - at)).Normalizing();
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
		return (pos - at).Normalizing();
	}
};

/* END OF 'camera.h' FILE */
