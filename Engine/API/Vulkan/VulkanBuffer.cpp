#include "VulkanBuffer.h"

VertexColor vertices[] = { // Top Right
	VertexColor(0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f),  // Bottom Right
	VertexColor(0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f),  // Bottom Left
	VertexColor(-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f)   // Top Left 
};

RedSt4R::API::VulkanVertexBuffer::VulkanVertexBuffer(int size, Vertex* pVertexData)
{

}

RedSt4R::API::VulkanVertexBuffer::~VulkanVertexBuffer()
{

}

RedSt4R::API::VulkanVertexBuffer::VulkanVertexBuffer(VulkanDevice* pDevice, VertexColor* vertexData)
{
	VkResult r;

	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(VertexColor);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
	attributeDescriptions[0].offset = sizeof(glm::vec3);

	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[1].offset = sizeof(glm::vec3);

	//Buffer
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = sizeof(vertices);
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	r = vkCreateBuffer(pDevice->GetVkDevice(), &bufferInfo, nullptr, &m_VertexBuffer);
	if(r != VK_SUCCESS) RS_ERROR("Failed Creating ")

}
