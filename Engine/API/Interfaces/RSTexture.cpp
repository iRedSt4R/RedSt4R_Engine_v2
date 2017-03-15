#include "RSTexture.h"

#include "../Vulkan/VkTexture.h"
#include "../OpenGL/OpenGLTexture.h"

namespace RedSt4R 
{ 
	namespace API 
	{
		RSTexture* RSTexture::CreateTexture(char* texturePath, bool bGenerateMipMaps)
		{
			if (USE_VULKAN) return new VkTexture(texturePath, bGenerateMipMaps);
			if (USE_OPENGL) return new OpenGLTexture(texturePath, bGenerateMipMaps);
		}
	} 
}
