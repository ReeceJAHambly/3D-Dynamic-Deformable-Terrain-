#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#define POSITION glm::vec3
#define NORMAL glm::vec3
#define LIGHTING glm::vec3

struct Vertex {
	POSITION Position;
	NORMAL Normal;
	LIGHTING Lighting = glm::vec3(0, 1, 0);

	Vertex() {};
	Vertex(POSITION pos) : Position(pos) {}
	Vertex(POSITION pos, NORMAL norm) : Position(pos), Normal(norm) {}
	float getY();
	void setY(float Value);
	float getX();
	void setX(float Value);
	float getZ();
	void setZ(float Value);
	glm::vec3 getXYZ();

	float normalGetY();
	void normalSetY(float Value);
	float normalGetX();
	void normalSetX(float Value);
	float normalGetZ();
	void normalSetZ(float Value);

	glm::vec3 getNormal();


	void addNormal(glm::vec3 newNormal);
	void setNormal(glm::vec3 newNormal);

};

class Mesh {
public:
	Mesh();
	glm::mat4 identity = glm::mat4(1);
	float time;
	glm::vec3 velocity;
	glm::vec3 startPosition;
	bool hit = false; 
	bool deformable = true;
	int indexPos;
	int hitCount = 0;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	std::string Type; 
	void setY(float Ypos);
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	void updateVertices(std::vector<Vertex> vertices, std::vector<GLuint> indices);
private:
	void SetUp();
};