#include "OGLFragmentShader.h"

OGLFragmentShader::OGLFragmentShader(GLchar* source) : OGLShaderCompiler(source)
{
	if (this->source == NULL) {
		this->source = OGLFragmentShader::stockSource();
	}
}

OGLFragmentShader::~OGLFragmentShader()
{
}

bool OGLFragmentShader::compile()
{
	OGLShaderCompiler::compile(GL_FRAGMENT_SHADER, this->source);
	if (this->handle == 0) return false;
	return true;
}

GLchar * OGLFragmentShader::stockSource()
{
	static GLchar* fragmentSource =
		"#version 330\n"\
		"in vec4 fragColor;\n"\
		"out vec4 color;\n"\
		"void main()\n"\
		"{\n"\
		"   color = fragColor;\n"\
		"}\n";
	return fragmentSource;
}