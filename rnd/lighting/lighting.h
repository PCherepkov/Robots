/* Property of Cherepkov Petr
 * FILE: 'lighting.h'
 * LAST UPDATE: 22.03.2021
 */

#pragma once
#include "../../def.h"
#include "../prim/shd/shaders.h"

namespace lights {
	class light {
	public:
		vector<shader*> shds;
		vec3 ka, kd, ks;

		void ApplyADS(void) {
			for (auto shd : shds) {
				shd->SetUniform("light.ka", shader::VEC3, &ka);
				shd->SetUniform("light.kd", shader::VEC3, &kd);
				shd->SetUniform("light.ks", shader::VEC3, &ks);
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
			for (auto shd : shds) {
				shd->SetUniform("light.pos", shader::VEC3, &pos);
				shd->SetUniform("light.con", shader::FLT, &con);
				shd->SetUniform("light.lin", shader::FLT, &lin);
				shd->SetUniform("light.qad", shader::FLT, &qad);
			}
		}

		point() : light() {
			pos = vec3(0);
			con = 1;
			lin = 0.09;
			qad = 0.032;
		}
		~point() {}
	};

	class direct : public light {
		vec3 dir;

		void Apply(void) {
			ApplyADS();
			for (auto shd : shds)
				shd->SetUniform("light.dir", shader::VEC3, &dir);
		}

		direct() : light() {}
		~direct();
	};
};

/* END OF 'lighting.h' FILE */
