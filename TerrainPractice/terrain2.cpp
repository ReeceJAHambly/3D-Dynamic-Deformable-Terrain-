#include "terrain2.h"
#include <ctime>
#include <math.h>
#include <glm/gtc/noise.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "glm/gtx/normal.hpp"
#include "Perlin.h"
#include "fractalnoise.h"



void Terrain2::createGroups()
{
	Groups.clear();
	std::vector<Vertex> newVert = std::vector<Vertex>();
	for (int i = 0; i < this->Vertices.size(); i++)
	{				
		if (i % terrainSize == 0 && i != 0)
		{
			Groups.push_back(newVert);
			newVert.clear();
		}		
		newVert.push_back(this->Vertices[i]);		
	}
}

/*std::vector<Vertex>*/ void Terrain2::generateVertices(glm::vec3 pPos) {
	glm::vec3 Position = pPos;
	worldPosition = pPos;
	std::vector<Vertex> newVertices;
	for (int i = 0; i < terrainSize; i++)
	{
		float tileSize = 1; //Changes size of single tile
		for (int j = 0; j < terrainSize; j++)
		{
			newVertices.push_back(Vertex(POSITION(Position) 
				+ POSITION(i * tileSize,0, j * tileSize), NORMAL(0, 0, 0)));
		}
	}
	this->Vertices = newVertices;
}

void Terrain2::generateIndices() {
	std::vector<GLuint> indices;
	//Calculates the indices 
	for (int i = 0; i < terrainSize - 1; i++)
	{
		for (int j = 0; j < terrainSize - 1; j++)
		{
			indices.push_back(j + terrainSize * i);
			indices.push_back(j + terrainSize + terrainSize * i);
			indices.push_back(j + terrainSize + 1 + terrainSize * i);
	
			indices.push_back(j + terrainSize + 1 + terrainSize * i);
			indices.push_back(j + terrainSize * i);
			indices.push_back(j + 1 + terrainSize * i);	
		}
	}
	this->Indices = indices;
}
Mesh* Terrain2::generateMesh() {
	return new Mesh(Vertices, Indices);	
}

void Terrain2::updateMesh(Mesh* pterrainMesh) {
//	terrainGeneration->updateVertices(Vertices);
}

void Terrain2::Noise()
{ 
	float average = 0;
	//PerlinNoise noise2 = PerlinNoise(25, 5, 1.2, 0.55);

	FractalNoise perlin;
	int terrainActual = terrainSize;
	std::vector<int> index;
	
	for (int i = 0; i < pow(terrainActual - 1,2); i++)
	{	
		this->Vertices[i].setY(perlin.noise(this->Vertices[i].getX(),
			this->Vertices[i].getZ() + 0.451, 0));	
	}    
	average = average / pow(terrainActual, 2);	
}

void Terrain2::centreTerrain(std::vector<Vertex>* pVertices)
{
	int terrainActual = terrainSize;
	for (int i = 0; i < pVertices->size(); i++)
	{		
		pVertices[0][i].setX(pVertices[0][i].getX() - terrainActual / 2);
		pVertices[0][i].setZ(pVertices[0][i].getZ() - terrainActual / 2);
	}
}

void Terrain2::generateNormals(std::vector<Vertex>& Vertices, std::vector<GLuint> Indices)
{
	for (int i = 0; i < terrainSize - 1; i++)
	{
		for (int j = 0; j < terrainSize - 1; j++)
		{
			glm::vec3 calculatedNormal = glm::triangleNormal(this->Vertices[j + terrainSize * i].getXYZ(),
				this->Vertices[j + terrainSize * (i+1)].getXYZ(), this->Vertices[(j+1) + terrainSize * (i+1)].getXYZ());
			this->Vertices[j + terrainSize * i].addNormal(calculatedNormal);
			this->Vertices[j + terrainSize + terrainSize * i].addNormal(calculatedNormal);
			this->Vertices[j + terrainSize + 1 + terrainSize * i].addNormal(calculatedNormal);

			glm::vec3 calculatedNormal2 = glm::triangleNormal(this->Vertices[(j+1) + terrainSize * (i+1)].getXYZ(),
				this->Vertices[j + terrainSize * i].getXYZ(), this->Vertices[(j+1) + terrainSize * i].getXYZ());
			this->Vertices[j + terrainSize + 1 + terrainSize * i].addNormal(calculatedNormal2);
			this->Vertices[j + terrainSize * i].addNormal(calculatedNormal2);
			this->Vertices[j + 1 + terrainSize * i].addNormal(calculatedNormal2);
		}
	}
	
	// normalise normals
	for (Vertex& vert: this->Vertices)
		vert.setNormal(glm::normalize(vert.getNormal()));
	
}


