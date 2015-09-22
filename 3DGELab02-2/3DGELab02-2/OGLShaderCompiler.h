#pragma once
#ifndef OGL_SHADER_COMPILER
#define OGL_SHADER_COMPILER

#include "OGLBaseShader.h"

#ifndef NULL
#define NULL 0
#endif

class OGLShaderCompiler :
	public OGLBaseShader
{
protected:
	GLchar * source;

public:
	OGLShaderCompiler(GLchar* source = NULL);
	virtual ~OGLShaderCompiler();

	virtual bool compile() = 0;

protected:
	void compile(GLenum type, const GLchar* source);
};

#endif

