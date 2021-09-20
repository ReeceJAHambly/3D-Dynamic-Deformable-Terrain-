#pragma once
#include "mesh.h"
#include "vector"
#include "glm/glm.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "camera.h"



/*struct Object {
	glm::mat4 identity = glm::mat4(1);
	
	Mesh* objectMesh;
	glm::vec3 position;
	glm::vec3 velocity;

	Object() {};
	Object(Mesh* mesh, glm::mat4 translation) {};
};*/



class Primitives {	
public:
	glm::vec3 mPosition = glm::vec3(0, 0, 0);
	glm::vec3 mVelocity = glm::vec3(0,0.1,0);
	glm::mat4 Identity = glm::mat4(1.0);	

	//Cube Vertices
	Vertex v[36] = {
		Vertex(POSITION(-1.0f, -1.0f, -1.0f), NORMAL(0.0f,  0.0f, -1.0f)),
		Vertex(POSITION(1.0f, -1.0f, -1.0f),  NORMAL(0.0f,  0.0f, -1.0f)),
		Vertex(POSITION(1.0f,  1.0f, -1.0f),  NORMAL(0.0f,  0.0f, -1.0f)),
		Vertex(POSITION(1.0f,  1.0f, -1.0f),  NORMAL(0.0f,  0.0f, -1.0f)),
		Vertex(POSITION(-1.0f,  1.0f, -1.0f), NORMAL(0.0f,  0.0f, -1.0f)),
		Vertex(POSITION(-1.0f, -1.0f, -1.0f), NORMAL(0.0f,  0.0f, -1.0f)),

		Vertex(POSITION(-1.0f, -1.0f,  1.0f), NORMAL(0.0f,  0.0f,  1.0f)),
		Vertex(POSITION(1.0f, -1.0f,  1.0f),  NORMAL(0.0f,  0.0f,  1.0f)),
		Vertex(POSITION(1.0f,  1.0f,  1.0f),  NORMAL(0.0f,  0.0f,  1.0f)),
		Vertex(POSITION(1.0f,  1.0f,  1.0f),  NORMAL(0.0f,  0.0f,  1.0f)),
		Vertex(POSITION(-1.0f,  1.0f,  1.0f), NORMAL(0.0f,  0.0f,  1.0f)),
		Vertex(POSITION(-1.0f, -1.0f,  1.0f), NORMAL(0.0f,  0.0f,  1.0f)),

		Vertex(POSITION(-1.0f,  1.0f,  1.0f), NORMAL(-1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(-1.0f,  1.0f, -1.0f), NORMAL(-1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(-1.0f, -1.0f, -1.0f), NORMAL(-1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(-1.0f, -1.0f, -1.0f), NORMAL(-1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(-1.0f, -1.0f,  1.0f), NORMAL(-1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(-1.0f,  1.0f,  1.0f), NORMAL(-1.0f,  0.0f,  0.0f)),

		Vertex(POSITION(1.0f,  1.0f,  1.0f),  NORMAL(1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(1.0f,  1.0f, -1.0f),  NORMAL(1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(1.0f, -1.0f, -1.0f),  NORMAL(1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(1.0f, -1.0f, -1.0f),  NORMAL(1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(1.0f, -1.0f,  1.0f),  NORMAL(1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(1.0f,  1.0f,  1.0f),  NORMAL(1.0f,  0.0f,  0.0f)),

		Vertex(POSITION(-1.0f, -1.0f, -1.0f), NORMAL(0.0f, -1.0f,  0.0f)),
		Vertex(POSITION(1.0f, -1.0f, -1.0f),  NORMAL(0.0f, -1.0f,  0.0f)),
		Vertex(POSITION(1.0f, -1.0f,  1.0f),  NORMAL(0.0f, -1.0f,  0.0f)),
		Vertex(POSITION(1.0f, -1.0f,  1.0f),  NORMAL(0.0f, -1.0f,  0.0f)),
		Vertex(POSITION(-1.0f, -1.0f,  1.0f), NORMAL(0.0f, -1.0f,  0.0f)),
		Vertex(POSITION(-1.0f, -1.0f, -1.0f), NORMAL(0.0f, -1.0f,  0.0f)),

		Vertex(POSITION(-1.0f,  1.0f, -1.0f), NORMAL(0.0f,  1.0f,  0.0f)),
		Vertex(POSITION(1.0f,  1.0f, -1.0f),  NORMAL(0.0f,  1.0f,  0.0f)),
		Vertex(POSITION(1.0f,  1.0f,  1.0f),  NORMAL(0.0f,  1.0f,  0.0f)),
		Vertex(POSITION(1.0f,  1.0f,  1.0f),  NORMAL(0.0f,  1.0f,  0.0f)),
		Vertex(POSITION(-1.0f,  1.0f,  1.0f), NORMAL(0.0f,  1.0f,  0.0f)),
		Vertex(POSITION(-1.0f,  1.0f, -1.0f), NORMAL(0.0f,  1.0f,  0.0f))

	};
	
	//CUBE AND CUBOID INDICES
	GLuint i[36] = {
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,
		15,16,17,
		18,19,20,
		21,22,23,
		24,25,26,
		27,28,29,
		30,31,32,
		33,34,35
	};

	//Cuboid Vertices
	Vertex cuboidV[36] = {
		Vertex(POSITION(-0.5f, -0.5f, -1.5f), NORMAL(0.0f,  0.0f, -1.0f)), //0.5
		Vertex(POSITION(0.5f, -0.5f, -1.5f),  NORMAL(0.0f,  0.0f, -1.0f)),
		Vertex(POSITION(0.5f,  0.5f, -1.5f),  NORMAL(0.0f,  0.0f, -1.0f)),
		Vertex(POSITION(0.5f,  0.5f, -1.5f),  NORMAL(0.0f,  0.0f, -1.0f)),
		Vertex(POSITION(-0.5f,  0.5f, -1.5f), NORMAL(0.0f,  0.0f, -1.0f)),
		Vertex(POSITION(-0.5f, -0.5f, -1.5f), NORMAL(0.0f,  0.0f, -1.0f)),

		Vertex(POSITION(-0.5f, -0.5f,  1.5f), NORMAL(0.0f,  0.0f,  1.0f)),
		Vertex(POSITION(0.5f, -0.5f,  1.5f),  NORMAL(0.0f,  0.0f,  1.0f)),
		Vertex(POSITION(0.5f,  0.5f,  1.5f),  NORMAL(0.0f,  0.0f,  1.0f)),
		Vertex(POSITION(0.5f,  0.5f,  1.5f),  NORMAL(0.0f,  0.0f,  1.0f)),
		Vertex(POSITION(-0.5f,  0.5f,  1.5f), NORMAL(0.0f,  0.0f,  1.0f)),
		Vertex(POSITION(-0.5f, -0.5f,  1.5f), NORMAL(0.0f,  0.0f,  1.0f)),

		Vertex(POSITION(-0.5f,  0.5f,  1.5f), NORMAL(-1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(-0.5f,  0.5f, -1.5f), NORMAL(-1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(-0.5f, -0.5f, -1.5f), NORMAL(-1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(-0.5f, -0.5f, -1.5f), NORMAL(-1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(-0.5f, -0.5f,  1.5f), NORMAL(-1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(-0.5f,  0.5f,  1.5f), NORMAL(-1.0f,  0.0f,  0.0f)),

		Vertex(POSITION(0.5f,  0.5f,  1.5f),  NORMAL(1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(0.5f,  0.5f, -1.5f),  NORMAL(1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(0.5f, -0.5f, -1.5f),  NORMAL(1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(0.5f, -0.5f, -1.5f),  NORMAL(1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(0.5f, -0.5f,  1.5f),  NORMAL(1.0f,  0.0f,  0.0f)),
		Vertex(POSITION(0.5f,  0.5f,  1.5f),  NORMAL(1.0f,  0.0f,  0.0f)),

		Vertex(POSITION(-0.5f, -0.5f, -1.5f), NORMAL(0.0f, -1.0f,  0.0f)),
		Vertex(POSITION(0.5f, -0.5f, -1.5f),  NORMAL(0.0f, -1.0f,  0.0f)),
		Vertex(POSITION(0.5f, -0.5f,  1.5f),  NORMAL(0.0f, -1.0f,  0.0f)),
		Vertex(POSITION(0.5f, -0.5f,  1.5f),  NORMAL(0.0f, -1.0f,  0.0f)),
		Vertex(POSITION(-0.5f, -0.5f,  1.5f), NORMAL(0.0f, -1.0f,  0.0f)),
		Vertex(POSITION(-0.5f, -0.5f, -1.5f), NORMAL(0.0f, -1.0f,  0.0f)),

		Vertex(POSITION(-0.5f,  0.5f, -1.5f), NORMAL(0.0f,  1.0f,  0.0f)),
		Vertex(POSITION(0.5f,  0.5f, -1.5f),  NORMAL(0.0f,  1.0f,  0.0f)),
		Vertex(POSITION(0.5f,  0.5f,  1.5f),  NORMAL(0.0f,  1.0f,  0.0f)),
		Vertex(POSITION(0.5f,  0.5f,  1.5f),  NORMAL(0.0f,  1.0f,  0.0f)),
		Vertex(POSITION(-0.5f,  0.5f,  1.5f), NORMAL(0.0f,  1.0f,  0.0f)),
		Vertex(POSITION(-0.5f,  0.5f, -1.5f), NORMAL(0.0f,  1.0f,  0.0f))
	};
	
	//CUBE
	std::vector<Vertex> cubeVerts = std::vector<Vertex>(std::begin(v), std::end(v));
	std::vector<GLuint> cubeIndices = std::vector<GLuint>(std::begin(i), std::end(i));

	//CUBOID
	std::vector<Vertex> cuboidVerts = std::vector<Vertex>(std::begin(cuboidV), std::end(cuboidV));
	std::vector<GLuint> cuboidIndices = std::vector<GLuint>(std::begin(i), std::end(i));

	//SPHERE VERTICES
	float x, y, z, xy;
	float nx, ny, nz, lengthInv = 1.0f / radius;
	float radius = 1.5;
	float sectorCount = 20.0; //36
	float sectorAngle;
	float stackCount = 10.0; //18
	float stackAngle;
	float stackStep = glm::pi<float>() / stackCount;
	float sectorStep = 2 * glm::pi<float>() / sectorCount;

	std::vector<Vertex> createSphereVerts();
	std::vector<GLuint> createSphereIndices();

	std::vector<Vertex> sphereVerts;
	std::vector<GLuint> sphereIndices;
	void CreateSphere();

	
	
	glm::vec3 previousSphereMovement = glm::vec3(0,0,0);
	void CentreCube();
	void CentreCuboid();
	void CentreSphere();

	glm::vec3 GetPosition();
	Mesh* cubeMesh();
	Mesh* cuboidMesh();
	Mesh* sphereMesh();
};