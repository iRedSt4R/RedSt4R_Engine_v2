#pragma once
#include "../Interfaces/RSShader.h"
#include "../../RSIncludeVulkan.h"
#include "../../Debug/DebugMacros.h"
#include "VulkanRenderer.h"
#include <string.h>
#include <vector>
#include <fstream>


namespace RedSt4R
{
	namespace API
	{
		class VulkanShader : public RSShader
		{
		private:
			std::vector<char> vertexShaderCode;
			std::vector<char> pixelShaderCode;

			VkShaderModule vertexShaderModule;
			VkShaderModule pixelShaderModule;

		public:
			std::vector<VkPipelineShaderStageCreateInfo> shaderStages;

		public:
			VulkanShader(char* vertexShaderPath, char* pixelShaderPath);
			~VulkanShader();

			std::string ReadFileToString(char* filePath);
			std::vector<char> ReadFileToString2(char* filePath);

		};
	}
}