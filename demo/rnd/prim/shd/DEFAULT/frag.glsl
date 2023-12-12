#version 420 core
out vec4 FragColor;

in vec4 vertex_color;
in vec3 vertex_norm;
in vec3 FragPos;
in vec2 tex_coord;

uniform vec3 cam_pos;

uniform float time;

uniform int light_num;
uniform int tex_num;

uniform sampler2D tex0;
uniform sampler2D tex1;


struct light {
	vec3 ka, kd, ks;
};

struct dir_light {
	vec3 dir;
	vec3 ka, kd, ks;
};

struct point_light {
	vec3 pos;
	vec3 ka, kd, ks;

	float con, lin, qad;
};

struct material {
	vec3 ka, kd, ks;
	float ph;
};

uniform material mtl;
uniform point_light point_lights[12];
uniform dir_light direct_lights[12];

vec3 compute_dir(dir_light L) {
	// ambient
	vec3 ambient = L.ka * mtl.ka;

	// diffuse
	vec3 norm = normalize(vertex_norm);
	if (tex_num == 2)
		norm = texture(tex1, tex_coord).xyz;
	float diff = max(dot(norm, L.dir), 0.0);
	vec3 diffuse = L.kd * (diff * mtl.kd);

	// specular
	vec3 viewDir = normalize(cam_pos - FragPos);
    vec3 reflectDir = reflect(-L.dir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mtl.ph * 128);
    vec3 specular = L.ks * (spec * mtl.ks);
	return ambient + diffuse + specular;
}

vec3 compute_point(point_light L) {
	float dist  = length(L.pos - FragPos);
	float atten = 1.0 / (L.con + L.lin * dist + L.qad * (dist * dist));

	// ambient
	vec3 ambient = L.ka * mtl.ka;

	// diffuse
	vec3 norm = normalize(vertex_norm);
	if (tex_num == 2)
		norm = texture(tex1, tex_coord).xyz;
	vec3 lightDir = normalize(L.pos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = L.kd * (diff * mtl.kd);

	// specular
	vec3 viewDir = normalize(cam_pos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mtl.ph * 128);
    vec3 specular = L.ks * (spec * mtl.ks);
	return (ambient + diffuse + specular) * atten;
}

void main() {
	vec3 result = compute_point(point_lights[0]) +
				  compute_point(point_lights[1]) + 
				  compute_dir(direct_lights[0]);
	result = clamp(result, vec3(0), vec3(1));
	FragColor = vec4(result, 1.0);
	// FragColor = vec4(tex_coord, 0.0, 1.0);
}
