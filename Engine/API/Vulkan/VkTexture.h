#pragma once
#include "../Interfaces/RSTexture.h"
#include "../../RSIncludeVulkan.h"
#include "../../Debug/DebugMacros.h"

namespace RedSt4R
{
	namespace API
	{
		class VkTexture : public RSTexture
		{
		private:
			VkImage image;
			VkImageView imageView;
			VkFramebuffer frameBuffer;

		public:
			VkTexture(char* texturePath, bool bGenerateMipMaps);
			~VkTexture();

			virtual void LoadTextureFromFile(char* texturePath) override;
			virtual void Bind(int bindPoint) override;
			virtual void GenerateMipMaps() override;
			virtual void ClearTexture() override;
			virtual void ClearTexture(glm::vec3 clearColor) override;

		};
	}
}
