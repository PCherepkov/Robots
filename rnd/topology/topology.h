/* Property of Cherepkov Petr
 * FILE: 'topology.h'
 * LAST UPDATE: 12.12.2023
 */

#pragma once

#include "../../def.h"

namespace topo
{
	template <typename T>
	void sphere(vector<T>& topo, vector<uint>& ind, dbl r, int n, int m) {
		topo.resize(n * m + 2);
		ind.clear();

		int i, j;
		dbl phi, theta;
		topo[0].p = vec3(0, 0, r);
		topo[0].n = vec3(0, 0, 1);
		topo[0].t = vec2(0, 0);
		for (i = 0; i < n; i++) {
			theta = i * PI * 2 / (n - 1 + 1);
			for (j = 0; j < m; j++) {
				phi = j * 2 * PI / (m - 1);
				vec3 pos(r * sin(theta) * cos(phi),
					r * sin(theta) * sin(phi),
					r * cos(theta));
				topo[i * m + j + 1].p = pos;
				topo[i * m + j + 1].n = normalize(pos);
				topo[i * m + j + 1].t = vec2((flt)phi / PI / 2, (flt)theta / PI);
			}
		}
		topo[n * m + 1].p = vec3(0, 0, -r);
		topo[n * m + 1].n = vec3(0, 0, -1);
		topo[n * m + 1].t = vec2(1, 0);
		
		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < m + 1; j++) {
				ind.push_back(i * m + j);
				ind.push_back((i + 1) * m + j);
			}
		}
	}

	template <typename T>
	void grid(vector<T>& topo, vector<uint>& ind, dbl w, dbl h, int m, int n) {
		n += 1, m += 1;
		topo.resize(n * m);
		ind.clear();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				topo[i * m + j].p = vec3((flt)j / (m - 1) * w - w / 2, 0, (flt)i / (n - 1) * h - h / 2);
				topo[i * m + j].n = vec3(0, 1, 0);
				topo[i * m + j].t = vec2((flt)j / (m - 1), (flt)i / (n - 1));
			}
		}
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < m; j++) {
				ind.push_back(i * m + j);
				ind.push_back((i + 1) * m + j);
			}
			ind.push_back(-1);
		}
		return;
	}
}

/* END OF 'topology.h' FILE */
