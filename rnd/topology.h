/* Property of Cherepkov Petr
 * FILE: 'topology.h'
 * LAST UPDATE: 08.10.2021
 */

#pragma once

 /* common header file for topologies */

#include <vector>
#include "../def.h"

/* additional structure for vertex of topology */

struct vertex
{
  vec3 p, t, n, c; // position, texture coordinates, normal, color
};

/* topology class itself */

class topo {
public:
  int descr;
  std::vector<vertex> verts;

  topo() {
  }

  ~topo() {
  }

  VOID Draw(VOID) {
    glBegin(descr);
    for (uint i = 0; i < verts.size(); i++) {
      vec3 c = verts[i].c, p = verts[i].p, n = verts[i].n, t = verts[i].t;
      glColor3d(c[0], c[1], c[2]);
      glNormal3d(n[0], n[1], n[2]);
      glTexCoord2d(t[0], t[1]);
      glVertex3d(p[0], p[1], p[2]);
    }
    glEnd();
  }
};


/* END OF 'topology.h' FILE */
