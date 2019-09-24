#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float timeSin;

void main() {
	gl_Position = vec4(aPos.x + timeSin * 0.5, aPos.yz, 0.1f*timeSin + 0.8f);
	ourColor = aColor;
}
