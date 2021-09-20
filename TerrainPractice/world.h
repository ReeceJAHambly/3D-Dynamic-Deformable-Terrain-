#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "scene.h"
#include "terrain2.h"
#include "Primitives.h"
#include <string>
//#include <list>

class Mesh;

class World : public Scene {
private:
	
	int createValue = -1;
	int worldSize = 256; //Value is squared 256
	bool movement = true;
	Terrain2 terrain;
	Terrain2 water;
	//std::vector<Mesh*> terrainSquares;
	Mesh* terrainMesh;
	Mesh* waterMesh;
	Mesh* ObjectMesh;
	Primitives collidable;
	std::vector<Mesh*> objectList;
	std::vector<Mesh*> sphereList;
	std::vector<Vertex> vertices;
	GLuint shader;
	glm::mat4 model;
	bool wireframe = true;
	float time, speed,fspeed;
	Vertex practicePoint;
	Mesh * CollisionMesh;
	std::vector<bool> collideArray; 
	bool create = true;
	bool moved = false;
	std::vector<glm::vec3> objectPositions = std::vector<glm::vec3>();
public:
	void Initialize();
	void Update(float delta);
	void Render();
	void Release();
	void CubeDeformation(std::vector<Vertex> verts,std::vector<Mesh*> objectList, Mesh* terrain);

	bool doneOnce = false;
	bool doneTwice = false;
	bool doneThree = false;
	bool doneFour = false;
	bool doneFive = false;
	bool doneSix = false;
	bool doneSeven = false;
	bool doneEight = false;
	bool doneNine = false;
	bool doneTen = false;

	void ObjectInfo();

	void CameraInfo();

	static World* GetInstance();
private:
	static World instance;
	World();
};