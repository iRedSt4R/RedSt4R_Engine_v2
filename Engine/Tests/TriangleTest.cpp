#include "TriangleTest.h"

VertexBase vertices[] =
{
	VertexBase(-0.5f, -0.5f, 0.0f, 0.25f, 0.25f, 0.25f),
	VertexBase(0.5f, -0.5f, 0.0f, 0.2f, 0.9f, 0.5f),
	VertexBase(0.0f,  0.5f, 0.0f, 0.2f, 0.2f, 0.75f)
};

TriangleTest::TriangleTest(GLFWwindow* pWindow)
	:window(pWindow)
{
	renderer = RSRenderer::CreateRenderer(pWindow);
	renderer->InitRenderer();

	vb = RSVertexBuffer::CreateVertexBuffer(sizeof(vertices), vertices);
	vs = RSVertexShader::CreateVertexShader("Engine/Shaders/GLSL/basicVS.glsl");
	ps = RSPixelShader::CreatePixelShader("Engine/Shaders/GLSL/basicPS.glsl");

	graphicsPipeline = RSGraphicsPipeline::CreateGraphicsPipeline(vb, vs, ps);
}

TriangleTest::~TriangleTest()
{

}

void TriangleTest::Prepare()
{

}

void TriangleTest::Update()
{
	renderer->BeginRenderer();
	renderer->Render();
	graphicsPipeline->Execute();
	renderer->EndRenderer();
}

void TriangleTest::Render()
{

}

void TriangleTest::End()
{

}
