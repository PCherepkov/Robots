/* Property of Cherepkov Petr
 * FILE: 'topology.h'
 * LAST UPDATE: 08.10.2021
 */

#pragma once

 /* common header file for topologies */

#include <vector>
#include "../def.h"
#include "shd/shaders.h"

/* additional structure for vertex of topology */

struct vertex
{
  vec3 p, t, n, c; // position, texture coordinates, normal, color
};

/* topology class itself */

class prim {
  uint vbo, vao;
public:
  std::string descr;
  std::vector<vertex> verts;  
  shader* shd;

  prim() {
    shd = new shader("rnd/shd/DEFAULT/");
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
  }

  prim(std::vector<vertex> vcs) {
    verts = vcs;
    shd = new shader("rnd/shd/DEFAULT/");
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    flt vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f
    };

#if 0
    flt* vertices = new flt[vcs.size() * 3];
    for (uint i = 0; i < vcs.size(); i++) {
      vertices[i * 3 + 0] = (flt)vcs[i].p[0];
      vertices[i * 3 + 1] = (flt)vcs[i].p[1];
      vertices[i * 3 + 2] = (flt)vcs[i].p[2];
    }
#endif

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  ~prim() {
  }

  VOID Draw(VOID) {
    glUseProgram(shd->prg);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, verts.size());
  }
};


/* END OF 'topology.h' FILE */
