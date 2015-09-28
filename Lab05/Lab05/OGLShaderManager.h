#pragma once
#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include <string>
using std::string;
#include <map>
using std::map;

#include <gl\glew.h>

#include "OGLShaderProgram.h"

class OGLShaderCompiler;

struct ShadingUnit {
	OGLShaderProgram * shaderProgram;
	string vertexShaderName;
	string fragmentShaderName;
};

class OGLShaderManager
{
private:
	map<string, OGLShaderCompiler *> vertexShaders;
	map<string, OGLShaderCompiler *> fragmentShaders;
	map<string, ShadingUnit> shaderPrograms;

public:
	OGLShaderManager();
	~OGLShaderManager();

	void addVertexShader(string name, OGLShaderCompiler* vertexShader);
	void addFragmentShader(string name, OGLShaderCompiler* fragmentShader);
	void addShaderProgram(string name, OGLShaderProgram* shaderProgram, string vertexShaderName, string fragmentShaderName);
	bool createShader(string shaderName);
	GLuint getShaderHandle(string shaderName);

private:
	bool compileVertexShader(string vertexShaderName);
	bool compileFragmentShader(string fragmentShaderName);
	bool linkShader(string shaderName, OGLShaderCompiler * vertexShader, OGLShaderCompiler * fragmentShader);
};

#endif

