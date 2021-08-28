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

uniform int sceneState;

uniform float timeTotal;

vec3 InterpolatedPositions() {
	vec3 calcPoint = vec3(0.0f);

	float posX = vertex_position.x;
	float posY = vertex_position.y;
	float posZ = vertex_position.z;

	float radius = (abs(posX) > abs(posY) ? posX : posY);
	radius = abs(radius) > abs(posZ) ? radius : posZ;
	radius = abs(radius);

	vec3 currPos = vec3(posX, posY, posZ);
	calcPoint = normalize(currPos);

	calcPoint *= radius;

	vec3 newPos = currPos + ((calcPoint - currPos) * sin(timeTotal * timeTotal));

	return newPos;
};

void main() {
	if (sceneState == 0) {
		gl_Position =  projection * view * model * vec4(vertex_position, 1.0f);
		FragPos = vec3(model * vec4(vertex_position, 1.0f));
		Normal = mat3(transpose(inverse(model))) * aNormal;
	}
	else if (sceneState == 1) {
		gl_Position =  projection * view * aInstanceModelMatrix * vec4(vertex_position, 1.0f);
		FragPos = vec3(aInstanceModelMatrix * vec4(vertex_position, 1.0f));
		Normal = mat3(transpose(inverse(aInstanceModelMatrix))) * aNormal;
	} else if (sceneState == 2) {
		vec3 newVertexPositions = InterpolatedPositions();
		gl_Position =  projection * view * model * vec4(newVertexPositions, 1.0f);
		FragPos = vec3(model * vec4(vertex_position, 1.0f));
		Normal = mat3(transpose(inverse(model))) * aNormal;
	}
}
