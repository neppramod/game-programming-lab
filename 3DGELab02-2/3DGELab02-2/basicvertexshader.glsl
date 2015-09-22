#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
out vec4 fragColor;

void main()
{
	vec4 transformed = vec4(position * .01, 1.0);
	gl_Position = transformed;
	fragColor = vec4(vertexColor, 1.0);
}