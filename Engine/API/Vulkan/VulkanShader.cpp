#include "VulkanShader.h"

RedSt4R::API::VulkanShader::VulkanShader(char* vertexShaderPath, char* pixelShaderPath)
{
	vertexShaderCode = ReadFileToString2(vertexShaderPath);
	pixelShaderCode = ReadFileToString2(pixelShaderPath);

	//Vertex Shader Module
	{
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = vertexShaderCode.size();

		std::vector<uint32_t> codeAligned(vertexShaderCode.size() / sizeof(uint32_t) + 1);
		memcpy(codeAligned.data(), vertexShaderCode.data(), vertexShaderCode.size());
		createInfo.pCode = codeAligned.data();

		vkCreateShaderModule(VulkanRenderer::m_Device, &createInfo, nullptr, &vertexShaderModule);
	}

	//Pixel Shader Module
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = pixelShaderCode.size();

	std::vector<uint32_t> codeAligned(pixelShaderCode.size() / sizeof(uint32_t) + 1);
	memcpy(codeAligned.data(), pixelShaderCode.data(), pixelShaderCode.size());
	createInfo.pCode = codeAligned.data();

	auto p = vkCreateShaderModule(VulkanRenderer::m_Device, &createInfo, nullptr, &pixelShaderModule);



	VkPipelineShaderStageCreateInfo vertexShaderStageInfo = {};
	vertexShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertexShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertexShaderStageInfo.module = vertexShaderModule;
	vertexShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo pixelShaderStageInfo = {};
	pixelShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	pixelShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	pixelShaderStageInfo.module = pixelShaderModule;
	pixelShaderStageInfo.pName = "main";

	shaderStages.push_back(vertexShaderStageInfo);
	shaderStages.push_back(pixelShaderStageInfo);
}

RedSt4R::API::VulkanShader::~VulkanShader()
{

}

std::string RedSt4R::API::VulkanShader::ReadFileToString(char* filePath)
{
	FILE* fp = fopen(filePath, "r");
	fseek(fp, 0, SEEK_END);
	long fileLenght = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* contents = new char[fileLenght + 1];
	for (int i = 0; i < fileLenght; i++)
	{
		contents[i] = 0;
	}
	fread(contents, 1, fileLenght, fp);
	contents[fileLenght + 1] = '\0';
	fclose(fp);

	std::string result(contents);
	return result;
}

std::vector<char> RedSt4R::API::VulkanShader::ReadFileToString2(char * filePath)
{
	std::ifstream file(filePath, std::ios::ate | std::ios::binary);

	if (!file.is_open()) 
	{
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}
