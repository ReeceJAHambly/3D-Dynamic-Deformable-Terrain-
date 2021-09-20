#include "Main.h"
#include "main.h"
#include "renderer.h"
#include "window.h"
#include "scene.h"
#include "world.h"
#include "keyboard.h"
#include "mouse.h"

float Main::lastTime = 0;
float Main::delta = 0;
Scene* Main::currentScene = nullptr;

bool Main::Initialize()
{
	int width = 1920; //1000
	int height = 1080; //800
	if (!Window::Initialize(width, height)) {
		return false;
	}
	if (!Renderer::Initialize(width, height)) {
		return false;
	}

	Keyboard::Initialize();
	Mouse::Initialize();

	SetUpScenes();
	lastTime = (float)glfwGetTime();
}

void Main::Run()
{
	while (!Window::ShouldClose()) {
		UpdateDelta();
		Window::Poll();

		currentScene->Update(delta);
		currentScene->Render();

		Window::SwapBuffers();
	}
}

void Main::Exit()
{
	Window::Dispose();
}

float Main::GetDelta()
{
	return delta;
}

void Main::SetScene(Scene * scene)
{
	currentScene = scene;
}

void Main::UpdateDelta()
{
	float current = (float)glfwGetTime();
	delta = current - lastTime;
	lastTime = current;
}

void Main::SetUpScenes()
{
	World::GetInstance()->Initialize();

	currentScene = World::GetInstance();

	
}

int main() {
	if (!Main::Initialize()) {
		Main::Exit();
		return -1;
	}
	Main::Run();
	Main::Exit();
	return 0;
}