std::vector<Vertex> Terrain2::generateWaterVertices(glm::vec3 pPos) {
	glm::vec3 Position = pPos;
	std::vector<Vertex> newVertices;
	newVertices.push_back(Vertex(POSITION(Position) + POSITION(0, 0, 0), NORMAL(0, 1, 0)));
	newVertices.push_back(Vertex(POSITION(Position) + POSITION(0, 0, terrainSize), NORMAL(0, 1, 0)));
	newVertices.push_back(Vertex(POSITION(Position) + POSITION(terrainSize, 0, terrainSize), NORMAL(0, 1, 0)));
	newVertices.push_back(Vertex(POSITION(Position) + POSITION(terrainSize, 0, 0), NORMAL(0, 1, 0)));
	return newVertices;
}
std::vector<GLuint> Terrain2::generateWaterIndices() {
	std::vector<GLuint> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);
	return indices;
}

int Terrain2::findTerrainPosition(float worldX, float worldZ)
{
	int indexPosition = worldX * terrainSize;
	return indexPosition;
}

float Terrain2::getHeightOfTerrain(float worldX, float worldZ)
{
	float terrainX = worldX;// -worldPosition.x;
	float terrainZ = worldZ;// -worldPosition.z;
	float gridSquareSize = terrainSize / (Groups.size() - 1);//(terrainSize * terrainSize) / (heights.size() - 1);
	int gridX = (int)glm::floor(terrainX / gridSquareSize);
	int gridZ = (int)glm::floor(terrainZ / gridSquareSize);

	if (gridX >= (Groups.size() - 1) || gridZ >= (Groups.size() - 1) || gridX < 0 || gridZ < 0) {
		return -10; //Collision height when not above terrain
	}
	
	//Vertex newVert = Groups[gridX][gridZ];
	float xCoord = fmod(terrainX,gridSquareSize) / gridSquareSize;
	float zCoord = fmod(terrainZ,gridSquareSize) / gridSquareSize;
	float answer;
	//Vertices[1]
	if (zCoord <= xCoord) {
		answer = barryCentric(glm::vec3(0, Groups[gridX][gridZ].Position.y, 0),
			glm::vec3(1, Groups[gridX][gridZ + 1].Position.y, 0),
			glm::vec3(1, Groups[gridX + 1][gridZ + 1].Position.y, 1), glm::vec2(xCoord, zCoord));
		//answer = barryCentric(glm::vec3(xCoord, Groups[gridX][gridZ].Position.y, zCoord), glm::vec3(xCoord, /*change*/Groups[gridX][gridZ + 1].Position.y, zCoord), glm::vec3(xCoord, Groups[gridX + 1][gridZ + 1].Position.y, zCoord), glm::vec2(xCoord, zCoord));
	}
	else
	{
		answer = barryCentric(glm::vec3(0, Groups[gridX][gridZ].Position.y, 0),
			glm::vec3(0, Groups[gridX + 1][gridZ].Position.y, 1),
			glm::vec3(1, Groups[gridX + 1][gridZ + 1].Position.y, 1), glm::vec2(xCoord, zCoord));
	}
	return answer;
}


float Terrain2::GetNoiseValue(float x, float z,float terrainActual)
{
	return 0;
}
float Terrain2::Clamp(float n) { return 0.5f * n + 0.5f; }


float Terrain2::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{	
	pos.y = 0;
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}


