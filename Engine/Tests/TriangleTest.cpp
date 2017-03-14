#include "TriangleTest.h"


VertexBase vertices[] = {
	VertexBase(0.5f,  0.5f, 0.0f, 0.7f, 0.7f, 0.7f),  // Top Right
	VertexBase(0.5f, -0.5f, 0.0f, 0.7f, 0.7f, 0.7f),  // Bottom Right
	VertexBase(-0.5f, -0.5f, 0.0f, 0.7f, 0.7f, 0.7f),  // Bottom Left
	VertexBase(-0.5f,  0.5f, 0.0f, 0.7f, 0.7f, 0.7f)   // Top Left 
};
uint32_t indices[] = {  // Note that we start from 0!
	0, 1, 3,   // First Triangle
	1, 2, 3    // Second Triangle
};

TriangleTest::TriangleTest(GLFWwindow* pWindow)
	:window(pWindow)
{
	renderer = RSRenderer::CreateRenderer(pWindow);
	renderer->InitRenderer();

	vb = RSVertexBuffer::CreateVertexBuffer(sizeof(vertices), vertices);
	ib = RSIndexBuffer::CreateIndexBuffer(sizeof(indices), indices);

	vs = RSVertexShader::CreateVertexShader("Engine/Shaders/GLSL/basicVS.glsl");
	ps = RSPixelShader::CreatePixelShader("Engine/Shaders/GLSL/basicPS.glsl");

	graphicsPipeline = RSGraphicsPipeline::CreateGraphicsPipeline(vb, vs, ps, ib);
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
