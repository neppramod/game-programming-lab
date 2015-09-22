#pragma once
#ifndef OGL_SHADER
#define OGL_SHADER

#include "Renderer.h"
#include "OGLObject.h"

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
	struct Vertex {
		GLfloat x, y, z;
		GLfloat red, green, blue;
	};
		

	OGLShaderCompiler * vertexShader;
	OGLShaderCompiler * fragmentShader;
	OGLShaderProgram * shaderProgram;
   
	map<string, OGLObject*>objects; // To draw all the objects
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

