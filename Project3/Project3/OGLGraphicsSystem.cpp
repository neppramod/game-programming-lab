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
#include "LocalLightSource.h"

#include <map>
using std::map;
#include <glm\gtc\type_ptr.hpp>
#include <glutil\glutil.h>

OGLGraphicsSystem::OGLGraphicsSystem(
	OGLShaderManager *shaderManager, 
	GameWorld *gameWorld, 
	OGLViewingFrustum *oglFrustum,
	LocalLightSource *localLightSource) :
		GraphicsSystem(shaderManager, gameWorld, oglFrustum, localLightSource)
{
	this->oglShaderManager = (OGLShaderManager*)this->shaderManager;
	this->oglFrustum = (OGLViewingFrustum*)this->frustum;
	this->oglCamera = (OGLCamera*)this->gameWorld->getCamera();
	this->localLightSource = localLightSource;
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

void OGLGraphicsSystem::setObjectShaderProgram(const string& objectName, const string& shaderProgramName)
{
	GLuint shaderProgram =
		this->oglShaderManager->getShaderHandle(shaderProgramName);
	GameObjectManager *objectMgr = this->gameWorld->getObjectManager();
	OGLObject *object = (OGLObject *)objectMgr->getObject(objectName);
	object->shaderProgram = shaderProgram;

}

void OGLGraphicsSystem::update(float elapsedSeconds)
{
	GraphicsSystem::update(elapsedSeconds);
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
	glm::vec3 globalLightPos = glm::vec3(100, 100, 0);
	
	
	
	this->oglShaderManager->sendVectorToGPU(
		this->activeShaderProgram,
		"worldGlobalLightPos",
		globalLightPos);

	glm::vec3 localLightPos = (glm::vec3) this->getLocalLightSource()->getPostion();

	//glm::vec3 worldLightPos = glm::vec3(-8, 9, -8);
	this->oglShaderManager->sendVectorToGPU(
		this->activeShaderProgram,
		"worldLightPos",
		localLightPos);

	float globalLightIntensity = 0.1f;
	this->oglShaderManager->sendValueToGPU(
		this->activeShaderProgram,
		"globalLightIntensity",
		globalLightIntensity);

	//float lightIntensity = 0.4f;
	float lightIntensity = this->getLocalLightSource()->getIntensity();
	this->oglShaderManager->sendValueToGPU(
		this->activeShaderProgram,
		"lightIntensity",
		lightIntensity);

	this->oglShaderManager->sendMatrixToGPU(
		this->activeShaderProgram,
		"worldToCameraMatrix",
		this->oglCamera->orientation);

	this->oglShaderManager->sendVectorToGPU(
		this->activeShaderProgram,
		"worldCameraPos",
		glm::vec3(this->oglCamera->orientation[3]));

	/*
	this->oglShaderManager->sendVectorToGPU(
		this->activeShaderProgram,
		"localLightPos",
		localLightSource->getPostion());

	this->oglShaderManager->sendValueToGPU(
		this->activeShaderProgram,
		"localLight",
		localLightSource->getIntensity());

    */
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
