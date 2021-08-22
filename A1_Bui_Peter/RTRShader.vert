#version 400
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
out vec3 v_color;

void main() {
	v_color = vertex_color;
	gl_Position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.0);
}
