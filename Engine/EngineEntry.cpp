#include "RSIncludeVulkan.h"
#include "Debug/DebugMacros.h"
#include "API/RS_API.h"

RedSt4R::API::Renderer* renderer;
GLFWwindow* gameWindow;

void main()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	gameWindow = glfwCreateWindow(800, 600, "RedSt4R Vulkan Engine v0.1", nullptr, nullptr);

	renderer = RedSt4R::API::Renderer::CreateRenderer(gameWindow);
	renderer->InitRenderer();
	

	while (!glfwWindowShouldClose(gameWindow))
	{
		glfwPollEvents();

		renderer->Render();
	}


	glfwDestroyWindow(gameWindow);
	glfwTerminate();
}