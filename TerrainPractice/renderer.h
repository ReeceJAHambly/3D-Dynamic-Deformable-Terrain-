#pragma once
#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "mesh.h"

#define PI 3.14159265358979f

class Mesh;

class Renderer {
private:
	static glm::mat4 projection;
	static float distance, near, fov;
	static bool wireframe;
	static GLuint currentShader;

	static int frameWidth, frameHeight;
public:
	static bool Initialize(int width, int height);
	static void Resize(int width, int height);

	static void Clear();
	static void Render(Mesh* mesh);
	static void RenderObject(Mesh* mesh, glm::mat4 object, glm::vec3 translation);
	static void Update(std::vector<Vertex> vertices,Mesh* mesh);

	static void SetShader(GLuint shader);
	static void SetVAO(GLuint vao);
	static void SetFrameBuffer(GLuint fbo);

	static void SetUniform(const char* name, float f);
	static void SetUniform(const char* name, int i);
	static void SetUniform(const char* name, float x, float y, float z);
	static void SetUniform(const char* name, glm::mat4 mat);

	static GLuint PassShaders(const char*, const char*);
	static GLuint CreateShader(const char*, const char*);

	static void SetWireframe(bool wire);

    static Mesh* CreateCube();
	static Mesh* CreateTerrain();
private:
	static void CompileShader(GLuint, const char*);
};