/* Property of Cherepkov Petr
 * FILE: 'prim.h'
 * LAST UPDATE: 10.02.2023
 */

#pragma once

 /* common header file for topologies */

#include <vector>
#include "../def.h"
#include "shd/shaders.h"
#include "render.h"

class anim;

/* additional structure for vertex of topology */

struct vertex
{
  vec3 p, t, n, c; // position, texture coordinates, normal, color
};

/* topology class itself */

class prim {
  uint vbo, vao, ebo;

public:
  uint prim_type; // GL_TRIANGLES, ...
  std::vector<vertex> verts;  
  std::vector<uint> inds;
  shader* shd;
  glm::mat4 projection, view, model;

  prim() {
    shd = new shader("rnd/shd/DEFAULT/");
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
  }

  prim(std::vector<vertex> vcs, std::vector<uint> indxs) {
    prim_type = GL_TRIANGLE_STRIP;
    verts = vcs;
    inds = indxs;
    shd = new shader("rnd/shd/DEFAULT/");
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    flt* vertices = new flt[vcs.size() * 11];
    for (uint i = 0; i < vcs.size(); i++) {
      vertices[i * 11 + 0] = (flt)vcs[i].p[0];
      vertices[i * 11 + 1] = (flt)vcs[i].p[1];
      vertices[i * 11 + 2] = (flt)vcs[i].p[2];

      vertices[i * 11 + 3] = (flt)vcs[i].c[0];
      vertices[i * 11 + 4] = (flt)vcs[i].c[1];
      vertices[i * 11 + 5] = (flt)vcs[i].c[2];

      vertices[i * 11 + 6] = (flt)vcs[i].n[0];
      vertices[i * 11 + 7] = (flt)vcs[i].n[1];
      vertices[i * 11 + 8] = (flt)vcs[i].n[2];

      vertices[i * 11 + 9 ] = (flt)vcs[i].t[0];
      vertices[i * 11 + 10] = (flt)vcs[i].t[1];
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vcs.size() * 11 * sizeof(flt), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(inds[0]), inds.data(), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(flt), (void*)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(flt), (void*)(3 * sizeof(flt)));
    glEnableVertexAttribArray(1);
    // normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(flt), (void*)(6 * sizeof(flt)));
    glEnableVertexAttribArray(2);
    // texture
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(flt), (void*)(9 * sizeof(flt)));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  ~prim() {
  }

  void Draw(void) {
    glUseProgram(shd->prg);
    
    glUniform1f(glGetUniformLocation(shd->prg, "time"), (flt)glfwGetTime());
	glUniformMatrix4fv(glGetUniformLocation(shd->prg, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shd->prg, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shd->prg, "model"), 1, GL_FALSE, glm::value_ptr(model));
    
    glBindVertexArray(vao);
    glDrawElements(prim_type, verts.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
};


/* END OF 'prim.h' FILE */
