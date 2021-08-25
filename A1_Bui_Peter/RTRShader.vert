#version 400
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position =  projection * view * model * vec4(vertex_position, 1.0f);
	FragPos = vec3(model * vec4(vertex_position, 1.0f));
	Normal = mat3(transpose(inverse(model))) * aNormal;  
}
