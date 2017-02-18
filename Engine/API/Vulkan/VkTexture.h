#pragma once
#include "../Interfaces/ITexture.h"
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

		public:
			VkTexture(float width, float hight, int textureType, int flags);
			~VkTexture();

			virtual void Bind(int bindFlag) override;

		};
	}
}
