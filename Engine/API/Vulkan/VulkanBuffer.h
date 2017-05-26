#pragma once
#include "../../RSIncludeVulkan.h"
#include "../Interfaces/RSVertexBuffer.h"
#include "../../Core/Vertex/VertexTypes.h"
#include "VulkanDevice.h"
#include <vector>
#include <array>



namespace RedSt4R
{
	namespace API
	{
		class VulkanDevice;
		class VulkanVertexBuffer : public RSVertexBuffer
		{
			VulkanDevice* vulkanDevice;

			VkBuffer m_VertexBuffer = VK_NULL_HANDLE;
			VkDeviceMemory m_DeviceMemory;

			VkVertexInputBindingDescription bindingDescription = {};
			std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};


		public:
			VulkanVertexBuffer(int size, Vertex* pVertexData);
			VulkanVertexBuffer(VulkanDevice* pDevice, VertexColor* vertexData);
			~VulkanVertexBuffer();

		private:

		public:
			__inline VkVertexInputBindingDescription GetVkVertexInputBindDesc() { return bindingDescription; }
			__inline std::array<VkVertexInputAttributeDescription, 2> GetVkVertexInputAttDesc() { return attributeDescriptions; }
			__inline VkBuffer* GetVkBuffer() { return &m_VertexBuffer; }
		};
	}
}