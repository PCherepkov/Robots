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
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;


struct light {
	vec3 ka, kd, ks;
};

struct spot_light {
	vec3 ka, kd, ks;
	vec3 pos, dir;
	float cuti, cuto;
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
uniform spot_light spot_lights[12];

vec3 compute_spot(spot_light L) {
	L.dir = vec3(sin(time) / 6, -1, cos(time) / 4);
	vec3 lightDir = normalize(L.pos - FragPos);
	float theta     = dot(lightDir, normalize(-L.dir));
	float epsilon   = L.cuti - L.cuto;
	float intensity = clamp((theta - L.cuto) / epsilon, 0.0, 1.0);

	// ambient
	vec3 ambient = L.ka * 0;

	// diffuse
	vec3 norm = normalize(vertex_norm + vec3(texture(tex2, tex_coord * vec2(1.0, -1.0) + vec2(0.0, 1.0))));
	if (tex_num == 2)
		norm = texture(tex1, tex_coord).xyz;
	float diff = max(dot(norm, lightDir), 0.0);
	// vec3 diffuse = L.kd * (diff * mtl.kd) * intensity;
	vec3 diffuse = L.kd * (diff * vec3(texture(tex1, tex_coord * vec2(1.0, -1.0) + vec2(0.0, 1.0)))) * intensity;

	// specular
	vec3 viewDir = normalize(cam_pos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mtl.ph * 128);
    // vec3 specular = L.ks * (spec * mtl.ks) * intensity;
    vec3 specular = L.ks * (spec * vec3(texture(tex2, tex_coord * vec2(1.0, -1.0) + vec2(0.0, 1.0)))) * intensity;

	return ambient + diffuse + specular;
}

vec3 compute_dir(dir_light L) {
	// ambient
	vec3 ambient = L.ka * 0;

	// diffuse
	vec3 norm = normalize(vertex_norm + vec3(texture(tex2, tex_coord * vec2(1.0, -1.0) + vec2(0.0, 1.0))));
	float diff = max(dot(norm, L.dir), 0.0);
	// vec3 diffuse = L.kd * (diff * mtl.kd);
	vec3 diffuse = L.kd * (diff * vec3(texture(tex1, tex_coord * vec2(1.0, -1.0) + vec2(0.0, 1.0))));

	// specular
	vec3 viewDir = normalize(cam_pos - FragPos);
    vec3 reflectDir = reflect(-L.dir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mtl.ph * 128);
    // vec3 specular = L.ks * (spec * mtl.ks);
    vec3 specular = L.ks * (spec * vec3(texture(tex2, tex_coord * vec2(1.0, -1.0) + vec2(0.0, 1.0))));
	return ambient + diffuse + specular;
}

vec3 compute_point(point_light L) {
	float dist  = length(L.pos - FragPos);
	float atten = 1.0 / (L.con + L.lin * dist + L.qad * (dist * dist)) * (sin(time) / 2 + 2);

	// ambient
	vec3 ambient = L.ka * 0;

	// diffuse
	vec3 norm = normalize(vertex_norm + vec3(texture(tex2, tex_coord * vec2(1.0, -1.0) + vec2(0.0, 1.0))));
	vec3 lightDir = normalize(L.pos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	// vec3 diffuse = L.kd * (diff * mtl.kd);
	vec3 diffuse = L.kd * (diff * vec3(texture(tex1, tex_coord * vec2(1.0, -1.0) + vec2(0.0, 1.0))));

	// specular
	vec3 viewDir = normalize(cam_pos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mtl.ph * 128);
    // vec3 specular = L.ks * (spec * mtl.ks);
    vec3 specular = L.ks * (spec * vec3(texture(tex2, tex_coord * vec2(1.0, -1.0) + vec2(0.0, 1.0))));
	return (ambient + diffuse + specular) * atten;
}

void main() {
	vec3 result = compute_point(point_lights[0]) +
				  compute_point(point_lights[1]) + 
				  compute_dir(direct_lights[0]) +
				  compute_spot(spot_lights[0]);
	result = clamp(result, vec3(0), vec3(1));
	FragColor = vec4(result, 1.0);
}
