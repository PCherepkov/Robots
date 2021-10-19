#version 420 core
out vec4 FragColor;

in vec4 vertex_color;
uniform float time;

void main() {
  FragColor = vertex_color;
}
