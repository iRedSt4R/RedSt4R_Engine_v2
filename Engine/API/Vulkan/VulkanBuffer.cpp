#include "VulkanBuffer.h"

uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDeviceMemoryProperties memProperties)
{
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}
}

RedSt4R::API::VulkanVertexBuffer::VulkanVertexBuffer(int size, Vertex* pVertexData)
{

}

RedSt4R::API::VulkanVertexBuffer::~VulkanVertexBuffer()
{
	vkDestroyBuffer(vulkanDevice->GetVkDevice(), m_VertexBuffer, nullptr);
	vkFreeMemory(vulkanDevice->GetVkDevice(), m_DeviceMemory, nullptr);
}

RedSt4R::API::VulkanVertexBuffer::VulkanVertexBuffer(VulkanDevice* pDevice, VertexColor* vertexData)
	:vulkanDevice(pDevice)
{
	VkResult r;

	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(VertexColor);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[0].offset = 0;

	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[1].offset = sizeof(glm::vec3);

	//Buffer
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = sizeof(VertexColor) * 3;
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	r = vkCreateBuffer(pDevice->GetVkDevice(), &bufferInfo, nullptr, &m_VertexBuffer);
	if(r != VK_SUCCESS) RS_ERROR("Failed Creating ")

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(pDevice->GetVkDevice(), m_VertexBuffer, &memRequirements);

	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties((pDevice->GetVkPhysicalDevices().data()[0]), &memProperties);
	
	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, memProperties);

	r = vkAllocateMemory(pDevice->GetVkDevice(), &allocInfo, nullptr, &m_DeviceMemory);
	if (r != VK_SUCCESS) RS_ERROR("Failed Allocating Memory for Vertex Buffer");

	vkBindBufferMemory(pDevice->GetVkDevice(), m_VertexBuffer, m_DeviceMemory, 0);

	void* data;
	vkMapMemory(pDevice->GetVkDevice(), m_DeviceMemory, 0, bufferInfo.size, 0, &data);
	memcpy(data, vertexData, (size_t)sizeof(VertexColor) * 3);
	vkUnmapMemory(pDevice->GetVkDevice(), m_DeviceMemory);

}