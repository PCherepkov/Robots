/* Property of Cherepkov Petr
 * FILE: 'prim.h'
 * LAST UPDATE: 12.12.2023
 */

#pragma once

 /* common header file for topologies */

#include "../../def.h"
#include "shd/shaders.h"
#include "textures/textures.h"
#include "materials/materials.h"

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

/* primitive class itself */

class prim {
    uint vbo, vao, ebo;
    uint tex_num; // number of active textures

public:
    uint prim_type; // GL_TRIANGLES, ...
    vector<vertex> verts;  
    vector<uint> inds;
    mtl* material;
    shader* shd;
    vector<tex*> textures;
    mat4 projection, view, model;

    prim() {
        shd = nullptr;
        material = nullptr;
        model = mat4(1.0f);
        view = mat4(1.0f);
        projection = mat4(1.0f);
        prim_type = GL_POINTS;
    }

    prim(vector<vertex>& vcs, vector<uint>& indxs) {
        prim_type = GL_TRIANGLE_STRIP;
        verts = vcs;
        inds = indxs;
        shd = nullptr;
        material = nullptr;
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glGenVertexArrays(1, &vao);
        
        int stride = 12;
        flt* vertices = new flt[vcs.size() * stride];
        for (uint i = 0; i < vcs.size(); i++) {
            vertices[i * stride + 0] = (flt)vcs[i].p[0];
            vertices[i * stride + 1] = (flt)vcs[i].p[1];
            vertices[i * stride + 2] = (flt)vcs[i].p[2];
            
            vertices[i * stride + 3] = (flt)vcs[i].c[0];
            vertices[i * stride + 4] = (flt)vcs[i].c[1];
            vertices[i * stride + 5] = (flt)vcs[i].c[2];
            vertices[i * stride + 6] = (flt)vcs[i].c[3];
            
            vertices[i * stride + 7] = (flt)vcs[i].n[0];
            vertices[i * stride + 8] = (flt)vcs[i].n[1];
            vertices[i * stride + 9] = (flt)vcs[i].n[2];
            
            vertices[i * stride + 10] = (flt)vcs[i].t[0];
            vertices[i * stride + 11] = (flt)vcs[i].t[1];
        }
        
        glBindVertexArray(vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vcs.size() * stride * sizeof(flt), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(uint), inds.data(), GL_STATIC_DRAW);
        
        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(flt), (void*)0);
        glEnableVertexAttribArray(0);
        // color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(flt), (void*)(3 * sizeof(flt)));
        glEnableVertexAttribArray(1);
        // normal
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(flt), (void*)(7 * sizeof(flt)));
        glEnableVertexAttribArray(2);
        // texture
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride * sizeof(flt), (void*)(10 * sizeof(flt)));
        glEnableVertexAttribArray(3);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        delete vertices;
    }

    ~prim() {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);
    }

    void Draw(void) {
        glUseProgram(shd->prg);

        glUniform3fv(glGetUniformLocation(shd->prg, "mtl.ka"), 1, &material->ka[0]);
        glUniform3fv(glGetUniformLocation(shd->prg, "mtl.kd"), 1, &material->kd[0]);
        glUniform3fv(glGetUniformLocation(shd->prg, "mtl.ks"), 1, &material->ks[0]);
        glUniform1f(glGetUniformLocation(shd->prg, "mtl.ph"), material->ph);

        glUniform1f(glGetUniformLocation(shd->prg, "time"), (flt)glfwGetTime());
	    glUniformMatrix4fv(glGetUniformLocation(shd->prg, "model"), 1, GL_FALSE, value_ptr(model));
	    glUniformMatrix4fv(glGetUniformLocation(shd->prg, "tim"), 1, GL_FALSE, value_ptr(transpose(inverse(model))));
        
        glUniform1i(glGetUniformLocation(shd->prg, "tex_num"), textures.size());
        for (int i = 0; i < textures.size(); i++) {
            glUniform1i(glGetUniformLocation(shd->prg, (string("tex") + (char)('0' + i)).c_str()), i);
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textures[i]->code);
        }

        glBindVertexArray(vao);
        glDrawElements(prim_type, inds.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(0);
    }
};


/* END OF 'prim.h' FILE */
