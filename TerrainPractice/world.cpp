#include <glm/gtc/matrix_transform.hpp>
#include <ctime>
#include <iostream>
#include "constants.h"
#include "world.h"
#include "renderer.h"
#include "window.h"
#include "camera.h"
#include "keyboard.h"
#include "mouse.h"
#include "mesh.h"
#include "player.h"
#include "Primitives.h"
#include <vector>

void World::Initialize() {
	//Terrain
    terrain.generateVertices(glm::vec3(0,0,0));	
	terrain.Noise();

	//Collision////////////////
	terrain.createGroups();
	///////////////////////

	terrain.generateIndices();
	terrain.generateNormals(terrain.Vertices, terrain.Indices);
	terrainMesh = terrain.generateMesh();

	//----------------------------------------------------------------------------------------------- 
	shader = Renderer::PassShaders("test.vert", "test.frag");
	time = 0;
	speed = 10.0f;
	fspeed = 0.100;
	Camera::SetPosition(terrain.terrainSize/2, 20.0f, terrain.terrainSize/2);
	Renderer::SetWireframe(false);	
	Window::GrabCursor(true);
	
}

void World::Update(float delta) {
	float last = 0;
	float initial = 0;
	float acceleration = -45.0;
	float displacement = 0;
	
	bool newObjectVelocity = false;	
	if (newObjectVelocity == true)
	{
	    last = 0;
		initial = 0;
		displacement = 0;
	}
	
	Mesh* newObject;

	std::vector<Vertex> newVerts;
	// Input resolving - Event
	while (Keyboard::NextEvent()) {
		KeyEvent e = Keyboard::Event;
		if (e.action == PRESS) {
			switch (e.key) {
			case KEY_TAB:
				wireframe = !wireframe;
				Renderer::SetWireframe(wireframe);
				break;
			case KEY_ESCAPE:
				Window::SetShouldClose(true);
				break;
			case KEY_T:				
				collidable.CentreCube();
				newObject = collidable.cubeMesh();
				//newObject->indexPos = cubeCount;
				collidable.mPosition = Camera::GetPosition();
				newObject->startPosition = Camera::GetPosition();
				newObject->time = 0;
				objectList.push_back(newObject);
				//cubeCount++;
				newObjectVelocity = true;
				newObject->Type = "Cube";
				break;
			case KEY_Y:
				collidable.CentreCuboid();
				newObject = collidable.cuboidMesh();
				collidable.mPosition = Camera::GetPosition();
				newObject->startPosition = Camera::GetPosition();
				newObject->time = 0;
				objectList.push_back(newObject);
				newObjectVelocity = true;
				newObject->Type = "Cuboid";
				break;
			case KEY_U:
				collidable.CreateSphere();
				collidable.CentreSphere();
				newObject = collidable.sphereMesh();
				collidable.mPosition = Camera::GetPosition();
				newObject->startPosition = Camera::GetPosition();
				newObject->time = 0;
				objectList.push_back(newObject);
				//collidable.sphereVerts.clear();
				newObjectVelocity = true;
				newObject->Type = "Sphere";
				/*vertLocX = glm::floor(newObject->startPosition.x);
				vertLocZ = glm::floor(newObject->startPosition.z);
				objectPositions.push_back(glm::vec3(vertLocX, 0, vertLocZ));*/
				break;
			case KEY_R:
				//cubeCount = 0;
				objectList.clear();
				break;
			case KEY_I:
				ObjectInfo();
				break;
			case KEY_0:
				CameraInfo();
				break;
			case KEY_C:
				createValue = createValue * -1;
				break;
			}
			
		}
	} 


	//Camera Collision
	float heightCamera = terrain.getHeightOfTerrain(Camera::GetPosition().x, Camera::GetPosition().z);
	if (Camera::GetPosition().y <= heightCamera + 0.5)
	{
		Camera::SetPosition(Camera::GetPosition().x, heightCamera + 0.5, Camera::GetPosition().z);
		int indexPos = (glm::floor(Camera::GetPosition().x) * terrain.terrainSize) + (glm::floor(Camera::GetPosition().z));
	}

	if (objectList.size() > 0)	///////Object Collision with Terrain
	{
		for (Mesh* mesh : objectList)
		{
			displacement = (initial * (mesh->time)) + (0.5 * acceleration * (mesh->time) * (mesh->time));
			mesh->velocity = { 0, displacement, 0 };

			if (mesh->velocity.y < -(mesh->startPosition.y 
				- terrain.getHeightOfTerrain(mesh->startPosition.x, mesh->startPosition.z) + 0.5))
			{
				glm::vec3 travelled = mesh->velocity;
				mesh->velocity = glm::vec3(0, -1 * (mesh->startPosition.y 
					- terrain.getHeightOfTerrain(mesh->startPosition.x, mesh->startPosition.z)), 0);
				mesh->hitCount++;
				if (mesh->hitCount == 1)
				{
					mesh->hit = true;
				}				
			}
			mesh->time += delta;	
		}


		for (int i = 0; i < objectList.size(); i++)
		{
			if (objectList[i]->hit == true && objectList[i]->Type == "Sphere")
			{
				int indexPos = (glm::floor(objectList[i]->startPosition.x) * terrain.terrainSize)
					+ (glm::floor(objectList[i]->startPosition.z));
				
				float startHeight = terrain.Vertices[indexPos].Position.y;
				terrain.Vertices[indexPos - 1].Position.y = terrain.Vertices[indexPos].Position.y + (createValue);
				terrain.Vertices[indexPos - 1].Position.x = terrain.Vertices[indexPos].Position.x;
				terrain.Vertices[indexPos - 1].Position.z = terrain.Vertices[indexPos].Position.z;

				terrain.Vertices[indexPos].Position.y = terrain.Vertices[indexPos].Position.y + createValue;
				terrain.Vertices[indexPos + 1].Position.y = terrain.Vertices[indexPos].Position.y + (createValue);
				terrain.Vertices[indexPos + 1].Position.x= terrain.Vertices[indexPos].Position.x;
				terrain.Vertices[indexPos + 1].Position.z = terrain.Vertices[indexPos].Position.z;
				terrain.Vertices[indexPos + 2].Position.y = terrain.Vertices[indexPos].Position.y + (createValue);
				terrain.Vertices[indexPos + 2].Position.x = terrain.Vertices[indexPos].Position.x;
				terrain.Vertices[indexPos + 2].Position.z = terrain.Vertices[indexPos].Position.z;

				terrain.Vertices[indexPos + terrain.terrainSize].Position.y = terrain.Vertices[indexPos].Position.y + (createValue);
				terrain.Vertices[indexPos + terrain.terrainSize - 1].Position.y = terrain.Vertices[indexPos].Position.y + (createValue);
				terrain.Vertices[indexPos + terrain.terrainSize - 1].Position.x = terrain.Vertices[indexPos + terrain.terrainSize].Position.x;
				terrain.Vertices[indexPos + terrain.terrainSize - 1].Position.z = terrain.Vertices[indexPos + terrain.terrainSize].Position.z;
				terrain.Vertices[indexPos + terrain.terrainSize + 1].Position.y = terrain.Vertices[indexPos].Position.y + (createValue);
				terrain.Vertices[indexPos + terrain.terrainSize + 1].Position.x = terrain.Vertices[indexPos + terrain.terrainSize].Position.x;
				terrain.Vertices[indexPos + terrain.terrainSize + 1].Position.z = terrain.Vertices[indexPos + terrain.terrainSize].Position.z;
				terrain.Vertices[indexPos + terrain.terrainSize + 2].Position.y = terrain.Vertices[indexPos].Position.y + (createValue);
				terrain.Vertices[indexPos + terrain.terrainSize + 2].Position.x = terrain.Vertices[indexPos + terrain.terrainSize].Position.x;
				terrain.Vertices[indexPos + terrain.terrainSize + 2].Position.z = terrain.Vertices[indexPos + terrain.terrainSize].Position.z;

				terrain.Vertices[indexPos + (terrain.terrainSize * 2)].Position.y = terrain.Vertices[indexPos].Position.y + (createValue);
				terrain.Vertices[indexPos + (terrain.terrainSize * 2) - 1].Position.y = terrain.Vertices[indexPos].Position.y + (createValue);
				terrain.Vertices[indexPos + (terrain.terrainSize * 2) - 1].Position.x = terrain.Vertices[indexPos + terrain.terrainSize].Position.x;
				terrain.Vertices[indexPos + (terrain.terrainSize * 2) - 1].Position.z = terrain.Vertices[indexPos + terrain.terrainSize].Position.z;

				terrain.Vertices[indexPos + (terrain.terrainSize * 2) + 1].Position.y = terrain.Vertices[indexPos].Position.y + (createValue);
				terrain.Vertices[indexPos + (terrain.terrainSize * 2) + 1].Position.x = terrain.Vertices[indexPos + terrain.terrainSize].Position.x;
				terrain.Vertices[indexPos + (terrain.terrainSize * 2) + 1].Position.z = terrain.Vertices[indexPos + terrain.terrainSize].Position.z;
				terrain.Vertices[indexPos + (terrain.terrainSize * 2) + 2].Position.y = terrain.Vertices[indexPos].Position.y + (createValue);
				terrain.Vertices[indexPos + (terrain.terrainSize * 2) + 2].Position.x = terrain.Vertices[indexPos + terrain.terrainSize].Position.x;
				terrain.Vertices[indexPos + (terrain.terrainSize * 2) + 2].Position.z = terrain.Vertices[indexPos + terrain.terrainSize].Position.z;

				
				terrain.Vertices[indexPos - (terrain.terrainSize)].Position.y = terrain.Vertices[indexPos].Position.y + (createValue * 0.5);
				terrain.Vertices[indexPos - (terrain.terrainSize) - 1].Position.y = terrain.Vertices[indexPos].Position.y + (createValue * 0.1);
				terrain.Vertices[indexPos - (terrain.terrainSize) - 1].Position.x = terrain.Vertices[indexPos + terrain.terrainSize].Position.x;
				terrain.Vertices[indexPos - (terrain.terrainSize) - 1].Position.z = terrain.Vertices[indexPos + terrain.terrainSize].Position.z;
				terrain.Vertices[indexPos - (terrain.terrainSize) + 1].Position.y = terrain.Vertices[indexPos].Position.y + (createValue * 0.5);
				terrain.Vertices[indexPos - (terrain.terrainSize) + 1].Position.x = terrain.Vertices[indexPos + terrain.terrainSize].Position.x;
				terrain.Vertices[indexPos - (terrain.terrainSize) + 1].Position.z = terrain.Vertices[indexPos + terrain.terrainSize].Position.z;
				terrain.Vertices[indexPos - (terrain.terrainSize) + 2].Position.y = terrain.Vertices[indexPos].Position.y + (createValue * 0.25);
				terrain.Vertices[indexPos - (terrain.terrainSize) + 2].Position.x = terrain.Vertices[indexPos + terrain.terrainSize].Position.x;
				terrain.Vertices[indexPos - (terrain.terrainSize) + 2].Position.z = terrain.Vertices[indexPos + terrain.terrainSize].Position.z;
			


				if ((startHeight + (terrain.Vertices[indexPos].Position.y - 1.5) ) < -2 && createValue == -1
					|| (startHeight + terrain.Vertices[indexPos].Position.y) > 5 && createValue == 1)
				{
					objectList[i]->hit = false;
				}
				Renderer::Update(terrain.Vertices, terrainMesh);
				terrain.createGroups();
			}
			if (objectList[i]->hit == true && objectList[i]->Type == "Cuboid")
			{
				int indexPos = (glm::floor(objectList[i]->startPosition.x) * terrain.terrainSize) + (glm::floor(objectList[i]->startPosition.z));
				float startHeight = terrain.Vertices[indexPos].Position.y;

				terrain.Vertices[indexPos - 1].Position.y = terrain.Vertices[indexPos - 1].Position.y + createValue; //Centre //Important
				terrain.Vertices[indexPos].Position.y = terrain.Vertices[indexPos].Position.y + createValue; //Centre //Important
				terrain.Vertices[indexPos + 1].Position.y = terrain.Vertices[indexPos + 1].Position.y + createValue; //Centre //Important
				terrain.Vertices[indexPos + 2].Position.y = terrain.Vertices[indexPos + 2].Position.y + createValue; //Centre //Important

				terrain.Vertices[indexPos + terrain.terrainSize - 1].Position.y = terrain.Vertices[indexPos + terrain.terrainSize - 1].Position.y + createValue; //Centre //Important
				terrain.Vertices[indexPos + terrain.terrainSize].Position.y = terrain.Vertices[indexPos + terrain.terrainSize].Position.y + createValue; //Centre //Important
				terrain.Vertices[indexPos + terrain.terrainSize + 1].Position.y = terrain.Vertices[indexPos + terrain.terrainSize + 1].Position.y + createValue; //Centre //Important
				terrain.Vertices[indexPos + terrain.terrainSize + 2].Position.y = terrain.Vertices[indexPos + terrain.terrainSize + 2].Position.y + createValue; //Centre //Important


				if ((startHeight + terrain.Vertices[indexPos].Position.y) < -2
					&& createValue == -1 || 
					(startHeight + terrain.Vertices[indexPos].Position.y) > 5 && createValue == 1)
				{
					objectList[i]->hit = false;
				}
				Renderer::Update(terrain.Vertices, terrainMesh);
				terrain.createGroups();
			}
			if (objectList[i]->hit == true && objectList[i]->Type == "Cube")
			{
				int indexPos = (glm::floor(objectList[i]->startPosition.x) * terrain.terrainSize) + (glm::floor(objectList[i]->startPosition.z));
				float startHeight = terrain.Vertices[indexPos].Position.y;

				terrain.Vertices[indexPos].Position.y = terrain.Vertices[indexPos].Position.y + createValue; //Centre //Important

				terrain.Vertices[indexPos + 1].Position.y = terrain.Vertices[indexPos + 1].Position.y + createValue; //Right
				terrain.Vertices[indexPos + 1].Position.x = terrain.Vertices[indexPos + 2].Position.x;
				terrain.Vertices[indexPos + 1].Position.z = terrain.Vertices[indexPos + 2].Position.z;

				terrain.Vertices[indexPos - 1].Position.y = terrain.Vertices[indexPos - 1].Position.y + createValue; // Left
				terrain.Vertices[indexPos - 1].Position.x = terrain.Vertices[indexPos - 2].Position.x;
				terrain.Vertices[indexPos - 1].Position.z = terrain.Vertices[indexPos - 2].Position.z;

				terrain.Vertices[indexPos + terrain.terrainSize + 1].Position.y
					= terrain.Vertices[indexPos + terrain.terrainSize + 1].Position.y + createValue; // Bottom Right
				terrain.Vertices[indexPos + terrain.terrainSize + 1].Position.x
					= terrain.Vertices[indexPos + terrain.terrainSize + 2].Position.x;
				terrain.Vertices[indexPos + terrain.terrainSize + 1].Position.z
					= terrain.Vertices[indexPos + terrain.terrainSize + 2].Position.z;

				terrain.Vertices[indexPos + terrain.terrainSize].Position.y =
					terrain.Vertices[indexPos + terrain.terrainSize].Position.y + createValue; // Bottom 

				terrain.Vertices[indexPos + (terrain.terrainSize - 1)].Position.y =
					terrain.Vertices[indexPos + (terrain.terrainSize - 1)].Position.y + createValue; // Bottom Left
				terrain.Vertices[indexPos + (terrain.terrainSize - 1)].Position.x =
					terrain.Vertices[indexPos + (terrain.terrainSize - 2)].Position.x;
				terrain.Vertices[indexPos + (terrain.terrainSize - 1)].Position.z = terrain.Vertices[indexPos + (terrain.terrainSize - 2)].Position.z;

				terrain.Vertices[indexPos - (terrain.terrainSize + 1)].Position.y =
					terrain.Vertices[indexPos - (terrain.terrainSize + 1)].Position.y + createValue; // Top Left
				terrain.Vertices[indexPos - (terrain.terrainSize + 1)].Position.x =
					terrain.Vertices[indexPos - (terrain.terrainSize + 2)].Position.x;
				terrain.Vertices[indexPos - (terrain.terrainSize + 1)].Position.z = terrain.Vertices[indexPos - (terrain.terrainSize + 2)].Position.z;

				terrain.Vertices[indexPos - terrain.terrainSize].Position.y = terrain.Vertices[indexPos - terrain.terrainSize].Position.y + createValue; // Top 

				terrain.Vertices[indexPos - (terrain.terrainSize - 1)].Position.y = terrain.Vertices[indexPos - (terrain.terrainSize - 1)].Position.y + createValue; // Top Right
				terrain.Vertices[indexPos - (terrain.terrainSize - 1)].Position.x = terrain.Vertices[indexPos - (terrain.terrainSize - 2)].Position.x;
				terrain.Vertices[indexPos - (terrain.terrainSize - 1)].Position.z = terrain.Vertices[indexPos - (terrain.terrainSize - 2)].Position.z;


				if ((startHeight + terrain.Vertices[indexPos].Position.y) < -2 && createValue == -1
					|| (startHeight + terrain.Vertices[indexPos].Position.y) > 5 && createValue == 1)
				{
					objectList[i]->hit = false;
				}
				Renderer::Update(terrain.Vertices, terrainMesh);
				terrain.createGroups();
			}
			
		}
	}

	
	while (Mouse::NextEvent()) {
		MouseEvent e = Mouse::Event;
		switch (e.type) {
		case CURSOR:
			Player::RotateCamera(e.dx, e.dy);
			break;
		}
	}

	// Input resolving - Pressed
	float cameraSpeed = speed * delta;

	if (Keyboard::IsKeyDown(KEY_W)) Camera::Move(Camera::GetFront() * cameraSpeed);
	if (Keyboard::IsKeyDown(KEY_S)) Camera::Move(-Camera::GetFront() * cameraSpeed);
	if (Keyboard::IsKeyDown(KEY_A)) Camera::Move(-Camera::GetRight() * cameraSpeed);
	if (Keyboard::IsKeyDown(KEY_D)) Camera::Move(Camera::GetRight() * cameraSpeed);
	if (Keyboard::IsKeyDown(KEY_SPACE)) Camera::Move(glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed);
	if (Keyboard::IsKeyDown(KEY_LEFT_SHIFT)) Camera::Move(glm::vec3(0.0f, -1.0f, 0.0f) * cameraSpeed);
	
	
	time += delta; //* speed;
}

