#version 400
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in mat4 aInstanceModelMatrix;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform bool arrayState;

void main() {
	if (arrayState) {
		gl_Position =  projection * view * aInstanceModelMatrix * vec4(vertex_position, 1.0f);
		FragPos = vec3(aInstanceModelMatrix * vec4(vertex_position, 1.0f));
		Normal = mat3(transpose(inverse(aInstanceModelMatrix))) * aNormal;
	} else {
		gl_Position =  projection * view * model * vec4(vertex_position, 1.0f);
		FragPos = vec3(model * vec4(vertex_position, 1.0f));
		Normal = mat3(transpose(inverse(model))) * aNormal;
	}
}
