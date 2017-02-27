#pragma once
#include "../Interfaces/Texture.h"
#include "../../RSIncludeVulkan.h"
#include "../../Debug/DebugMacros.h"

namespace RedSt4R
{
	namespace API
	{
		class VkTexture : public Texture
		{
		private:
			VkImage image;
			VkImageView imageView;
			VkFramebuffer frameBuffer;

		public:
			VkTexture(float width, float hight, int textureType, int flags);
			~VkTexture();

			virtual void Bind(int bindFlag) override;

		};
	}
}
