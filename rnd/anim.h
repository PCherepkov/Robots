/* Property of Cherepkov Petr
 * FILE: 'anim.h'
 * LAST UPDATE: 25.03.2023
 */

#pragma once

/* animation class file */

#include "../utils/timer.h"

#include "rnddef.h"

#include "lighting/lighting.h"
#include "../mth/camera.h"
#include "../ui/controls.h"

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

	anim();
	~anim();

	void Response(GLFWwindow* window, int key, int scancode, int action, int mods);
	void Response(const int& newx, const int& newy);

	inline shader* GetShd(const string& path) {
		return &shaders[path];
	}

	inline void GetObjs(vector<object*>* ptr) {
		*ptr = objs;
	}

	void AddLight(lights::light* L);
	void AddObj(object* obj);
	void AddPrim(object* obj, prim* pr);

	void SetShader(prim* pr, const string& name = "rnd/prim/shd/DEFAULT/");
	void SetShader(object* obj, const string& name = "rnd/prim/shd/DEFAULT/");
	void SetShader(prim* pr, shader& shd);

	void SetTexture(prim* pr, const string& name = "", const int& ind = -1);

	void SetMaterial(prim* pr, const string& name);
	void SetMaterial(prim* pr, mtl* src);
};

/* END OF 'anim.h' FILE */
