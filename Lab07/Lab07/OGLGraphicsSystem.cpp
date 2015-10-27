#include "OGLGraphicsSystem.h"
#include "OGLShaderManager.h"
#include "OGLVertexShader.h"
#include "OGLFragmentShader.h"
#include "OGLShaderProgram.h"
#include "GameWorld.h"
#include "OGLViewingFrustum.h"
#include "Logger.h"
#include "OGLCamera.h"
#include "GameObjectManager.h"
#include "OGLObject.h"

#include <map>
using std::map;
#include <glm\gtc\type_ptr.hpp>
#include <glutil\glutil.h>

OGLGraphicsSystem::OGLGraphicsSystem(
	OGLShaderManager *shaderManager, 
	GameWorld *gameWorld, 
	OGLViewingFrustum *oglFrustum) :
		GraphicsSystem(shaderManager, gameWorld, oglFrustum)
{
	this->oglShaderManager = (OGLShaderManager*)this->shaderManager;
	this->oglFrustum = (OGLViewingFrustum*)this->frustum;
	this->oglCamera = (OGLCamera*)this->gameWorld->getCamera();
	this->activeShaderProgram = 0;
}

OGLGraphicsSystem::~OGLGraphicsSystem()
{
}

void OGLGraphicsSystem::addVertexShader(
	const string& name, OGLVertexShader *shader, const string& sourceCode)
{
	if (sourceCode != "") {
		shader->setSource(sourceCode);
	}
	shader->setLogger(this->logger);
	this->oglShaderManager->addVertexShader(name, shader);
}

void OGLGraphicsSystem::addFragmentShader(
	const string& name, OGLFragmentShader *shader, const string& sourceCode)
{
	if (sourceCode != "") {
		shader->setSource(sourceCode);
	}
	shader->setLogger(this->logger);
	this->oglShaderManager->addFragmentShader(name, shader);
}

void OGLGraphicsSystem::addShaderProgram(
	const string& name,
	OGLShaderProgram *shaderProgram, const string& vertexShaderName, const string& fragmentShaderName)
{
	shaderProgram->setLogger(this->logger);
	this->oglShaderManager->addShaderProgram(
		name, shaderProgram, vertexShaderName, fragmentShaderName);
}

bool OGLGraphicsSystem::initialize()
{
	this->initialized = this->oglShaderManager->createShaders();
	return this->initialized;
}

void OGLGraphicsSystem::setUpViewingEnvironment()
{
	updateViewingFrustum();

	// Cull back faces and use counter-clockwise winding of front faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
}

void OGLGraphicsSystem::setActiveShaderProgram(const string& shaderProgramName)
{
	this->activeShaderProgram = this->oglShaderManager->getShaderHandle(shaderProgramName);
	if (this->activeShaderProgram == 0) {
		if (this->logger) {
			this->logger->log("Could not set active shader program!");
		}
	}
}

void OGLGraphicsSystem::setObjectsShaderProgram(const string& shaderProgramName)
{
	GLuint shaderProgram = 
		this->oglShaderManager->getShaderHandle(shaderProgramName);
	auto allObjects = this->getGameWorld()->getObjectManager()->getAllObjects();

	OGLObject *object;
	auto iterator = allObjects.begin();
	while (iterator != allObjects.end()) {
		object = (OGLObject*)iterator->second;
		object->shaderProgram = shaderProgram;
		iterator++;
	}
}

void OGLGraphicsSystem::update(float elapsedSeconds)
{
	GraphicsSystem::update(elapsedSeconds);

	this->oglShaderManager->sendMatrixToGPU(
		this->activeShaderProgram,
		"worldToCameraMatrix",
		this->oglCamera->orientation);
}

void OGLGraphicsSystem::updateViewingFrustum()
{
	this->oglShaderManager->sendMatrixToGPU(
		this->activeShaderProgram,
		"cameraToScreenMatrix",
		this->oglFrustum->getMatrix());
}

void OGLGraphicsSystem::render()
{
	GameObjectManager *objectMgr = this->gameWorld->getObjectManager();
	objectMgr->renderVisibleObjects();
}

void OGLGraphicsSystem::clearViewPort(
	unsigned int left, unsigned int top,
	unsigned int width, unsigned int height,
	RGBA color)
{
	glViewport(left, top, width, height);
	glClearColor(color.red, color.green, color.blue, color.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
