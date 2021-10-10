/* Property of Cherepkov Petr
 * FILE: 'shaders.h'
 * LAST UPDATE: 10.10.2021
 */

#pragma once

#include <vector>
#include <fstream>

#include "../../def.h"

/* common header file for shaders */

class shader {
public:
  uint prg;
  shader() {}
  ~shader() {
  }

  shader(const std::string& name) {
    /* loading data for shaders */
    ifstream
      f(name + "frag.glsl", ios::in),
      v(name + "vert.glsl", ios::in);
    // f.open(/*name + "../rnd/shd/DEFAULT/frag.glsl"*/ "tmp.txt");
    // v.open(/*name + "../rnd/shd/DEFAULT/vert.glsl"*/ "tmp.txt");

    if (f.fail() || v.fail()) {
      std::cout << "Error while shader source loading";
      f.close();
      v.close();
      return;
    }

    uint vert_id, frag_id;

    std::string src;
    char buf[256];
    while (!f.eof()) {
      f.getline(buf, 256);
      src += buf;
      src += '\n';
    }

    char* fsrc = new char[src.size()];
    memcpy(fsrc, src.data(), src.size());
    fsrc[src.size() - 1] = 0;
    src.clear();

    while (!v.eof()) {
      v.getline(buf, 256);
      src += buf;
      src += '\n';
    }

    const char* vsrc;
    vsrc = src.data();

    f.close();
    v.close();

    /* compiling vertex shader */
    vert_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_id, 1, &vsrc, NULL);
    glCompileShader(vert_id);

    char log[512];

    /* vertex shader logs */
    int status;
    glGetShaderiv(vert_id, GL_COMPILE_STATUS, &status);
    if (!status) {
      glGetShaderInfoLog(vert_id, 512, NULL, log);
      std::cout << "vertex shader compilation error\n" << log << std::endl;
      return;
    }

    /* compiling fragment shader */
    frag_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_id, 1, &fsrc, NULL);
    glCompileShader(frag_id);

    /* fragment shader logs */
    glGetShaderiv(frag_id, GL_COMPILE_STATUS, &status);
    if (!status) {
      glGetShaderInfoLog(frag_id, 512, NULL, log);
      std::cout << "fragment shader compilation error\n" << log << std::endl;
      return;
    }

    /* Shader program creation */
    prg = glCreateProgram();
    glAttachShader(prg, vert_id);
    glAttachShader(prg, frag_id);
    glLinkProgram(prg);

    /* linking logs */
    glGetProgramiv(prg, GL_LINK_STATUS, &status);
    if (!status) {
      glGetProgramInfoLog(prg, 512, NULL, log);
      std::cout << "linking error\n" << log << std::endl;
      return;
    }

    /* shader objects deleting */
    glDeleteShader(vert_id);
    glDeleteShader(frag_id);
  }
};

/* END OF 'shaders.h' FILE */
