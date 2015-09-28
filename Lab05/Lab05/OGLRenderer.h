#pragma once
#ifndef OGL_SHADER
#define OGL_SHADER

#include "Renderer.h"
#include "OGLObject.h"
#include "OGLSphericalCamera.h"

#include <gl/glew.h>
#include <map>
using std::map;

class Logger;
class OGLShaderManager;

class OGLRenderer : public Renderer
{
protected:
	struct Triple {
		GLfloat p1, p2, p3;
	};

	Triple pyramid[36];

	OGLSphericalCamera camera;
	GLuint cameraToScreenMatrixUnif;

	OGLShaderManager * shaderMgr;

	map<string, OGLObject *> objects;

	float theta;
	float phi;

public:
	OGLRenderer(OGLShaderManager * shaderMgr);
	~OGLRenderer(void);

	bool create();
	void renderObjects();
	void addObject(string name, OGLObject *object);

	void updateViewingFrustum(string shaderName, float fov, float aspectRatio, float zNear, float zFar);

	void moveCameraRight();
	void moveCameraLeft();

	void moveCameraUp();
	void moveCameraDown();

protected:
	bool setupShaders();

	void createPyramid();

	void updateCameraPosition();
};

#endif

