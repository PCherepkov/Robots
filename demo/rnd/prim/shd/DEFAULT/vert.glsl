#version 420 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 norm;
layout (location = 3) in vec2 tex;

out vec4 vertex_color;
out vec3 vertex_norm;
out vec3 FragPos;
out vec2 tex_coord;

uniform float time;

// matrices
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 tim;

mat4 rotateY(float angle) {
	mat4 m = mat4(
		cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1
	);
	return m;
}

mat4 rotateX(float angle) {
	mat4 m = mat4(
		1, 0, 0, 0,
		0, cos(angle), -sin(angle), 0,
		0, sin(angle), cos(angle), 0,
		0, 0, 0, 1
	);
	return m;
}

void main() {
  float t = 0;
  mat4 m = rotateX(sin(t * 8) / 8.0) * rotateY(t) * model;
  gl_Position = projection * view * m * vec4(pos, 1.0);
  vertex_color = vec4(tex, 0.0, 1.0);
  tex_coord = tex;
  vertex_norm = mat3(tim) * norm;
  FragPos = vec3(model * vec4(pos, 1.0));
}