void World::Render() {
	Renderer::Clear();
	Renderer::SetShader(shader);	
	Renderer::SetUniform("Color", 1.0f, 0.0f, 0.0f);

	//Terrain	
	Renderer::Render(terrainMesh);

	//Objects 	
	for (int i = 0; i < objectList.size(); i++)
	{
		Renderer::RenderObject(objectList[i],
			glm::mat4(1), objectList[i]->velocity);
	}

	Renderer::SetShader(0);
}

void World::Release() {
	//delete ObjectMesh;
	//delete terrainMesh;

}



void World::ObjectInfo() {
	std::cout << "\nAll Object Info" << std::endl;
	if (objectList.size() > 0)	
	{
		for (int i = 0; i < objectList.size(); i++)
		{
			std::cout << "\nID: " << i << " Type: " << objectList[i]->Type << " X: " <<  glm::floor(objectList[i]->startPosition.x) << " , Z:" << glm::floor(objectList[i]->startPosition.z) << std::endl;
		}
	}
	else
	{
		std::cout << "\nNo Objects Present" << std::endl;
	}
}


void World::CameraInfo() {
	std::cout << "\nAll Camera Info" << std::endl;
	std::cout << "\nCamera Position X: " << Camera::GetX() << " Y: " << Camera::GetY() << " Z: " << Camera::GetZ() << std::endl;
}

World World::instance = World();

World* World::GetInstance() { return &instance; }

World::World() {}
