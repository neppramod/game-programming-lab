#include "OGLBaseShader.h"
#include "Logger.h"

#include <cstring>

OGLBaseShader::OGLBaseShader() : BaseShader()
{
	this->handle = 0;
}

OGLBaseShader::~OGLBaseShader()
{
}

void OGLBaseShader::showInfoLog(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
{
	GLint logLength;
	glGet__iv(object, GL_INFO_LOG_LENGTH, &logLength);
	char* log = (char*)malloc(logLength);
	glGet__InfoLog(object, logLength, NULL, log);
	if (this->logger) {
		this->logger->log(string(log));
	}
	free(log);
}