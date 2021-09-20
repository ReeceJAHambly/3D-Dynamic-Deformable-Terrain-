#pragma once
#include "mesh.h"
#include "vector"
#include "glm/glm.hpp"
#include <string.h>


class Terrain2 {
private:
	float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos); 
	
public:
	POSITION position = POSITION(0, 0, 0);
	POSITION worldPosition = POSITION(0, 0, 0);
	std::vector<Vertex> Vertices = std::vector<Vertex>();
	std::vector<GLuint> Indices = std::vector<GLuint>();

	std::vector < std::vector<Vertex>> Groups = std::vector<std::vector<Vertex>>();
	void createGroups();

	int terrainSize = 128; //256 - Standard Size
	
	Mesh* terrainGeneration;
	void generateVertices(glm::vec3);
	void generateIndices();
	Mesh* generateMesh();
	void updateMesh(Mesh* pTerrainMesh);
	void Noise();
	void generateNormals(std::vector<Vertex>& Vertices, std::vector<GLuint> Indices);
	void centreTerrain(std::vector<Vertex>* pVertices);

	std::vector<Vertex> generateWaterVertices(glm::vec3);
	std::vector<GLuint> generateWaterIndices();

	int findTerrainPosition(float worldX, float worldZ);
	float getHeightOfTerrain(float worldX, float worldZ);

	float GetNoiseValue(float x, float z, float value);
	float Clamp(float n);
};