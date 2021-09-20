#include "mesh.h"
#include <iostream>
#include <glm/glm.hpp>
#include "camera.h"

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) {
	this->vertices = vertices;
	this->indices = indices;

	SetUp();
}

void Mesh::setY(float Ypos)
{
	for (Vertex vert : vertices)
	{
		vert.Position.y += Ypos;
	}
}

float Vertex::getY() {
	return Position.y;
}

void Vertex::setY(float pValue) {
	 Position.y += pValue;
}

float Vertex::getX() {
	return Position.x;
}

void Vertex::setX(float pValue) {
	Position.x = pValue;
}

float Vertex::getZ()
{
	return Position.z;
}

void Vertex::setZ(float Value)
{
	Position.z = Value;
}

glm::vec3 Vertex::getXYZ()
{
	glm::vec3 xyz = glm::vec3(Position.x, Position.y, Position.z);
	return xyz;
}

float Vertex::normalGetY()
{
	return Normal.y;
}

void Vertex::normalSetY(float Value)
{
	Normal.y = Value;
}

float Vertex::normalGetX()
{
	return Normal.x;
}

void Vertex::normalSetX(float Value)
{
	Normal.x = Value;
}

float Vertex::normalGetZ()
{
	return Normal.z;
}

void Vertex::normalSetZ(float Value)
{
	Normal.z = Value;
}

glm::vec3 Vertex::getNormal()
{
	return Normal;
}

void Vertex::addNormal(glm::vec3 newNormal)
{
	Normal.x =+ newNormal.x;
	Normal.y = +newNormal.y;
	Normal.z = +newNormal.z;
}

void Vertex::setNormal(glm::vec3 newNormal)
{
	Normal = newNormal;
}


void Mesh::updateVertices(std::vector<Vertex> pVertices, std::vector<GLuint> indices)//changed this
{
	this->vertices = pVertices;
	this->indices = indices;
	//SetUp();
}

void Mesh::SetUp() { //this?
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_DYNAMIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// Vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	glBindVertexArray(0);
}