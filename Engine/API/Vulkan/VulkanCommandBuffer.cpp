#include "VulkanCommandBuffer.h"
#include "VkBase.h"
#include "VulkanRenderer.h"


void RedSt4R::API::VulkanCommandBuffer::rsCmdBindVertexBuffers(RSVertexBuffer* pVertexBuffers, uint32_t firstBinding, uint32_t bindingCount, int offsets)
{
	VkDeviceSize devSize = { 0 };
	VulkanVertexBuffer* vulkanVertexBuffer= (VulkanVertexBuffer*)pVertexBuffers;

	vkCmdBindVertexBuffers(m_CommandBuffer, firstBinding, bindingCount, vulkanVertexBuffer->GetVkBuffer(), &devSize);
}

void RedSt4R::API::VulkanCommandBuffer::rsCmdBindPipeline(RSGraphicsPipeline* pGraphicsPipeline, EPipelineBindPoint bindPoint)
{
	VulkanGraphicsPipeline* graphicsPip = (VulkanGraphicsPipeline*)pGraphicsPipeline;

	if (bindPoint == EPipelineBindPoint::Graphics)
	{
		vkCmdBindPipeline(m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPip->GetVkPipeline());
	}
}

void RedSt4R::API::VulkanCommandBuffer::rsCmdBeginRenderPass(RSGraphicsPipeline* pGraphicsPipeline, uint32_t frameBufferIndex)
{
	VulkanGraphicsPipeline* graphicsPip = (VulkanGraphicsPipeline*)pGraphicsPipeline;

	vkCmdBeginRenderPass(m_CommandBuffer, &graphicsPip->GetVkRenderPassBeginInfo(frameBufferIndex), VK_SUBPASS_CONTENTS_INLINE);
}

void RedSt4R::API::VulkanCommandBuffer::rsCmdDraw(uint32_t vertexCount, uint32_t firstVertex)
{
	vkCmdDraw(m_CommandBuffer, vertexCount, 1, firstVertex, 0);
}

RedSt4R::API::VulkanCommandBuffer::VulkanCommandBuffer(float flags)
{
	VkResult r;

	VkCommandPoolCreateInfo cpcf = {};
	cpcf.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cpcf.pNext = nullptr;
	cpcf.queueFamilyIndex = VulkanRenderer::queueFamilyIndexWithGB;
	cpcf.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	r = vkCreateCommandPool(VulkanRenderer::m_Device, &cpcf, nullptr, &m_CommandPool);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating Command Pool!")
	else RS_LOG("Successfully Created Command Pool")

	VkCommandBufferAllocateInfo cbAllocateInfo = {};
	cbAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cbAllocateInfo.pNext = nullptr;
	cbAllocateInfo.commandBufferCount = 1;
	cbAllocateInfo.commandPool = m_CommandPool;
	cbAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	r = vkAllocateCommandBuffers(VulkanRenderer::m_Device, &cbAllocateInfo, &m_CommandBuffer);
	if (r != VK_SUCCESS) RS_ERROR("Failed Allocating Command Buffers!");

	cbBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cbBeginInfo.pNext = nullptr;
	cbBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_CommandBuffer;
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

void RedSt4R::API::VulkanCommandBuffer::SubmitToQueue(void* pQueue)
{
	VkResult r;
	r = vkQueueSubmit((VkQueue)pQueue, 1, &submitInfo, VulkanRenderer::m_Fence);
	if (r != VK_SUCCESS) RS_ERROR("Failed Submitting to Queue!");
}

void RedSt4R::API::VulkanCommandBuffer::Reset()
{
	
}
