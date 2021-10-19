#version 420 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 norm;
layout (location = 3) in vec2 tex;

out vec4 vertex_color;
uniform float time;

void main() {
  vec3 res_pos = pos / 2;
  gl_Position = vec4(res_pos, 1.0);
  vertex_color = vec4(color, 1.0);
}
