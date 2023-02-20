#version 420 core
out vec4 FragColor;

in vec4 vertex_color;
in vec2 tex_coord;

uniform float time;

uniform sampler2D Texture;

void main() {
  // FragColor = vertex_color;
  FragColor = texture(Texture, tex_coord);
}
