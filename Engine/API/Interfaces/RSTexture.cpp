#include "RSTexture.h"

#include "../Vulkan/VkTexture.h"

namespace RedSt4R 
{ 
	namespace API 
	{
		RSTexture* RSTexture::CreateTexture(float width, float hight, int textureType, int flags)
		{
			if (USE_VULKAN) return new VkTexture(width, hight, textureType, flags);
		}
	} 
}
