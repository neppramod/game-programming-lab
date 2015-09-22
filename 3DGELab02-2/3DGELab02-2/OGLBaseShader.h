#pragma once
#ifndef OGL_BASE_SHADER
#define OGL_BASE_SHADER

#include "BaseShader.h"

#include <gl/glew.h>

class OGLBaseShader : public BaseShader
{
protected:
	GLuint handle;

public:
	OGLBaseShader();
	virtual ~OGLBaseShader();

	GLuint getHandle() const { return this->handle; }

protected:
	void showInfoLog(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
};

#endif

