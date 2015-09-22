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
   
	map<string, OGLObject*>objects;
	vector<Vertex> siVertexData;
	Vertex squareVertexData[6];  // For background
	float delta = 0.01f;
	
public:
	OGLRenderer(OGLShaderCompiler * vertexShader, OGLShaderCompiler * fragmentShader, OGLShaderProgram * shaderProgram);
	~OGLRenderer(void);

	bool create();
	void renderObjects();
	void ReadGraphicsFile(string filename, vector<Vertex> & vertices);


protected:
	bool setupShaders();

	//void createsecondI();	
	void createUI();

	//void createBackground();
};

#endif

