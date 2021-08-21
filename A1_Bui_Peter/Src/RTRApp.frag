#version 400
in vec3 verColour;

out vec4 fragmentColour;

void main() {
	fragmentColour = vec4(verColour, 1.0f);
}