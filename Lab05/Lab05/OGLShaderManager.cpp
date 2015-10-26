	#include "OGLShaderManager.h"
#include "OGLShaderCompiler.h"


OGLShaderManager::OGLShaderManager()
{
}

OGLShaderManager::~OGLShaderManager()
{
}

GLuint OGLShaderManager::getShaderHandle(string shaderName)
{
	if (this->shaderPrograms.find(shaderName) != this->shaderPrograms.end()) {
		return this->shaderPrograms[shaderName].shaderProgram->getHandle();
	}
	return 0;
}

void OGLShaderManager::addVertexShader(string name, OGLShaderCompiler* vertexShader)
{
	if (this->vertexShaders.find(name) == this->vertexShaders.end()) {
		this->vertexShaders[name] = vertexShader;
	}
}

void OGLShaderManager::addFragmentShader(string name, OGLShaderCompiler* fragmentShader)
{
	if (this->fragmentShaders.find(name) == this->fragmentShaders.end()) {
		this->fragmentShaders[name] = fragmentShader;
	}
}

void OGLShaderManager::addShaderProgram(string name, OGLShaderProgram* shaderProgram, string vertexShaderName, string fragmentShaderName)
{
	if (this->shaderPrograms.find(name) == this->shaderPrograms.end()) {
		ShadingUnit unit = { shaderProgram, vertexShaderName, fragmentShaderName };
		this->shaderPrograms[name] = unit;
	}
}

bool OGLShaderManager::createShader(string shaderName)
{
	string vertexShaderName = this->shaderPrograms[shaderName].vertexShaderName;
	bool result = this->compileVertexShader(vertexShaderName);
	if (!result) return false;

	string fragmentShaderName = this->shaderPrograms[shaderName].fragmentShaderName;
	result = this->compileFragmentShader(fragmentShaderName);
	if (!result) return false;

	return this->linkShader(
		shaderName, 
		this->vertexShaders[vertexShaderName], 
		this->fragmentShaders[fragmentShaderName]);
}

bool OGLShaderManager::compileVertexShader(string vertexShaderName)
{
	bool result = false;
	OGLShaderCompiler* vertexShader = NULL;
	if (this->vertexShaders.find(vertexShaderName) != this->vertexShaders.end()) {
		vertexShader = this->vertexShaders[vertexShaderName];
		if (vertexShader->getHandle() == 0) {
			result = vertexShader->compile();
		}
		else {
			result = true;
		}
	}
	return result;
}

bool OGLShaderManager::compileFragmentShader(string fragmentShaderName)
{
	bool result = false;
	OGLShaderCompiler* fragmentShader = NULL;
	if (this->fragmentShaders.find(fragmentShaderName) != this->fragmentShaders.end()) {
		fragmentShader = this->fragmentShaders[fragmentShaderName];
		if (fragmentShader->getHandle() == 0) {
			result = fragmentShader->compile();
		}
		else {
			result = true;
		}
	}
	return result;
}

bool OGLShaderManager::linkShader(
	string shaderName, OGLShaderCompiler * vertexShader, OGLShaderCompiler * fragmentShader)
{
	bool result = false;
	OGLShaderProgram* shaderProgram = NULL;
	if (this->shaderPrograms.find(shaderName) != this->shaderPrograms.end()) {
		shaderProgram = this->shaderPrograms[shaderName].shaderProgram;
		result = shaderProgram->link(vertexShader->getHandle(), fragmentShader->getHandle());
	}
	return result;
}
