#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
out vec4 fragColor;

uniform mat4 localToWorldMatrix;
uniform mat4 worldToCameraMatrix;
uniform mat4 cameraToScreenMatrix;

void main()
{
	gl_Position = cameraToScreenMatrix * worldToCameraMatrix * localToWorldMatrix * vec4(position, 1.0);
	fragColor = vec4(vertexColor, 1.0);
}