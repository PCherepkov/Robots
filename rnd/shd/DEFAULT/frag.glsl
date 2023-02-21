#version 420 core
out vec4 FragColor;

in vec4 vertex_color;
in vec2 tex_coord;

uniform float time;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() {
  // FragColor = vertex_color;
  FragColor = mix(texture(tex1, tex_coord), texture(tex2, tex_coord), 0.5);
}
