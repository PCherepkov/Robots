#version 420 core
out vec4 FragColor;

in vec4 vertex_color;
in vec3 vertex_norm;
in vec3 FragPos;
in vec2 tex_coord;

uniform vec3 cam_pos;

uniform float time;
uniform int tex_num;

uniform sampler2D tex0;
uniform sampler2D tex1;

struct material {
	vec3 ka, kd, ks;
	float ph;
};

uniform material mtl;

void main() {
	/*
    if (tex_num == 2) {
		// FragColor = mix(texture(tex0, tex_coord), texture(tex1, tex_coord), 0.5);
		// FragColor = vec4(c, 1);
		FragColor = texture(tex0, tex_coord);
	}
    else
		FragColor = texture(tex0, tex_coord);
	*/
	vec3 lightColor = vec3(1, 1, 0.9);
	vec3 lightPos = vec3(1);

	// ambient
	vec3 ambient = lightColor * mtl.ka;

	// diffuse
	vec3 norm = normalize(vertex_norm);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = lightColor * (diff * mtl.kd);

	// specular
	vec3 viewDir = normalize(cam_pos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mtl.ph * 128);
    vec3 specular = lightColor * (spec * mtl.ks);

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
	// FragColor = vec4(mtl.kd, 1.0);
}
