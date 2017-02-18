#include "VulkanCommandBuffer.h"
#include "VkBase.h"
#include "VkRenderer.h"

RedSt4R::API::VulkanCommandBuffer::VulkanCommandBuffer(float flags)
{
	VkResult r;

	VkCommandPoolCreateInfo cpcf = {};
	cpcf.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cpcf.pNext = nullptr;
	cpcf.queueFamilyIndex = VkRenderer::queueFamilyIndexWithGB;
	cpcf.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	r = vkCreateCommandPool(VkBase::device, &cpcf, nullptr, &m_CommandPool);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating Command Pool!")
	else RS_LOG("Successfully Created Command Pool")

		VkCommandBufferAllocateInfo cbAllocateInfo = {};
	cbAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cbAllocateInfo.pNext = nullptr;
	cbAllocateInfo.commandBufferCount = 1;
	cbAllocateInfo.commandPool = m_CommandPool;
	cbAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	r = vkAllocateCommandBuffers(VkBase::device, &cbAllocateInfo, &m_CommandBuffer);
	if (r != VK_SUCCESS) RS_ERROR("Failed Allocating Command Buffers!");

	cbBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cbBeginInfo.pNext = nullptr;
}

RedSt4R::API::VulkanCommandBuffer::~VulkanCommandBuffer()
{

}

void RedSt4R::API::VulkanCommandBuffer::Begin()
{
	vkBeginCommandBuffer(m_CommandBuffer, &cbBeginInfo);
}

void RedSt4R::API::VulkanCommandBuffer::End()
{
	vkEndCommandBuffer(m_CommandBuffer);
}

void RedSt4R::API::VulkanCommandBuffer::Reset()
{
	
}