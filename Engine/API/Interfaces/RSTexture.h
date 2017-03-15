#pragma once
#include "../RSIncludeOpenGL.h"

namespace RedSt4R
{
	namespace API
	{
		class RSTexture
		{
		public:
			virtual void LoadTextureFromFile(char* texturePath) = 0;
			virtual void Bind(int bindPoint) =  0;
			virtual void GenerateMipMaps() = 0;
			virtual void ClearTexture() = 0;
			virtual void ClearTexture(glm::vec3 clearColor) = 0;

			static RSTexture* CreateTexture(char* texturePath, bool bGenerateMipMaps);
		};
	}
}