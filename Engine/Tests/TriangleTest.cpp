#include "TriangleTest.h"


//VertexColor vertices[] = { // Top Right
	//VertexColor(0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f),  // Bottom Right
	//VertexColor(0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f),  // Bottom Left
	//VertexColor(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f)   // Top Left 
//};

VertexColor verticess[] = { // Top Right
	VertexColor(0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f),  // Bottom Right
	VertexColor(0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f),  // Bottom Left
	VertexColor(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f)   // Top Left 
};

TriangleTest::TriangleTest(Window* pWindow)
	:window(pWindow)
{

	//rsDevice = RSDevice::CreateDevice(EDeviceType::BestGPU, true);

	renderer = RSRenderer::CreateRenderer(rsDevice, pWindow);
	renderer->InitRenderer();

	rsDevice = VulkanRenderer::GetRSDevice();

	vertexBuffer = RSVertexBuffer::CreateVertexBuffer(rsDevice, verticess);
	m_commandbuf = RSCommandBuffer::CreateCommandBuffer(1);
	m_commandbuf2 = RSCommandBuffer::CreateCommandBuffer(1);
	shader = RSShader::CreateShader("Shaders/vert.spv", "Shaders/frag.spv");
	RS_DESC_GRAPHICSPIPELINE gpDesc;
	gpDesc = *(VulkanRenderer::Get_RS_DESC_GRAPHICSPIPELINE());
	gpDesc.vertexBuffer = vertexBuffer;

	graphicsPipeline = RSGraphicsPipeline::CreateGraphicsPipeline(shader, &gpDesc);

	m_commandbuf->Begin();
		m_commandbuf->rsCmdBeginRenderPass(graphicsPipeline, 0);
		m_commandbuf->rsCmdBindPipeline(graphicsPipeline, EPipelineBindPoint::Graphics);
		m_commandbuf->rsCmdBindVertexBuffers(vertexBuffer, 0, 1, 0);
		m_commandbuf->rsCmdDraw(3, 0);
	m_commandbuf->End();

	m_commandbuf2->Begin();
		m_commandbuf2->rsCmdBeginRenderPass(graphicsPipeline, 1);
		m_commandbuf2->rsCmdBindPipeline(graphicsPipeline, EPipelineBindPoint::Graphics);
		m_commandbuf2->rsCmdBindVertexBuffers(vertexBuffer, 0, 1, 0);
		m_commandbuf2->rsCmdDraw(3, 0);
	m_commandbuf2->End();

	/*
	ib = RSIndexBuffer::CreateIndexBuffer(sizeof(indices), indices);

	vs = RSVertexShader::CreateVertexShader("Engine/Shaders/GLSL/basicVS.glsl");
	ps = RSPixelShader::CreatePixelShader("Engine/Shaders/GLSL/basicPS.glsl");

	texture = RSTexture::CreateTexture("Assets/Textures/img_cheryl.jpg", true);

	graphicsPipeline = RSGraphicsPipeline::CreateGraphicsPipeline(vb, vs, ps, ib);
	*/
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
	renderer->Render(m_commandbuf, m_commandbuf2);
	//graphicsPipeline->Execute();
	renderer->EndRenderer();
}

void TriangleTest::Render()
{

}


void TriangleTest::End()
{

}
