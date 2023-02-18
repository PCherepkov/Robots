/* Property of Cherepkov Petr
 * FILE: 'prim.h'
 * LAST UPDATE: 18.02.2023
 */

#pragma once

 /* common header file for topologies */

#include "../def.h"
#include "shd/shaders.h"
#include "render.h"

class anim;

/* additional structure for vertex of primitive */

struct vertex
{
	vec3 p; // position
    vec2 t; // texture coordinates
	vec3 n; // normal
    vec4 c; // color
    
	vertex(void) : p(0), t(0), n(0), c(1) {}
	vertex(const vec3& p, const vec2& t, const vec3& n, const vec4& c) :p(p), t(t), n(n), c(c) {}
};

/* topology class itself */

class prim {
    uint vbo, vao, ebo;

public:
    uint prim_type; // GL_TRIANGLES, ...
    vector<vertex> verts;  
    vector<uint> inds;
    shader* shd;
    mat4 projection, view, model;

    prim() {
        shd = nullptr; // new shader("rnd/shd/DEFAULT/");
        model = mat4(1.0f);
        view = mat4(1.0f);
        projection = mat4(1.0f);
        prim_type = GL_POINTS;
    }

    prim(vector<vertex> vcs, vector<uint> indxs) {
        prim_type = GL_TRIANGLE_STRIP;
        verts = vcs;
        inds = indxs;
        shd = nullptr; // new shader("rnd/shd/DEFAULT/");
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glGenVertexArrays(1, &vao);
        
        flt* vertices = new flt[vcs.size() * 12];
        for (uint i = 0; i < vcs.size(); i++) {
            vertices[i * 12 + 0] = (flt)vcs[i].p[0];
            vertices[i * 12 + 1] = (flt)vcs[i].p[1];
            vertices[i * 12 + 2] = (flt)vcs[i].p[2];
            
            vertices[i * 12 + 3] = (flt)vcs[i].c[0];
            vertices[i * 12 + 4] = (flt)vcs[i].c[1];
            vertices[i * 12 + 5] = (flt)vcs[i].c[2];
            vertices[i * 12 + 6] = (flt)vcs[i].c[3];
            
            vertices[i * 12 + 7] = (flt)vcs[i].n[0];
            vertices[i * 12 + 8] = (flt)vcs[i].n[1];
            vertices[i * 12 + 9] = (flt)vcs[i].n[2];
            
            vertices[i * 12 + 10] = (flt)vcs[i].t[0];
            vertices[i * 12 + 11] = (flt)vcs[i].t[1];
        }
        
        glBindVertexArray(vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vcs.size() * 12 * sizeof(flt), vertices, GL_STATIC_DRAW);
        delete vertices;
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(uint), inds.data(), GL_STATIC_DRAW);
        
        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(flt), (void*)0);
        glEnableVertexAttribArray(0);
        // color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(flt), (void*)(3 * sizeof(flt)));
        glEnableVertexAttribArray(1);
        // normal
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(flt), (void*)(7 * sizeof(flt)));
        glEnableVertexAttribArray(2);
        // texture
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(flt), (void*)(10 * sizeof(flt)));
        glEnableVertexAttribArray(3);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ~prim() {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);
    }

    void Draw(void) {
        glUseProgram(shd->prg);
        
        glUniform1f(glGetUniformLocation(shd->prg, "time"), (flt)glfwGetTime());
	    glUniformMatrix4fv(glGetUniformLocation(shd->prg, "projection"), 1, GL_FALSE, value_ptr(projection));
	    glUniformMatrix4fv(glGetUniformLocation(shd->prg, "view"), 1, GL_FALSE, value_ptr(view));
	    glUniformMatrix4fv(glGetUniformLocation(shd->prg, "model"), 1, GL_FALSE, value_ptr(model));
        
        glBindVertexArray(vao);
        glDrawElements(prim_type, verts.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};


/* END OF 'prim.h' FILE */
