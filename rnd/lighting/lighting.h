/* Property of Cherepkov Petr
 * FILE: 'lighting.h'
 * LAST UPDATE: 15.12.2021
 */

#pragma once
#include "../../def.h"
#include "../prim/shd/shaders.h"

class anim;

namespace lights {
	class light {
	protected:
		friend class anim;
		uint ind;
		string type;
	public:
		vector<shader*> shds;
		vec3 ka, kd, ks;

		void ApplyADS(void) {
			string addres = type + "_lights[" + to_string(ind);
			for (auto shd : shds) {
				shd->SetUniform(addres + "].ka", shader::VEC3, &ka);
				shd->SetUniform(addres + "].kd", shader::VEC3, &kd);
				shd->SetUniform(addres + "].ks", shader::VEC3, &ks);
			}
		}

		light() : ka(1), kd(1), ks(1) {}
	};

	class point : public light {
	public:
		vec3 pos;
		flt con, lin, qad;

		void Apply(void) {
			ApplyADS();
			string addres = "point_lights[" + to_string(ind) + "].",
				P = addres + "pos", C = addres + "con",
				L = addres + "lin", Q = addres + "qad";
			for (auto shd : shds) {
				shd->SetUniform(P, shader::VEC3, &pos);
				shd->SetUniform(C, shader::FLT, &con);
				shd->SetUniform(L, shader::FLT, &lin);
				shd->SetUniform(Q, shader::FLT, &qad);
			}
		}

		point() : light() {
			pos = vec3(0);
			con = 0.8;
			lin = 0.02;
			qad = 0.001;
			type = "point";
		}
		~point() {}
	};

	class direct : public light {
	public:
		vec3 dir;

		void Apply(void) {
			ApplyADS();
			string addres = "direct_lights[" + to_string(ind) + "].dir";
			for (auto shd : shds)
				shd->SetUniform(addres, shader::VEC3, &dir);
		}

		direct() : light() {
			type = "direct";
		}
		~direct();
	};

	class spot : public light {
	public:
		vec3 pos, dir;
		flt cuti, cuto;

		void Apply(void) {
			ApplyADS();
			string addres = "spot_lights[" + to_string(ind) + "].",
				P = addres + "pos", D = addres + "dir", I = addres + "cuti",
				O = addres + "cuto";
			for (auto shd : shds) {
				shd->SetUniform(P, shader::VEC3, &pos);
				shd->SetUniform(D, shader::VEC3, &dir);
				shd->SetUniform(I, shader::FLT, &cuti);
				shd->SetUniform(O, shader::FLT, &cuto);
			}
		}

		spot() : light() {
			type = "spot";
			cuti = 0.976296;
			cuto = 0.953717;
		}
	};
};

/* END OF 'lighting.h' FILE */
