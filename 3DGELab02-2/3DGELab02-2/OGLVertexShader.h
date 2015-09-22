#pragma once
#ifndef OGL_VERTEX_SHADER
#define OGL_VERTEX_SHADER

#include "OGLShaderCompiler.h"

#ifndef NULL
#define NULL 0
#endif

class OGLVertexShader : public OGLShaderCompiler
{

public:
	OGLVertexShader(GLchar* source=NULL);
	virtual ~OGLVertexShader();

	bool compile();

	static GLchar * stockSource();
};

#endif

