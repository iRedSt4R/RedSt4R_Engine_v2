#include "TriangleTest.h"


Vertex vertices[] = {
	Vertex(0.5f,  0.5f, 0.0f, 1.0f, 1.0f),  // Top Right
	Vertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),  // Bottom Right
	Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f),  // Bottom Left
	Vertex(-0.5f,  0.5f, 0.0f, 0.0f, 1.0f)   // Top Left 
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

	texture = RSTexture::CreateTexture("Assets/Textures/img_cheryl.jpg", true);

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
	texture->Bind(1);
	graphicsPipeline->Execute();
	renderer->EndRenderer();
}

void TriangleTest::Render()
{

}

void TriangleTest::End()
{

}
