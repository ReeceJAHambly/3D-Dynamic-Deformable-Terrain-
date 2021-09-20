#include "Primitives.h"
#include <glm/gtc/noise.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "glm/gtx/normal.hpp"
#include "glm/gtx/transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "world.h"



std::vector<Vertex> Primitives::createSphereVerts()  {
	std::vector<Vertex> sphereVerts;
	for (int i = 0; i <= stackCount; i++) {
		stackAngle = glm::pi<float>() / 2 - i * stackStep;
		xy = radius * glm::cos(stackAngle);
		z = radius * sin(stackAngle);
		for (int j = 0; j <= sectorCount; j++)
		{
			Vertex newVert;
			sectorAngle = j * sectorStep;
			x = xy * cos(sectorAngle);
			y = xy * sin(sectorAngle);
			newVert.Position.x = x;
			newVert.Position.y = y;
			newVert.Position.z = z;

			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			newVert.Normal.x = nx;
			newVert.Normal.y = ny;
			newVert.Normal.z = nz;
			sphereVerts.push_back(newVert);
		}
	}
	return sphereVerts;
}

std::vector<GLuint> Primitives::createSphereIndices() {
	int k1, k2;
	std::vector<GLuint> indices;// lineIndices;
	for (int i = 0; i < stackCount; i++)
	{
		k1 = i * (sectorCount + 1);
		k2 = k1 + sectorCount + 1;
		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
	return indices;
}

void Primitives::CreateSphere()
{
	sphereVerts = createSphereVerts();
	sphereIndices = createSphereIndices();
}

void Primitives::CentreCube()
{
	std::vector<Vertex> newVerts;
	for (Vertex verts : v)
	{
		verts.Position += glm::vec3(Camera::GetPosition().x, Camera::GetPosition().y, Camera::GetPosition().z);
		newVerts.push_back(verts);
	}
	cubeVerts = newVerts;
}

void Primitives::CentreCuboid()
{
	std::vector<Vertex> newVerts;
	for (Vertex verts : cuboidV)
	{
		verts.Position += glm::vec3(Camera::GetPosition().x, Camera::GetPosition().y, Camera::GetPosition().z);
		newVerts.push_back(verts);
	}
	cuboidVerts = newVerts;
}

void Primitives::CentreSphere()
{
	std::vector<Vertex> newVerts;
	for (Vertex verts : sphereVerts)
	{
		verts.Position += (glm::vec3(Camera::GetPosition().x , Camera::GetPosition().y, Camera::GetPosition().z));
		newVerts.push_back(verts);
	}
	sphereVerts = newVerts;
}


glm::vec3 Primitives::GetPosition()
{
	return mPosition;
}


Mesh* Primitives::cubeMesh()
{
	return new Mesh(cubeVerts, cubeIndices);
}

Mesh* Primitives::cuboidMesh()
{
	return new Mesh(cuboidVerts, cuboidIndices);
}

Mesh* Primitives::sphereMesh()
{
	return new Mesh(sphereVerts, sphereIndices);
}



