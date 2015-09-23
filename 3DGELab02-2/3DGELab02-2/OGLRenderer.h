#pragma once
#ifndef OGL_SHADER
#define OGL_SHADER

#include "Renderer.h"
#include "OGLObject.h"
#include "Core.h"

#include <gl/glew.h>
#include <map>
#include <vector>

using namespace std;
using std::map;

class Logger;
class OGLShaderCompiler;
class OGLShaderProgram;

class OGLRenderer : public Renderer
{
protected:
	
	OGLShaderCompiler * vertexShader;
	OGLShaderCompiler * fragmentShader;
	OGLShaderProgram * shaderProgram;
   
	map<string, OGLObject*>objects; // To draw all the objects

	typedef Core::Vertex Vertex;
	Core core;
	
	// To make vector available to file, it had to be put inside Core
	vector<Vertex> siVertexData;
	
public:
	OGLRenderer(OGLShaderCompiler * vertexShader, OGLShaderCompiler * fragmentShader, OGLShaderProgram * shaderProgram);
	~OGLRenderer(void);

	bool create();
	void renderObjects();
	void ReadGraphicsFile(string filename, vector<Vertex> & vertices);

protected:
	bool setupShaders();
	void createUI();

};

#endif

