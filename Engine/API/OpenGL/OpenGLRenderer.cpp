#include "OpenGLRenderer.h"

RedSt4R::API::OpenGLRenderer::OpenGLRenderer(GLFWwindow* pWindow)
{
	glfwMakeContextCurrent(pWindow);
	glViewport(0, 0, RedSt4R::EngineConfig::GetWindowWidth(), RedSt4R::EngineConfig::GetWindowHeight());

	m_Window = pWindow;
}

RedSt4R::API::OpenGLRenderer::~OpenGLRenderer()
{

}

void RedSt4R::API::OpenGLRenderer::InitRenderer()
{
	
}

void RedSt4R::API::OpenGLRenderer::BeginRenderer()
{
	glClearColor(0.4f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void RedSt4R::API::OpenGLRenderer::Update()
{
	
}

void RedSt4R::API::OpenGLRenderer::Render()
{
	
}

void RedSt4R::API::OpenGLRenderer::EndRenderer()
{
	//glfwSwapBuffers(m_Window);
}

void RedSt4R::API::OpenGLRenderer::ShutDownRenderer()
{
	
}
