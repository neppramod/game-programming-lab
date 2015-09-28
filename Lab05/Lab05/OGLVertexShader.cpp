#include "OGLVertexShader.h"

#include <cstring>

OGLVertexShader::OGLVertexShader(GLchar* source) : OGLShaderCompiler(source)
{
	if (this->source == NULL) {
		this->source = OGLVertexShader::stockSource();
	}
}

OGLVertexShader::~OGLVertexShader()
{
}

bool OGLVertexShader::compile()
{
	OGLShaderCompiler::compile(GL_VERTEX_SHADER, this->source);
	if (this->handle == 0) return false;
	return true;
}

GLchar * OGLVertexShader::stockSource()
{
	static GLchar* vertexSource =
		"#version 330\n"\
		"layout(location = 0) in vec4 position;\n"\
		"layout(location = 1) in vec4 vertexColor;\n"\
		"out vec4 fragColor;\n"\
		"void main()\n"\
		"{\n"\
		"   gl_Position = position;\n" \
		"   fragColor = vertexColor;\n" \
		"}\n";
	return vertexSource;
}
