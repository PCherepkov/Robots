#version 420 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 norm;
layout (location = 3) in vec2 tex;

out vec4 vertex_color;
out vec3 vertex_norm;
out vec2 tex_coord;

uniform float time;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 tim;

void main() {
  gl_Position = projection * view * model * vec4(pos, 1.0);
  vertex_color = color;
  tex_coord = tex;
}
