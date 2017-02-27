#include "RSIncludeVulkan.h"
#include "Config/RenderingConfig.h"
#include "Debug/DebugMacros.h"
#include "API/RS_API.h"

RedSt4R::API::Renderer* renderer;
GLFWwindow* gameWindow;

void main()
{

	RedSt4R::EngineConfig::SetWindowSize(800, 600);
	



	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	gameWindow = glfwCreateWindow(RedSt4R::EngineConfig::GetWindowWidth(), RedSt4R::EngineConfig::GetWindowHeight(), "RedSt4R Vulkan Engine v0.1", nullptr, nullptr);

	renderer = RedSt4R::API::Renderer::CreateRenderer(gameWindow);
	renderer->InitRenderer();
	

	while (!glfwWindowShouldClose(gameWindow))
	{
		glfwPollEvents();

		renderer->BeginRenderer();
		renderer->Render();
		renderer->EndRenderer();
	}


	glfwDestroyWindow(gameWindow);
	glfwTerminate();
}