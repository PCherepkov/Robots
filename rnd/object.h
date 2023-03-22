/* Property of Cherepkov Petr
 * FILE: 'object.h'
 * LAST UPDATE: 21.03.2021
 */

#pragma once

#include "./prim/prim.h"

class object {
public:
	mat4 projection, view, model;
	vector<prim*> prs;
	shader* shd;

	void Draw(void) {
		shd->ApplyVP(view, projection);
		for (auto pr : prs) {
			pr->Draw();
		}
	}

	object() { shd = nullptr; }
	~object() {
		for (auto pr : prs) delete pr;
	}
};

/* END OF 'object.h' FILE */
