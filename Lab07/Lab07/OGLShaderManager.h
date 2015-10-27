#pragma once
#ifndef OGL_SHADER_MANAGER
#define OGL_SHADER_MANAGER

#include <string>
using std::string;
#include <map>
using std::map;

#include <gl\glew.h>
#include <glm\glm.hpp>

#include "OGLShaderProgram.h"
#include "ShaderManager.h"

class OGLShaderCompiler;

struct ShadingUnit {
	OGLShaderProgram * shaderProgram;
	string vertexShaderName;
	string fragmentShaderName;
};

class OGLShaderManager : public ShaderManager
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

	void addShaderProgram(
		string name, 
		OGLShaderProgram* shaderProgram, 
		string vertexShaderName, 
		string fragmentShaderName);

	bool createShader(const string& shaderName);

	bool createShaders();

	GLuint getShaderHandle(string shaderName);

	void sendMatrixToGPU(
		GLuint shaderProgram, 
		const string& uniformName, 
		const glm::mat4 &matrix);

private:
	bool compileVertexShader(string vertexShaderName);
	bool compileFragmentShader(string fragmentShaderName);
	bool linkShader(string shaderName, OGLShaderCompiler * vertexShader, OGLShaderCompiler * fragmentShader);
};

#endif

