#pragma once
#ifndef OGL_FRAGMENT_SHADER
#define OGL_FRAGMENT_SHADER

#include "OGLShaderCompiler.h"

#ifndef NULL
#define NULL 0
#endif

class OGLFragmentShader : public OGLShaderCompiler
{
public:
	OGLFragmentShader(GLchar* source = NULL);
	virtual ~OGLFragmentShader();

	bool compile();

	static GLchar * stockSource();
};

#endif

