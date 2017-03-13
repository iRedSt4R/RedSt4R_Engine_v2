//#include "RSIncludeVulkan.h"
#include "API/RSIncludeOpenGL.h"
#include "Config/RenderingConfig.h"
#include "Debug/DebugMacros.h"
#include "API/RS_API.h"
#include "API/Interfaces/RSVertexShader.h"
#include "API/Interfaces/RSPixelShader.h"

RedSt4R::API::RSRenderer* renderer;
GLFWwindow* gameWindow;
RedSt4R::API::RSVertexShader* vs;
RedSt4R::API::RSPixelShader* ps;

void main()
{

	RedSt4R::EngineConfig::SetWindowSize(800, 600);

	glfwInit();
	if (USE_VULKAN)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		gameWindow = glfwCreateWindow(RedSt4R::EngineConfig::GetWindowWidth(), RedSt4R::EngineConfig::GetWindowHeight(), "RedSt4R Vulkan Engine v0.1", nullptr, nullptr);

		
	}
	else
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		gameWindow = glfwCreateWindow(RedSt4R::EngineConfig::GetWindowWidth(), RedSt4R::EngineConfig::GetWindowHeight(), "RedSt4R Vulkan Engine v0.1", nullptr, nullptr);
	}
	
	renderer = RedSt4R::API::RSRenderer::CreateRenderer(gameWindow);
	renderer->InitRenderer();

	glewInit();
	vs = RedSt4R::API::RSVertexShader::CreateVertexShader("Engine/Shaders/GLSL/basicVS.glsl");
	ps = RedSt4R::API::RSPixelShader::CreatePixelShader("Engine/Shaders/GLSL/basicPS.glsl");

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